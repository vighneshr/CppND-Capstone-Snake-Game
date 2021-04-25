#include "bonuspoints.h"
#include <thread>
#include <iostream>

template <typename T>
T MessageQueue<T>::receive(){
    std::unique_lock<std::mutex> uLock(_mutex);
    _cond.wait(uLock, [this] { return !_queue.empty(); });
    T msg = std::move(_queue.back());
    _queue.pop_back();
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg){
    std::lock_guard<std::mutex> uLock(_mutex);
    _queue.push_back(std::move(msg));
    _cond.notify_one();
}

session Bonuspoints::get_Current_Session() {
    return _current_session;
}

Bonuspoints::Bonuspoints() {
  _current_session = session::normal_session;
  bonus_consumed = false;
  _points = new MessageQueue<msgs>;
}

Bonuspoints::~Bonuspoints() {
  if (_points != nullptr) {
    delete _points;
    _points = nullptr;
  }
}

void Bonuspoints::resetThread(){
  while(true){
    auto rcvd_msg = _points->receive();
    std::cout << "msg received: " << rcvd_msg << "\n";
    if (msgs::end_game == rcvd_msg){
      destroy_bonus = true;
      break;
    } else if (msgs::bonus == rcvd_msg) {
      bonus_consumed = true;
    } else {
      bonus_consumed = false;
    }
  }
  return;
}

bool Bonuspoints::getBonusConsumed(){
  return bonus_consumed;
}

void Bonuspoints::informSuccess(){
  std::cout << "informing \n";
  _points->send(msgs::bonus);
  return;
}

void Bonuspoints::informEndGame(){
  std::cout << "informingEndGame \n";
  _points->send(msgs::end_game);
  return;
}

void Bonuspoints::startSession(){
    std::random_device generator;
    std::mt19937 random_time(generator());
    // Specify the interval to be between 10 to 12 sec
    std::uniform_int_distribution<> interval{10000, 12000};

    std::cout << "running" << std::endl;
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        double cycleDuration = interval(random_time);
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (destroy_bonus) {
          break;
        } else if (timeSinceLastUpdate >= cycleDuration || getBonusConsumed()) {
            //Toggles the session
          	if(_current_session == bonus_session)
            {
              _current_session = normal_session;
            }
          	else
            {
              _current_session = bonus_session;
            }
          _points->send(msgs::no_bonus);
          // reset stop watch for next cycle
          lastUpdate = std::chrono::system_clock::now();
        }
    } // eof simulation loop
    return;
}
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

Bonuspoints::Bonuspoints():random_time(generator()) {
  _current_session = session::normal_session;
  bonus_consumed = false;
}

void Bonuspoints::resetThread(){
  while(true){
    auto msg = _points.receive();
    std::cout << "msg received: " << msg << "\n";
    if (awards::chocolate == msg) {
      bonus_consumed = true;
    } else {
      bonus_consumed = false;
    }
  }
}

bool Bonuspoints::getBonusConsumed(){
  return bonus_consumed;
}

void Bonuspoints::informSuccess(){
  std::cout << "informing \n";
  _points.send(awards::chocolate);
  return;
}

void Bonuspoints::startSession(){
    std::cout << "running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::chrono::time_point<std::chrono::system_clock> lastUpdate;

    lastUpdate = std::chrono::system_clock::now();
    while (true)
    {
        double cycleDuration = interval(random_time);
        // sleep at every iteration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        // compute time difference to stop watch
        long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
        if (timeSinceLastUpdate >= cycleDuration || getBonusConsumed())
        {
            //Toggles the session
          	if(_current_session == bonus_session)
            {
              _current_session = normal_session;
            }
          	else
            {
              _current_session = bonus_session;
            }

          _points.send(awards::no_chocolate);
          // reset stop watch for next cycle
          lastUpdate = std::chrono::system_clock::now();
        }
    } // eof simulation loop
    return;
}
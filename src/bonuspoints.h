#ifndef BONUSPOINTS_H
#define BONUSPOINTS_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include <random>

/*
class bonuspoints is used to reward player if snake consumes special food within certain time limit
This class is started as thread in parallel to game thread.
Special food appears on game screen and 

*/

enum awards{
    ignore = -1,
    no_chocolate = 0,
    chocolate,
    dark_chocolate // extra point when food is placed in difficult location
};

//session is to indicate if bonus score is active or not
enum session{
  bonus_session = 0,
  normal_session
};

/* Messanger between game thread and this thread */
template <class T>
class MessageQueue
{
public:
  void send(T &&msg);
  T receive();

private:
  std::deque<T> _queue;
  std::condition_variable _cond;
  std::mutex _mutex;
};

class Bonuspoints {
public:
  Bonuspoints();
  ~Bonuspoints(){};

  session get_Current_Session();
  void resetThread();
  void startSession();
  void informSuccess();
  bool getBonusConsumed();
private:
    std::random_device generator;
    std::mt19937 random_time;
    // Specify the interval to be between 10 to 12 sec
    std::uniform_int_distribution<> interval{10000, 12000};
    session _current_session;
    MessageQueue<awards> _points;
    bool bonus_consumed;

    std::condition_variable _condition;
    std::mutex _mutex;
};
#endif
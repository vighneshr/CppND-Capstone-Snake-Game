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

enum msgs{
    ignore = -1,
    no_bonus = 0,
    bonus,
    end_game // extra point when food is placed in difficult location
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
  ~Bonuspoints();

  session get_Current_Session();
  void resetThread();
  void startSession();
  void informSuccess();
  void informEndGame();
  bool getBonusConsumed();
private:
    session _current_session;
    MessageQueue<msgs> *_points;
    bool bonus_consumed;
    bool destroy_bonus;
};
#endif
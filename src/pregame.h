#ifndef PRE_GAME_H
#define PRE_GAME_H

#include <dirent.h>
#include <sys/types.h>
#include <thread>
#include <future>
#include "SDL.h"

class PreGame {
public:
  PreGame(){};
  ~PreGame(){};

public:
  bool getUserInput() {
    int availableLevels = getAvailableLevels();
    std::cout << "Hello welcome to snake game!!\n";
    std::cout << "Available levels: " << availableLevels << std::endl;
    std::thread t(PreGame::readConsoleInput, std::move(prms));
    t.detach();
    auto status = ftr.wait_for(std::chrono::seconds(5));
    if (status == std::future_status::ready) // result is ready
    {
      level = ftr.get();
      std::cout << "Great!! loading level: " << getLevel() << std::endl;
    } else {
      std::cout << "\nOops! Timeout waiting for user input! Restart again!!\n";
      std::cout << "Well! To play this game move your fingers faster!!\n";
      return false;
    }
    return true;
  }
  virtual int &getLevel() {
    return level;
  }
  virtual bool setup() = 0;

  int getAvailableLevels() {
    DIR *dir;
    struct dirent *d;
    int count = 0;
    dir = opendir("../board/");
    if (dir) {
      while ((d = readdir(dir)) != NULL) {
        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
          continue;

        count++;
      }
    }
    closedir(dir);
    return count;
  }
private:
  std::promise<int> prms;
  std::future<int> ftr = prms.get_future();
  static void readConsoleInput(std::promise<int> &&prms) {
    int level;
    std::cout << "Enter the level you want to play: ";
    std::cin >> level;
    prms.set_value(level);
  }
  static int level;
};

#endif
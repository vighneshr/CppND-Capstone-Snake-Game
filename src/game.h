#ifndef GAME_H
#define GAME_H

#include <random>
#include <iostream>
#include <algorithm>
#include "pregame.h"
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "bonuspoints.h"
#include "layout.h"

class Renderer;

class Portable {
public:
  Portable(){};
  Portable(int len) {
    //Portable() {
    std::cout << "CREATING instance of Portable :" << this << std::endl;
    length = len;
    point = new SDL_Point[len];
  }
  ~Portable() {
    std::cout << "DELETING instance of Portable :" << this << std::endl;
    delete[] point;
  };
  Portable(const Portable &source) {
    std::cout << "COPYING " << &source << " instance to instance: " << this << std::endl;
    length = source.length;
    point = new SDL_Point[length];
    *point = *source.point;
  }

  Portable &operator= (const Portable &source) {
    std::cout << "ASSIGNING " << &source << " instance to instance: " << this << std::endl;
    delete[] point;
    point = new SDL_Point[source.length];
    *point = *source.point;
    length = source.length;
    return *this;
  }

  Portable(Portable &&source) {
    std::cout << "MOVING " << &source << " instance to instance: " << this << std::endl;
    length = source.length;
    point = source.point;
    source.length = 0;
    source.point = nullptr;
  }

  Portable &operator= (Portable &&source) {
    std::cout << "MOVING ASSIGNMENT" << &source << " instance to instance: " << this << std::endl;
    delete[] point;
    length = source.length;
    point = source.point;
    source.length = 0;
    source.point = nullptr;
    return *this;
  }
  friend class Renderer;
  friend class Game;
private:
  SDL_Point *point;
  int length;
};

class Game : public PreGame {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  bool Load();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  bool LayoutCell(int x, int y);
  int GetScore() const;
  int GetSize() const;
  ~Game();

 private:
  Snake snake;
  Layout layout;
  SDL_Point food;
  SDL_Point bonus_food;
  std::vector<SDL_Point> gamelayout;
  std::unique_ptr<Bonuspoints> bonuspoints;
  std::vector<std::thread> bonus_threads;
  Portable arr;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  void PlaceFood();
  void PlaceBonusFood();
  void Update();
  void Construct();

  bool setup() {
    return getUserInput();
  }
};

#endif
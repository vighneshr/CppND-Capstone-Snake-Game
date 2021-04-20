#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "bonuspoints.h"
#include "layout.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int level = 0);
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
  //std::vector<SDL_Point> layout;
  std::vector<SDL_Point> gamelayout;
  //std::unique_ptr<Bonuspoints> bonuspoints;
  Bonuspoints *bonuspoints;
  std::vector<std::thread> bonus_threads;
  int game_level{0};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceBonusFood();
  void Update();
  void SetLayout();
};

#endif
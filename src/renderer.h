#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "game.h"
class Portable;
class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &bonus_food) ;
  void UpdateWindowTitle(int score, int fps);
  void SetLayout(SDL_Point in);
  void populateLayout(Portable &Arr);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  std::vector<SDL_Point> layout;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
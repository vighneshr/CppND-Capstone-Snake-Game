#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>

int PreGame::level;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)){
  PlaceFood();
  PlaceBonusFood();
  bonuspoints = std::make_unique<Bonuspoints>();
}

bool Game::Load() {
  // pregame section
  if (setup() == true) {
    return layout.setup();
  }
  return false;
}

void Game::Construct() {
    std::vector<SDL_Point> temp;
    layout.Construct(temp);
    int l = temp.size();
    int count = 0;
    // Demostrate rule of 5
    Portable p1(l);
    Portable *p = &p1;
    for (const SDL_Point i : temp) {
      p->point[count].x = i.x;
      p->point[count].y = i.y;
      count++;
      gamelayout.emplace_back(i);
    }
    arr = std::move(*p);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  // game layout loaded and start now
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // demo of rule of 5
  Construct();
  renderer.populateLayout(arr);

  snake.UpdateLayout(gamelayout);

  bonus_threads.emplace_back(std::move(std::thread{&Bonuspoints::startSession, bonuspoints.get()}));
  bonus_threads.emplace_back(std::move(std::thread{&Bonuspoints::resetThread, bonuspoints.get()}));

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    if (session::bonus_session == bonuspoints->get_Current_Session() && !bonuspoints->getBonusConsumed()) {
      renderer.Render(snake, food, bonus_food);
    } else {
      renderer.Render(snake, food);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  bonuspoints->informEndGame();
}

bool Game::LayoutCell(int x, int y) {
  for (auto const &item : gamelayout) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !LayoutCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceBonusFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !LayoutCell(x, y)) {
      bonus_food.x = x;
      bonus_food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check and place bonus food
  if (session::bonus_session == bonuspoints->get_Current_Session() && !bonuspoints->getBonusConsumed()) {
    int bonus_new_x = static_cast<int>(snake.head_x);
    int bonus_new_y = static_cast<int>(snake.head_y);
    if (bonus_food.x == bonus_new_x &&
        bonus_food.y == bonus_new_y) {
        //update score based on bonus won
        score = score + 5;
        PlaceBonusFood();
        std::cout << "placing bonus food\n" ;
        bonuspoints->informSuccess();
        snake.GrowBody();
        snake.speed += 0.02;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

Game::~Game(){
  std::for_each(bonus_threads.begin(), bonus_threads.end(), [](std::thread &t) {
        t.join();
  });
}
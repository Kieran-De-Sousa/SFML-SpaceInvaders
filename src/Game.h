
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool initGame();
  bool initText();
  bool initGameObject();
  bool initGameVariables();
  void updateGameVariables();
  void updatePlayerShip(float dt);
  void updateAlienShip(float dt);
  void alienMovementStandard(int alien_num, float dt);
  void alienMovementGravity(int alien_num, float dt);
  void alienMovementQuadratic(int alien_num, float dt);
  void alienMovementSine(int alien_num, float dt);
  void collisionDetection(int alien_num);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

 private:

  //Screens//
  sf::RenderWindow& window;
  bool start_screen = true;
  bool pause_screen = false;
  bool game_screen = false;
  bool win_screen = false;
  bool lose_screen = false;

  //Modes//
  enum gameMode
  {standard,
  sine,
  gravity,
  quadratic};
  enum gameMode mode_selected = gameMode::standard;

  //Text//
  sf::Font font;
  sf::Text start_text;
  sf::Text score_text;
  sf::Text win_text;
  sf::Text lose_text;
  sf::Text play_again_text;
  sf::Text mode_swap_text;
  sf::Text mode_selected_text;
  sf::Text pause_text;

  //Game objects//
  GameObject player_ship;
  sf::Texture player_ship_texture;

  static const int num_lasers = 20;
  GameObject* player_laser = nullptr;
  sf::Texture player_laser_texture;
  int active_lasers = 0;

  static const int enemy_gridsize_x = 10;
  static const int enemy_gridsize_y = 5;
  static const int enemy_array = enemy_gridsize_x * enemy_gridsize_y;
  GameObject* alien_ship = nullptr;
  sf::Texture alien_black_texture;
  sf::Texture alien_blue_texture;
  sf::Texture alien_green_texture;
  sf::Texture alien_red_texture;
  int alien_ship_speed = 30;
  float alien_gravity;

  bool player_movement = false;
  bool player_move_left = false;
  bool player_move_right = false;

  //Additional variables//
  int destroyed_ships = 0;
  int player_score = 0;

};

#endif // SPACEINVADERS_GAME_H

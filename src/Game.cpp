
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
  if (alien_ship != nullptr)
  {
    delete[] alien_ship;
  }
  if (player_laser != nullptr)
  {
    delete[] player_laser;
  }
}

bool Game::initGame()
{
  initText();
  initGameVariables();
  initGameObject();

  return true;
}

bool Game::initText()
{
  //Checks for fonts loading correctly
  if (!font.loadFromFile("Data/Fonts/open-sans/OpenSans-Bold.ttf"))
  {
    std::cout << "Font could not be loaded!\n";
  }
  start_text.setString("Press enter to start the game");
  start_text.setFont(font);
  start_text.setCharacterSize(30);
  start_text.setFillColor(sf::Color::White);
  start_text.setPosition(window.getSize().x/2 - start_text.getGlobalBounds().width/2,
                         window.getSize().y/2 - start_text.getGlobalBounds().height/2);

  score_text.setString("Score: " + std::to_string(player_score));
  score_text.setFont(font);
  score_text.setCharacterSize(15);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(window.getSize().x/5 - start_text.getGlobalBounds().width/2,
                         window.getSize().y/50 - start_text.getGlobalBounds().height/2);

  win_text.setString("You defeated the nefarious aliens and saved humanity!");
  win_text.setFont(font);
  win_text.setCharacterSize(30);
  win_text.setFillColor(sf::Color::Green);
  win_text.setPosition(window.getSize().x/2 - win_text.getGlobalBounds().width/2,
                         window.getSize().y/2 - win_text.getGlobalBounds().height/2);

  lose_text.setString("Blast it! You failed in your mission to protect us all!");
  lose_text.setFont(font);
  lose_text.setCharacterSize(30);
  lose_text.setFillColor(sf::Color::Red);
  lose_text.setPosition(window.getSize().x/2 - lose_text.getGlobalBounds().width/2,
                       window.getSize().y/2 - lose_text.getGlobalBounds().height/2);

  play_again_text.setString("Press 'P' to play again");
  play_again_text.setFont(font);
  play_again_text.setCharacterSize(30);
  play_again_text.setFillColor(sf::Color::White);
  play_again_text.setPosition(window.getSize().x/2 - play_again_text.getGlobalBounds().width/2,
                        window.getSize().y/1.5 - play_again_text.getGlobalBounds().height/2);

  mode_swap_text.setString("Game modes: \n"
                           "'Z' Standard\n'X' Quadratic\n'C' Curve\n'V' Gravity");
  mode_swap_text.setFont(font);
  mode_swap_text.setCharacterSize(25);
  mode_swap_text.setFillColor(sf::Color(255, 255, 255, 255));
  mode_swap_text.setPosition(
    window.getSize().x/2 - mode_swap_text.getGlobalBounds().width/2,
    window.getSize().y/1.5 - mode_swap_text.getGlobalBounds().height/2);

  mode_selected_text.setString("Mode selected: ----------------");
  mode_selected_text.setFont(font);
  mode_selected_text.setCharacterSize(15);
  mode_selected_text.setFillColor(sf::Color(255, 255, 255, 255));
  mode_selected_text.setPosition(
    window.getSize().x - mode_selected_text.getGlobalBounds().width,0);

  pause_text.setString("PAUSED");
  pause_text.setFont(font);
  pause_text.setCharacterSize(40);
  pause_text.setFillColor(sf::Color::White);
  pause_text.setPosition(window.getSize().x/2 - pause_text.getGlobalBounds().width/2,
                        window.getSize().y/2 - pause_text.getGlobalBounds().height/2);

  return true;
}

bool Game::initGameObject()
{
  //Player Ship
  player_ship.initialiseSprite(player_ship_texture, "Data/Images/SpaceShooterRedux/PNG/playerShip1_blue.png");
  player_ship.getSprite()->setPosition(window.getSize().x/2 - player_ship.getSprite()->getGlobalBounds().width/2,
                                       window.getSize().y/1.040 - player_ship.getSprite()->getGlobalBounds().width/2);

  //Alien Ships
  alien_ship = new GameObject[enemy_array];
  for (int i = 0; i < enemy_gridsize_x; i++)
  {
    for (int j = 0; j < enemy_gridsize_y; j++)
    {
      if (j == 0)
      {
        alien_ship[i*enemy_gridsize_y+j].initialiseSprite(alien_black_texture, "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack3.png");
      }
      else if (j == 1)
      {
        alien_ship[i*enemy_gridsize_y+j].initialiseSprite(alien_blue_texture, "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlue3.png");
      }
      else if (j == 2)
      {
        alien_ship[i*enemy_gridsize_y+j].initialiseSprite(alien_green_texture, "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyGreen3.png");
      }
      else if (j >= 3)
      {
        alien_ship[i*enemy_gridsize_y+j].initialiseSprite(alien_red_texture, "Data/Images/SpaceShooterRedux/PNG/Enemies/enemyRed3.png");
      }
      alien_ship[i*enemy_gridsize_y+j].setVisibility(true);
      alien_ship[i*enemy_gridsize_y+j].setReverse(false);
      alien_ship[i*enemy_gridsize_y+j].setSpeed(alien_ship_speed);
      alien_ship[i*enemy_gridsize_y+j].setDirection({10, 10});
      alien_ship[i*enemy_gridsize_y+j].getSprite()->setScale(0.625f, 0.625f);
      alien_ship[i*enemy_gridsize_y+j].getSprite()->setPosition(alien_ship[i*enemy_gridsize_y+j].getSprite()->getGlobalBounds().width +
                                                            (alien_ship[i*enemy_gridsize_y+j].getSprite()->getGlobalBounds().width*i*1.5),
                                                          alien_ship[i*enemy_gridsize_y+j].getSprite()->getGlobalBounds().height +
                                                            (alien_ship[i*enemy_gridsize_y+j].getSprite()->getGlobalBounds().height*j*1.5));
    }
  }

  //Lasers
  player_laser = new GameObject[num_lasers];
  for (int i = 0; i < num_lasers; i++)
  {
    player_laser[i].initialiseSprite(player_laser_texture, "Data/Images/SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
    player_laser[i].getSprite()->setScale(0.6f, 0.6f);
    player_laser[i].setVisibility(false);
    player_laser[i].setDirection({0, -500});
    player_laser[i].getSprite()->setPosition(window.getSize().x + player_laser[i].getSprite()->getGlobalBounds().width,
                                             window.getSize().y + player_laser[i].getSprite()->getGlobalBounds().height);
  }

  return true;
}

bool Game::initGameVariables()
{
  //Initialises/Resets game variables
  alien_ship_speed = 30;
  destroyed_ships = 0;
  player_score = 0;
  active_lasers = 0;

  //Initialises/Resets game screens
  //NOTE: Now I know how to use enums, for my next piece of coding work im 10000%
  //NOT going to use a buncha bools to keep track of game states when enums make
  //readability way easier and way easier to debug
  bool start_screen = true;
  bool pause_screen = false;
  bool game_screen = false;
  bool win_screen = false;
  bool lose_screen = false;

  //Initialises/Resets game mode
  enum gameMode mode_selected = gameMode::standard;

  return true;
}

void Game::updateGameVariables()
{
  //Game win condition
  if (destroyed_ships == enemy_array)
  {
    game_screen = false;
    win_screen = true;
  }
  //Error handling if counter for lasers goes beyond specified laser limit
  if (active_lasers == num_lasers)
  {
    active_lasers = 0;
  }
  //Ensures player score cannot be a negative integer
  if (player_score < 0)
  {
    player_score = 0;
  }
  //Updating mode displayed text strings
  if (mode_selected == gameMode::standard)
  {
    mode_selected_text.setString("Mode selected: Standard");
  }
  else if (mode_selected == gameMode::sine)
  {
    mode_selected_text.setString("Mode selected: Sine");
  }
  else if (mode_selected == gameMode::quadratic)
  {
    mode_selected_text.setString("Mode selected: Quadratic");
  }
  else if (mode_selected == gameMode::gravity)
  {
    mode_selected_text.setString("Mode selected: Gravity");
  }
  //Updates player score
  score_text.setString("Score: " + std::to_string(player_score));
}

void Game::updatePlayerShip(float dt)
{
  if (!start_screen)
  {
    //Ensures actions for ship cannot happen unless the game screen is active
    if (game_screen && !pause_screen)
    {
      //Player movement//
      if (player_movement)
      {
        if (player_move_left)
        {
          player_ship.setDirection({-500, 0});
          player_ship.getSprite()->move(player_ship.getDirection().x * dt,
                                        player_ship.getDirection().y * dt);
        }
        else if (player_move_right)
        {
          player_ship.setDirection({500, 0});
          player_ship.getSprite()->move(player_ship.getDirection().x * dt,
                                        player_ship.getDirection().y * dt);
        }
      }

      //Lasers//
      for (int i = 0; i < num_lasers; i++)
      {
        if (player_laser[i].getVisibility())
        {
          player_laser[i].getSprite()->move(player_laser[i].getDirection().x * dt,
                                            player_laser[i].getDirection().y * dt);
        }
        //Checks for laser going off screen ceiling
        if (player_laser[i].getSprite()->getPosition().y <
            (0 - player_laser[i].getSprite()->getGlobalBounds().height))
        {
          player_laser[i].setVisibility(false);
          player_laser[i].getSprite()->setPosition(window.getSize().x + player_laser[i].getSprite()->getGlobalBounds().width,
                                                   window.getSize().y + player_laser[i].getSprite()->getGlobalBounds().height);
          player_laser[i].getSprite()->move(0, 0);
          player_score -= 1;
          active_lasers -= 1;
          if (active_lasers < 0)
          {
            active_lasers = 0;
          }
        }
      }
    }
  }
}

void Game::updateAlienShip(float dt)
{
  if (!start_screen)
  {
    //Ensures actions for ship cannot happen unless the game screen is active (and
    //not in the pause screen)
    if (game_screen && !pause_screen)
    {
      for (int i = 0; i < enemy_array; i++)
      {
        //Checks only visible ships
        if (alien_ship[i].getVisibility())
        {
          if (mode_selected == gameMode::standard)
          {
            alienMovementStandard(i, dt);
          }
          else if (mode_selected == gameMode::gravity)
          {
            alienMovementGravity(i, dt);
          }
          else if (mode_selected == gameMode::quadratic)
          {
            alienMovementQuadratic(i, dt);
          }
          else if (mode_selected == gameMode::sine)
          {
            alienMovementSine(i, dt);
          }
          //Runs collision detection function every update
          collisionDetection(i);
        }
      }
    }
  }
}

void Game::alienMovementStandard(int i, float dt)
{
  // Checks which direction ships are moving in
  if (!alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(alien_ship->getSpeed() * dt, 0);
  }
  else if (alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(-alien_ship->getSpeed() * dt, 0);
  }

  // Checks for ships colliding with borders of window, if so moves them down
  if (alien_ship[i].getSprite()->getPosition().x +
      alien_ship[i].getSprite()->getGlobalBounds().width > window.getSize().x)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].getSprite()->setPosition(
        alien_ship[j].getSprite()->getPosition().x - 1,
        alien_ship[j].getSprite()->getPosition().y + (alien_ship[j].getSprite()->getGlobalBounds().height / 2));
      alien_ship[j].setReverse(true);
    }
  }
  if (alien_ship[i].getSprite()->getPosition().x < 0)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].getSprite()->setPosition(
        alien_ship[j].getSprite()->getPosition().x +
          alien_ship[j].getSprite()->getGlobalBounds().width / 2,
        alien_ship[j].getSprite()->getPosition().y +
          (alien_ship[j].getSprite()->getGlobalBounds().height / 2));
      alien_ship[j].setReverse(false);
    }
  }
}

void Game::alienMovementGravity(int i, float dt)
{
  alien_gravity = (alien_ship[i].getSprite()->getPosition().y / window.getSize().y) * 5;
  // Checks which direction ships are moving in
  if (!alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(alien_ship[i].getDirection().x * dt, alien_ship[i].getDirection().y * alien_gravity * dt);
  }
  else if (alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(-alien_ship[i].getDirection().x * dt, alien_ship[i].getDirection().y * alien_gravity * dt);
  }

  if (alien_ship[i].getSprite()->getPosition().x +
      alien_ship[i].getSprite()->getGlobalBounds().width > window.getSize().x)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].setReverse(true);
    }
  }
  if (alien_ship[i].getSprite()->getPosition().x < 0)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].setReverse(false);
      alien_ship[j].getSprite()->setPosition(alien_ship[j].getSprite()->getPosition().x + alien_ship[j].getSprite()->getGlobalBounds().width / 2,
                                                alien_ship[j].getSprite()->getPosition().y);
    }
  }
}

void Game::alienMovementQuadratic(int i, float dt)
{
  alien_ship[i].setDirection({5, 5});
  if (!alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(alien_ship[i].getDirection().x * dt, pow(alien_ship[i].getDirection().x, 2) * dt);
  }
  else if (alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(-alien_ship[i].getDirection().x * dt, pow(alien_ship[i].getDirection().x, 2) * dt);
  }

  if (alien_ship[i].getSprite()->getPosition().x +
      alien_ship[i].getSprite()->getGlobalBounds().width > window.getSize().x)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].setReverse(true);
    }
  }
  if (alien_ship[i].getSprite()->getPosition().x < 0)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].setReverse(false);
      alien_ship[j].getSprite()->setPosition(alien_ship[j].getSprite()->getPosition().x + alien_ship[j].getSprite()->getGlobalBounds().width / 2,
                                                alien_ship[j].getSprite()->getPosition().y);
    }
  }
}

void Game::alienMovementSine(int i, float dt)
{
  if (!alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(alien_ship[i].getDirection().x * dt, sin(alien_ship[i].getDirection().x) * dt);
  }
  else if (alien_ship[i].getReverse())
  {
    alien_ship[i].getSprite()->move(-alien_ship[i].getDirection().x * dt, sin(alien_ship[i].getDirection().x) * dt);
  }

  if (alien_ship[i].getSprite()->getPosition().x +
      alien_ship[i].getSprite()->getGlobalBounds().width > window.getSize().x)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].setReverse(true);
    }
  }
  if (alien_ship[i].getSprite()->getPosition().x < 0)
  {
    for (int j = 0; j < enemy_array; j++)
    {
      alien_ship[j].setReverse(false);
      alien_ship[j].getSprite()->setPosition(alien_ship[j].getSprite()->getPosition().x + alien_ship[j].getSprite()->getGlobalBounds().width / 2,
                                             alien_ship[j].getSprite()->getPosition().y);
    }
  }
}

void Game::collisionDetection(int i)
{
  //Checks for ship touching bottom of screen or if it touches the player
  if (alien_ship[i].getSprite()->getPosition().y + alien_ship[i].getSprite()->getGlobalBounds().height > window.getSize().y ||
      alien_ship[i].getSprite()->getGlobalBounds().intersects(player_ship.getSprite()->getGlobalBounds()))
  {
    game_screen = false;
    lose_screen = true;
  }

  //Detection for lasers hitting aliens
  for (int j = 0; j < num_lasers; j++)
  {
    if (player_laser[j].getVisibility())
    {
      if (player_laser[j].getSprite()->getGlobalBounds().intersects(alien_ship[i].getSprite()->getGlobalBounds()))
      {
        alien_ship[i].setVisibility(false);
        player_laser[j].setVisibility(false);
        destroyed_ships += 1;
        player_score += 3;
      }
    }
  }
}

void Game::render()
{
  window.draw(mode_selected_text);

  if (start_screen)
  {
    window.draw(start_text);
    window.draw(mode_swap_text);
  }
  else if (!start_screen)
  {
    //If game screen is active
    if (game_screen)
    {
      window.draw(score_text);
      window.draw(*player_ship.getSprite());

      //Enemy Ships
      for (int i = 0; i < enemy_gridsize_x * enemy_gridsize_y; i++)
      {
        if (alien_ship[i].getVisibility())
        {
          window.draw(*alien_ship[i].getSprite());
        }
      }
      //Lasers
      for (int i = 0; i < num_lasers; i++)
      {
        if (player_laser[i].getVisibility())
        {
          window.draw(*player_laser[i].getSprite());
        }
      }
      //Keeps all background drawings whilst drawing pause text in front
      if (pause_screen)
      {
        window.draw(pause_text);
      }
    }
    //If the player has won/lost the game
    else if (win_screen || lose_screen)
    {
      window.draw(play_again_text);
      if (win_screen)
      {
        window.draw(win_text);
      }
      else if (lose_screen)
      {
        window.draw(lose_text);
      }
    }
  }
}


void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)
  {
    window.close();
  }

  if (start_screen || pause_screen)
  {
    if (start_screen)
    {
      if (event.key.code == sf::Keyboard::Enter)
      {
        start_screen = false;
        game_screen = true;
      }
    }
    if (pause_screen)
    {
      if (event.key.code == sf::Keyboard::P)
      {
        pause_screen = !pause_screen;
      }
    }

    if (event.key.code == sf::Keyboard::Z)
    {
      mode_selected = gameMode::standard;
    }
    if (event.key.code == sf::Keyboard::X)
    {
      mode_selected = gameMode::quadratic;
    }
    if (event.key.code == sf::Keyboard::C)
    {
      mode_selected = gameMode::sine;
    }
    if (event.key.code == sf::Keyboard::V)
    {
      mode_selected = gameMode::gravity;
    }
  }
  else if (game_screen)
  {
    if (event.key.code == sf::Keyboard::P)
    {
      pause_screen = true;
    }
    //Player ship movement
    if (event.key.code == sf::Keyboard::A)
    {
      player_movement = true;
      player_move_left = true;
      player_move_right = false;
    }
    if (event.key.code == sf::Keyboard::D)
    {
      player_movement   = true;
      player_move_left  = false;
      player_move_right = true;
    }
    //Player shooting
    if (event.key.code == sf::Keyboard::Space)
    {
      //Check to ensure there isn't more lasers then specified
      if (active_lasers < num_lasers)
      {
        player_laser[0 + active_lasers].setVisibility(true);
        player_laser[0 + active_lasers].getSprite()->setPosition(player_ship.getSprite()->getPosition().x + player_ship.getSprite()->getGlobalBounds().width/2,
                                                                 player_ship.getSprite()->getPosition().y);
        active_lasers += 1;
      }
    }
  }
  else if (win_screen || lose_screen)
  {
    if (event.key.code == sf::Keyboard::P)
    {
      initGame();
      win_screen = false;
      lose_screen = false;
      game_screen = true;
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (game_screen)
  {
    if (event.key.code == sf::Keyboard::A)
    {
      player_movement = false;
      player_move_left = false;
    }
    if (event.key.code == sf::Keyboard::D)
    {
      player_movement = false;
      player_move_right = false;
    }
  }
}



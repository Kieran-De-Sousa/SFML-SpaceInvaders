#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1080, 720), "Space Invaders!");
  window.setFramerateLimit(60);

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  //initialise an instance of the game class
  Game game(window);

  //run the init function of the game class and check it all initialises ok
  if (!game.initGame())
  {
    return 0;
  }


  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      //Checks if player makes a keyboard input
      if (event.type == sf::Event::KeyPressed)
      {
       game.keyPressed(event);
      }
      //Checks if player releases keyboard input
      if (event.type == sf::Event::KeyReleased)
      {
        game.keyReleased(event);
      }
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }


    //'update' element of the game loop
    game.updateGameVariables();
    game.updatePlayerShip(dt);
    game.updateAlienShip(dt);

    window.clear(sf::Color(38, 38, 38, 0));

    //'render' element of the game loop
    game.render();
    window.display();
  }

  return 0;
}


#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  void* setVisibility(bool visibility);
  bool getVisibility();
  void* setDirection(Vector2 object_direction);
  Vector2 getDirection();
  void* setSpeed(float object_speed);
  float getSpeed();
  void* setReverse(bool reverse);
  bool getReverse();

 private:
  sf::Sprite* sprite = nullptr;
  bool is_visible;
  Vector2 direction = {0, 0};
  bool is_reverse;
  float speed;
};

#endif // SPACEINVADERS_GAMEOBJECT_H

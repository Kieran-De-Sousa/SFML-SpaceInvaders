
#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

// SPRITE //
bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "Texture could not be loaded\n";
  }
  sprite = new sf::Sprite();
  sprite->setTexture(texture);

  sprite->setPosition(0,0);

  return true;
}
sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

// VISIBILITY //
void* GameObject::setVisibility(bool visibility)
{
  is_visible = visibility;
}
bool GameObject::getVisibility()
{
  return is_visible;
}

// DIRECTION //
void* GameObject::setDirection(Vector2 object_direction)
{
  direction = object_direction;
}
Vector2 GameObject::getDirection()
{
  return direction;
}

// REVERSE //
void* GameObject::setReverse(bool object_reverse)
{
  is_reverse = object_reverse;
}
bool GameObject::getReverse()
{
  return is_reverse;
}

// SPEED //
void* GameObject::setSpeed(float object_speed)
{
  speed = object_speed;
}
float GameObject::getSpeed()
{
  return speed;
}

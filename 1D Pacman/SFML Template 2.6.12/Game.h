#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

int screenWidth = 800;
int screenHeight = 600;
int dotsEaten = 0;
int dotReset = 20;
int special = 0;
bool huntMode = false;

float rectWidth = 30;
float rectHeight = 30;

float xPosition = rand() % 800;
float yPosition = 200;
float speed = 5;
bool spacePressed = false;
int ticker = 0;

const int numCircles = 20;
sf::CircleShape circles[numCircles];

sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
sf::Time timeSinceLastUpdate = sf::Time::Zero;
sf::Clock clockForFrameRate;

sf::String m_counter{ "0" };
sf::Font m_ArialBlackfont;
sf::Text m_pointCount;
sf::RectangleShape simpleRectangle;

void setupFontAndText();
void update();
void orbCreation();
#endif
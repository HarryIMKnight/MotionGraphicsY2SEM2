//Noel O' Hara
//first simple game. 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"

//recreate the game ..
//
//https://abagames.github.io/crisp-game-lib-11-games/?pakupaku
// see blackboard for sample sprites.
// 
int main()
{
	std::cout << "Started Game" << std::endl;

	setupFontAndText();
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "1D Pacman");

	simpleRectangle.setSize(sf::Vector2f(rectWidth, rectHeight));

	simpleRectangle.setPosition(100, 200);

	srand(time(NULL));

	clockForFrameRate.restart();

	while (window.isOpen())
	{
		std::cout << ticker << std::endl;

		if (huntMode == true)
		{ 
			ticker++;

			if (ticker > 10000)
			{
				huntMode = false;
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timeSinceLastUpdate += clockForFrameRate.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			update();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (spacePressed == false)
				{
					speed *= -1;
					spacePressed = true;
				}
			}
			else {
				spacePressed = false;
			}

			xPosition += speed;

			if (xPosition > screenWidth)
			{
				xPosition = 0;
			}
			else if (xPosition + 30 < 0)
			{
				xPosition = screenWidth;
			}

			simpleRectangle.setPosition(xPosition, yPosition);

			for (int index = 0; index < numCircles; index++)
			{
				if (simpleRectangle.getGlobalBounds().intersects(circles[index].getGlobalBounds()))
				{
					circles[index].setPosition(1000, 1000);
					dotsEaten++;
					dotReset--;
				}
				if (simpleRectangle.getGlobalBounds().intersects(circles[special].getGlobalBounds()))
				{
					huntMode = true;
				}
			}

			if (dotReset == 0)
			{
				orbCreation();
				dotReset = 20;
			}

			window.clear();
			for (int index = 0; index < numCircles; index++)
			{
				window.draw(circles[index]);
			}
			window.draw(simpleRectangle);
			window.draw(m_pointCount);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}

void setupFontAndText()
{
	orbCreation();
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_pointCount.setFont(m_ArialBlackfont);
	m_pointCount.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_pointCount.setPosition(40.0f, 40.0f);
	m_pointCount.setCharacterSize(30U);
	m_pointCount.setOutlineColor(sf::Color::Red);
	m_pointCount.setFillColor(sf::Color::Black);
	m_pointCount.setOutlineThickness(3.0f);

}

void update()
{
	m_counter = std::to_string(dotsEaten);
	m_pointCount.setString(m_counter);

	if (huntMode == true)
	{
		simpleRectangle.setFillColor(sf::Color::Red);
	}
	else if (huntMode == false)
	{
		simpleRectangle.setFillColor(sf::Color::Yellow);
	}
}

void orbCreation()
{
	int chosenDot = rand() % 20;

	for (int index = 0; index < numCircles; index++)
	{
		if (index == chosenDot)
		{
			circles[index].setFillColor(sf::Color::Yellow);
			circles[index].setRadius(15);
			circles[index].setPosition(40 * index, 195);
			special = index;
		}
		else
		{
			circles[index].setFillColor(sf::Color::White);
			circles[index].setRadius(10);
			circles[index].setPosition(40 * index, 200);
		}
	}
}
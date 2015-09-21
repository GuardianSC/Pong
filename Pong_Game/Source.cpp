#include <iostream>
#include <cstdlib>
#include <time.h>
#include "sfwdraw.h"
#include <cmath>


const int screenWidth = 640;
const int screenHeight = 480;

float Ball_posX = 320;
float Ball_posY = 240;
float Ball_dirX = -1.0f;
float Ball_dirY = 1.0f;
float Ball_randomPosX = Ball_posX * 4;
float Ball_randomPosY = Ball_posY * 4;
float Ball_posR = 15;

float score1 = 0; // Left paddle score
float score2 = 0; // Right paddle score

float Ball_speed = 2;

float leftPaddle_posX = 30;
float leftPaddle_posY = 225;
float leftPaddle_speed = 3;

float leftPaddle_height = 50;
float leftPaddle_width = 20;

float rightPaddle_posX = 585;
float rightPaddle_posY = 225;
float rightPaddle_speed = 3;

float rightPaddle_height = 50;
float rightPaddle_width = 20;

// Vector 2 normal, taken from http://noobtuts.com/cpp/2d-pong-game
void vec2_norm(float x, float y) {
	float length = sqrt((x * x) + (y * y));
	if (length != 0.0f) {
		length = 1.0f / length;
		x *= length;
		y *= length;
	}
}

void leftPaddle()
{
	// Draw sides

	sfw::drawLine(leftPaddle_posX, leftPaddle_posY, leftPaddle_posX, leftPaddle_posY + 50);
	sfw::drawLine(leftPaddle_posX + 20, leftPaddle_posY, leftPaddle_posX + 20, leftPaddle_posY + 50);

	// Draw Top and Bottom

	sfw::drawLine(leftPaddle_posX, leftPaddle_posY, leftPaddle_posX + 20, leftPaddle_posY);
	sfw::drawLine(leftPaddle_posX, leftPaddle_posY + 50, leftPaddle_posX + 20, leftPaddle_posY + 50);
	
	// Movement

	if (sfw::getKey('w'))
	{
		--leftPaddle_posY -= leftPaddle_speed;
	}
	if (sfw::getKey('s'))
	{
		++leftPaddle_posY += leftPaddle_speed;
	}

	// Stops paddle from going through top and bottom of the screen

	if (leftPaddle_posY <= 1)
	{
		leftPaddle_posY = 1;
	}
	if (leftPaddle_posY >= 428)
	{
		leftPaddle_posY = 428;
	}
}

void rightPaddle()
{
	// Draw sides

	sfw::drawLine(rightPaddle_posX, rightPaddle_posY, rightPaddle_posX, rightPaddle_posY + 50);
	sfw::drawLine(rightPaddle_posX + 20, rightPaddle_posY, rightPaddle_posX + 20, rightPaddle_posY + 50);

	// Draw Top and Bottom

	sfw::drawLine(rightPaddle_posX, rightPaddle_posY, rightPaddle_posX + 20, rightPaddle_posY);
	sfw::drawLine(rightPaddle_posX, rightPaddle_posY + 50, rightPaddle_posX + 20, rightPaddle_posY + 50);

	// Movement

	if (sfw::getKey('i'))
	{
		rightPaddle_posY -= rightPaddle_speed;
	}
	if (sfw::getKey('k'))
	{
		++rightPaddle_posY += rightPaddle_speed;
	}

	// Stops paddle from going through top and bottom walls
	if (rightPaddle_posY <= 1)
	{
		rightPaddle_posY = 1;
	}
	if (rightPaddle_posY >= 428)
	{
		rightPaddle_posY = 428;
	}
}

struct Ball
{
	float x, y, r;

	void updateBall()
	{
		sfw::drawCircle(x, y, r);
		x += rand() % 4 + 1;
		y += rand() % 4 + 1;
		Ball_posX += Ball_dirX * Ball_speed;
		Ball_posY += Ball_dirY * Ball_speed;

		// Collision, code found and modified from http://noobtuts.com/cpp/2d-pong-game

		// Left Paddle
		if (Ball_posX < leftPaddle_posX + leftPaddle_width && Ball_posX < leftPaddle_posX && Ball_posY < leftPaddle_posY + leftPaddle_height &&  Ball_posY < leftPaddle_posY)
		{
			float f = ((Ball_posY - leftPaddle_posY)) / leftPaddle_height;
			Ball_dirX = fabs(Ball_dirX);
			Ball_dirY = f;
		}
		// Right Paddle
		if (Ball_posX < rightPaddle_posX + rightPaddle_width && Ball_posX < rightPaddle_posX && Ball_posY < rightPaddle_posY + rightPaddle_height &&  Ball_posY < rightPaddle_posY)
		{
			float f = ((Ball_posY - rightPaddle_posY)) / rightPaddle_height;
			Ball_dirX = fabs(Ball_dirX);
			Ball_dirY = f;
		}

		// Top Wall
		if (Ball_posY < 0)
		{
			Ball_dirY = -fabs(Ball_dirY);
		}
		// Bottom Wall
		if (Ball_posY > screenHeight)
		{
			Ball_dirY = fabs(Ball_dirY);
		}
		// Score for Right Paddle
		if (Ball_posX < 0)
		{
			score2++;
			Ball_posX = 320;
			Ball_posY = 240;
		}
		// Score for Left Paddle
		if (Ball_posX > screenWidth)
		{
			score1++;
			Ball_posX = 320;
			Ball_posY = 240;
		}
		vec2_norm(Ball_dirX, Ball_dirY);
	}
};

	void MapBoundaries()
	{
		// Draw Top and Bottom
		sfw::drawLine(0, 0, 640, 0);
		sfw::drawLine(0, 479, 640, 479);
	}

	int main()
	{
		srand(time(NULL));
		int random_number = rand() % 4 + 1;

		sfw::initContext(screenWidth, screenHeight, "Terrible Pong");

		Ball b = { 320 , 240 , 10 };

		while (sfw::stepContext())
		{
			leftPaddle();
			rightPaddle();
			MapBoundaries();
			b.updateBall();

			std::cout << sfw::getDeltaTime << std::endl;
		}
		sfw::termContext;
		return 0;
	}
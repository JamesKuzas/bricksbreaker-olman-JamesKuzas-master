#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>
class Game
{
	Ball ball;
	Box paddle;

	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	Box brick;
	Box brick2;
	Box brick3;
	Box brick4;
	Box brick5;

	std::vector<Box> v;
public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};

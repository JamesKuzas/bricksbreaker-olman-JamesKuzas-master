#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
	brick.width = 10;
	brick.height = 2;
	brick.x_position = 5;
	brick.y_position = 5;
	brick.doubleThick = true;
	brick.color = ConsoleColor::DarkGreen;

	brick2.width = 10;
	brick2.height = 2;
	brick2.x_position = 20;
	brick2.y_position = 5;
	brick2.doubleThick = true;
	brick2.color = ConsoleColor::DarkGreen;

	brick3.width = 10;
	brick3.height = 2;
	brick3.x_position = 35;
	brick3.y_position = 5;
	brick3.doubleThick = true;
	brick3.color = ConsoleColor::DarkGreen;

	brick4.width = 10;
	brick4.height = 2;
	brick4.x_position = 50;
	brick4.y_position = 5;
	brick4.doubleThick = true;
	brick4.color = ConsoleColor::DarkGreen;

	brick5.width = 10;
	brick5.height = 2;
	brick5.x_position = 65;
	brick5.y_position = 5;
	brick5.doubleThick = true;
	brick5.color = ConsoleColor::DarkGreen;
	

}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = true;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering should be done between the locks in this function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks
	brick.Draw();
	brick2.Draw();
	brick3.Draw();
	brick4.Draw();
	brick5.Draw();
	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	if (brick.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		brick.color = ConsoleColor(brick.color - 1);
		ball.y_velocity *= -1;

		// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
		if (brick.Contains(ball.x_position + ball.x_velocity,ball.y_position+ball.y_velocity))
		{
			brick.color = Black;
			brick.height = 0;
			brick.width = 0;
		}
	}

	if (brick2.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		brick2.color = ConsoleColor(brick.color - 1);
		ball.y_velocity *= -1;
		if (brick2.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			brick2.color = Black;
			brick2.height = 0;
			brick2.width = 0;
		}
	}

	if (brick3.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		brick3.color = ConsoleColor(brick.color - 1);
		ball.y_velocity *= -1;
		if (brick3.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			brick3.color = Black; 
			brick3.height = 0;
			brick3.width = 0;
		}
	}

	if (brick4.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		brick4.color = ConsoleColor(brick.color - 1);
		ball.y_velocity *= -1;
		
		brick4.color = Black;
		brick4.height = 0;
		brick4.width = 0;
		
	}

	if (brick5.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
	{
		brick5.color = ConsoleColor(brick.color - 1);
		ball.y_velocity *= -1;
		if (brick5.Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			brick5.color = Black;
			brick5.visage = true;
			brick5.height = 0;
			brick5.width = 0;
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display victory text with R to reset
	if (v.size()==10)
	{
		ball.moving = false;
		std::cout << "You Win! (Press 'R' to reset the game.)";
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display defeat text with R to reset
	if (ball.y_position - 5 > paddle.y_position)
	{
		ball.moving = false;
		
		std::cout << "You Lost! (Press 'R' to reset the game.)";
	}
	
}

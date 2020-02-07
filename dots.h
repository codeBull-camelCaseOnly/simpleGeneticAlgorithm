#pragma once
#include<vector>

float dist(float x1, float y1, float x2, float y2);

class dots
{
public:
	float x, y;
	std::vector<int> directions;	//one of 0, 1, 2, 3
	int steps;
	float distanceFromGoal;
	bool pause;
	float fitness;

	dots() = delete;
	dots(float x, float y);

	void update(float goalx, float goaly);
	void display(float r = 1, float g = 0.3, float b = 0);
};

std::vector<int> crossover(dots father, dots mother);


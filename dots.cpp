#include "dots.h"
#include<GL/glew.h>

int dotSize = 5;
int maxSteps = 300;
int stepSize = dotSize;

dots::dots(float x, float y)
	: x(x), y(y) 
{
	for (int i = 0; i < maxSteps; ++i)
		directions.emplace_back(rand() % 4);
	steps = 0;
	pause = false;
}

void dots::update(float goalx, float goaly)
{
	if (!pause)
	{
		distanceFromGoal = dist(x, y, goalx, goaly);
		fitness = 1 / distanceFromGoal + 3.0 / steps;
		if (distanceFromGoal == 0)
			pause = true;

		switch (directions[steps])
		{
		case 0: x += stepSize;
			break;
		case 1: y += stepSize;
			break;
		case 2: x -= stepSize;
			break;
		case 3: y -= stepSize;
			break;
		}

		++steps;
		if (steps >= maxSteps)
			pause = true;
	}
}

void dots::display(float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(x			,	y			);
	glVertex2f(x + dotSize	,	y			);
	glVertex2f(x + dotSize	,	y + dotSize	);
	glVertex2f(x			,	y + dotSize	);
	glEnd();
}

float dist(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

std::vector<int> crossover(dots father, dots mother)
{
	std::vector<int> res;

	for (int i = 0; i < maxSteps; ++i)
	{
		int t = rand() % 100;

		if(t < 100)										//90% of the time, father's genes are taken
			res.emplace_back(father.directions[i]);		//because father is the fittest
		else if(t < 100)
			res.emplace_back(mother.directions[i]);
	}

	for (int i = 0; i < maxSteps; ++i)
	{
		int t = rand() % 1000;							//mutation 
		if (t < 8)										//having chance 10 in 1000
			res[i] = rand() % 4;						//choose a random direction
	}

	return res;
}

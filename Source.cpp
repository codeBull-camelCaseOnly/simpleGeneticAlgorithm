#define NDEBUG
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<GL/freeglut.h>
#include"dots.h"
#include<ctime>
#include<string>

int noOfDots = 10;
int goalx = 100, goaly = 100;
int initx = 100, inity = 100;

void drawCube(float x, float y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + 5, y);
	glVertex2f(x + 5, y + 5);
	glVertex2f(x, y + 5);
	glEnd();
}

void drawBitmapText(std::string str, float x, float y, float z)
{
	glRasterPos3f(x, y, z);
	for (char c : str)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

int main()
{
	srand(time(0));

	std::vector<dots> d;
	for (int i = 0; i < noOfDots; ++i)
		d.emplace_back(initx, inity);

	int argc = 1;
	char* argv[] = { (char*)"nothing" };
	glutInit(&argc, argv);

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "untitled", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 600, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.1, 0.1, 0.1, 1);

	int maxIndex = 0;
	int gen = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		drawCube(goalx, goaly, 0, 1, 0);						//goal

		int flag = 0;

		std::string s = "generation " + std::to_string(gen);
		drawBitmapText(s, 600, 20, 0);

		for (int i = 0; i < noOfDots; ++i)
		{
			d[i].update(goalx, goaly);
			if(i != maxIndex)
				d[i].display();

			if (!d[i].pause)
				flag = 1;
		}

		d[maxIndex].display(1, 0, 1);

		if(flag == 0)		//will reach here only if all dots have stopped
		{ 
			gen++;
			maxIndex = 0;
			for (int i = 0; i < noOfDots; ++i)
			{
				if (d[i].fitness > d[maxIndex].fitness)
					maxIndex = i;
			}

			for (int i = 0; i < noOfDots; ++i)
			{
				d[i].directions = crossover(d[maxIndex], d[i]);	//mate every other dot with fittest dot

				d[i].pause = false;
				d[i].x = initx;
				d[i].y = inity;
				d[i].steps = 0;
			}
		}

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
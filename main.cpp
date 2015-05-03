#include <iostream>
#include <cstdlib>
#include <math.h>
#include <GL/glut.h>
using namespace std;

const int N = 3; // ширина
const int M = 3; // высота

int Scale = 70;

int w = N * Scale; // ширина экрана = 350
int h = M * Scale; // высота экрана = 350

bool gamer = 0;
int count = 0;

struct Card
{
	int x;
	int y;
	int value;
	Card():value(0){}
} c[N][M]; // 0-4 массивы

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CheckVertical(int row, int col)
{
	bool state = 0;
	for(int i = 0; i < N; i++)
	{
		if(c[i][col].value == gamer){}
		else
		{
			state = 1;
			break;
		}
	}
	if(!state)
	{
		cout << "Вертикальный выйгрыш у " << gamer << endl;
		exit(1);
	}
}

void CheckHorizontal(int row, int col)
{
	bool state = 0;
	for(int i = 0; i < M; i++)
	{
		if(c[row][i].value == gamer){}
		else
		{
			state = 1;
			break;
		}
	}
	if(!state)
	{
		cout << "Горизонтальный выйгрыш у " << gamer << endl;
		exit(1);
	}
}

void CheckMainDiagonal()
{
	bool state = 0;
	for(int i = 0; i < M; i++)
	{
		if(c[i][i].value == gamer){}
		else
		{
			state = 1;
			break;
		}
	}
	if(!state)
	{
		cout << "Диагональный выйгрыш у " << gamer << endl;
		exit(1);
	}
	for(int i = 0; i < M; i++)
	{
		if(c[i][i].value == !gamer){}
		else
		{
			state = 1;
			break;
		}
	}
	if(!state)
	{
		cout << "Диагональный выйгрыш у " << !gamer << endl;
		exit(1);
	}
}

void CheckNotMainDiagonal()
{
	bool state = 0;
	for(int i = 0, j = M-1; i < M; i++, j--)
	{
		if(c[i][j].value == gamer){}
		else
		{
			state = 1;
			break;
		}
	}
	if(!state)
	{
		cout << "Поб Диагональный выйгрыш у " << gamer << endl;
		exit(1);
	}
}

void CheckAll()
{
	if(count >= N*M - 1)
	{
		cout << "НИЧЬЯ!\n";
		exit(1);
	}
}

void drawCircle(float x, float y, float r, int amountSegments)
{
	glBegin(GL_LINE_LOOP);

	for(int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}

	glEnd();
}

void DrawField()
{
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	for(int i = 0; i < w; i += Scale)
	{
		glVertex2i(i, 0);
		glVertex2i(i, h);
	}
	for(int i = 0; i < h; i += Scale)
	{
		glVertex2i(0, i);
		glVertex2i(w, i);
	}
	glEnd();
}

void DrawCards()
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			if(c[i][j].value != -1)
			{
				glLineWidth(2);
				if(c[i][j].value == 0)
				{
					glBegin(GL_LINES);
					glVertex2i(j * Scale, i * Scale);
					glVertex2i(j * Scale + Scale, i * Scale + Scale);
					glVertex2i(j * Scale, i * Scale + Scale);
					glVertex2i(j * Scale + Scale, i * Scale);
					glEnd();
				}
				if(c[i][j].value == 1)
				{
					drawCircle((j * Scale + (Scale/2)), (i * Scale + (Scale/2)), 34, 20);
				}
			}
		}
	}
}

void PrintCards()
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < M; j++)
		{
			cout << c[i][j].value << " ";
		}cout << endl;
	}
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawField();
	DrawCards();
	glutSwapBuffers();
}

void MousePressed(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		int row = y/Scale;
		int col = x/Scale;
		if(c[row][col].value == -1)
			c[row][col].value = gamer;
		else
			return;
		CheckVertical(row, col);
		CheckHorizontal(row, col);
		CheckMainDiagonal();
		CheckNotMainDiagonal();
		CheckAll();
		gamer = !gamer;
		++count;
	}
}

void timer(int)
{
	display();
	glutTimerFunc(50, timer, 0);
}

int main(int argc, char** argv)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			c[i][j].value = -1;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(480,200);
	glutCreateWindow("Tic-tac-toe");

	glClearColor(1, 1, 1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);

	glutDisplayFunc(display);
	glutMouseFunc(MousePressed);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
}


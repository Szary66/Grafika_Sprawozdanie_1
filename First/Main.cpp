
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif

// Pocztkowy rozmiar i pozycja prostokta
GLfloat glX = 100.0f;
GLfloat glY = 150.0f;
GLsizei rsize = 50;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////


void DrawPolygon(float x0, float y0)
{
	// Narysowanie prostok¹ta wype³nionego aktualnym kolorem
	//glRectf(glX, glY, glX + rsize, glY + rsize);
	GLfloat x, y, kat = 0;

	const GLfloat GL_PI = 3.1415f;

	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(x0, y0, 0); //srodek kola

//	for(kat = 0.0f; kat < (2.0f*GL_PI); kat += (GL_PI /100.0f))
	for(size_t i = 1; i < 8; ++i)
	{
		kat += (2 * 3.14) / i;

		x = 50.0f*sin(kat) + x0;

		y = 50.0f*cos(kat) + y0;

		glVertex3f(x, y, 0);

	}

	glEnd();

}


// Wywo³ywana w celu przerysowania sceny
void RenderScene(void)
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysuj¹cy - czerwony
	//	R	G	B
	glColor3f(1.0f, 0.0f, 0.0f);

	DrawPolygon(glX, glY);

	// Wys³anie poleceñ do wykonania - !!! dla animacji to jest inne polecenie

	glutSwapBuffers();
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkoœæ
void TimerFunction(int value)
{
	// Odwrócenie kierunku, je¿eli osi¹gniêto lew¹ lub praw¹ krawêdŸ
	if(glX > windowWidth - rsize || glX < 50)
		xstep = -xstep;

	// Odwrócenie kierunku, je¿eli osi¹gniêto doln¹ lub górn¹ krawêdŸ
	if(glY > windowHeight - rsize || glY < 50)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy³o swoj wielkoœæ w czasie, gdy kwadrat odbija³ siê od     
	// krawêdzi, co mog³oby spowodowaæ, ¿e znalaz³ by siê poza      
	// przestrzeni¹ ograniczajc¹.     
	if(glX > windowWidth - rsize)
		glX = windowWidth - rsize - 1;

	if(glY > windowHeight - rsize)
		glY = windowHeight - rsize - 1;

	// Wykonanie przesuniêcia kwadratu
	glX += xstep;
	glY += ystep;

	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void)
{
	// Ustalenie niebieskiego koloru czyszcz¹cego     
	glClearColor(0.0f, 0.0f, 1.0f, .5f);
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT przy ka¿dej zmianie wielkoœci okna
void ChangeSize(GLsizei w, GLsizei h)
{
	// Zabezpieczenie przed dzieleniem przez zero
	if(h == 0)
		h = 1;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk³adu wspó³rzêdnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if(w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	} else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G³ówny punkt wejœcia programu
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bounce");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
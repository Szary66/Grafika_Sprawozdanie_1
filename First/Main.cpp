
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
// Dane zmieniajcych si� rozmiar�w okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////


void DrawPolygon(float x0, float y0)
{
	// Narysowanie prostok�ta wype�nionego aktualnym kolorem
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


// Wywo�ywana w celu przerysowania sceny
void RenderScene(void)
{
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysuj�cy - czerwony
	//	R	G	B
	glColor3f(1.0f, 0.0f, 0.0f);

	DrawPolygon(glX, glY);

	// Wys�anie polece� do wykonania - !!! dla animacji to jest inne polecenie

	glutSwapBuffers();
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielko��
void TimerFunction(int value)
{
	// Odwr�cenie kierunku, je�eli osi�gni�to lew� lub praw� kraw�d�
	if(glX > windowWidth - rsize || glX < 50)
		xstep = -xstep;

	// Odwr�cenie kierunku, je�eli osi�gni�to doln� lub g�rn� kraw�d�
	if(glY > windowHeight - rsize || glY < 50)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy�o swoj wielko�� w czasie, gdy kwadrat odbija� si� od     
	// kraw�dzi, co mog�oby spowodowa�, �e znalaz� by si� poza      
	// przestrzeni� ograniczajc�.     
	if(glX > windowWidth - rsize)
		glX = windowWidth - rsize - 1;

	if(glY > windowHeight - rsize)
		glY = windowHeight - rsize - 1;

	// Wykonanie przesuni�cia kwadratu
	glX += xstep;
	glY += ystep;

	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void)
{
	// Ustalenie niebieskiego koloru czyszcz�cego     
	glClearColor(0.0f, 0.0f, 1.0f, .5f);
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT przy ka�dej zmianie wielko�ci okna
void ChangeSize(GLsizei w, GLsizei h)
{
	// Zabezpieczenie przed dzieleniem przez zero
	if(h == 0)
		h = 1;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych
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

	// Ustanowienie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G��wny punkt wej�cia programu
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
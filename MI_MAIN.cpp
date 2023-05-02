#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>
#include <GL/glut.h>
#include "DEFINES.h"
#include "Class_Camara.h"
#include "Controles.h"
#include "DISPLAY.h"
#include "PARTICULAS_H.h"
#include "PARTICULAS.h"

/*

	EJEMPLO DE USO DE LA CAMARA CON "glFrustum" y "gluLookAt".


	Excelente ejemplo donde se muestra el uso de la camara y tambien
	el uso del teclado y mouse.

*/




// TIMER : 16MS PARA 60fpss
void Timer(int x) {
	glutPostRedisplay();
	glutTimerFunc(16, Timer, 1);
}


void Config_Inicial() {

	// PONEMOS EL MODO DE MATRIZ EN PROJECCION
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glPointSize(2.0f);

	//// POSICIONES INICIALES PARTICULAS
	//Posiciones_Iniciales();

	//// CALCULAMOS TODOS LOS CICLOS DE LAS POSICIONES
	//// DE LAS PARTICULAS
	//Gravity();
	Menu();


	// INDICAMOS LO QUE SE VA A MOSTRAR CON LA
	// CAMARA (CON PROJECCION). Notar que hacer
	// cambios en left, right, top y bottom
	// genera distosion.
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0,1000.0);
}


static void display(void) {

	Coor3d Rot_, Trasl_, Ang_;

	// Limpiamos 
	glClear(GL_COLOR_BUFFER_BIT);

	// MODO MATRIZ (GL_MODELVIEW)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// CAMARA
	Camara.Movimiento_Camara();

	Rot_ = Camara.Get_Rotacion();
	Trasl_ = Camara.Get_Traslacion();
	Ang_ = Camara.Get_Angulos();

	gluLookAt(Trasl_.X_, Trasl_.Y_, Trasl_.Z_,
			  Rot_.X_, Rot_.Y_, Rot_.Z_,
			  0.0, 1.0, 0.0);

	// DIBUJO
	Dibujar_Grilla();		// grilla , angulo 0.0°
	Dibujar_Grilla(90.0);	// grilla, angulo 90.0

	// DIBUJAMOS LAS POSICIONES DE LAS PARTICULAS
	Dibujar_Posiciones();

	// Intercambiamos Buffers
	glutSwapBuffers();

}


// SIN USO
static void reshape(int w, int h) {

	double Formato = double(w) / double(h);

}


int main(int argc, char** argv) {

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(RESOLUCION_X, RESOLUCION_Y);
	glutInitWindowPosition(500, 100);
	glutCreateWindow(argv[0]);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutDisplayFunc(display);

	glutMotionFunc(Mouse_func);									// mientras presionamos click
	//glutPassiveMotionFunc(Mouse_func);						//  en todo momento

	glutMouseFunc(Mouse_Buttons);
	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);
	glutSpecialFunc(Keyboard_Special_Down);
	glutSpecialUpFunc(Keyboard_Special_Up);

	//glutFullScreen();

	Timer(1);

	Config_Inicial();

	glutMainLoop();

	return 0;
}


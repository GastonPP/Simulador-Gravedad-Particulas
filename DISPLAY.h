#pragma once


// DIBUJO DE GRILLA.
// Notar el uso del argumento "Angulo" para girar la grilla y con la misma
// funcion, dibujar tanto las lineas verticales como horizontales.
void Dibujar_Grilla(double Angulo = 0.0) {

	float COLOR[3] = { 0.3, 0.0, 0.0 };

	double MAX_X = 1000.0;
	double MIN_X = -1000.0;

	double MAX_Z = 1000.0;
	double MIN_Z = -1000.0;
	double SALTO_Z = 4.0;

	// USO MATRIZ
	glPushMatrix();
		
		glRotated(Angulo, 0.0, 1.0, 0.0);

		for (double z = MIN_Z; z < MAX_Z; z += SALTO_Z) {

			glBegin(GL_LINES);
				glColor3fv(COLOR);
				glVertex3f(MIN_X, 0.0, z);
				glVertex3f(MAX_X, 0.0, z);
			glEnd();
		}

	glPopMatrix();
}

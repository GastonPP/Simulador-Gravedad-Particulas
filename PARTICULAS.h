#pragma once

/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*************************									FUNCIONES										**********************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/



// FUNCION IMPRIMIR INFORMACION
void Imprimir_Info(int ciclo, float tiempo = 0.0f) {

	pos = { 0, 0 };
	SetConsoleCursorPosition(hConsole, pos);
	std::cout << "Ciclo: " << ciclo;

	if (tiempo > 0) {
		pos = { 0, 1 };
		SetConsoleCursorPosition(hConsole, pos);
		std::cout << "Tiempo en Seg: " << tiempo;
	}

}



// FUNCION DIBUJADO DE POSICIONES
void Dibujar_Posiciones() {

	static unsigned int VelDibujado;
	unsigned int Iterador;
	float x, y, z;

	// Si se llega al final de los ciclos, se mantiene el ultimo ciclo.
	if (CicloActual >= NUM_CICLOS) { CicloActual = NUM_CICLOS - 1; }

	// Dibujamos cada particula en su posision del ciclo.
	glBegin(GL_POINTS);

	// Color Blanco
	glColor3f(1, 1, 1);

	for (Iterador = 0; Iterador < NUM_PARTICLES; Iterador++) {

		// si esta activo se dibuja.
		if (POSICIONES[CicloActual][Iterador].Activo) {

			x = POSICIONES[CicloActual][Iterador].Pos.x;
			y = POSICIONES[CicloActual][Iterador].Pos.y;
			z = POSICIONES[CicloActual][Iterador].Pos.z;

			glVertex3f(x, y, z);
		}
	}

	glEnd();

	// imprimirmos informacion
	Imprimir_Info(CicloActual);


	// Velocidad Dibujado
	VelDibujado++;

	// Pasamos al siguiente ciclo.
	if (VelDibujado >= DIBUJADO_FPS) {
		CicloActual++;

		VelDibujado = 0;
	}
}



// SIGUIENTE CICLO
void Siguiente_Ciclo() {
	for (int i = 0; i < NUM_PARTICLES; i++) {
		ESTADO_INI[i] = ESTADO_FIN[i];
	}
}



// FUNCION POSICIONES INICIALES
// Insertamos en el Vector global cada particula creada.
// Asignamos Posiciones y Velocidades aleatorias a cada particula.
bool Posiciones_Iniciales() {
	float mass, x, y, z, vx, vy, vz;

	std::srand(std::time(nullptr));								// semilla rnd

	for (int i = 0; i < NUM_PARTICLES; i++) {

		mass = float(std::rand() % (MASSMAX * 100)) / 100.0f;									// rnd entre 1 y MASSMAX 

		x = float((std::rand() % (POSINIMAX_X * 100 * 2)) - POSINIMAX_X * 100) / 100;				// rnd entre -POSINIMAX_X y POSINIMAX_X
		y = float((std::rand() % (POSINIMAX_Y * 100 * 2)) - POSINIMAX_Y * 100) / 100;				// rnd entre -POSINIMAX_X y POSINIMAX_Y
		z = float((std::rand() % (POSINIMAX_Z * 100 * 2)) - POSINIMAX_Z * 100) / 100;				// rnd entre -POSINIMAX_X y POSINIMAX_Z

		vx = (float(std::rand() % VELINI * 2) / VELINI_X) - (VELINI / VELINI_X);		// rnd entre -(VELINI / VELINI_X) y
		vy = (float(std::rand() % VELINI * 2) / VELINI_Y) - (VELINI / VELINI_Y);		// +(VELINI / VELINI_X)
		vz = (float(std::rand() % VELINI * 2) / VELINI_Z) - (VELINI / VELINI_Z);

		ESTADO_INI[i].Pos.Guardar(x, y, z);
		ESTADO_INI[i].Vel.Guardar(vx, vy, vz);
		ESTADO_INI[i].Set_Mass(mass);
	}

	return true;
}



// FUNCION GRAVITY
// La funcion calcula las posiciones de todas las particulas del vector global "particles"
// y va guardando cada posicion en el vector global "Posiciones"
bool Gravity() {
	int t_inicial = glutGet(GLUT_ELAPSED_TIME), t_final = 0;

	Vector3D Vxyz, Axyz, Dxyz, Pxyz;							// VECTORES VELOCIDAD, ACELERACION ,DISTANCIA, POSICION
	float f = .0f, r = .0f;										// FUERZA G Y RADIO
	float MassI = .0f, MassJ = .0f;								// MASA DE LAS PARTICULAS

	// Calculo de las velocidades y posiciones de las particulas.
	while (Ciclo < NUM_CICLOS) {
		for (int i = 0; i < NUM_PARTICLES; i++) {

			if (!ESTADO_INI[i].Activo) { continue; }									// si no esta activa se ignora.

			// Comparamos Particula "i" con todas las demas "j".
			for (int j = 0; j < NUM_PARTICLES; j++) {
				
				if (i == j) continue;													// si son la misma particula se ignora

				if (!ESTADO_INI[j].Activo) {
					ESTADO_FIN[i].Pos = ESTADO_INI[i].Pos + ESTADO_INI[i].Vel;			// guardamos posision final

					POSICIONES[Ciclo][i].Pos = ESTADO_INI[i].Pos;						// guardamos la posicion de "i", ya que "j" esta inactiva
					POSICIONES[Ciclo][i].Activo = true;									// y la marcamos como un punto activo.
					continue;															// continuamos al siguiente "j"
				}

				// si estan fusionadas se ignoran.
				if ((ESTADO_INI[j].Fusion == i) or (ESTADO_INI[i].Fusion == j)) { continue;	}

				Dxyz = ESTADO_INI[j].Pos - ESTADO_INI[i].Pos;			// Dxyz : distancia entre particula "j" y particula "i"
				r = Dxyz.magnitude();									// Radio: magnitud de la distancia Dxyz

				MassI = ESTADO_INI[i].Mass;
				MassJ = ESTADO_INI[j].Mass;

				// Si estan separados, se calcula normal, si estan cerca (chocan) se fusionan.
				if (r > RADIO_MIN) {
					// CALCULO NORMAL

					f = GRAVITATIONAL_CONSTANT * MassI * MassJ / (r * r);		// F = G * m1 * m2 / r^2

					Axyz = Dxyz * (f / r);										// Calculo aceleracion
					Vxyz = ESTADO_INI[i].Vel + (Axyz / MassI);					// velocidad: la aceleracion se aplica segun la masa

					ESTADO_FIN[i].Pos = ESTADO_INI[i].Pos + Vxyz;				// guardamos posision final
					ESTADO_FIN[i].Vel = Vxyz;									// y velocidad final de la particula.

					POSICIONES[Ciclo][i].Pos = ESTADO_FIN[i].Pos;				// guardamos la posicion y la marcamos activa
					POSICIONES[Ciclo][i].Activo = true;

				} else {
					//// CALCULO FUSION
					//ESTADO_INI[j].Fusion = i;											// indicamos que se fusiono con "i"
					//ESTADO_FIN[j].Activo = false;										// y la desactivamos para el prox ciclo.

					//// masa_combinada = m1 + m2
					//ESTADO_FIN[i].Mass = MassI + MassJ;

					//// posicion_combinada = (x1 + x2) / 2
					//Pxyz = (ESTADO_INI[j].Pos + ESTADO_INI[i].Pos) / 2;
					//ESTADO_FIN[i].Pos = Pxyz;

					//// velocidad_combinada = (m1v1 + m2v2) / (m1 + m2)
					////Vxyz = (ESTADO_INI[j].Vel + ESTADO_INI[i].Vel) / (ESTADO_INI[j].Mass + ESTADO_INI[i].Mass);
					//Vxyz = (ESTADO_INI[j].Vel * ESTADO_INI[j].Mass) + (ESTADO_INI[i].Vel * ESTADO_INI[i].Mass);
					//Vxyz = Vxyz / 2;
					//ESTADO_FIN[i].Vel = Vxyz;

					//POSICIONES[Ciclo][i].Pos = ESTADO_FIN[i].Pos;				// guardamos la posicion y la marcamos activa
					//POSICIONES[Ciclo][i].Activo = true;

					ESTADO_FIN[i].Pos = ESTADO_INI[i].Pos + ESTADO_INI[i].Vel;			// guardamos posision final

					POSICIONES[Ciclo][i].Pos = ESTADO_INI[i].Pos;						// guardamos la posicion de "i", ya que "j" esta inactiva
					POSICIONES[Ciclo][i].Activo = true;									// y la marcamos como un punto activo.
					continue;															// continuamos al siguiente "j"
					
				}
			}
		}

		Imprimir_Info(Ciclo);

		// siguiente ciclo
		Siguiente_Ciclo();
		Ciclo++;
	}

	// Al finalizar la funcion imprimimos el tiempo que se tardo y los ciclos.
	t_final = glutGet(GLUT_ELAPSED_TIME);

	Imprimir_Info(Ciclo, float(t_final - t_inicial) / 1000);
	std::cout << "\nSimulacion finalizada...";

	Sleep(3000);

	// GUARDAMOSLA SIMULACION
	//Guardar_Simulacion();

	system("cls");
	return true;
}



// GUARDAR SIMULACION
bool Guardar_Simulacion() {

	int Ciclo = 0;
	std::string Fichero, MSG, Error;
	MSG = "\n\nEscriba el nombre de la simulacion ( sin espacios y formato '.bin'): ";
	Error = "\nEl archivo de simulacion no se pudo guardar.";

	std::cout << MSG;
	std::cin >> Fichero;

	// Abrimos archivo de simulacion.
	std::ofstream outfile(Fichero, std::ios::binary);

	if (!outfile) {
		std::cout << Error;
		return false;
	}

	// Guardamos los datos en el archivo.
	for (const auto& row : POSICIONES) {
		for (const auto& element : row) {
			outfile << element;
		}
		Ciclo++;
	}

	outfile.close();

	std::cout << "\nDatos guardados en el archivo " + Fichero + ".\n";
	system("pause");

	return true;
}



// CARGAR SIMULACION
bool Cargar_Simulacion() {

	std::string Fichero, MSG, Error;
	MSG = "\n\nEscriba el nombre de la simulacion ( sin espacios y formato '.bin'): ";
	Error = "\nEl archivo de simulacion no se puede abrir o no existe.";

	int Ciclo = 0;

	std::cout << MSG;
	std::cin >> Fichero;

	// Abrimos el fichero.
	std::ifstream infile(Fichero, std::ios::binary);

	if (!infile) {
		std::cout << Error;
		return false;
	}

	// Cargamos lo datos desde el fichero.
	for (const auto& row : POSICIONES) {
		for (const auto& element : row) {
			infile >> element;
		}
		Ciclo++;
	}

	infile.close();

	std::cout << "\nDatos cargados desde el archivo " + Fichero + ".\n";
	system("pause");

	return true;
}



// MENU
void Menu() {
	std::string Texto, Respuesta, ErrorI, ErrorO;

	Texto = "Que desea hacer?:";
	Texto += "\n1 - Cargar Simulacion.";
	Texto += "\n2 - Nueva Simulacion.";
	Texto += "\n3 - Guardar Simulacion.";
	Texto += "\n4 - Salir.";
	Texto += "\nEscriba su respuesta: ";

INICIO:
	system("cls");

	//std::getline(std::cin, Texto);			// para capturar linea completa (hasta '\n')

	std::cout << Texto;
	std::cin >> Respuesta;						// captura solo una palabra (hasta espacio)

	// Opciones de Menu CARGAR
	if (Respuesta == "1") {
		if (Cargar_Simulacion()) {
			CicloActual = 0;
		}
		else {
			goto INICIO;
		}
	}

	// Opciones de Menu NUEVA SIMULACION
	if (Respuesta == "2") {

		system("cls");

		if (Posiciones_Iniciales()) {

			Ciclo = 0;					// Para simulacion

			if (Gravity()) {
				CicloActual = 0;		// para dibujado
			}
			else {
				goto INICIO;
			}
		}
		else {
			goto INICIO;
		}
	}

	// Opciones de Menu GUARDAR SIMULACION
	if (Respuesta == "3") {
		Guardar_Simulacion();
		goto INICIO;
	}

	// Opciones de Menu SALIR
	if (Respuesta == "4") {
		exit(0);
	}

	// Opcion incorrecta.
	if (!(Respuesta == "1") && !(Respuesta == "2") && !(Respuesta == "3") && !(Respuesta == "4")) {
		std::cout << "\nNo se reconoce el comando.\n";
		system("pause");

		goto INICIO;		// Empezamos de nuevo.
	}
}


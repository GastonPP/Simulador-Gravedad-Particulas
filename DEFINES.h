#pragma once

// NAMESPACES
using std::cout;
using std::endl;


// CONSTANTES
const short RESOLUCION_X = 800;
const short RESOLUCION_Y = 600;

const double PI_ = 3.1415;

// VARIABLES
HANDLE hConsole;
COORD pos;

// TECLADO
bool Teclado_[14];


// MACROS
// Devuelve la coordenada Y+ de un circulo definido por (Y1, X1), radio R_ y el valor de X_ indicado.
#define CIRCULO1(X1,Y1,R_,X_)		 Y1 + sqrt( pow(R_,2.0) - pow((X_ - X1),2.0))

// Devuelve la coordenada Y- de un circulo definido por (Y1, X1), radio R_ y el valor de X_ indicado.
#define CIRCULO2(X1,Y1,R_,X_)		 Y1 - sqrt( pow(R_,2.0) - pow((X_ - X1),2.0))


// ENUMS
enum ENUM_KEYBOARD {
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_E,
	KEY_Q,
	KEY_Y,
	KEY_H,
	KEY_G,
	KEY_J,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
};

enum ENUM_MOUSE {
	BTN_IZQ,
	BTN_DER,
	MOUSE_X = 0,
	MOUSE_Y
};

enum DIR_MOVIMIENTO {
	DERECHA,
	IZQUIERDA,
	ARRIBA,
	ABAJO,
	ADELANTE,
	ATRAS,
	HOR_DERECHA,
	HOR_IZQUIERDA,
	PRO_ARRIBA,
	PRO_ABAJO,
	PRO_IZQUIERDA,
	PRO_DERECHA,
	MOUSE_DERECHO
};


// ESTRUCTURAS
struct STRUCT_MOUSE {
	int POSICION[2];
	int RELATIVO[2];
	bool BOTONES[2];
}MOUSE_;

struct STRUCT_ROTACION {
	double X_;
	double Y_;
	double Z_;

	STRUCT_ROTACION() : X_(0.0), Y_(0.0), Z_(0.0) {}
};

struct STRUCT_TRASLACION {
	double X_;
	double Y_;
	double Z_;

	STRUCT_TRASLACION() : X_(0.0), Y_(0.0), Z_(0.0) {}
};

struct Coor3f {
	float X_;
	float Y_;
	float Z_;

	Coor3f() : X_(0.0f), Y_(0.0f), Z_(0.0f) {}
	Coor3f(float x, float y, float z) : X_(x), Y_(y), Z_(z) {}
};

struct Coor3d {
	double X_;
	double Y_;
	double Z_;

	Coor3d() : X_(0.0f), Y_(0.0f), Z_(0.0f) {}
	Coor3d(double x, double y, double z) : X_(x), Y_(y), Z_(z) {}
};


// DECLARACION DE FUNCIONES
void Dibujar_Grilla(double);


/*
------------------------------------------------------------------------------------------------------------------------
--										F U N C I O N E S   U T I L E S												  --
------------------------------------------------------------------------------------------------------------------------
*/

// Pasamos Angulo, devuelve Radiales
double Rad_(double Angulo_) {

	return (Angulo_ * (PI_ / 180));
}

// Pasamos Radiales, devuelve Angulo.
double Ang_(double Radianes_) {

	return (Radianes_ / (PI_ / 180));
}

// Seno para angulos (no radiales)
double sin_(double Angulo) {

	return sin(Rad_(Angulo));
}

// Coseno para angulos (no radiales)
double cos_(double Angulo) {

	return cos(Rad_(Angulo));
}

// Limite de angulo entre 0° y 360°
double Lim_Ang(double Angulo) {

	if (Angulo > 360.0) { Angulo = 0.0; }
	if (Angulo < 0.0) { Angulo = 360.0; }

	return Angulo;
}

// Funcion Esfera. calculamos cada posicion de la esfera de 
// radio R_, pasando los angulos de X° e Y°
Coor3d Esfera(double R_, double AngX, double AngY) {
	Coor3d Temp;


	Temp.X_ = cos_(AngY) * R_ * cos_(AngX);
	Temp.Y_ = sin_(AngY) * R_ * cos_(AngX);
	Temp.Z_ = sin_(AngX) * R_;

	return Temp;
}

// Funcion Circulo. Calculamos la coordenada X,Z  por el 
// angulo y el radio dados. La altura es el valor de Y
// donde se dibujara.
Coor3d Circulo(double Radio, double Angulo, double Altura) {
	Coor3d Temp;

	Temp.X_ = sin_(Angulo) * Radio;
	Temp.Y_ = Altura;
	Temp.Z_ = cos_(Angulo) * Radio;

	return Temp;
}
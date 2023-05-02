#pragma once


/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*************************								CONSTANTES Y DEFINICIONES							**********************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/

// CONF INICIAL PARTICULAS
const int NUM_PARTICLES = 100;
const int NUM_CICLOS = 5000;

const float RADIO_MIN = 0.3f;
const int MASSMAX = 10;

// CONSTANTE GRAVITACIONAL
const float GRAVITATIONAL_CONSTANT = 0.0003;

// DISTANCIA POSICIONES INICIALES
const int POSINIMAX_X = 10;
const int POSINIMAX_Y = 10;
const int POSINIMAX_Z = 10;

// VELOCIDAD INICIAL
const int VELINI = 20;
const float VELINI_X = 10000.0f;			// VELINI / VELINI_X	mas grande, menos velocidad
const float VELINI_Y = 10000.0f;			// VELINI / VELINI_Y	mas grande, menos velocidad
const float VELINI_Z = 10000.0f;			// VELINI / VELINI_Z	mas grande, menos velocidad

// Para el dibujado
unsigned int CicloActual;
unsigned int DIBUJADO_FPS = 1;

// Para Simulacion
unsigned int Ciclo = 0;

/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*************************								D E C L A R A C I O N E S							**********************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/



/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*************************									C L A S E S										**********************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/


// Clase Vector3D para representar vectores en 3D
class Vector3D {
public:
	float x, y, z;

	// Constructor por defecto
	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}

	// Constructor que recibe las componentes x, y, z
	Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	void Guardar(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }

	// Sobrecarga del operador de asignación
	Vector3D& operator=(const Vector3D& vec) {
		x = vec.x; y = vec.y; z = vec.z;
		return *this;
	}

	// Operador suma de vectores
	Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	// Operador resta de vectores
	Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	// Operador multiplicación escalar de vectores
	Vector3D operator*(float s) const {

		return Vector3D(x * s, y * s, z * s);
	}

	// Operador división escalar de vectores
	Vector3D operator/(float s) const {

		if (s == 0.0f)
			return Vector3D(.0f, .0f, .0f);

		return Vector3D(x / s, y / s, z / s);
	}

	// Producto punto de vectores
	float dot(const Vector3D& v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	// Producto cruz de vectores
	Vector3D cross(const Vector3D& v) const {
		return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	// Magnitud del vector
	float magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// Normalización del vector
	Vector3D normalize() const {

		float m = magnitude();

		if (m == 0.0f) {
			return Vector3D();
		}
		else {
			return (*this) / m;
		}
	}
};


// Clase Particula que almacena la masa, posición y velocidad de una partícula
class clsPARTICULA {
public:
	float Mass;
	Vector3D Pos;
	Vector3D Vel;

	// si esta activo, sigue calculando
	bool Activo;					

	// indicamos si se fuciona con otra particula. Solo las particulas
	// que se desactivan guardan este valor.
	int Fusion;						

	// CONSTRUCTOR
	clsPARTICULA() : Mass(1.0f), Activo(true), Fusion(-1) {}
	
	// FUNCIONES
	void Set_Mass(float Mass_) { Mass_ < 1.0f ? Mass = 1.0f : Mass = Mass_;  }
	void Set_Fusion(int Part) { Part < 0 ? Fusion = -1 : Fusion = Part; }

	// SOBRECARGAS
	// Sobrecarga del operador de asignación
	clsPARTICULA& operator=(const clsPARTICULA& P) {
		Pos = P.Pos; Vel = P.Vel; Mass = P.Mass;
		Activo = P.Activo; Fusion = P.Fusion;

		return *this;
	}
};


// Clase Posiciones para almacenar todas las posiciones de las particulas
// en cada ciclo.
class clsPOSICIONES {
public:
	Vector3D Pos;
	bool Activo;

	clsPOSICIONES() : Activo(false) {}
};

// FICHEROS DE TEXTO
//// OPERADOR SOBRECARGADO >>: ifstream & clsPOSICIONES
//std::ifstream& operator>>(std::ifstream& in, clsPOSICIONES Vec) {
//	char Sep;
//
//	in >> Vec.Pos.x >> Sep >> Vec.Pos.y >> Sep >> Vec.Pos.z >> Sep >> Vec.Activo >> Sep;
//
//	return in;
//}
//
//// OPERADOR SOBRECARGADO <<: ofstream & clsPOSICIONES
//std::ofstream& operator<<(std::ofstream& os, clsPOSICIONES Vec)
//{
//	char Sep = ';', End = '\n';
//
//	os << Vec.Pos.x << Sep << Vec.Pos.y << Sep << Vec.Pos.z << Sep << Vec.Activo << End;
//
//	return os;
//}

// OPERADOR SOBRECARGADO >>: ifstream & clsPOSICIONES (ifstream BINARIOS)
std::ifstream& operator>>(std::ifstream& in, clsPOSICIONES Vec) {
	
	in.read(reinterpret_cast<char*>(&Vec.Pos.x), sizeof(float));
	in.read(reinterpret_cast<char*>(&Vec.Pos.y), sizeof(float));
	in.read(reinterpret_cast<char*>(&Vec.Pos.z), sizeof(float));
	in.read(reinterpret_cast<char*>(&Vec.Activo), sizeof(bool));

	return in;
}

// OPERADOR SOBRECARGADO <<: ofstream & clsPOSICIONES  (ofstream BINARIOS)
std::ofstream& operator<<(std::ofstream& os, clsPOSICIONES Vec) {

	os.write(reinterpret_cast<char*>(&Vec.Pos.x), sizeof(float));
	os.write(reinterpret_cast<char*>(&Vec.Pos.y), sizeof(float));
	os.write(reinterpret_cast<char*>(&Vec.Pos.z), sizeof(float));
	os.write(reinterpret_cast<char*>(&Vec.Activo), sizeof(bool));

	return os;
}


/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*************************									VARIABLES GLOBALES								**********************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/

// donde almacenamos los estados de cada ciclo
clsPARTICULA ESTADO_INI[NUM_PARTICLES];
clsPARTICULA ESTADO_FIN[NUM_PARTICLES];

clsPOSICIONES POSICIONES[NUM_CICLOS][NUM_PARTICLES];
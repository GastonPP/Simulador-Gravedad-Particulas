#pragma once

// La idea de esta clase es que basandose en la posicion
// de la camara, en radio definido del objetivo y el angulo
// de los planos XZ e YZ, nos calcule el objetivo de la
// camara. De manera que podamos movernos con la camara de
// la misma manera que en los juegos de primera persona.
class CLS_CAMARA {
	private:
		double VAR_ANG_ROTACION;
		double RADIO_TRASLACION;

		// Estado de los angulos X°, Y°, Z°
		STRUCT_ROTACION		ANG_ROTACION;

		// Estado posiciones de rotacion y traslacion
		STRUCT_ROTACION		ROTACION;
		STRUCT_TRASLACION	TRASLACION;

	private:
		void Movimiento(DIR_MOVIMIENTO);
		void Rotacion();
		void Traslacion(DIR_MOVIMIENTO);

	public:
		void Movimiento_Camara();
		void Reset();

		Coor3d Get_Rotacion();
		Coor3d Get_Traslacion();
		Coor3d Get_Angulos();

		// CONSTRUCTOR
		CLS_CAMARA();
} Camara;


// CONSTRUCTOR
CLS_CAMARA::CLS_CAMARA()  {
	VAR_ANG_ROTACION = 1.0;
	RADIO_TRASLACION = 0.12;

	ROTACION.X_ = 1.0;
	ROTACION.Y_ = 0.0;
	ROTACION.Z_ = 0.0;

	ANG_ROTACION.X_ = 0.0;
	ANG_ROTACION.Y_ = 0.0;
	ANG_ROTACION.Z_ = 0.0;

	TRASLACION.X_ = 0.0;
	TRASLACION.Y_ = 0.0;
	TRASLACION.Z_ = 0.0;
}


// RESET
void CLS_CAMARA::Reset() {
	ANG_ROTACION.X_ = 0.0;
	ANG_ROTACION.Y_ = 0.0;
	ANG_ROTACION.Z_ = 0.0;

	TRASLACION.X_ = 0.0;
	TRASLACION.Y_ = 0.0;
	TRASLACION.Z_ = 0.0;

	ROTACION.X_ = 1.0;
	ROTACION.Y_ = 0.0;
	ROTACION.Z_ = 0.0;
}


// MOVIMIENTOS DE LA CAMARA
// Con esta funcion recuperamos los estados del
// teclado y mouse y realizamos las acciones
// correspondientes.
void  CLS_CAMARA::Movimiento_Camara() {

	// ANGULO DEL EJE Y
	if (Teclado_[KEY_A]) {
		Movimiento(IZQUIERDA);
	}

	if (Teclado_[KEY_D]) {
		Movimiento(DERECHA);
	}

	// ANGULO DEL EJE X
	if (Teclado_[KEY_W]) {
		Movimiento(ARRIBA);
	}

	if (Teclado_[KEY_S]) {
		Movimiento(ABAJO);
	}

	// MOVIMIENTOS ADELANTE, ATRAS, Y LATERALES
	if (Teclado_[KEY_UP]) {
		Movimiento(ADELANTE);
	}

	if (Teclado_[KEY_DOWN]) {
		Movimiento(ATRAS);
	}

	// MOVIMIENTO LATERAL
	if (Teclado_[KEY_LEFT]) {
		Movimiento(HOR_IZQUIERDA);
	}

	if (Teclado_[KEY_RIGHT]) {
		Movimiento(HOR_DERECHA);
	}

	// ACELERACION CAMARA: Traslacion
	if (Teclado_[KEY_E]) {
		if (RADIO_TRASLACION < 2.0)
			RADIO_TRASLACION += RADIO_TRASLACION * 0.02;
	}
	if (Teclado_[KEY_Q]) {
		if (RADIO_TRASLACION > 0.02)
			RADIO_TRASLACION -= RADIO_TRASLACION * 0.01;
	}
	
	// MOUSE, con boton derecho apretado
	if (MOUSE_.BOTONES[BTN_DER]) {
		Movimiento(MOUSE_DERECHO);
	}
}


// Movimiento. Angulo de Camara, Rotacion y Traslacion
void CLS_CAMARA::Movimiento(DIR_MOVIMIENTO Mov) {

	double VAR_MOUSE_X, VAR_MOUSE_Y;

	VAR_MOUSE_X = (double(MOUSE_.RELATIVO[MOUSE_X]) / 500.0);
	VAR_MOUSE_Y = -(double(MOUSE_.RELATIVO[MOUSE_Y]) / 500.0);

	switch (Mov) {

			// MOVIMIENTO DE LA ROTACION DE CAMARA
		case DERECHA:
			ANG_ROTACION.Y_ += VAR_ANG_ROTACION;
			break;

		case IZQUIERDA:
			ANG_ROTACION.Y_ -= VAR_ANG_ROTACION;
			break;

		case ARRIBA:
			ANG_ROTACION.X_ += VAR_ANG_ROTACION;
			break;

		case ABAJO:
			ANG_ROTACION.X_ -= VAR_ANG_ROTACION;
			break;

		case MOUSE_DERECHO:
			ANG_ROTACION.Y_ += VAR_ANG_ROTACION * VAR_MOUSE_X;
			ANG_ROTACION.X_ += VAR_ANG_ROTACION * VAR_MOUSE_Y;
			break;
	}

	// lo limitamos de -90 a 90 (no da la vuelta)
	if (ANG_ROTACION.X_ > 90.0) { ANG_ROTACION.X_ = 90; }
	if (ANG_ROTACION.X_ < -90.0) { ANG_ROTACION.X_ = -90; }

	// Limitamos la ANG_ROTACION a 360°
	ANG_ROTACION.Y_ = Lim_Ang(ANG_ROTACION.Y_);
	ANG_ROTACION.Z_ = Lim_Ang(ANG_ROTACION.Z_);

	// IMPORTANTE: Primero nos trasladamos, luego
	// calculamos el objetivo, y no al revez.
	Traslacion(Mov);
	Rotacion();
}


// APLICAR ROTACION
void CLS_CAMARA::Rotacion() {

	// PLANO X, Y
	ROTACION.X_ = TRASLACION.X_ + cos_(ANG_ROTACION.Y_) * cos_(ANG_ROTACION.X_);
	ROTACION.Z_ = TRASLACION.Z_ + sin_(ANG_ROTACION.Y_) * cos_(ANG_ROTACION.X_);

	// ALTURA, EJE Y
	ROTACION.Y_ = TRASLACION.Y_ + sin_(ANG_ROTACION.X_);
}


// APLICAR TRASLACION
void CLS_CAMARA::Traslacion(DIR_MOVIMIENTO Mov) {

	switch (Mov) {

		case ADELANTE:
			TRASLACION.X_ += cos_(ANG_ROTACION.Y_) * RADIO_TRASLACION * cos_(ANG_ROTACION.X_);
			TRASLACION.Z_ += sin_(ANG_ROTACION.Y_) * RADIO_TRASLACION * cos_(ANG_ROTACION.X_);

			TRASLACION.Y_ += sin_(ANG_ROTACION.X_) * RADIO_TRASLACION;
			break;

		case ATRAS:
			TRASLACION.X_ -= cos_(ANG_ROTACION.Y_) * RADIO_TRASLACION * cos_(ANG_ROTACION.X_);
			TRASLACION.Z_ -= sin_(ANG_ROTACION.Y_) * RADIO_TRASLACION * cos_(ANG_ROTACION.X_);

			TRASLACION.Y_ -= sin_(ANG_ROTACION.X_) * RADIO_TRASLACION;
			break;

		// Nos trasladamos solo en el palo X, Z no afecta ni el angulo X° ni la trasl en Y
		case HOR_IZQUIERDA:
			TRASLACION.X_ += cos_(ANG_ROTACION.Y_ - 90.0) * RADIO_TRASLACION;
			TRASLACION.Z_ += sin_(ANG_ROTACION.Y_ - 90.0) * RADIO_TRASLACION;
			break;

		case HOR_DERECHA:
			TRASLACION.X_ += cos_(ANG_ROTACION.Y_ + 90.0) * RADIO_TRASLACION;
			TRASLACION.Z_ += sin_(ANG_ROTACION.Y_ + 90.0) * RADIO_TRASLACION;
			break;

	}
}


// Leer Posiciones de Rotacion
Coor3d CLS_CAMARA::Get_Rotacion() {
	Coor3d Temp;

	Temp.X_ = ROTACION.X_;
	Temp.Y_ = ROTACION.Y_;
	Temp.Z_ = ROTACION.Z_;

	return Temp;
}

// Leer Posiciones de Traslacion
Coor3d CLS_CAMARA::Get_Traslacion() {
	Coor3d Temp;

	Temp.X_ = TRASLACION.X_;
	Temp.Y_ = TRASLACION.Y_;
	Temp.Z_ = TRASLACION.Z_;

	return Temp;
}

// Leer valores de los Angulos
Coor3d CLS_CAMARA::Get_Angulos() {
	Coor3d Temp;

	Temp.X_ = ANG_ROTACION.X_;
	Temp.Y_ = ANG_ROTACION.Y_;
	Temp.Z_ = ANG_ROTACION.Z_;

	return Temp;
}








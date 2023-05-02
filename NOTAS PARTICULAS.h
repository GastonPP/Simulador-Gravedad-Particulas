#pragma once

/*

La combinaci�n de dos part�culas con distancia cero implica la fusi�n de las dos part�culas en una sola part�cula.
Para realizar esto en C++, se pueden seguir los siguientes pasos:

	Seleccionar una de las dos part�culas para ser la "part�cula combinada". En general, la elecci�n de la part�cula combinada
	depender� de las propiedades f�sicas de las part�culas y de las condiciones espec�ficas del problema.

	Sumar las masas de las dos part�culas y promediar sus velocidades y posiciones para obtener las propiedades de la
	nueva part�cula combinada. Por ejemplo, si las part�culas tienen masas m1 y m2 y velocidades v1 y v2, y est�n ubicadas
	en las posiciones x1 y x2, entonces la masa y la velocidad de la part�cula combinada ser�an:

	m_combinada = m1 + m2

	v_combinada = (m1v1 + m2v2) / (m1 + m2)

	x_combinada = (x1 + x2) / 2

	Eliminar las part�culas originales del vector que las contiene. Por ejemplo, si las part�culas se almacenan en un
	vector llamado "particulas", se pueden eliminar usando el m�todo "erase" de la siguiente manera:

	particulas.erase(particulas.begin() + indice_particula1);

	particulas.erase(particulas.begin() + indice_particula2 - 1);

	donde "indice_particula1" e "indice_particula2" son los �ndices de las part�culas seleccionadas en el vector "particulas".

	Agregar la nueva part�cula combinada al vector "particulas". Por ejemplo, si la nueva part�cula se llama
	"particula_combinada", se puede agregar al vector "particulas" de la siguiente manera:

	particulas.push_back(particula_combinada);

Es importante tener en cuenta que la combinaci�n de part�culas con distancia cero puede presentar algunos desaf�os adicionales
en t�rminos de la conservaci�n de la energ�a y el momento. Por lo tanto, es importante verificar que la combinaci�n de las
part�culas no afecte negativamente la precisi�n y estabilidad de la simulaci�n.

*/



/*

S�, se puede aplicar la Segunda Ley de Newton al ejemplo para calcular la aceleraci�n de cada part�cula a partir
de la fuerza gravitacional que experimenta. La Segunda Ley de Newton establece que la aceleraci�n de una part�cula
es proporcional a la fuerza neta que act�a sobre ella, y se relaciona mediante la siguiente ecuaci�n:

	F = m * a

donde F es la fuerza neta que act�a sobre la part�cula, m es su masa y a es su aceleraci�n.

En el ejemplo de atracci�n gravitatoria entre dos part�culas, se puede aplicar la Segunda Ley de Newton para calcular
la aceleraci�n de cada part�cula a partir de la fuerza gravitacional que experimenta debido a la otra part�cula.
Por ejemplo, para la primera part�cula, se tendr�a:

	F = G * m1 * m2 * (p2 - p1) / |p2 - p1|^3

donde p1 y p2 son los vectores de posici�n de las dos part�culas, y |p2 - p1| es la distancia euclidiana entre ellas.
Entonces, la aceleraci�n de la primera part�cula ser�a:

	a1 = F / m1

donde m1 es la masa de la primera part�cula.

De manera similar, se podr�a calcular la aceleraci�n de la segunda part�cula a partir de la fuerza gravitacional que
experimenta debido a la primera part�cula.

Con las aceleraciones calculadas, se puede actualizar la velocidad y posici�n de cada part�cula en cada paso de la
simulaci�n, utilizando los m�todos num�ricos adecuados (por ejemplo, el m�todo de Euler o el m�todo de Verlet).

�Qu� dice la segunda ley de Newton y ejemplos?
�La aceleraci�n de un objeto es directamente proporcional a la fuerza que act�a sobre �l e inversamente proporcional
a la masa�. Eso significa que para que un objeto se mueva r�pidamente debes aplicarle mucha fuerza, pero tambi�n,
que la rapidez con la que se mueve el objeto depende de qu� tan liviano o pesado es.

*/
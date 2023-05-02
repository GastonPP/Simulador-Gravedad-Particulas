#pragma once

/*

La combinación de dos partículas con distancia cero implica la fusión de las dos partículas en una sola partícula.
Para realizar esto en C++, se pueden seguir los siguientes pasos:

	Seleccionar una de las dos partículas para ser la "partícula combinada". En general, la elección de la partícula combinada
	dependerá de las propiedades físicas de las partículas y de las condiciones específicas del problema.

	Sumar las masas de las dos partículas y promediar sus velocidades y posiciones para obtener las propiedades de la
	nueva partícula combinada. Por ejemplo, si las partículas tienen masas m1 y m2 y velocidades v1 y v2, y están ubicadas
	en las posiciones x1 y x2, entonces la masa y la velocidad de la partícula combinada serían:

	m_combinada = m1 + m2

	v_combinada = (m1v1 + m2v2) / (m1 + m2)

	x_combinada = (x1 + x2) / 2

	Eliminar las partículas originales del vector que las contiene. Por ejemplo, si las partículas se almacenan en un
	vector llamado "particulas", se pueden eliminar usando el método "erase" de la siguiente manera:

	particulas.erase(particulas.begin() + indice_particula1);

	particulas.erase(particulas.begin() + indice_particula2 - 1);

	donde "indice_particula1" e "indice_particula2" son los índices de las partículas seleccionadas en el vector "particulas".

	Agregar la nueva partícula combinada al vector "particulas". Por ejemplo, si la nueva partícula se llama
	"particula_combinada", se puede agregar al vector "particulas" de la siguiente manera:

	particulas.push_back(particula_combinada);

Es importante tener en cuenta que la combinación de partículas con distancia cero puede presentar algunos desafíos adicionales
en términos de la conservación de la energía y el momento. Por lo tanto, es importante verificar que la combinación de las
partículas no afecte negativamente la precisión y estabilidad de la simulación.

*/



/*

Sí, se puede aplicar la Segunda Ley de Newton al ejemplo para calcular la aceleración de cada partícula a partir
de la fuerza gravitacional que experimenta. La Segunda Ley de Newton establece que la aceleración de una partícula
es proporcional a la fuerza neta que actúa sobre ella, y se relaciona mediante la siguiente ecuación:

	F = m * a

donde F es la fuerza neta que actúa sobre la partícula, m es su masa y a es su aceleración.

En el ejemplo de atracción gravitatoria entre dos partículas, se puede aplicar la Segunda Ley de Newton para calcular
la aceleración de cada partícula a partir de la fuerza gravitacional que experimenta debido a la otra partícula.
Por ejemplo, para la primera partícula, se tendría:

	F = G * m1 * m2 * (p2 - p1) / |p2 - p1|^3

donde p1 y p2 son los vectores de posición de las dos partículas, y |p2 - p1| es la distancia euclidiana entre ellas.
Entonces, la aceleración de la primera partícula sería:

	a1 = F / m1

donde m1 es la masa de la primera partícula.

De manera similar, se podría calcular la aceleración de la segunda partícula a partir de la fuerza gravitacional que
experimenta debido a la primera partícula.

Con las aceleraciones calculadas, se puede actualizar la velocidad y posición de cada partícula en cada paso de la
simulación, utilizando los métodos numéricos adecuados (por ejemplo, el método de Euler o el método de Verlet).

¿Qué dice la segunda ley de Newton y ejemplos?
“La aceleración de un objeto es directamente proporcional a la fuerza que actúa sobre él e inversamente proporcional
a la masa”. Eso significa que para que un objeto se mueva rápidamente debes aplicarle mucha fuerza, pero también,
que la rapidez con la que se mueve el objeto depende de qué tan liviano o pesado es.

*/
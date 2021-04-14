#include "Random.h"
#include<cstdlib>
#include<ctime>

int arr[15] = { 0 };

int Random::GetValor() {
	if (indice < 15) {
		valor = arr[indice];
		indice++;
	}
	if (indice == 15)
		indice = 0;

	return valor;
};

Random::Random() {
	srand(time(NULL));

	for (int i = 0; i < 15; i++) {
		int random = rand() % 3 - 0;
		arr[i] = random;
	}
	indice = 0;
};



#include <stdio.h>

typedef struct {
	char nume[20]; //20 de caractere maxim
	char cod[4]; //4 numere - eventual, validare
	enum {A=1, B=2, M=3} categorie;
	char um[2]; //2 caractere - unitate de masura (ex: kg)
	double cant; //cantitate - numar real
	double pret; //pretul per unitate - numar real
	// nu ma intereseaza aici magazia in care se situeaza, intrucat materialul se afla in lista unei magazii
} Material;

typedef struct {
	Material* lista_materiale;
} Magazie;

Magazie A, B, M; //cele trei magazii



int main() {

}
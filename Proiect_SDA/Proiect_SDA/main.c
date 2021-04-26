#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F1 "f1.txt"
#define F2 "f2.txt"

typedef struct Material {
	char nume[21]; //20 de caractere maxim; ultimul caracter - terminator de sir
	char cod[5]; //4 numere - eventual, validare; ultimul caracter - terminator de sir
	enum {A=1, B=2, M=3} categorie;
	char um[2]; //2 caractere - unitate de masura (ex: kg)
	double cant; //cantitate - numar real
	double pret; //pretul per unitate - numar real
	// nu ma intereseaza aici magazia in care se situeaza, intrucat materialul se afla in lista unei magazii
} Material;

typedef struct Magazie {
	Material material;
	struct Magazie* next;
} Magazie;

Magazie* _A, * _B, * _M; //cele trei magazii


Magazie* introducereMaterial(Magazie* mag, Material mat) {
	Magazie* q1, * q2, * aux;
	aux = (Magazie*)malloc(sizeof(Magazie));
	aux->material = mat;
	aux->next = NULL;	

	for (q1 = q2 = mag; q1 != NULL && strcmp(q1->material.nume, mat.nume) < 0; q2 = q1, q1 = q1->next); // metoda celor doi pointeri
	if (q1 != NULL && q1->material.cod == mat.cod) {
		return mag; // materialul exista deja in lista
	}
	else {
		if (q1 != q2) {
			q2->next = aux;
			aux->next = q1;
			return mag;
		}
		else {
			aux->next = mag;
			return aux;
		}
	}
}

void citireFisiere() {
	FILE* f1 = fopen(F1, "r");
	FILE* f2 = fopen(F2, "r");
	Material newMat;
	char buffer[100];

	while (!feof(f1)) {
		fgets(buffer, 100, f1);
		sscanf(buffer, "%s %s %d %s %lf %lf", newMat.nume, newMat.cod, &newMat.categorie, newMat.um,
			&newMat.cant, &newMat.pret);
		switch (newMat.categorie)
		{
		case A:
			_A = introducereMaterial(_A, newMat);
			break;
		case B:
			_B = introducereMaterial(_B, newMat);
			break;
		case M:
			_M = introducereMaterial(_M, newMat);
			break;
		default:
			printf("DATE DIN FISIER CORUPTE!\n");
			break;
		}
	}

	fclose(f1);
	fclose(f2);
}

void afisareMagazie(Magazie* mag) {
	Magazie* p;
	for (p = mag; p != NULL; p = p->next) {
		printf("%s\t%s\t%d\t%s\t%.2lf\t%.2lf\n", p->material.nume, p->material.cod, p->material.categorie, p->material.um,
			p->material.cant, p->material.pret);
	}
}


int main() {
	citireFisiere();
	afisareMagazie(_A);
	printf("\n");
	afisareMagazie(_B);
	printf("\n");
	afisareMagazie(_M);
}
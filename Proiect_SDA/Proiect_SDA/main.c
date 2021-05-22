#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define F1 "f1.txt"
#define F2 "f2.txt"
#define F_A "f_a.txt"
#define F_B "f_b.txt"
#define F_M "f_m.txt"

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


int existaMaterial(char cod[5]) {
	Magazie* p;
	for (p = _A; p != NULL; p = p->next) {
		if (strcmp(p->material.cod, cod) == 0)
			return 1;
	}
	for (p = _B; p != NULL; p = p->next) {
		if (strcmp(p->material.cod, cod) == 0)
			return 1;
	}
	for (p = _M; p != NULL; p = p->next) {
		if (strcmp(p->material.cod, cod) == 0)
			return 1;
	}

	return 0;
}
Magazie* introducereMaterial(Magazie* mag, Material mat) {
	Magazie* q1, * q2, * aux;
	aux = (Magazie*)malloc(sizeof(Magazie));
	aux->material = mat;
	aux->next = NULL;	

	for (q1 = q2 = mag; q1 != NULL && strcmp(q1->material.nume, mat.nume) < 0; q2 = q1, q1 = q1->next); // metoda celor doi pointeri
	if (q1 != NULL && strcmp(q1->material.cod, mat.cod)==0 || existaMaterial(mat.cod)) {
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

void _citireFisiere() {
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

	while (!feof(f2)) {
		fgets(buffer, 100, f2);
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

void afisareToateMagaziile() {
	printf("MAGAZIA A\n");
	afisareMagazie(_A);
	printf("\nMAGAZIA B\n");
	afisareMagazie(_B);
	printf("\nMAGAZIA M\n");
	afisareMagazie(_M);
	printf("\n");
}

void afisareMaterialeDupaNumeInMagazie(Magazie* mag, char nume[21]) {
	Magazie* p;
	char magChar = (mag == _A) ? 'A' : ((mag == _B) ? 'B' : 'M');
	for (p = mag; p != NULL; p = p->next) {
		if (strcmp(p->material.nume, nume) == 0) {
			printf("%s\t%s\t%d\t%s\t%.2lf\t%.2lf\t%c\n", p->material.nume, p->material.cod, p->material.categorie, p->material.um,
				p->material.cant, p->material.pret, magChar);
		}
	}
}

void afisareMaterialeDupaNume(char nume[21]) {
	afisareMaterialeDupaNumeInMagazie(_A, nume);
	afisareMaterialeDupaNumeInMagazie(_B, nume);
	afisareMaterialeDupaNumeInMagazie(_M, nume);	
}

void _afisareMag() {
	Magazie* mag;
	char buffer[100], nume[21];

	do {
		printf("Dati magazia (A, B sau M): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) != 1 || strchr("ABMabm", buffer[0]) == NULL);

	switch (*buffer) {
	case 'A':
	case 'a':
		mag = _A;
		break;
	case 'b':
	case 'B':
		mag = _B;
		break;
	case 'm':
	case 'M':
		mag = _M;
		break;
	default:
		return;
		break;
	}

	afisareMagazie(mag);
}

void _afisareMatNume() {
	char buffer[100], nume[21];
	Magazie* mag;
	do {
		printf("Dati nume (maxim 20 caractere): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) > 20 || strlen(buffer) == 0);
	strcpy(nume, buffer);

	do {
		printf("Dati magazie (A, B sau M): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) != 1 || strchr("ABMabm", *buffer)==NULL);

	switch (*buffer)
	{
	case 'a':
	case 'A':
		mag = _A;
		break;
	case 'b':
	case 'B':
		mag = _B;
		break;
	case 'm':
	case 'M':
		mag = _M;
		break;
	default:
		return;
		break;
	}

	afisareMaterialeDupaNumeInMagazie(mag, nume);
}

int isNumeric(char* s) { // pentru validare cod
	for (int i = 0; i < strlen(s); i++) {
		if (strchr("0123456789", s[i]) == NULL)
			return 0;
	}
	return 1;
}

Magazie* stergereMaterialDupaCod(Magazie* mag, char cod[5]) {
	Magazie* q1, * q2;
	for (q1 = q2 = mag; q1 != NULL && strcmp(q1->material.cod, cod) != 0; q2 = q1, q1 = q1->next); // metoda celor doi pointeri
	if (q1 != NULL && strcmp(q1->material.cod, cod)==0) { //daca s-a gasit nodul in lista
		if (q1 != q2) // daca nodul nu este la inceputul listei
			q2->next = q1->next;
		else // nodul apare la inceputul listei
			mag = mag->next;
		free(q1);
	}
	else {
		printf("Materialul nu exista");
	}
	return mag;
}

void _stergereMatCod() {
	char buffer[100];
	char cod[5];
	Magazie** mag;

	do {
		printf("Dati magazia: ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) != 1 || strchr("ABM", buffer[0]) == NULL);

	switch (*buffer) {
	case 'A':
		mag = &_A;
		break;
	case 'B':
		mag = &_B;
		break;
	case 'M':
		mag = &_M;
		break;
	default:
		return;
		break;
	}

	afisareMagazie(*mag);

	do {
		printf("Dati cod (4 cifre): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) > 4 && !isNumeric(buffer));
	strcpy(cod, buffer);

	*mag = stergereMaterialDupaCod(*mag, cod);
}

void _stergereMaterialeSubCantitate() {
	double cantLim;
	char buffer[100];
	printf("Dati cantitatea limita: ");
	fgets(buffer, 100, stdin);
	sscanf(buffer, "%lf", &cantLim);

	Magazie* p = _A;
	while (p != NULL) {
		if (p->material.cant < cantLim) {
			_A = stergereMaterialDupaCod(_A, p->material.cod);
			p = _A;
		}
		else {
			p = p->next;
		}
	}
}

void _introducereMaterialTastatura() {
	Material mat;
	char buffer[100];

	// nume
	do {
		printf("Dati nume (max 20 caractere): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) > 20);
	strcpy(mat.nume, buffer);
	
	// cod
	do {
		printf("Dati cod (4 cifre): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		if (existaMaterial(buffer)) {
			printf("Acest cod exista deja!\n");
			buffer[0] = 'E';
			continue;
		}
	} while (strlen(buffer) > 4 || !isNumeric(buffer));
	strcpy(mat.cod, buffer);
	
	// categorie
	do {
		printf("Dati categorie (1, 2 sau 3): ");
		fgets(buffer, 100, stdin);
		sscanf(buffer, "%d", &mat.categorie);
	} while (mat.categorie != A && mat.categorie != B && mat.categorie != M);

	// unitate de masura
	do {
		printf("Dati unitate de masura (2 caractere): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) > 2);
	strcpy(mat.um, buffer);

	// cantitate
	printf("Dati cantitate: ");
	fgets(buffer, 100, stdin);
	sscanf(buffer, "%lf", &mat.cant);

	// pret
	printf("Dati pret / unitate de masura: ");
	fgets(buffer, 100, stdin);
	sscanf(buffer, "%lf", &mat.pret);

	switch (mat.categorie)
	{
	case A:
		introducereMaterial(_A, mat);
		break;
	case B:
		introducereMaterial(_B, mat);
		break;
	case M:
		introducereMaterial(_M, mat);
		break;
	default:
		break;
	}
}

int cautareMaterialDupaCod(char cod[5], Material* mat, Magazie*** src) {
	int gasit = 0;
	Magazie* p;
	for (p = _A; p != NULL && !gasit; p = p->next) {
		if (strcmp(p->material.cod, cod) == 0) {
			*mat = p->material;
			gasit = 1;
			*src = &_A;
		}
	}
	for (p = _B; p != NULL && !gasit; p = p->next) {
		if (strcmp(p->material.cod, cod) == 0) {
			*mat = p->material;
			gasit = 1;
			*src = &_B;
		}
	}
	for (p = _M; p != NULL && !gasit; p = p->next) {
		if (strcmp(p->material.cod, cod) == 0) {
			*mat = p->material;
			gasit = 1;
			*src = &_M;
		}
	}

	return gasit;
}

void _mutareMaterialDupCod() {
	Magazie* p, ** src, ** dest;
	char cod[5], buffer[100];
	Material mat;
	do {
		printf("Dati cod (4 cifre): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) > 4 || strlen(buffer) <= 0 || !isNumeric(buffer));
	strcpy(cod, buffer);

	do {
		printf("Dati magazia destinatie (A, B sau M): ");
		fgets(buffer, 100, stdin);
		buffer[strlen(buffer) - 1] = '\0';
	} while (strlen(buffer) != 1 || strchr("ABM", buffer[0]) == NULL);

	switch (*buffer) {
	case 'A':
		dest = &_A;
		break;
	case 'B':
		dest = &_B;
		break;
	case 'M':
		dest = &_M;
		break;
	default:
		return;
		break;
	}	

	if (!cautareMaterialDupaCod(cod, &mat, &src)) {
		printf("Nu exista niciun material cu codul introdus!\n");
		return;
	}
	else if (*src == *dest) {
		printf("Materialul se afla deja in magazia aleasa!\n");
		return;
	}

	*src = stergereMaterialDupaCod(*src, cod);

	*dest = introducereMaterial(*dest, mat);
}

void salvareMagazie(Magazie* mag, char* fileName) {
	Magazie* p;
	FILE* fout = fopen(fileName, "w");

	for (p = mag; p != NULL; p = p->next) {
		fprintf(fout, "%s %s %d %s %.2lf %.2lf\n", p->material.nume, p->material.cod, p->material.categorie,
			p->material.um, p->material.cant, p->material.pret);
	}

	fclose(fout);
}

void _salvareMagazii() {
	salvareMagazie(_A, F_A);
	salvareMagazie(_B, F_B);
	salvareMagazie(_M, F_M);
}

double calculValoareMagazie(Magazie* mag) {
	if (mag == NULL) return 0;
	return mag->material.cant * mag->material.pret + calculValoareMagazie(mag->next);
}

void afisareValoareTotala() {
	double valA = calculValoareMagazie(_A);
	double valB = calculValoareMagazie(_B);
	double valM = calculValoareMagazie(_M);
	double valTot = valA + valB + valM;

	printf("Valoare totala magazia A: %.2lf\n", valA);
	printf("Valoare totala magazia B: %.2lf\n", valB);
	printf("Valoare totala magazia M: %.2lf\n", valM);
	printf("Valoare totala: %.2lf RON\n", valTot);
}


int main() {
	enum {Iesire, CitireFis, AfisareMag, AfisareMatNume, AfisareVal, StergereMat, 
	MutareMat, IntroducereMat, StergereMatCant, SalvareMagazii} opt;

	do {
		printf("1. Citire din fisiere\n");
		printf("2. Afisare materiale dintr-o magazie, ordonate alfabetic\n");
		printf("3. Afisare materiale dupa nume dintr-o magazie\n");
		printf("4. Calcul valoarea totala a materialelor din magazii\n");
		printf("5. Stergere material din evidenta\n");
		printf("6. Mutare material in alta magazie\n");
		printf("7. Introducere material de la tastatura\n");
		printf("8. Stergere materiale din A de cantitate sub limita\n");
		printf("9. Salvare magazii in fisiere\n");
		printf("0. Parasire program\n");
		printf("Opt = ");
		scanf("%d", &opt);
		getchar();
		printf("\n");

		switch (opt)
		{
		case Iesire:
			break;
		case CitireFis:
			_citireFisiere();
			break;
		case AfisareMag:
			_afisareMag();
			break;
		case AfisareMatNume:
			_afisareMatNume();
			break;
		case AfisareVal:
			afisareValoareTotala();
			break;
		case StergereMat:
			_stergereMatCod();
			break;
		case MutareMat:
			afisareToateMagaziile();
			_mutareMaterialDupCod();
			break;
		case IntroducereMat:
			_introducereMaterialTastatura();
			break;
		case StergereMatCant:
			_stergereMaterialeSubCantitate();
			break;
		case SalvareMagazii:
			_salvareMagazii();
			break;
		default:
			break;
		}
		printf("\n");
		
	} while (opt != Iesire);
}

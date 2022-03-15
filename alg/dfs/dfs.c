/*Pesquisa de profundidade primeiro*/
#include <stdio.h>
#include <string.h>

#define MAX 100

struct FL {
	char de[20];
	char para[20];
	int distancia;
	char ignora;
} voos[MAX];

int voos_n = 0; /*n de elementos do banco de dados*/
int stk_n = 0; /*n de elementos da pilha*/
int sol_n = 0; /*n de elementos da pilhade soluções*/

struct stack {
	char de[20];
	char para[20];
	int dist;
} stckbt[MAX], solucao[MAX];

void setup(void);
int rota(void);
void setvoo(char *de, char *para, int distca);
void push(char *de, char *para, int distca);
void pop(char *de, char *para, int *distca);
void voavel(char *de, char *para);
void solpush(char *de, char *para, int distca);
int encntr(char *de, char *algmlcl);
int combin(char *de, char *para);

void main(void) {
	system("chcp 65001");
	char de[20];
	char para[20];
	int d;
	
	printf("Algoritmo de Busca em Profundidade Primeiro (DFS)\n\n");
	printf("Cidades (nós):\n");
	printf("\tNew York \tChicago \tDenver\n");
	printf("\tToronto \tCalgary \tUrbana\n");
	printf("\tLos Angeles \tHouston\n");
	printf("Rotas (arestas):\n");
	setup();
	printf("De? ");
	gets(de);
	printf("Para? ");
	gets(para);
	
	do {
		voavel(de, para);
		d = rota();
		stk_n = 0;
	} while (d != 0);
	
	printf("A solução ótima é:\n\t");
	
	for (int i = 0; i < sol_n; i++) {
		printf("%s para ", solucao[i].de);
		d += solucao[i].dist;
	}
	
	printf("%s\n", para);
	printf("\tA distância é %dkm\n", d);
	
	system("pause");
}

void setup(void) {
	setvoo("New York", "Chicago", 1000);
	setvoo("Chicago", "Denver", 1000);
	setvoo("New York", "Toronto", 800);
	setvoo("New York", "Denver", 1900);
	setvoo("Toronto", "Calgary", 1500);
	setvoo("Toronto", "Los Angeles", 1800);
	setvoo("Toronto", "Chicago", 500);
	setvoo("Denver", "Urbana", 1000);
	setvoo("Denver", "Houston", 1500);
	setvoo("Houston", "Los Angeles", 1500);
	setvoo("Denver", "Los Angeles", 1000);
}

void setvoo(char *de, char *para, int distca) {
	if (voos_n < MAX) {
		strcpy(voos[voos_n].de, de);
		strcpy(voos[voos_n].para, para);
		voos[voos_n].distancia = distca;
		voos[voos_n].ignora = 0;
		printf("\tde %s para %s: %dkm\n", voos[voos_n].de,
			voos[voos_n].para, voos[voos_n].distancia);
		voos_n++;
	} else {
		printf("Banco de dados de vôo cheio\n");
	}	
}

int rota(void) {
	int d = 0;
	static int min_d = 32000;
	
	if (!stk_n) return 0;
	
	for (int i = 0; i < stk_n; i++) {
		d += stckbt[i].dist;		
	}
	
	if (d < min_d && d) {
		min_d = d;
		sol_n = 0;
		
		for (int i = 0; i < stk_n; i++) {
			solpush(stckbt[i].de, stckbt[i].para, stckbt[i].dist);
		}
	}
	
	return d;
}

int combin(char *de, char *para) {
	for (int i = 0; i < voos_n; i++) {
		if (!strcmp(voos[i].de, de) && !strcmp(voos[i].para, para)) {
			return voos[i].distancia;
		}
	}
	
	return 0;
}

int encntr(char *de, char *algmlcl) {
	for (int i = 0; i < voos_n; i++) {
		if (!strcmp(voos[i].de, de) && !voos[i].ignora) {
			strcpy(algmlcl, voos[i].para);
			voos[i].ignora = 1;
			return voos[i].distancia;
		}
	}
	
	return 0;
}

void voavel(char *de, char *para) {
	int d_p;
	int d_a;
	char algmlcl[20];
	
	if (d_p = combin(de, para)) {
		push(de, para, d_p);
		return;
	}
	
	if (d_a = encntr(de, algmlcl)) {
		push(de, para, d_a);
		voavel(algmlcl, para);
	} else if (stk_n > 0) {
		pop(de, para, &d_a);
		voavel(de, para);
	}
}

void push(char *de, char *para, int distca) {
	if (stk_n < MAX) {
		strcpy(stckbt[stk_n].de, de);
		strcpy(stckbt[stk_n].para, para);
		stckbt[stk_n].dist = distca;
		stk_n++;
	} else {
		printf("Pilha cheia\n");
	}
}

void pop(char *de, char *para, int *distca) {
	if (stk_n > 0) {
		stk_n--;
		strcpy(de, stckbt[stk_n].de);
		strcpy(para, stckbt[stk_n].para);
		*distca = stckbt[stk_n].dist;		
	} else {
		printf("Pilha vazia\n");
	}
}

void solpush(char *de, char *para, int distca) {
	if (sol_n < MAX) {
		strcpy(solucao[sol_n].de, de);
		strcpy(solucao[sol_n].para, para);
		solucao[sol_n].dist = distca;
		sol_n++;
	} else {
		printf("Pilha de menor distância cheia\n");
	}
}
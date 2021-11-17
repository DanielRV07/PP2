#include <stdio.h>
#include <stdlib.h>

#include "headerGrafosEquipos.h"

typedef struct NodoCola {

	int dato;
	int anterior;
	
	struct NodoCola * next;

} NodoCola;

typedef struct Cola {
	
	NodoCola * inicio;
	NodoCola * final;
	
} Cola;

NodoCola * crearNodoCola(int dato, int anterior) {
	
	NodoCola * nuevo;
	
	nuevo = (NodoCola*)malloc(sizeof(NodoCola));
	
	nuevo->dato = dato;
	nuevo->anterior = anterior;
	
	nuevo->next = NULL;
	
	return nuevo;
	
}

Cola * crearCola() {
	
	Cola * nuevo;
	
	nuevo = (Cola*)malloc(sizeof(Cola));
	
	nuevo->inicio = NULL;
	nuevo->final = NULL;
	
	return nuevo;
	
}

NodoCola * sacarDeCola(Cola *C) {
	
	NodoCola * nAux = C->inicio;
	
	C->inicio = nAux->next;
	
	return nAux;
	
}

void insertarEnCola(Cola *C, int dato, int anterior) {
	
	if(C->inicio == NULL) {
		C->inicio = crearNodoCola(dato, anterior);
		C->final = C->inicio;
		return;
	}
	C->final->next = crearNodoCola(dato, anterior);
	C->final = C->final->next;
	
}

void prepararVector(GrafoColaboradores *G, int arr[]) {
	
	int i;
	
	for (i = 0; i < G->size; i++) {
		arr[i] = -1;
	}
}

void insertarAdyacentesCola(AristaColaborador *nAux, Cola *C, int arr[], int origen) {
	
	while (nAux != NULL) {
		if(arr[nAux->posicion] == -1) {
			insertarEnCola(C, nAux->posicion, origen);
		}
		nAux = nAux->next;
	}
	
}

void imprimirArr(int arr[], int size) {
	
	int i;
	
	for (i = 0; i < size; i++) {
		printf("%d, ", arr[i]);
	}
	printf("\n");
}

void imprimirCola(Cola *C) {
	
	NodoCola *nAux = C->inicio;
	
	printf("\nUNA ITERACION\n");
	
	while (nAux != NULL) {
		
		printf("Anterior: %d\n", nAux->anterior);
		printf("Actual: %d\n\n", nAux->dato);
		
		nAux = nAux->next;
	}
	
}

void buscarCaminoColaboradores(GrafoColaboradores *G, char persona[124], char personaSecundaria[124]) {
	
	system("cls");
	
	int arrControl[G->size];
	
	prepararVector(G, arrControl);
	
	Cola *C = crearCola();
	
	int actual = buscarPosicionColaborador(G->array, G->size, persona);
	
	arrControl[actual] = actual;
	
	insertarAdyacentesCola(G->array[actual].cabezaAristas, C, arrControl, actual);
	
	while (C->inicio != NULL) {
		
		NodoCola *nColaAux = sacarDeCola(C);
		
		if (arrControl[nColaAux->dato] == -1) {
			arrControl[nColaAux->dato] = nColaAux->anterior;
		}
		
		actual = nColaAux->dato;
		insertarAdyacentesCola(G->array[actual].cabezaAristas, C, arrControl, actual);
		
	}
	
	int porBuscar = buscarPosicionColaborador(G->array, G->size, personaSecundaria);
	int inicial = buscarPosicionColaborador(G->array, G->size, persona);
	
	if (arrControl[porBuscar] == -1) {
		printf("Lo sentimos, usted no esta relacionado con el colaborador ingresado...\n");
		printf("Lamentablemente no existe una ruta para que la persona ingresada reciba su mensaje...\n");
		return;
	}
	
	if (arrControl[porBuscar] == 0) {
		printf("Usted esta conectado con la persona, iniciando sesion de chat...\n");
		return;
	}
	
	printf("Lo sentimos, usted no esta relacionado con el colaborador ingresado...\n");
	printf("Para que esta persona reciba su mensaje puede utilizar la siguiente ruta: \n\n");
	
	printf("LEER DE ABAJO HACIA ARRIBA!\n\n");
	
	printf("Final: %s\n\n", G->array[buscarPosicionColaborador(G->array, G->size, personaSecundaria)].info->nombre);
	
	while (arrControl[porBuscar] != inicial) {
		
		printf(" %c Nombre Intermediario: %s %s  \n", 24, G->array[arrControl[porBuscar]].info->nombre, G->array[arrControl[porBuscar]].info->apellidos);
		porBuscar = arrControl[porBuscar];
		
	}
	
	printf("\nInicio: %s\n\n", G->array[buscarPosicionColaborador(G->array, G->size, persona)].info->nombre);

}

void menuBuscarCaminoColaboradores(GrafoColaboradores *G) {
	
	system("cls");
	
	char persona1[1024];
	char persona2[1024];
	
	printf("BIENVENIDO AL CHAT ENTRE COLABORADORES\n\n");
	
	printf("Ingrese su cedula: ");
	gets(persona1);
	printf("Ingrese la cedula de la persona que desea contactar: ");
	gets(persona2);
	
	if (strcmp(persona1, persona2) == 0) {
		printf("\nNo se puede iniciar un chat con uno mismo...\n");
	}
	else if (buscarPosicionColaborador(G->array, G->size, persona1) == -1 || buscarPosicionColaborador(G->array, G->size, persona2) == -1) {
		printf("\nNo se encontro a una de las personas...\n");
	}
	else {
		buscarCaminoColaboradores(G, persona1, persona2);
	}
	printf("\nRegresando al <<Menu Principal>> ");
	system("pause");
	
}




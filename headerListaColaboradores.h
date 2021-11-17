#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000

typedef struct Colaborador{
	
	char cedula[1024];
	char nombre[1024];
	char apellidos[1024];
	char correo[1024];
	char rol[1024];
	char nacimiento[1024];
		
} Colaborador;

typedef struct NodoColaborador {
	
	Colaborador *info;
	
	struct NodoColaborador *next;
	
} NodoColaborador;

typedef struct ListaColaboradores{
	
	NodoColaborador *cabeza;

} ListaColaboradores;

ListaColaboradores * crearListaColaboradores() {
	
	ListaColaboradores *lista;
	lista = (ListaColaboradores*) malloc(sizeof(ListaColaboradores));
	lista->cabeza = NULL;
	
	return lista;
	
}

Colaborador * obtenerColaborador(ListaColaboradores *lista, char cedula[1024]) {
	
	NodoColaborador *nAux = lista->cabeza;
	
	while (nAux != NULL) {
		if (strcmp(nAux->info->cedula, cedula) == 0) {
			return nAux->info;
		}
		nAux = nAux->next;
	}
	return NULL;
}

void imprimirListaColaboradores(ListaColaboradores *lista) {
	
	system("cls");
	
	NodoColaborador *nAux = lista->cabeza;
	
	printf("Colaboradores Registrados: \n\n");
	
	while (nAux != NULL) {
		
		printf("Cedula: %s\n", nAux->info->cedula);
		printf("Nombre: %s\n", nAux->info->nombre);
		printf("Apellidos: %s\n", nAux->info->apellidos);
		printf("Correo: %s\n", nAux->info->correo);
		printf("Rol en la Organizacion: %s\n", nAux->info->rol);
		printf("Fecha de Nacimiento: %s\n", nAux->info->nacimiento);
		
		printf("\n");
		
		nAux = nAux->next;
		
	}
	
	system("pause");
	
}

void imprimirListaEquipos(NodoColaborador *nAux) {
	
	printf("\nCOLABORADORES EN EL EQUIPO: \n\n");
	
	while (nAux != NULL) {
		
		printf("Cedula: %s\n", nAux->info->cedula);
		printf("Nombre: %s\n", nAux->info->nombre);
		printf("Apellidos: %s\n", nAux->info->apellidos);
		printf("Correo: %s\n", nAux->info->correo);
		printf("Rol en la Organizacion: %s\n", nAux->info->rol);
		printf("Fecha de Nacimiento: %s\n", nAux->info->nacimiento);
		
		printf("\n");
		
		nAux = nAux->next;
		
	}
	
}

void eliminarColaborador(ListaColaboradores *lista, char cedula[1024]) {
	
	NodoColaborador *nAux = lista->cabeza;
	
	if(strcmp(nAux->info->cedula, cedula) == 0){
		lista->cabeza = nAux->next;
		return;
	}
	while(nAux->next != NULL){
		if(strcmp(nAux->next->info->cedula, cedula) == 0){
			nAux->next = nAux->next->next;
			return;
		}
		nAux = nAux->next;
	}
}




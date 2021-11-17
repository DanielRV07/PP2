#include <stdio.h>
#include <stdlib.h>

#include "headerGrafosColaboradores.h"

typedef struct AristaEquipo {
	
	char nombre[1024];
	
	int posicion;
	
	struct AristaEquipo * next;
	
} AristaEquipo;

typedef struct ListaAdyacenciaEquipos {
	
	char nombre[1024];
	char detalle[1024];
	
	NodoColaborador * cabezaColaboradores;
	AristaEquipo * cabezaAristas;
	
} ListaAdyacenciaEquipos;

typedef struct GrafoEquipos {
	
	int size;
	
	ListaAdyacenciaEquipos * array;
	
} GrafoEquipos;

AristaEquipo * crearAristaEquipo(char nombre[1024], int posicion) {
	
	AristaEquipo * nuevo;
	
	nuevo = (AristaEquipo*)malloc(sizeof(AristaEquipo));
	
	strcpy(nuevo->nombre, nombre);
	
	nuevo->posicion = posicion;
	
	nuevo->next = NULL;
	
	return nuevo;
	
}

GrafoEquipos * crearGrafoEquipos() {
	
	GrafoEquipos * nuevo;
	
	nuevo = (GrafoEquipos*)malloc(sizeof(GrafoEquipos));
	
	nuevo->array = (ListaAdyacenciaEquipos*)malloc(100 * sizeof(ListaAdyacenciaEquipos));
	
	int i;
	
	for (i= 0; i < 100; i++) {
		nuevo->array[i].cabezaColaboradores = NULL;
		nuevo->array[i].cabezaAristas = NULL;
	}
	
	nuevo->size = 0;

}

int existeColaboradorEquipo(NodoColaborador *nAux, char cedula[1024]) {
	
	while (nAux != NULL) {
		if (strcmp(nAux->info->cedula, cedula) == 0) {
			return 1;
		}
		nAux = nAux->next;
	}
	return 0;
}

int buscarPosicionEquipo(ListaAdyacenciaEquipos array[], int size, char nombre[1024]) {
	
	int i;
	
	for (i = 0; i < size; i++) {
		if (strcmp(array[i].nombre, nombre) == 0) {
			return i;
		}
	}
	return -1;
}

void agregarEquipo(GrafoEquipos * G, char nombre[1024], char detalle[1024]) {
	
	int size = G->size;
	int i;
	
	strcpy(G->array[size].nombre, nombre);
	strcpy(G->array[size].detalle, detalle);
	
	G->size++;
}

void relacionarEquipos(GrafoEquipos * G, char equipoPrimario[124], char equipoSecundario[124]) {
	
	int size = G->size;
	int i;
	
	ListaAdyacenciaEquipos *array = G->array;
	
	for (i = 0; i < size; i++) {
		if (strcmp(array[i].nombre, equipoPrimario) == 0) {
			break;
		}
	}
	
	int j = buscarPosicionEquipo(array, size, equipoSecundario);
	
	if (j >= 0 && i < size && size < 100) {
		
		AristaEquipo * nuevo = crearAristaEquipo(equipoSecundario, j);
		
		nuevo->next = array[i].cabezaAristas;
		array[i].cabezaAristas = nuevo;
		
		int k = buscarPosicionEquipo(array, size, equipoPrimario);
		
		AristaEquipo * nuevo2 = crearAristaEquipo(equipoPrimario, k);
		
		nuevo2->next = array[j].cabezaAristas;
		array[j].cabezaAristas = nuevo2;
		
	}
	
}

void imprimirAristasEquipos(AristaEquipo * nAux) {
	
	while (nAux != NULL) {
		printf("Equipo: %s #%d\n", nAux->nombre, nAux->posicion);
		nAux = nAux->next;
	}
}

void imprimirGrafoEquipos(GrafoEquipos * G) {
	
	system("cls");
	
	printf("LOS EQUIPOS REGISTRADOS ACTUALMENTE SON:\n\n");
	
	int size = G->size;
	int i;
	
	for (i = 0; i < size; i++) {
		printf("%d) %s\n", i, G->array[i].nombre);
		printf("\nDetalle: %s\n", G->array[i].detalle);
		printf("\nESTE EQUIPO SE RELACIONA CON: \n\n");
		imprimirAristasEquipos(G->array[i].cabezaAristas);
		imprimirListaEquipos(G->array[i].cabezaColaboradores);
		printf("\n------------------------------------\n");
	}
	
	system("pause");
	return;
	
}

void menuAgregarEquipo(GrafoEquipos * G) {
	
	system("cls");
	
	printf("MENU PARA CREAR EQUIPO\n\n");
	
	char nombre[1024];
	char detalle[1024];
	
	printf("Ingrese el nombre del Equipo: ");
	gets(nombre);
	printf("Ingrese detalle del Equipo: ");
	gets(detalle);
	
	if (buscarPosicionEquipo(G->array, G->size, nombre) == -1 && G->size < 100) {
		
		agregarEquipo(G, nombre, detalle);
		printf("\nEquipo creado correctamente! \n\n");
	}
	
	else {
		printf("Ya existe un equipo con ese nombre... \n\n");
	}
	
	printf("Regresando al <<Menu Principal>> ");
	system("pause");
	
}

void menuRelacionarEquipos(GrafoEquipos * G) {
	
	system("cls");
	
	printf("MENU PARA RELACIONAR EQUIPOS\n\n");
	
	char primerEquipo[1024];
	char segundoEquipo[1024];
	
	printf("Ingrese el nombre del primer Equipo: ");
	gets(primerEquipo);
	printf("Ingrese el nombre del segundo Equipo: ");
	gets(segundoEquipo);
	
	if (buscarPosicionEquipo(G->array, G->size, primerEquipo) != -1 && buscarPosicionEquipo(G->array, G->size, segundoEquipo) != -1) {
		
		int i = buscarPosicionEquipo(G->array, G->size, primerEquipo);
		
		AristaEquipo *nAux = G->array[i].cabezaAristas;
		
		while (nAux != NULL) {
			if (strcmp(nAux->nombre, segundoEquipo) == 0) {
				printf("\nLos equipos mencionados ya se encuentran conectados... \n\n");
				printf("Regresando al <<Menu Principal>> ");
				system("pause");
				return;
			}
			nAux = nAux->next;
		}
		
		relacionarEquipos(G, primerEquipo, segundoEquipo) ;
		printf("\nLos equipos fueron relacionados exitosamente! \n\n");
		printf("Regresando al <<Menu Principal>> ");
		system("pause");
		return;
		
	}
	
	printf("\nNo se encontro uno de los equipos... \n\n");
	printf("Regresando al <<Menu Principal>> ");
	system("pause");
	return;
	
}

void relacionarPersonasEquipo(GrafoEquipos *G, GrafoColaboradores *grafoColaboradores, char cedula[1024], char equipo[1024]) {
	
	int i = buscarPosicionEquipo(G->array, G->size, equipo);
	
	NodoColaborador *nAux = G->array[i].cabezaColaboradores;
	
	while (nAux != NULL) {
		if (colaboradorRelacionado(grafoColaboradores, cedula, nAux->info->cedula) == 0 && strcmp(cedula, nAux->info->cedula) != 0) {
			relacionarColaboradores(grafoColaboradores, cedula, nAux->info->cedula);
		}
		nAux = nAux->next;
	}
	
}

void agregarPeronaEquipo(GrafoEquipos *G, ListaColaboradores *lista, char equipo[1024], char cedula[1024], GrafoColaboradores *grafoColaboradores) {
	
	int i = buscarPosicionEquipo(G->array, G->size, equipo);
	
	NodoColaborador *nuevo = (NodoColaborador*)malloc(sizeof(NodoColaborador));
	
	nuevo->info = obtenerColaborador(lista, cedula);
	
	nuevo->next = G->array[i].cabezaColaboradores;
	G->array[i].cabezaColaboradores = nuevo;
	
	relacionarPersonasEquipo(G, grafoColaboradores, cedula, equipo);
	
}

void menuAgregarPersonaEquipo(GrafoEquipos * G, ListaColaboradores *lista,  GrafoColaboradores *grafoColaboradores) {
	
	system("cls");
	
	printf("MENU PARA AGREGAR UN COLABORADOR A UN EQUIPO\n\n");
	
	char cedula[1024];
	char equipo[1024];
	
	printf("Ingrese la cedula del colaborador: ");
	gets(cedula);
	printf("Ingrese el nombre del equipo: ");
	gets(equipo);
	
	int i = buscarPosicionEquipo(G->array, G->size, equipo);
	
	if (i == -1) {
		
		printf("\nNo se encontro el equipo... \n\n");
		printf("Regresando al <<Menu Principal>> ");
		system("pause");
		return;
		
	}
	
	if (obtenerColaborador(lista, cedula) != NULL && existeColaboradorEquipo(G->array[i].cabezaColaboradores, cedula) == 0) {
		
		NodoColaborador *nuevo = (NodoColaborador*)malloc(sizeof(NodoColaborador));
		
		nuevo->info = obtenerColaborador(lista, cedula);
		
		nuevo->next = G->array[i].cabezaColaboradores;
		G->array[i].cabezaColaboradores = nuevo;
		
		relacionarPersonasEquipo(G, grafoColaboradores, cedula, equipo);
		
		printf("\nSe registro el colaborador en el equipo... \n\n");
		printf("Regresando al <<Menu Principal>> ");
		system("pause");
		return;
	
	}
	
	printf("\nEl colaborador no ha sido registrado o ya fue agregado al equipo... \n\n");
	printf("Regresando al <<Menu Principal>> ");
	system("pause");
	return;
	
}

void menuEliminarColaborador(GrafoEquipos * G, ListaColaboradores *lista, GrafoColaboradores *gColaboradores) {
	
	system("cls");
	
	printf("MENU PARA ELIMINAR UN COLABORADOR\n\n");
	
	char cedula[1024];
	
	printf("Ingrese la cedula del colaborador: ");
	gets(cedula);
	
	eliminarColaborador(lista, cedula);
	eliminarColaboradorGrafo(gColaboradores, cedula);
	
	int size = G->size;
	int i;
	
	for (i = 0; i < size; i++) {
		
		if (G->array[i].cabezaColaboradores != NULL) {
	
			if (strcmp(G->array[i].cabezaColaboradores->info->cedula, cedula) == 0) {
				G->array[i].cabezaColaboradores = G->array[i].cabezaColaboradores->next;
			}
			
			else {
				
				NodoColaborador *nAux = G->array[i].cabezaColaboradores;
			
				while(nAux->next != NULL){
					if(strcmp(nAux->next->info->cedula, cedula) == 0){
						nAux->next = nAux->next->next;
						break;
					}
					nAux = nAux->next;
				}
			}
		}	
	}
	
	printf("\nEl colaborador se ha eliminado correctamente... \n\n");
	printf("Regresando al <<Menu Principal>> ");
	system("pause");
	return;
	
}


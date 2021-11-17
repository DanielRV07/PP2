#include <stdio.h>
#include <stdlib.h>

#include "headerListaColaboradores.h"

typedef struct AristaColaborador {
	
	char cedula[1024];
	
	int posicion;
	
	struct AristaColaborador * next;
	
} AristaColaborador;

typedef struct ListaAdyacenciaColaboradores {
	
	Colaborador * info;
	
	AristaColaborador * cabezaAristas;
	
} ListaAdyacenciaColaboradores;

typedef struct GrafoColaboradores {
	
	int size;
	
	ListaAdyacenciaColaboradores * array;
	
} GrafoColaboradores;


AristaColaborador * crearAristaColaborador(char cedula[1024], int posicion) {
	
	AristaColaborador * nuevo;
	
	nuevo = (AristaColaborador*)malloc(sizeof(AristaColaborador));
	
	strcpy(nuevo->cedula, cedula);
	
	nuevo->posicion = posicion;
	
	nuevo->next = NULL;
	
	return nuevo;
	
}

GrafoColaboradores * crearGrafoColaboradores() {
	
	GrafoColaboradores * nuevo;
	
	nuevo = (GrafoColaboradores*)malloc(sizeof(GrafoColaboradores));
	
	nuevo->array = (ListaAdyacenciaColaboradores*)malloc(10000 * sizeof(ListaAdyacenciaColaboradores));
	
	int i;
	
	for (i= 0; i < 100; i++) {
		nuevo->array[i].info = NULL;
		nuevo->array[i].cabezaAristas = NULL;
	}
	
	nuevo->size = 0;

}

int buscarPosicionColaborador(ListaAdyacenciaColaboradores array[], int size, char cedula[1024]) {
	
	int i;
	
	for (i = 0; i < size; i++) {
		if (strcmp(array[i].info->cedula, cedula) == 0) {
			return i;
		}
	}
	return -1;
}

int colaboradorRelacionado(GrafoColaboradores *G, char cedula1[1024], char cedula2[1024]) {
	
	int i = buscarPosicionColaborador(G->array, G->size, cedula1);
	
	AristaColaborador *nAux = G->array[i].cabezaAristas;
	
	while (nAux != NULL) {
		if (strcmp(nAux->cedula, cedula2) == 0) {
			return 1;
		}
		nAux = nAux->next;
	}
	
	i = buscarPosicionColaborador(G->array, G->size, cedula2);
	
	while (nAux != NULL) {
		if (strcmp(nAux->cedula, cedula1) == 0) {
			return 1;
		}
		nAux = nAux->next;
	}
	
	return 0;
}

void agregarColaboradorGrafo(GrafoColaboradores * G, Colaborador *colaborador) {
	
	int size = G->size;
	int i;
	
	G->array[size].info = colaborador;
	
	G->size++;
}

void insertarColaborador(ListaColaboradores *lista, GrafoColaboradores *G, char cedula[1024], char nombre[1024], char apellidos[1024], char correo[1024], char rol[1024], char nacimiento[1024]) {
	
	Colaborador *nuevoColaborador;
	nuevoColaborador = (Colaborador*)malloc(sizeof(Colaborador));
	
	strcpy(nuevoColaborador->cedula, cedula);
	strcpy(nuevoColaborador->nombre, nombre);
	strcpy(nuevoColaborador->apellidos, apellidos);
	strcpy(nuevoColaborador->correo, correo);
	strcpy(nuevoColaborador->rol, rol);
	strcpy(nuevoColaborador->nacimiento, nacimiento);
	
	
	NodoColaborador *nuevoNodoColaborador;
	nuevoNodoColaborador = (NodoColaborador*)malloc(sizeof(NodoColaborador));
	
	nuevoNodoColaborador->info = nuevoColaborador;
	
	agregarColaboradorGrafo(G, nuevoNodoColaborador->info);

	nuevoNodoColaborador->next = lista->cabeza;
	lista->cabeza = nuevoNodoColaborador;
	
}

void relacionarColaboradores(GrafoColaboradores * G, char primeraPersona[124], char segundaPersona[124]) {
	
	int size = G->size;
	int i;
	
	ListaAdyacenciaColaboradores *array = G->array;
	
	for (i = 0; i < size; i++) {
		if (strcmp(array[i].info->cedula, primeraPersona) == 0) {
			break;
		}
	}
	
	int j = buscarPosicionColaborador(array, size, segundaPersona);
	
	if (j >= 0 && i < size && size < 10000) {
		
		AristaColaborador * nuevo = crearAristaColaborador(segundaPersona, j);
		
		nuevo->next = array[i].cabezaAristas;
		array[i].cabezaAristas = nuevo;
		
		int k = buscarPosicionColaborador(array, size, primeraPersona);
		
		AristaColaborador * nuevo2 = crearAristaColaborador(primeraPersona, k);
		
		nuevo2->next = array[j].cabezaAristas;
		array[j].cabezaAristas = nuevo2;
		
	}
	
}

void actualizarGrafoColaboradores(GrafoColaboradores *G) {
	
	int i;
	
	for (i = 0; i < G->size; i++) {
		AristaColaborador *nAux = G->array[i].cabezaAristas;
		
		while (nAux != NULL) {	
			nAux->posicion = buscarPosicionColaborador(G->array, G->size, nAux->cedula);
			nAux = nAux->next;
		}
	}
}

void eliminarColaboradorGrafo(GrafoColaboradores *G, char cedula[1024]) {
	
	int size = G->size;
	int i;
	
	int k = 0;
	
	ListaAdyacenciaColaboradores *array = G->array;
	
	for (i = 0; i < size; i++) {
		if (strcmp(array[i].info->cedula, cedula) == 0) {
			k = 1;
			break;
		}
	}
	
	if (k = 1) {
		
		G->size = size - 1;
		
		for (i = i; i < size; i++) {
			array[i] = array[i + 1];
		}
		
		for (i = 0; i < G->size; i++) {
			
			AristaColaborador *nAux = array[i].cabezaAristas;
			
			if (nAux != NULL) {
			
				if(strcmp(nAux->cedula, cedula) == 0){
					array[i].cabezaAristas = nAux->next;
				}
				else {
					while(nAux->next != NULL){
						if(strcmp(nAux->next->cedula, cedula) == 0){
							nAux->next = nAux->next->next;
							break;
						}
						nAux = nAux->next;
					}
				}
			}
		}
		actualizarGrafoColaboradores(G);
	}
}

void imprimirAristasColaboradores(AristaColaborador * nAux) {
	
	while (nAux != NULL) {
		printf("Cedula: %s #%d\n", nAux->cedula, nAux->posicion);
		nAux = nAux->next;
	}
}

void imprimirGrafoColaboradores(GrafoColaboradores * G) {
	
	system("cls");
	
	printf("LOS COLABORADORES REGISTRADOS ACTUALMENTE SON:\n\n");
	
	int size = G->size;
	int i;
	
	for (i = 0; i < size; i++) {
		printf("Cedula: %s\n", G->array[i].info->cedula);
		printf("Nombre: %s\n", G->array[i].info->nombre);
		printf("Apellidos: %s\n", G->array[i].info->apellidos);
		printf("Correo: %s\n", G->array[i].info->correo);
		printf("Rol en la Organizacion: %s\n", G->array[i].info->rol);
		printf("Fecha de Nacimiento: %s\n", G->array[i].info->nacimiento);
		printf("\n");
		printf("\nESTE COLABORADOR SE RELACIONA CON: \n\n");
		imprimirAristasColaboradores(G->array[i].cabezaAristas);
		printf("\n------------------------------------\n");
	}
	
	system("pause");
	return;
	
}

void menuInsertarColaborador(ListaColaboradores *lista, GrafoColaboradores *G) {
	
	system("cls");
	
	char cedula[1024];
	char nombre[1024];
	char apellidos[1024];
	char correo[1024];
	char rol[1024];
	char nacimiento[1024];
	
	printf("BIENVENIDO AL MENU PARA REGISTRAR UN COLABORADOR\n\n");
	
	printf("Ingrese la cedula del colaborador: ");
	gets(cedula);
	printf("Ingrese el nombre del colaborador: ");
	gets(nombre);
	printf("Ingrese el apellidos del colaborador: ");
	gets(apellidos);
	printf("Ingrese la correo de nacimiento del colaborador: ");
	gets(correo);
	printf("Ingrese el rol del colaborador: ");
	gets(rol);
	printf("Ingrese la fecha de nacimiento del colaborador: ");
	gets(nacimiento);
	
	if (obtenerColaborador(lista, cedula)){
		printf("\nEl colaborador ya se encuentra registrado...\n");
		printf("\nRegresando al <<Menu Principal>> ");
		system("pause");
		return;
	}
	
	insertarColaborador(lista, G, cedula, nombre, apellidos, correo, rol, nacimiento);
	
	printf("\nJugador Registrado Correctamente! \nRegresando al <<Menu Principal>> ");
	system("pause");
	
}
	
void menuEditarColaborador(ListaColaboradores *lista) {
	
	system("cls");
	
	printf("MENU DE EDITAR INFORMACION DE UN COLABORADOR\n\n");
	
	char cedula[1024];
	
	printf("Ingrese la cedula del colaborador: ");
	gets(cedula);
	
	if (obtenerColaborador(lista, cedula) != NULL) {
		
		system("cls");
		
		printf("MENU DE EDITAR INFORMACION COLABORADOR - POR FAVOR INGRESE UNA OPCION\n\n");
		
		char opcion[1024];
		
		printf("1. Editar Nombre\n");
		printf("2. Editar Apellidos\n");
		printf("3. Correo\n");
		printf("4. Rol\n");
		printf("5. Nacimiento\n");
		
		printf("\nIngrese cualquier otro caracter para <<Salir>>\n\n");
		
		gets(opcion);
		
		if (strcmp(opcion, "1") == 0) {
			
			Colaborador *nAux = obtenerColaborador(lista, cedula);
			
			printf("Ingrese el nuevo nombre del colaborador: ");
			gets(nAux->nombre);
			
		}
		else if (strcmp(opcion, "2") == 0) {
			
			Colaborador *nAux = obtenerColaborador(lista, cedula);
			
			printf("Ingrese los nuevos apellidos del colaborador: ");
			gets(nAux->apellidos);
			
		}
		else if (strcmp(opcion, "3") == 0) {
			
			Colaborador *nAux = obtenerColaborador(lista, cedula);
			
			printf("Ingrese el nuevo correo del colaborador: ");
			gets(nAux->correo);
			
		}
		else if (strcmp(opcion, "4") == 0) {
			
			Colaborador *nAux = obtenerColaborador(lista, cedula);
			
			printf("Ingrese el nuevo rol del colaborador: ");
			gets(nAux->rol);
			
		}
		else if (strcmp(opcion, "5") == 0) {
			
			Colaborador *nAux = obtenerColaborador(lista, cedula);
			
			printf("Ingrese la nueva fecha de nacimiento del colaborador: ");
			gets(nAux->nacimiento);
			
		}
		printf("\nColaborador actualizado correctamente:\n\n");
	}
	else {
		
		printf("Colaborador no encontrado... \n\n");
		printf("Regresando al <<Menu Principal>> ");
		system("pause");
		return;
	}

	printf("Regresando al <<Menu Principal>> ");
	system("pause");
}


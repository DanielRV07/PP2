#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define size 50

typedef struct Nodo Nodo;
typedef struct Arista Arista;
typedef struct Grafo Grafo;

struct Nodo{
   int verificador;
   char lugar[size];
   int cod;
   int postal;
   Nodo *siguiente;
   Arista *adyacente;
};

struct Arista{
   Nodo *vertice;
   Arista *siguiente;

   int tiempo;
   int distancia;
   char ruta[size];
};

struct Grafo{
   Nodo *dato;
   Grafo *siguiente;
};

Nodo *inicio = NULL;

int codigo = 0;
int ciudades = 0;


/*Funcion para agregar una ciudad con informacion
Entradas: lugar, codigo, codigo postla
Salida: se guardan la informacion de la ciudad
Restricciones: lugar,codigo y codigo postal deben ser de tipo char*/
void agregarCiudad(){
   Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));
   
   fflush(stdin);

   printf("\nIngrese el nombre del lugar: "); gets(nuevo->lugar);
   printf("Ingrese el codigo: "); scanf("%d", &nuevo->cod);
   printf("Ingrese el codigo postal: "); scanf("%d", &nuevo->postal);

   ciudades++;
   nuevo->verificador = codigo;
   codigo++;
   nuevo->siguiente = NULL;
   nuevo->adyacente = NULL;
   Nodo *i;

   if(inicio == NULL){
      inicio = nuevo;
   }
   else{
      i = inicio;
      while(i->siguiente != NULL){
         i = i->siguiente;
      }
      i->siguiente = nuevo;
   }
}


/*Funcion auxiliar para eliminar para eliminar una ciudad con su informacion
Entradas: ciudad origen, ciudad destino
Salida: se elimna la ciudad ingresada
Restricciones: ciudad origen y ciudad destino de tipo char*/
void eliminarCiudadAux(char ciudadOrigen[size], char ciudadDestino[size]){
   Nodo *aux, *aux2;
   Arista *i, *borrar;
   aux = inicio;

   while(aux != NULL){
      if(strcmp(aux->lugar, ciudadOrigen) == 0){
         borrar = aux->adyacente;
         int num;
         while(borrar != NULL){
            if(num == 0){
               if(strcmp(borrar->vertice->lugar, ciudadDestino) == 0){
                  aux->adyacente = borrar->siguiente;
                  free(borrar);
                  printf("\nCiudad eliminada.\n");
                  return;
               }
            }
            if(strcmp(borrar->vertice->lugar, ciudadDestino) == 0){
               i->siguiente = borrar->siguiente;
               free(borrar);
               printf("\nCidad eliminada.\n");
               return;
            }
            num++;
            i = borrar;
            borrar = borrar->siguiente;
         }
      }
      aux = aux->siguiente;
   }
   printf("\nCiudad no encontrada.\n");
   return;
}


/*Funcion para eliminar una ciudad
Entradas: lugar
Salida: la ciudad eliminada
Restricciones: lugar de tipo char*/
void eliminarCiudad(){
   Nodo *actual, *anterior;
   Arista *aux;
   
   fflush(stdin);

   ciudades--;
   codigo = codigo - 1;
   actual = inicio;
   char lugar[size];

   fflush(stdin);
   printf("\nIngrese el lugar que desea eliminar: "); gets(lugar);

   while(actual != NULL){
      aux = actual->adyacente;
      while(aux != NULL){
         if(strcmp(aux->vertice->lugar, lugar) == 0){
            eliminarCiudadAux(actual->lugar, aux->vertice->lugar);
            return;
         }
         aux = aux->siguiente;
      }
      actual = actual->siguiente;
   }
   actual = inicio;

   if(strcmp(actual->lugar, lugar) == 0){
      inicio = actual->siguiente;
      free(actual);
   }
   else{
      int info = strcmp(actual->lugar, lugar);
      while(info != 0){
         anterior = actual;
         actual = actual->siguiente;
         info = strcmp(actual->lugar, lugar);
      }
      anterior->siguiente = actual->siguiente;
      free(actual);
   }
}


//Funcion auxiliar para crear un camino que conecta dos ciudades

void agregarCaminoAux(Nodo *i, Nodo *aux, Arista *nuevo){
   Arista *x;
   if(i->adyacente == NULL){
      i->adyacente = nuevo;
      nuevo->vertice = aux;
   }
   else{
      x = i->adyacente;
      while(x->siguiente != NULL){
         x = x->siguiente;
      }
      nuevo->vertice = aux;
      x->siguiente = nuevo;
   }
}


/*Funcion para agregar un camino que conecta dos ciudades
Entradas: ciudadOrigen, ciudadDestino, ruta, tiempo y distancia
Salida: se guardan los datos ingresados
Restricciones: ciudadOrigen, ciudadDestino y ruta de tipo char, tiempo y distancia de tipo int*/
void agregarCamino(){
   char ciudadOrigen[size];
   int tiempo, distancia;
   char ciudadDestino[size];
   char ruta[size];
   
   fflush(stdin);
   
   Arista *nuevo = (Arista *) malloc(sizeof(Arista));
   nuevo->siguiente = NULL;

   if(inicio == NULL){
      printf("\nEl grafo esta vacio.\n");
      return;
   }

   printf("\nIngrese el lugar de origen: "); gets(ciudadOrigen);
   printf("Ingrese el lugar de destino: "); gets(ciudadDestino);
   fflush(stdin);
   printf("Ingrese el tipo de ruta (terrestre, aerea o maritima): "); gets(ruta);
   printf("Ingrese el tiempo: "); scanf("%d", &tiempo);
   printf("Ingrese la distancia: "); scanf("%d", &distancia);
   
   
   nuevo->tiempo = tiempo;
   nuevo->distancia = distancia;
   strcpy(nuevo->ruta, ruta);
   Nodo *i = inicio, *aux = inicio;
   while(aux != NULL){
      if(strcmp(aux->lugar, ciudadDestino) == 0){
         break;
      }
      aux = aux->siguiente;
   }
   if(aux == NULL){
      printf("\nLa ciudad no se encuentra registrada.\n");
      return;
   }
   while(i != NULL){
      if(strcmp(i->lugar, ciudadOrigen) == 0){
         agregarCaminoAux(i, aux, nuevo);
         return;
      }
      i = i->siguiente;
   }
   if(i == NULL){
      printf("\nLa ciudad no se encuentra registrada.\n");
   }
}


/*Funcion para eliminar un camino
Entradas: ciudadOrigen, ciudadDestino
Salida: se elimna el camino ingresado
Restricciones: ciudadOrigen y ciudadDestino de tipo char */
void eliminarCamino(){
	char ciudadOrigen[size];
   char ciudadDestino[size];
   
   fflush(stdin);

   Nodo *aux = inicio;
   Arista *i, *eliminar;
	
	printf("\nIngrese la ciudad de origen: "); gets(ciudadOrigen);
	printf("Ingrese la ciudad de destino: "); gets(ciudadDestino);
    
	while(aux != NULL){
		if(strcmp(aux->lugar, ciudadOrigen) == 0){
			eliminar = aux->adyacente;
			int num;
			while(eliminar != NULL){
				if(num == 0){
					if(strcmp(eliminar->vertice->lugar, ciudadDestino) == 0){
						aux->adyacente = eliminar->siguiente;
						free(eliminar);
						printf("\nCamino eliminado.\n");
						return;
					}
				}
				if(strcmp(eliminar->vertice->lugar, ciudadDestino) == 0){
					i->siguiente = eliminar->siguiente;
					free(eliminar);
					printf("\nCamino eliminado.\n");
					return;
				}
				num++;
				i = eliminar;
				eliminar = eliminar->siguiente;
			}	
		}
		aux = aux->siguiente;
	}
	printf("\nCamino no encontrado.\n");
	return;
}


/*Funcion para imprimir los grafos
Entradas: lugar, ruta, codigo, codigo postal, tiempo y distancia
Salida: se imprime el grafo 
Restricciones: lugar, ruta, distancia de tipo char, codigo, codigo postal y tiempo de tipo int */
void imprimirGrafo(){
   Nodo *i = inicio;
   Arista *x;
   while(i != NULL){
      printf("\nCiudad: %s - Codigo: %d - Codigo Postal: %d", i->lugar, i->cod, i->postal);
      x = i->adyacente;
      while(x != NULL){
         printf("\nCiudad de destino: %s - Tipo de ruta: %s - Tiempo: %d - Distancia: %d", x->vertice->lugar, x->ruta, x->tiempo, x->distancia);
         x = x->siguiente;
      }
      printf("\n");
      i = i->siguiente;
   }
   printf("\n");
}

char * obtenerNombre(int num) {
	
	Nodo *nAux = inicio;
	int contador = 0;
	
	static char nombre[1024];
	
	while(nAux != NULL) {
		
		if (contador == num) {
			return nAux->lugar;
		}
		contador++;
		nAux = nAux->siguiente;
	}
	
}

int obtenerPosicionArista(char nombre[1024]) {
	
	Nodo *nAux = inicio;
	int contador = 0;
	
	while(nAux != NULL) {
		
		if (strcmp(nAux->lugar, nombre) == 0) {
			return contador;
		}
		contador++;
		nAux = nAux->siguiente;
	}
	
}
/* Función para crear matriz 
Entradas: ciudades
Salida: matriz creada con las ciudades
Restricciones: ciudades de tipo int*/
int * crearMatriz(int matrizAux[ciudades][ciudades]){
   
    int i;
    int j;
    
    Nodo *nAux = inicio;
    
    for (i = 0; i < ciudades; i++) {
    	for (j = 0; j < ciudades; j++) {
    		matrizAux[i][j] = 0;
		}
	}
	
   
    for(i = 0; i < ciudades; i++) {
    	
    	Arista *aristaAux = nAux->adyacente;
    	
    	while (aristaAux != NULL) {
    		matrizAux[i][obtenerPosicionArista(aristaAux->vertice->lugar)] = aristaAux->distancia;
    		aristaAux = aristaAux->siguiente;
		}
		nAux= nAux->siguiente;
	}
}

int * crearMatrizTipo(int matrizAux[ciudades][ciudades], char tipo[1024]){
   
    int i;
    int j;
    
    Nodo *nAux = inicio;
    
    for (i = 0; i < ciudades; i++) {
    	for (j = 0; j < ciudades; j++) {
    		matrizAux[i][j] = 0;
		}
	}
   
    for(i = 0; i < ciudades; i++) {
    	
    	Arista *aristaAux = nAux->adyacente;
    	
    	while (aristaAux != NULL) {
    		if (strcmp(aristaAux->ruta, tipo) == 0) {
    			matrizAux[i][obtenerPosicionArista(aristaAux->vertice->lugar)] = aristaAux->distancia;
			}
    		aristaAux = aristaAux->siguiente;
		}
		nAux= nAux->siguiente;
	}
}

int minDistance(int dist[], 
                bool sptSet[])
{
    
    int min = INT_MAX, min_index;
    int v;
    
    for (v = 0; v < ciudades; v++)
        if (sptSet[v] == false &&
                   dist[v] <= min)
            min = dist[v], min_index = v;
   
    return min_index;
}

void printPath(int parent[], int j) {
       
    if (parent[j] == - 1)
        return;
   
    printPath(parent, parent[j]);
   
    printf("-> %s ", obtenerNombre(j));
}
   
int printSolution(int dist[], int n, 
                      int parent[])
{
    int src = 0;
    printf("\n\nLugares\t\t\t\t Distancia\t\t\tCamino");
    
    int i;
    
    for (i = 1; i < ciudades; i++)
    {
    	if (dist[i] < 5000) {
    		printf("\n%s -> %s \t\t %d\t\t%s ",
            inicio->lugar, obtenerNombre(i), dist[i], inicio->lugar);
        	printPath(parent, i);
		}
		else {
    		printf("\n%s -> %s \t\t INF\t\t%s ",
            inicio->lugar, obtenerNombre(i), inicio->lugar);
		}
    }
}

/* Funcion dijkstra para encontrar el camino mas corto
Entradas: ciudades 
Salida: camino mas corto entre dos ciudades
Restricciones: ciudades tipo char */
void dijkstra(int graph[ciudades][ciudades], int src) {
       
    int dist[ciudades]; 
   
    bool sptSet[ciudades];
   
    int parent[ciudades];
   
	int i;
	
    for (i = 0; i < ciudades; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
   
    dist[src] = 0;
   	
   	int count;
   
    for (count = 0; count < ciudades - 1; count++) {

        int u = minDistance(dist, sptSet);
   
        sptSet[u] = true;
   	
   		int v;
   		
        for (v = 0; v < ciudades; v++)
   
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            } 
    }
   
    printSolution(dist, ciudades, parent);
}

/*Función del menu de rutas
Entradas: tipo de ruta
Salida: el camino mas ccorto entre las  rutas
Restricciones: tipo de ruta tipo int*/
void menuRutasLugares() {
	
	char opcion[1024];
	char tipo[1024];
	
	int matriz[ciudades][ciudades];
	
	printf("Ingrese una de las siguientes opciones: \n\n");
	printf("1. Cualquier Ruta\n");
	printf("2. Ruta Especifica\n");
	
	fflush(stdin);
	gets(opcion);
	
	if (strcmp(opcion, "1") == 0) {
		
		printf("\n");
		crearMatriz(matriz);
		dijkstra(matriz, 0);
		printf("\n");
		
	}
	
	else if (strcmp(opcion, "2") == 0) {
		
		printf("Ingrese el tipo de ruta: \n");
		gets(tipo);
		printf("\n");
		crearMatrizTipo(matriz, tipo);
		dijkstra(matriz, 0);
		printf("\n");
		
	}
	
	else {
		printf("\nIngrese un numero valido...\n");
	}
	
}


//Funcion main del programa
void menuPaseo() {
	
   int opcion1, opcion2;
   while(opcion1 != 3){
      printf("Ingrese una de las siguientes opcion:\n1 - Agregar domicilio o ruta \n2 - Ver Rutas\n3 - Salir: "); scanf("%d", &opcion1);
      if(opcion1 == 1){
         while(opcion2 != 6){
            printf("\nIngrese una de las siguientes opciones:\n1 - Agregar un domicilio\n2 - Agregar una ruta entre dos caminos\n3 - Eliminar un domicilio\n4 - Eliminar una ruta\n5 - Mostrar grafo\n6 - Salir: "); scanf("%d", &opcion2);
            if(opcion2 == 1){
               agregarCiudad();
            }
            else if(opcion2 == 2){
               agregarCamino();
            }
            else if(opcion2 == 3){
               eliminarCiudad();
            }
            else if(opcion2 == 4){
               eliminarCamino();
            }
            else if(opcion2 == 5){
               imprimirGrafo();
            }
            else if(opcion2 == 6){
               printf("\nGracias.\n\n");
            }
            else{
               printf("\nIngrese una de las opciones indicadas.\n");
            }
         }
      }
      else if(opcion1 == 2){
         menuRutasLugares();
         printf("\n");
      }
      else if(opcion1 == 3){
         printf("\nGracias.\n");
      }
      else{
         printf("\nIngrese una de las opciones indicadas.\n\n");
      }
	}
}


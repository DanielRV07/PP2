#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


//Funncion para agregar una ciudad con informacion
void agregarCiudad(){
   Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));

   printf("\nIngrese el nombre del lugar: "); gets(nuevo->lugar); gets(nuevo->lugar);
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


//Funcion auxiliar para eliminar para eliminar una ciudad con su informacion
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


//Funcion para eliminar una ciudad
void eliminarCiudad(){
   Nodo *actual, *anterior;
   Arista *aux;

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


//Funcion auxiliar para crear un camino que conceta dos ciudades
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


//Funcion para agregar un camino que conecta dos ciudades
void agregarCamino(){
   char ciudadOrigen[size];
   int tiempo, distancia;
   char ciudadDestino[size];
   char ruta[size];
   
   Arista *nuevo = (Arista *) malloc(sizeof(Arista));
   nuevo->siguiente = NULL;

   if(inicio == NULL){
      printf("\nEl grafo esta vacio.\n");
      return;
   }

   printf("\nIngrese el lugar de origen: "); gets(ciudadOrigen); gets(ciudadOrigen);
   printf("Ingrese el lugar de destino: "); gets(ciudadDestino);
   printf("Ingrese el tipo de ruta (terrestre, aerea o maritima): "); gets(ruta); gets(ruta);
   printf("Ingrese el tiempo: "); scanf("%d", &tiempo);
   printf("Ingrese la distancia: "); scanf("%d", &distancia);
   
   
   nuevo->tiempo = tiempo;
   nuevo->distancia = distancia;
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


//Funcion para eliminar un camino
void eliminarCamino(){
	char ciudadOrigen[size];
   char ciudadDestino[size];

   Nodo *aux = inicio;
   Arista *i, *eliminar;
	
	printf("\nIngrese la ciudad de origen: "); gets(ciudadOrigen); gets(ciudadOrigen);
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


//Funcion para imprimir los grafos
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

void crearMatriz(int matriz[][ciudades]){
   int i, j;
   for(i = 0; i < ciudades; i++){
      for(j = 0; j < ciudades; j++){
         matriz[i][j] = 0;
      }
   }
}

//Funcion para convertir el grafo a una mtraiz usando los tiempos y las distancias entre cada camino
void agregarMatriz(int matriz[][ciudades], int ciudadSalida, int ciudadDestino, int distancia_tiempo){
   matriz[ciudadSalida][ciudadDestino] = distancia_tiempo;
}


//Funcion para imprimir la matriz
void imprimirMatriz(int matriz[][ciudades]){
   int i = 0, j = 0;
   for(i; i < ciudades; i++){
      for(j = 0; j < ciudades; j++){
         printf("%d ", matriz[i][j]);
      }
      printf("\n");
    }
}


//Funcion dijkstra para buscar el camino más corte entre dos ciudades
#define infinito 9999999
int dijkstra(int matriz[ciudades][ciudades], int ciudadSalida, int ciudadLlegada){
   int temporal[ciudades][ciudades], anterior[ciudades], distancia[ciudades];
   int visitado[ciudades], contador, distanciaMinima, siguiente, i, j;

   for(i = 0; i < ciudades; i++){
      for(j = 0; j < ciudades; j++){
         if(matriz[i][j] == 0){
            temporal[i][j] = infinito;
         }
         else{
            temporal[i][j] = matriz[i][j];
         }
      }
   }

   for(i = 0; i < ciudades; i++){
      distancia[i] = temporal[ciudadSalida][i];
      anterior[i] = ciudadSalida;
      visitado[i] = 0;
   }

   distancia[ciudadSalida] = 0;
   visitado[ciudadSalida] = 1;
   contador = 1;

   while(contador < ciudades - 1){
      distanciaMinima = infinito;
      for(i = 0; i < ciudades; i++){
         if(distancia[i] < distanciaMinima && !visitado[i]){
            distanciaMinima = distancia[i];
            siguiente = i;
         }
      }

      visitado[siguiente] = 1;

      for(i = 0; i < ciudades; i++)
         if(!visitado[i])
            if(distanciaMinima + temporal[siguiente][i] < distancia[i]){
               distancia[i] = distanciaMinima + temporal[siguiente][i];
               anterior[i] = siguiente;
            }
         contador++;
   }

   Nodo *ii = inicio;
   char salida[size], llegada[size];
   while(ii != NULL){
      if(ii->verificador == ciudadSalida){
         strcpy(salida, ii->lugar);
      }
      if(ii->verificador == ciudadLlegada){
         strcpy(llegada, ii->lugar);
      }
      ii = ii->siguiente;
   }

   if(ciudadLlegada != ciudadSalida){
      return distancia[ciudadLlegada];
   }
}

//Funcion main del programa
int main(){
   int opcion1, opcion2;
   while(opcion1 != 3){
      printf("Ingrese una de las siguientes opcion:\n1 - Agregar domicilio o ruta \n2 - Salir: "); scanf("%d", &opcion1);
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
         printf("\nGracias.\n");
      }
      else{
         printf("\nIngrese una de las opciones indicadas.\n\n");
      }
}
}


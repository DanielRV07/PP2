#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Observacionjefes{
	
	char cedulacolaborador[1024];
	char descripcionrendimiento[1024];
	
	
	struct Observacionjefes *next;
} Observacionjefes;



typedef struct ListaSimple {
	
	Observacionjefes *cabeza;
} ListaSimple;

/* Función genérica para que funcione la estructura*/
ListaSimple * crearLista() {
	
	ListaSimple *nuevo = NULL;
	nuevo = (ListaSimple*)malloc(sizeof(ListaSimple));
	
	nuevo->cabeza = NULL;
	
	return nuevo;
	
}

/* Funcion Para crear observación
-Entradas: 
- La cédula del colaborador
- La descripción de rendimiento
-Salidas:
- La nueva observación creada
-Restricciones:
- cedulacolaborador y descripcionrendimiento deben ser de tipo char*/
Observacionjefes * crearObservacion(char cedulacolaborador[1024],char descripcionrendimiento[1024]){
	
	Observacionjefes *nuevo = NULL;
	
	nuevo = (Observacionjefes*)malloc(sizeof(Observacionjefes));
	
	strcpy(nuevo-> cedulacolaborador,cedulacolaborador);	
	strcpy(nuevo ->descripcionrendimiento,descripcionrendimiento); 

	
	nuevo-> next = NULL;
	return nuevo;
	
}
/* Funcion Para Insertar Datos
-Entradas: 
- La cédula del colaborador
- La descripción de rendimiento
-Salidas:
- La nueva observación creada con ya los datos ingresados
-Restricciones:
- cedulacolaborador y descripcionrendimiento deben ser de tipo char*/
void insertarDato(ListaSimple *lista, char cedulacolaborador[1024],char descripcionrendimiento[1024]) {
	
	Observacionjefes * nuevo = crearObservacion(cedulacolaborador,descripcionrendimiento);
	
	nuevo->next = lista->cabeza;
	lista->cabeza = nuevo;
}


/* Función para imprimir documento con todos los datos(cédulacolaborador y descripción rendimiento) 
 Entradas: nuevo
 Salidas: La impresión de los colaboradores registrados,(su cédula y descripción de rendimiento)
 Restricciones: Nuevo debe ser de tipo ListaSimple
 */
void imprimirDocumento(ListaSimple *nuevo) {
	
	Observacionjefes *nAux = nuevo-> cabeza;
	
	while (nAux != NULL) {
		printf("%s", nAux->cedulacolaborador);
		printf("\n");
		printf("%s", nAux->descripcionrendimiento);
		printf("\n");

		nAux = nAux->next;
		printf("\n");
	}
	printf("\n");
}


/* Función para ver el comentario específico de un Colaborador
- Entradas: lista y cedulacolaborador 
- Salidas: la descripción del colaborador al cual corresponde la cedula ingresada
- Restricciones: 
- lista debe ser de tipo ListaSimple
- cedulacolaborador debe ser de tipo char*/
void verComentariosColaborador(ListaSimple* lista, char cedulacolaborador[1024]){
	
	Observacionjefes *nAux = lista-> cabeza;
	
	while(nAux != NULL){
	
		if (strcmp(nAux->cedulacolaborador,cedulacolaborador)== 0){
			
			printf("%s",nAux->descripcionrendimiento);
		}
		nAux= nAux->next;
		printf("\n");
	}
}		

void menuComentariosColaborador(ListaSimple *lista){
	
	
	char cedulacolaborador[1024];
	char opcion[1024];
	system("cls");
	
	printf("Bienvenido a la visualizacion de observaciones\n\n");
	printf("Ingrese 1 si desea ver los comentarios de un colaborador\n");
	printf("Ingrese 2 si desea ver todos los colaboradores que estan incluidos en el sistema\n");
	printf("Ingrese otro numero para regresar al Menu Principal");
	gets(opcion);
	
	if(strcmp(opcion, "1") == 0) {
		printf("Ingrese la cedula del colaborador del que desea ver el comentario");
		gets(cedulacolaborador);
		verComentariosColaborador(lista,cedulacolaborador);
					
}
	else if(strcmp(opcion,"2")== 0 ){
		printf("Los colaboradores son:");
		imprimirDocumento(lista);
		
	}
	else{
		printf("Regresando al <<Menu>>");
		system("pause");
		return;
	}
}

int main(){
	
	ListaSimple *nuevo = crearLista();
	insertarDato(nuevo, "5555", "bueno");
	insertarDato(nuevo, "355555", "regular");
 	menuComentariosColaborador(nuevo);
}
	

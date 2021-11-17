#include <stdio.h>
#include <stdlib.h>

#include "headerCaminos.h"

void menuPrincipal(GrafoEquipos *grafoEquipos, GrafoColaboradores *grafoColaboradores, ListaColaboradores *listaColaboradores) {
	
	char opcion[1024];
	
	system("cls");
	
	printf("BIENVENIDO AL MENU PRINCIPAL DEL MEJOR JUEGO DE COSTA RICA - POR FAVOR INGRESE UNA OPCION: \n\n");
	
	printf("1.  Registrar Colaborador\n");
	printf("2.  Editar Colaborador\n");
	printf("3.  Eliminar Colaborador\n");
	printf("4.  Imprimir Colaboradores\n");
	printf("5.  Crear Equipo\n");
	printf("6.  Insertar Colaborador a Equipo\n");
	printf("7.  Relacionar Equipos\n");
	printf("8.  Imprimir Equipos\n");
	printf("9.  Iniciar Chat con Colaborador\n");
	
	printf("\nIngrese cualquier otro caracter para <<Salir>>\n\n");
	
	scanf("%s", &opcion);
	fflush(stdin);
	
	if (strcmp(opcion, "1") == 0) {
		menuInsertarColaborador(listaColaboradores, grafoColaboradores);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "2") == 0) {
		menuEditarColaborador(listaColaboradores);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "3") == 0) {
		menuEliminarColaborador(grafoEquipos, listaColaboradores, grafoColaboradores);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "4") == 0) {
		imprimirGrafoColaboradores(grafoColaboradores);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "5") == 0) {
		menuAgregarEquipo(grafoEquipos);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "6") == 0) {
		menuAgregarPersonaEquipo(grafoEquipos, listaColaboradores, grafoColaboradores);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "7") == 0) {
		menuRelacionarEquipos(grafoEquipos);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "8") == 0) {
		imprimirGrafoEquipos(grafoEquipos);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	else if (strcmp(opcion, "9") == 0) {
		menuBuscarCaminoColaboradores(grafoColaboradores);
		menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	}
	
}

void main() {
	
	GrafoEquipos *grafoEquipos = crearGrafoEquipos();
	GrafoColaboradores *grafoColaboradores = crearGrafoColaboradores();
	ListaColaboradores *listaColaboradores = crearListaColaboradores();
	
	agregarEquipo(grafoEquipos, "ATI", "SON LOS EGRESADOS DE ATI");
	agregarEquipo(grafoEquipos, "PROGRAMADORES", "SON LOS QUE PROGRAMAN");
	agregarEquipo(grafoEquipos, "GERENCIA", "SON LOS ALTOS MANDOS DE LA ORGANIZACION");
	agregarEquipo(grafoEquipos, "CONTABILIDAD", "SON LOS QUE SE ENCARGAN DE LA CONTABILIDAD");
	agregarEquipo(grafoEquipos, "MERCADEO", "SE ENCARGAN DE TODO LO DE MERCADEO");
	
	relacionarEquipos(grafoEquipos, "ATI", "GERENCIA");
	relacionarEquipos(grafoEquipos, "PROGRAMADORES", "GERENCIA");
	relacionarEquipos(grafoEquipos, "ATI", "PROGRAMADORES");
	relacionarEquipos(grafoEquipos, "CONTABILIDAD", "GERENCIA");
	relacionarEquipos(grafoEquipos, "CONTABILIDAD", "MERCADEO");
	
	insertarColaborador(listaColaboradores, grafoColaboradores, "123456", "Daniel", "Rojas Vega", "daniel07@gmail.com", "Ninguno", "2002");
	insertarColaborador(listaColaboradores, grafoColaboradores, "456789", "Pepe", "Peperoni", "pepe@gmail.com", "Ninguno", "2002");
	insertarColaborador(listaColaboradores, grafoColaboradores, "789456", "Hombre", "Random", "hrandom@gmail.com", "Ninguno", "2002");
	insertarColaborador(listaColaboradores, grafoColaboradores, "456123", "Mujer", "Random", "mrandom@gmail.com", "Ninguno", "2002");
	insertarColaborador(listaColaboradores, grafoColaboradores, "123789", "Prueba", "Probadora", "prandom@gmail.com", "Ninguno", "2002");
	insertarColaborador(listaColaboradores, grafoColaboradores, "159753", "Persona", "Solitaria", "psolitaria@gmail.com", "Ninguno", "2002");
	
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "ATI", "123456", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "PROGRAMADORES", "123456", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "GERENCIA", "123456", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "PROGRAMADORES", "456789", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "ATI", "456789", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "CONTABILIDAD", "789456", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "GERENCIA", "789456", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "MERCADEO", "456123", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "CONTABILIDAD", "456123", grafoColaboradores);
	agregarPeronaEquipo(grafoEquipos, listaColaboradores, "MERCADEO", "123789", grafoColaboradores);
	
	menuPrincipal(grafoEquipos, grafoColaboradores, listaColaboradores);
	
}




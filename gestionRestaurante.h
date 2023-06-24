#include "index.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
using namespace std;

void gestionRestaurante();
void ingresarMenu();
void registrarPlato();

void gestionRestaurante() {
  int entrada, opcion = 1;
  do {
    system("cls");
    cout << DEFECTO << "GESTION RESTAURANTE" << endl;
    cout << DEFECTO << "Utilice las flechas del teclado para desplazarse." << endl;
    cout << DEFECTO << "Utilice el enter para escoger su opcion." << endl << endl;
    cout << DEFECTO << "Seleccione una opcion: " << endl << endl;
    cout << (opcion == 1 ? AZUL : "") << (opcion == 1 ? "> " : "") << (opcion == 1 ? DEFECTO : GRIS) << "Ingresar menu" << endl;
    cout << (opcion == 2 ? AZUL : "") << (opcion == 2 ? "> " : "") << (opcion == 2 ? DEFECTO : GRIS) << "Registro de platos" << endl;
    cout << (opcion == 3 ? AZUL : "") << (opcion == 3 ? "> " : "") << (opcion == 3 ? DEFECTO : GRIS) << "Asignacion menu por estudiante" << endl; 
    cout << (opcion == 4 ? AZUL : "") << (opcion == 4 ? "> " : "") << (opcion == 4 ? DEFECTO : GRIS) << "Facturacion" << endl;
    cout << (opcion == 5 ? AZUL : "") << (opcion == 5 ? "> " : "") << (opcion == 5 ? DEFECTO : GRIS) << "Consulta" << endl;
    cout << (opcion == 6 ? AZUL : "") << (opcion == 6 ? "> " : "") << (opcion == 6 ? DEFECTO : GRIS) << "Salir" << endl;
    cout << DEFECTO;

    /**
     * Mediante el codigo ASCII de las flechas del teclado, podemos realizar
     * la seleccion de opciones disponibles en el menu. Teniendo en cuenta:
     * Codigo ASCII para las flechas: 224
     * Codigo ASCII para la flecha hacia arriba: 72.
     * Codigo ASCII para la flecha hacia la derecha: 77.
     * Codigo ASCII para la flecha hacia abajo: 80.
     * Codigo ASCII para la flecha hacia la izquierda: 75.
     * Codigo ASCII para el enter: 13.
     */
    entrada = getch();
    if(entrada == 224) {
      entrada = getch();
      if(entrada == 80 || entrada == 77) opcion = (opcion == 6) ? 1 : opcion + 1;
      if(entrada == 72 || entrada == 75) opcion = (opcion == 1) ? 6 : opcion - 1;
    }

    /**
     * Una vez confirmada la opción del usuario y teniendo en cuenta el codigo ASCII 
     * del enter (13) se gestiona la selección.
     */ 
    else if(entrada == 13) {
      switch(opcion) {
        case 1: ingresarMenu(); break;
        case 2: registrarPlato(); break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
      }
    }
  } while(opcion != 6 || entrada != 13);
}

void ingresarMenu() {
  static int numero = 0;
  Menu menuLectura, menuEscritura;
  int cantidadPlatos;
  bool existePlato = false;
  
  // Lee el archivo de menus.txt para conocer los numeros de los menus anteriores.
  ifstream archivoLectura("menus.txt", ios::in | ios::binary);
  if(archivoLectura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  }
  archivoLectura.read(reinterpret_cast<char *>(&menuLectura), sizeof(Menu));
  while(!archivoLectura.eof()) {
    if(menuLectura.numero > numero) numero = menuLectura.numero;
    archivoLectura.read(reinterpret_cast<char *>(&menuLectura), sizeof(Menu));
  }
  archivoLectura.close();

  // Lee los datos ingresados del usuario
  system("cls");
  cout << "INGRESAR MENU " << numero + 1 << endl;
  cout << "Complete los campos." << endl << "Recuerde que la cantidad maxima de platos es " << CANT_MAX_PLATOS << "." <<  endl << endl;
  do {
    cout << "Digite la cantidad de platos: "; cin >> cantidadPlatos;
    if(cantidadPlatos > CANT_MAX_PLATOS || cantidadPlatos <= 0) {
      cout << ROJO << "La cantidad de platos definida sobrepasa el limite" << DEFECTO << endl;
    }
  } while(cantidadPlatos > CANT_MAX_PLATOS || cantidadPlatos <= 0);

  // Ingresa el nombre de los platos 
  for(int i = 0; i < cantidadPlatos; i++) {
    do {
      existePlato = false;
      cout << "Nombre del plato " << i + 1 << ": "; fflush(stdin); gets(menuEscritura.platos[i].nombre); 
      mayusculas(menuEscritura.platos[i].nombre);
       
      // Revisa que el nombre no este vacia
      if(menuEscritura.platos[i].nombre[0] == '\0') cout << ROJO << "El nombre del plato no puede estar vacio." << DEFECTO << endl;

      // Revisa que el nombre ingresado no haya sido ingresado anteriormente en el menu.
      for(int k = 0; k < i; k++) {
        if(strcmp(menuEscritura.platos[k].nombre , menuEscritura.platos[i].nombre) == 0) existePlato = true;
      }
      if(existePlato) cout << ROJO << "El nombre de un plato no puede estar repetido en un mismo menu." << DEFECTO << endl;
    } while(menuEscritura.platos[i].nombre[0] == '\0' || existePlato);
  }

  //Ingresa el coste del menu
  do {
    cout << "Coste total: " ; cin >> menuEscritura.coste;
    if(menuEscritura.coste < COSTO_MIN_MENU) cout << ROJO << "El coste minimo es $" << COSTO_MIN_MENU << DEFECTO << endl;
  } while(menuEscritura.coste < COSTO_MIN_MENU);

  // Escribe en el archivo
  ofstream archivoEscritura("menus.txt", ios::app | ios::binary);
  if(archivoEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  }
  numero++;
  menuEscritura.numero = numero;
  menuEscritura.cantidadPlatos = cantidadPlatos;
  archivoEscritura.write(reinterpret_cast<char *>(&menuEscritura), sizeof(Menu));
  archivoEscritura.close();
  cout << endl << VERDE << "Menu ingresado exitosamente..." << DEFECTO << endl;
  system("pause");
}

void registrarPlato() {
  
}
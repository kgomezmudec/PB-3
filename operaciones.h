#include "index.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
using namespace std;

void gestionRestaurante();
void ingresarMenu();
void registrarPlato();
void consultas();
void consultaListarCarta();
void consultaMenu();

void gestionAcademica();

// GESTION RESTAURANTE

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
        case 5: consultas(); break;
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
  cout << "INGRESAR MENU" << endl;
  cout << "Complete los campos." << endl << "Recuerde que la cantidad maxima de platos es " << CANT_MAX_PLATOS << "." <<  endl << endl;
  cout << "Menu No. " << numero + 1 << endl;
  do {
    cout << "Digite la cantidad de platos: "; cin >> cantidadPlatos;
    if(cantidadPlatos > CANT_MAX_PLATOS || cantidadPlatos <= 0) {
      cout << ROJO << "Fuera de rango" << DEFECTO << endl;
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
  Menu i;
  int numeroMenu, contMenus = 0;
  bool existeMenu = false;
  system("cls");
  cout << "REGISTRO DE PLATOS" << endl;
  cout << "Complete los campos." << endl << endl;
  cout << "Numero del menu: "; cin >> numeroMenu;
  
  ifstream archivo("menus.txt", ios::in | ios::binary);
  if(archivo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  } 

  // Calcula la cantidad de menus. 
  archivo.read(reinterpret_cast<char *>(&i), sizeof(Menu));
  while(!archivo.eof()) {
    contMenus++;
    archivo.read(reinterpret_cast<char *>(&i), sizeof(Menu));
  }
  archivo.close();

  ifstream archivoLectura("menus.txt", ios::in | ios::binary);
  if(archivoLectura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  } 

  // Llena el arreglo de menus
  Menu menus[contMenus];
  for(int i = 0; i < contMenus; i++){
    archivoLectura.read(reinterpret_cast<char *>(&menus[i]), sizeof(Menu));
  }
  archivoLectura.close();

  // Busca el menu
  for(int i = 0; i < contMenus; i++){
    if(menus[i].numero == numeroMenu && !menus[i].registroPlatos) {
      // Registra los ingredientes de los platos
      for(int k = 0; k < menus[i].cantidadPlatos; k++) {
        // Revisa que no sea un campo vacio
        do {
          cout << "Ingredientes del plato " << menus[i].platos[k].nombre << ": "; fflush(stdin); gets(menus[i].platos[k].ingredientes); 
          mayusculas(menus[i].platos[k].ingredientes);
          if(menus[i].platos[k].ingredientes[0] == '\0') cout << ROJO << "El nombre del plato no puede estar vacio." << DEFECTO << endl;
        } while(menus[i].platos[k].ingredientes[0] == '\0');
      }
      existeMenu = true;
      menus[i].registroPlatos = true;
      break;
    }

    if(menus[i].numero == numeroMenu && menus[i].registroPlatos) {
      cout << ROJO << "Los platos de este menu ya han sido registrados" << DEFECTO << endl;
      system("pause");
      return; 
    }

  }

  // Verifica si el menu no fue encontrado
  if(!existeMenu) {
    cout << ROJO << "El numero ingresado no esta registrado." << DEFECTO << endl; 
    system("pause");
    return;
  }

  /**
   * En este punto ya se encontro el menu y los ingredientes de los platos fueron registrados.
   * Se actualiza el archivo de menus.
   */
  ofstream archivoEscritura("menus.txt", ios::out | ios::binary);
   if(archivoEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  } 

  for(int i = 0; i < contMenus; i++) {
    archivoEscritura.write(reinterpret_cast<char *>(&menus[i]), sizeof(Menu));
  }
  archivoEscritura.close();

  cout << endl << VERDE << "Los ingredientes de los platos fueron registrados." << DEFECTO << endl;
  system("pause");
}

void consultas() {
  int entrada, opcion = 1;
  do {
    system("cls");
    cout << DEFECTO << "CONSULTAS (GESTION RESTAURANTE)" << endl;
    cout << DEFECTO << "Utilice las flechas del teclado para desplazarse." << endl;
    cout << DEFECTO << "Utilice el enter para escoger su opcion." << endl << endl;
    cout << DEFECTO << "Seleccione una opcion: " << endl << endl;
    cout << (opcion == 1 ? AZUL : "") << (opcion == 1 ? "> " : "") << (opcion == 1 ? DEFECTO : GRIS) << "Listar carta" << endl;
    cout << (opcion == 2 ? AZUL : "") << (opcion == 2 ? "> " : "") << (opcion == 2 ? DEFECTO : GRIS) << "Menu" << endl;
    cout << (opcion == 3 ? AZUL : "") << (opcion == 3 ? "> " : "") << (opcion == 3 ? DEFECTO : GRIS) << "Menu por estudiante" << endl; 
    cout << (opcion == 4 ? AZUL : "") << (opcion == 4 ? "> " : "") << (opcion == 4 ? DEFECTO : GRIS) << "Salir" << endl;
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
      if(entrada == 80 || entrada == 77) opcion = (opcion == 4) ? 1 : opcion + 1;
      if(entrada == 72 || entrada == 75) opcion = (opcion == 1) ? 4 : opcion - 1;
    }

    /**
     * Una vez confirmada la opción del usuario y teniendo en cuenta el codigo ASCII 
     * del enter (13) se gestiona la selección.
     */ 
    else if(entrada == 13) {
      switch(opcion) {
        case 1: consultaListarCarta(); break;
        case 2: consultaMenu(); break;
        case 3: break;
        case 4: break;
      }
    }
  } while(opcion != 4 || entrada != 13);
}

void consultaListarCarta() {
  Menu menu;
  system("cls");
  cout << "LISTAR CARTA" << endl;

  ifstream archivo("menus.txt", ios::in | ios::binary);
  if(archivo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  }

  archivo.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  while(!archivo.eof()) {
    if(menu.registroPlatos) {
      cout << endl << "Menu No. " << menu.numero << endl;
      for(int i = 0; i < menu.cantidadPlatos; i++) {
        cout << i + 1 << ". " << menu.platos[i].nombre << endl;
      }
      cout << "Coste: $" << menu.coste << endl;
    }
    archivo.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  }
  archivo.close();
  cout << endl << ROJO << "[SALIR] " << DEFECTO;; system("pause");
}

void consultaMenu() {
  Menu menu;
  int n;
  bool existeMenu = false;
  system("cls");
  cout << "MENU" << endl << "Numero del menu: "; cin >> n;

  ifstream archivo("menus.txt", ios::in | ios::binary);
  if(archivo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  }
  
  archivo.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  while(!archivo.eof()) {

    if(menu.numero == n && menu.registroPlatos) {
      cout << endl << "Menu No. " << menu.numero << endl;
      for(int i = 0; i < menu.cantidadPlatos; i++) {
        cout << endl << menu.platos[i].nombre << endl;
        cout << "Ingredientes: " << menu.platos[i].ingredientes << endl;
      }
      existeMenu = true;
      break;
    }
    if(menu.numero == n && !menu.registroPlatos) {
      cout << ROJO << "Los platos de este menu no han sido registrados." << DEFECTO << endl;
      system("pause");
      return;
    }
    archivo.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  }
  archivo.close();

  if(!existeMenu) {
    cout << ROJO << "El numero no coincide con ningun menu." << DEFECTO << endl;
    system("pause");
    return;
  }

  cout << endl << ROJO << "[SALIR] " << DEFECTO;; system("pause");
}

// GESTION ACADEMICA

void gestionAcademica() {
  int entrada, opcion = 1;
  do {
    system("cls");
    cout << DEFECTO << "GESTION ACADEMICA" << endl;
    cout << DEFECTO << "Utilice las flechas del teclado para desplazarse." << endl;
    cout << DEFECTO << "Utilice el enter para escoger su opcion." << endl << endl;
    cout << DEFECTO << "Seleccione una opcion: " << endl << endl;
    cout << (opcion == 1 ? AZUL : "") << (opcion == 1 ? "> " : "") << (opcion == 1 ? DEFECTO : GRIS) << "Matricula" << endl;
    cout << (opcion == 2 ? AZUL : "") << (opcion == 2 ? "> " : "") << (opcion == 2 ? DEFECTO : GRIS) << "Dar de baja matricula" << endl;
    cout << (opcion == 3 ? AZUL : "") << (opcion == 3 ? "> " : "") << (opcion == 3 ? DEFECTO : GRIS) << "Registro de acudientes" << endl; 
    cout << (opcion == 4 ? AZUL : "") << (opcion == 4 ? "> " : "") << (opcion == 4 ? DEFECTO : GRIS) << "Calculo pago mensualidad" << endl;
    cout << (opcion == 5 ? AZUL : "") << (opcion == 5 ? "> " : "") << (opcion == 5 ? DEFECTO : GRIS) << "Registro de pago mensualidad" << endl;
    cout << (opcion == 6 ? AZUL : "") << (opcion == 6 ? "> " : "") << (opcion == 6 ? DEFECTO : GRIS) << "Consultas" << endl;
    cout << (opcion == 7 ? AZUL : "") << (opcion == 7 ? "> " : "") << (opcion == 7 ? DEFECTO : GRIS) << "Salir" << endl;
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
      if(entrada == 80 || entrada == 77) opcion = (opcion == 7) ? 1 : opcion + 1;
      if(entrada == 72 || entrada == 75) opcion = (opcion == 1) ? 7 : opcion - 1;
    }

    /**
     * Una vez confirmada la opción del usuario y teniendo en cuenta el codigo ASCII 
     * del enter (13) se gestiona la selección.
     */ 
    else if(entrada == 13) {
      switch(opcion) {
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
      }
    }
  } while(opcion != 7 || entrada != 13);
}
/**
 * Kevin Andres Gomez Meza - 0222220034
 * Boris David Bello del Rio - 0222220046
 * Juan Camilo Corrales Fonseca - 0222220044 
 */

#include "index.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
using namespace std;

void gestionRestaurante();
void ingresarMenu();
void registrarPlato();
void asignarMenuPorEstudiante();
void facturacion();
void consultasRestaurante();
void consultaListarCarta();
void consultaMenu();
void consultaMenuPorEstudiante();

void gestionAcademica();
void matricula();
void darBajaMatricula();
void registrarAcudiente();
void calcularMensualidad();
void pagarMensualidad();
void consultasAcademica();
void listaActivos();
void listaConBajas();
void reporteEstadoFinanciero();
void consultaPorEstudiante();

int validacionAbonanteId(long id, long id_afiliado);
bool existeAcudienteId(long id);
bool existeMatricula(long id);

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
        case 3: asignarMenuPorEstudiante(); break;
        case 4: facturacion(); break;
        case 5: consultasRestaurante(); break;
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
        if(strcmp(menuEscritura.platos[k].nombre, menuEscritura.platos[i].nombre) == 0) existePlato = true;
      }
      if(existePlato) cout << ROJO << "El nombre de un plato no puede estar repetido en un mismo menu." << DEFECTO << endl;
    } while(menuEscritura.platos[i].nombre[0] == '\0' || existePlato);
  }

  //Ingresa el coste del menu
  do {
    cout << "Coste total: $" ; cin >> menuEscritura.coste;
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

    // Evita que se se reescriban los ingredientes, preeve desencadenar una alergia en dado caso a un niño.
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

void asignarMenuPorEstudiante() {
  int indice, numeroMenu, cantidadMatriculas = 0, cantidadMenusFiltrados = 0, cont = 0;
  bool menuApto, esNumeroValido = false;
  Consumo consumo;
  Matricula m;
  Menu menu;
  long id;

  system("cls");
  cout << "ASIGNAR MENU POR ESTUDIANTE" << endl;
  cout << "Ingrese el numero de matricula: "; cin >> id;

  // Verifica si la matricula no existe. (Finaliza la funcion)
  if(!existeMatricula(id)) {
    cout << ROJO << "El numero de matricula no esta registrado." << DEFECTO << endl;
    system("pause");
    return;
  } 

  // Cuenta las cantidad de niños matriculados.
  ifstream archivo("matriculas.txt", ios::in | ios::binary);
  if(archivo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
		system("pause");
		exit(0);
  }
  archivo.read(reinterpret_cast<char *>(&m), sizeof(Matricula));
  while(!archivo.eof()) {
    cantidadMatriculas++;
    archivo.read(reinterpret_cast<char *>(&m), sizeof(Matricula));
  }
  archivo.close();

  // Pasa las matriculas a un arreglo struct.
  ifstream archivoLectura("matriculas.txt", ios::in | ios::binary);
  if(archivoLectura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
		system("pause");
		exit(0);
  }
  Matricula matriculas[cantidadMatriculas];
  for(int i = 0; i < cantidadMatriculas; i++) {
    archivoLectura.read(reinterpret_cast<char *>(&matriculas[i]), sizeof(Matricula));
    if(matriculas[i].id == id) indice = i;
  }
  archivoLectura.close();

  // Verifica si la matricula esta dada de baja (Finaliza la funcion)
  if(!matriculas[indice].estado) {
    cout << ROJO << "Esta matricula esta dada de baja." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Verifica que se ha alcanzado el maximo de dias (Finaliza la funcion)
  if(matriculas[indice].dias == DIAS_MAX) {
    cout << ROJO << "Se ha alcanzado el limite de dias para este estudiante." << DEFECTO << endl;
    system("pause");
    return;
  }

  cout << "Estudiante: " << matriculas[indice].nombre << endl; 

  // Cuenta las cantidad de menus para filtrar.
  ifstream archivoMenus("menus.txt", ios::in | ios::binary);
  if(archivoMenus.fail()) {
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0);    
  } 
  archivoMenus.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  while(!archivoMenus.eof()) {
    menuApto = true;
    // Recorre las alergias
    if(menu.registroPlatos) {
      for(int i = 0; i < matriculas[indice].numeroAlergias; i++) {
        // Recorre los del menu determinado
        for(int k = 0; k < menu.cantidadPlatos; k++) {
          // Compara la i alergia con k plato del menu actual.
          if(strstr(menu.platos[k].ingredientes, matriculas[indice].alergias[i].nombre) != NULL) {
            menuApto = false;
            break;  
          } 
        }
        if(!menuApto) break;
      }
      if(menuApto) cantidadMenusFiltrados++;
    }
    archivoMenus.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  }
  archivoMenus.close();

  // Verifica si no hay menus aptos para el niño. (Finaliza la funcion)
  if(cantidadMenusFiltrados == 0) {
    cout << ROJO << "No hay menus aptos para el estudiante." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Llena el arreglo de menus aptos para el niño
  ifstream archivoMenuLectura("menus.txt", ios::in | ios::binary);
  if(archivoMenuLectura.fail()){
    cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
    system("pause");
    exit(0); 
  }
  Menu menusAptos[cantidadMenusFiltrados];
  archivoMenuLectura.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  while(!archivoMenuLectura.eof()) {
    menuApto = true;
    if(menu.registroPlatos) {
      // Recorre las alergias
      for(int i = 0; i < matriculas[indice].numeroAlergias; i++) {
        // Recorre los del menu determinado
        for(int k = 0; k < menu.cantidadPlatos; k++) {
          // Compara la i alergia con k plato del menu actual.
          if(strstr(menu.platos[k].ingredientes, matriculas[indice].alergias[i].nombre) != NULL) {
            menuApto = false;
            break;  
          } 
        }
        if(!menuApto) break;
      }
      if(menuApto) {
        menusAptos[cont] = menu;
        cont++;
      }
    }
    archivoMenuLectura.read(reinterpret_cast<char *>(&menu), sizeof(Menu));
  }
  archivoMenuLectura.close();

  // Imprime los menus disponibles
  cout << "Dia " << matriculas[indice].dias + 1 << endl << "Menus Seleccionables" << endl;
  for(int i = 0; i < cantidadMenusFiltrados ; i++) {
    cout << endl << "Menu No. " << menusAptos[i].numero  << endl;
    for(int k = 0; k < menusAptos[i].cantidadPlatos; k++) {
      cout << k + 1 << ". " << menusAptos[i].platos[k].nombre << endl;
    }
  }

  // Verifica que el menu seleccionado este dentro los menus aptos para registrar el consumo.
  do {
    cout << endl << "Seleccione el menu: "; cin >> numeroMenu;
    for(int i = 0; i < cantidadMenusFiltrados; i++) {
      if(menusAptos[i].numero == numeroMenu) {
        matriculas[indice].dias++;
        consumo.idMatricula = matriculas[indice].id;
        strcpy(consumo.nombreMatricula, matriculas[indice].nombre);
        consumo.numeroMenu = numeroMenu;
        consumo.costeMenu = menusAptos[i].coste;
        consumo.dia = matriculas[indice].dias;
        esNumeroValido = true;
        break;
      }
    }
    if(!esNumeroValido) cout << ROJO << "Escoja el numero de un menu apto." << DEFECTO << endl;
  } while(!esNumeroValido);

  /**
   * Redefine los campos banderas, para evitar que la matricula se de de baja o 
   * quiera efectuar pago sin haber hecho los calculos correspondientes. 
   * (Respetar las reglas del negocio) 
   */
  matriculas[indice].seCalculoFacturacion = matriculas[indice].seCalculoMensualidad = matriculas[indice].sePagoMensualidad = false;

  // Guarda el consumo
  ofstream archivoConsumo("consumos.txt", ios::app | ios::binary);
  if(archivoConsumo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
    system("pause");
    exit(0); 
  }
  archivoConsumo.write(reinterpret_cast<char *>(&consumo), sizeof(Consumo));
  archivoConsumo.close();

  // Actualiza las matriculas
  ofstream archivoMatricula("matriculas.txt", ios::out | ios::binary);
  if(archivoMatricula.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  }
  for(int i = 0; i < cantidadMatriculas; i++) {
    archivoMatricula.write(reinterpret_cast<char *>(&matriculas[i]), sizeof(Matricula));
  }
  archivoMatricula.close();

  cout << VERDE << "Menu asignado exitosamente..." << DEFECTO << endl;
  system("pause");
}

void consultasRestaurante() {
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
        case 3: consultaMenuPorEstudiante(); break;
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

void facturacion() {
  int cantidadMatriculas = 0, indice;
  long id;
  Matricula m;
  Consumo c;
  system("cls");
  cout << "FACTURACION" << endl << "Ingrese el numero de matricula: "; cin >> id;

  // Verifica si la matricula no existe (Finaliza funcion)
  if(!existeMatricula(id)) {
    cout << ROJO << "El numero de matricula ingresado no esta registrado" << DEFECTO << endl;
    system("pause");
    return;
  }

  // Cuenta las cantidad de matriculas
  ifstream archivom("matriculas.txt", ios::in | ios::binary);
  if(archivom.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  }
  while(archivom.read(reinterpret_cast<char *>(&m), sizeof(Matricula))) cantidadMatriculas++;
  archivom.close();

  // Llena el vector struct 
  ifstream archivoLectura("matriculas.txt" , ios::in | ios::binary);
  if(archivoLectura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  } 
  Matricula matriculas[cantidadMatriculas];
  for(int i = 0; i < cantidadMatriculas; i++) {
    archivoLectura.read(reinterpret_cast<char *>(&m), sizeof(Matricula));
    if(m.id == id) indice = i;
    matriculas[i] = m;
  }
  archivoLectura.close();

  // Verifica si la matricula ya se dio de baja (Finaliza funcion)
  if(!matriculas[indice].estado) {
    cout << ROJO << "Esta matricula ya fue dada de baja anteriormente." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Calcula las facturacion
  ifstream archivoConsumo("consumos.txt", ios::in | ios::binary);
  if(archivoConsumo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
    system("pause");
    exit(0); 
  } 
  matriculas[indice].facturacion = 0;
  while(archivoConsumo.read(reinterpret_cast<char *>(&c), sizeof(Consumo))) {
    if(c.idMatricula == id) matriculas[indice].facturacion += c.costeMenu;
  }
  archivoConsumo.close();
  matriculas[indice].seCalculoFacturacion = true;

  cout << "ESTUDIANTE: " << matriculas[indice].nombre << endl;
  cout << "Coste comidas realizadas: $" << matriculas[indice].facturacion << endl;

  // Guarda en el archivo
  ofstream archivo("matriculas.txt", ios::out | ios::binary);
  if(archivo.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  }
  for(int i = 0; i < cantidadMatriculas; i++) {
    archivo.write(reinterpret_cast<char *>(&matriculas[i]), sizeof(Matricula));
  }
  archivo.close();

  cout << ROJO << "[SALIR] " << DEFECTO; system("pause");
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

void consultaMenuPorEstudiante() {
	Consumo c;
	//Abrir archivos binarios
	ifstream archivoc("consumos.txt", ios::in | ios::binary);
	if(archivoc.fail()){
		cout << "Error al abrir el archivo consumos.txt." << endl;
		system("pause");
		exit(0);
	}
	system("cls");
	cout << AZUL << "MENU POR ESTUDIANTES" << endl;
	cout << "--------------------------------------------" << DEFECTO << endl;
	//Recorrer el archivo y mostrar datos
	archivoc.read(reinterpret_cast<char *>(&c), sizeof(Consumo));
	while(!archivoc.eof()){
    //Mostrar reporte
    cout << "Estudiante " << c.nombreMatricula << endl;
    cout << "Coste del menu: " << c.costeMenu << endl;
    cout << "Dia: " << c.dia << endl;
    cout << "ID de la matricula: " << c.idMatricula << endl;
    cout << "Numero de menu: " << c.numeroMenu << endl;
    cout << "-------------------------------------------" << endl;
    archivoc.read(reinterpret_cast<char *>(&c), sizeof(Consumo)); 
	}
	archivoc.close();
	system("pause");
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
        case 1: matricula(); break;
        case 2: darBajaMatricula(); break;
        case 3: registrarAcudiente(); break;
        case 4: calcularMensualidad(); break;
        case 5: pagarMensualidad(); break;
        case 6: consultasAcademica(); break;
        case 7: break;
      }
    }
  } while(opcion != 7 || entrada != 13);
}

void darBajaMatricula() {
	long numeroMatricula;
  int cantidadMatriculas = 0, cantidadConsumos = 0, cont = 0, indice;
  short diasMaximosPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool matriculaEncontrada = false;
	Matricula m;
  Consumo c;

	system("cls");
	cout << "DAR DE BAJA MATRICULA\n";
	cout << "Complete los campos." << endl << endl;
	
	// Solicitar numero o ID de matricula
	cout << "Ingrese el numero de matricula: "; cin >> numeroMatricula;
	
	if(existeMatricula(numeroMatricula)) {
    
		// Abrir archivo binario de matriculas lectura
		ifstream archivom("matriculas.txt", ios::in | ios::binary);
  	if(archivom.fail()) {
    	cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    	system("pause");
    	exit(0); 
  	} 

    // Cuenta las cantidad de matriculas
    while(archivom.read(reinterpret_cast<char *>(&m), sizeof(Matricula))) cantidadMatriculas++;
    archivom.close();

    // Llena el vector struct 
    ifstream archivoLectura("matriculas.txt" , ios::in | ios::binary);
    if(archivoLectura.fail()) {
    	cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    	system("pause");
    	exit(0); 
  	} 
    Matricula matriculas[cantidadMatriculas];
    for(int i = 0; i < cantidadMatriculas; i++) {
      archivoLectura.read(reinterpret_cast<char *>(&m), sizeof(Matricula));
      if(m.id == numeroMatricula) indice = i;
      matriculas[i] = m;
    }
    archivoLectura.close();

    // Verifica si la matricula ya se dio de baja (Finaliza funcion)
    if(!matriculas[indice].estado) {
      cout << ROJO << "Esta matricula ya fue dada de baja anteriormente." << DEFECTO << endl;
      system("pause");
      return;
    }

    // Verifica si la matricula esta a paz y salvo (Finaliza funcion)
    if(!matriculas[indice].sePagoMensualidad) {
      cout << ROJO << "Esta matricula se encuentra morosa." << endl << "Para dar de baja debe estar paz y salvo" << DEFECTO << endl;
      system("pause");
      return;
    }

    cout << endl << "ESTUDIANTE: " << matriculas[indice].nombre;
    // Pide los datos
    do {
      cout << endl << "Fecha de baja" << endl;  
      cout << "DD: " ; cin >> matriculas[indice].retiro.dia; 
      cout << "MM: " ; cin >> matriculas[indice].retiro.mes; 
      cout << "AAAA: " ; cin >> matriculas[indice].retiro.anio;
      if(compararFechas(matriculas[indice].retiro, matriculas[indice].ingreso) <= 0) cout << ROJO << "Fecha invalida. Recuerde que para retirarse debe ser una fecha posterior a la de ingreso." << DEFECTO << endl; 
    } while(compararFechas(matriculas[indice].retiro, matriculas[indice].ingreso) <= 0);

    // Da de baja.
    matriculas[indice].estado = false;

		// Guardar en el archivo (escribir)
    ofstream archivoc("matriculas.txt", ios::out | ios::binary);
    if(archivoc.fail()) {
      cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
      system("pause");
      exit(0); 
    }
    for(int i = 0; i < cantidadMatriculas; i++) {
      archivoc.write(reinterpret_cast<char *>(&matriculas[i]), sizeof(Matricula));
    }
    archivoc.close();

    // --- Elimina los consumos del estudiante dado de baja
    // Cuenta la cantidad de consumos que no seran eliminados
    ifstream archivoConsumos("consumos.txt", ios::in | ios::binary);
    if(archivoConsumos.fail()) {
      cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
      system("pause");
      exit(0); 
    }
    while(archivoConsumos.read(reinterpret_cast<char *>(&c), sizeof(Consumo))) {
      if(c.idMatricula != numeroMatricula) cantidadConsumos++;
    }
    archivoConsumos.close();

    // LLena el arreglo de consumos
    Consumo consumos[cantidadConsumos];
    ifstream archivoConsumosLectura("consumos.txt", ios::in | ios::binary);
    if(archivoConsumosLectura.fail()) {
      cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
      system("pause");
      exit(0); 
    }
    while(archivoConsumosLectura.read(reinterpret_cast<char *>(&c), sizeof(Consumo))) {
      if(c.idMatricula != numeroMatricula) {
        consumos[cont] = c;
        cont++;
      }
    }
    archivoConsumosLectura.close();

    // Guarda los consumos actualizados
    ofstream archivoConsumosEscritura("consumos.txt", ios::out | ios::binary);
    if(archivoConsumosEscritura.fail()) {
      cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
      system("pause");
      exit(0); 
    }
    for(int i = 0; i < cantidadConsumos; i++) {
      archivoConsumosEscritura.write(reinterpret_cast<char *>(&consumos[i]), sizeof(Consumo));
    }
    archivoConsumosEscritura.close();
  		
  	cout << VERDE << "Estudiante dado de baja exitosamente" << DEFECTO << endl;
  } else {
  	cout << ROJO << "No se encontro una matricula con el numero " << numeroMatricula << "." << DEFECTO << endl;
	}
	system("pause");
}

void matricula() {
  Matricula matricula;
  
  // Lee los datos ingresados del usuario
  system("cls");
  cout << "MATRICULAR ESTUDIANTE" << endl << "El rango de edad debe ser entre 2 - 5." << endl << "Complete los campos." << endl << endl;

  do {
    cout << "Numero de la matricula: "; cin >> matricula.id;
    if(matricula.id <= 0) cout << ROJO << "El numero debe ser mayor que 0" << DEFECTO << endl;
    if(existeMatricula(matricula.id)) cout << ROJO << "El numero ingresado ya le pertenece a otra matricula" << DEFECTO << endl;
  } while(matricula.id <= 0 or existeMatricula(matricula.id));

  // Ingresa el nombre del niño
  do {
    cout << "Nombre del estudiante: "; fflush(stdin); gets(matricula.nombre); mayusculas(matricula.nombre);
    // Revisa que el nombre no este vacio.
    if(matricula.nombre[0] == '\0') cout << ROJO << "El nombre del estudiante no puede estar vacio." << DEFECTO << endl;
  } while(matricula.nombre[0] == '\0');
  
  // Ingresa la fecha de naciemiento
  cout << endl << "Fecha de nacimiento (DD/MM/AAAA)" << endl;
  short diasMaximosPorMesA[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  do {
		cout << "AAAA: "; cin >> matricula.nacimiento.anio;
		if(matricula.nacimiento.anio < 2000) cout << ROJO << "Rango a partir del 2000's." << DEFECTO << endl;
	} while(matricula.nacimiento.anio < 2000);

	// Verifica si es año biciesto, cambia el dia maximo para febrero.
	if((matricula.nacimiento.anio % 4 == 0 && matricula.nacimiento.anio % 100 != 0) || (matricula.nacimiento.anio % 400 == 0)) diasMaximosPorMesA[1] = 29;

	do {
		cout << "MM: "; cin >> matricula.nacimiento.mes;
		if(matricula.nacimiento.mes < 1 || matricula.nacimiento.mes > 12) cout << ROJO << "El mes ingresado debe estar comprendido entre 1 y 12." << DEFECTO << endl;
	} while(matricula.nacimiento.mes < 1 || matricula.nacimiento.mes > 12);

	do {
		cout << "DD: "; cin >> matricula.nacimiento.dia;
		if(matricula.nacimiento.dia < 1 || matricula.nacimiento.dia > diasMaximosPorMesA[matricula.nacimiento.mes - 1]) cout << ROJO << "El dia ingresado debe estar comprendido entre 1 y " << diasMaximosPorMesA[matricula.nacimiento.mes - 1] << "." << DEFECTO << endl;
	} while(matricula.nacimiento.dia < 1 || matricula.nacimiento.dia > diasMaximosPorMesA[matricula.nacimiento.mes - 1]);

  // Ingresa fecha de ingreso. Rango de edad 2-5 años
  cout << endl << "Fecha de ingreso (DD/MM/AAAA)" << endl;
	short diasMaximosPorMesB[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	do {
		cout << "AAAA: "; cin >> matricula.ingreso.anio;
		if(matricula.ingreso.anio - matricula.nacimiento.anio > 5 || matricula.ingreso.anio - matricula.nacimiento.anio < 3) cout << ROJO << "El rango de edad esta entre poco mas de 2  y menor a 5." << DEFECTO << endl;
	} while(matricula.ingreso.anio - matricula.nacimiento.anio > 5 || matricula.ingreso.anio - matricula.nacimiento.anio < 3);

	// Verifica si es año biciesto, cambia el dia maximo para febrero.
	if((matricula.ingreso.anio % 4 == 0 && matricula.ingreso.anio % 100 != 0) || (matricula.ingreso.anio % 400 == 0)) diasMaximosPorMesB[1] = 29;

	do {
		cout << "MM: "; cin >> matricula.ingreso.mes;
		if(matricula.ingreso.mes < 1 || matricula.ingreso.mes > 12) cout << ROJO << "El mes ingresado debe estar comprendido entre 1 y 12." << DEFECTO << endl;
	} while(matricula.ingreso.mes < 1 || matricula.ingreso.mes > 12);

	do {
		cout << "DD: "; cin >> matricula.ingreso.dia;
		if(matricula.ingreso.dia < 1 || matricula.ingreso.dia > diasMaximosPorMesB[matricula.ingreso.mes - 1]) cout << ROJO << "El dia ingresado debe estar comprendido entre 1 y " << diasMaximosPorMesB[matricula.ingreso.mes - 1] << "." << DEFECTO << endl;
	} while(matricula.ingreso.dia < 1 || matricula.ingreso.dia > diasMaximosPorMesB[matricula.ingreso.mes - 1]);

  // Registro de alergias
  cout << endl;
  do {
    cout << "A cuantos ingredientes es alergico?: "; cin >> matricula.numeroAlergias;
    if(matricula.numeroAlergias > 100 || matricula.numeroAlergias < 0) cout << ROJO << "Fuera de rango" << DEFECTO << endl;
  } while(matricula.numeroAlergias > 100 || matricula.numeroAlergias < 0);
  
  bool alergiaRepetida;
  for(int i = 0; i < matricula.numeroAlergias; i++) {
    do {
      alergiaRepetida = false;
      cout << "Alergia No. " << i + 1 << ": "; fflush(stdin); gets(matricula.alergias[i].nombre); mayusculas(matricula.alergias[i].nombre);
      // Revisa que el campo no se quede vacio.
      if(matricula.alergias[i].nombre[0] == '\0') cout << ROJO << "El campo no puede estar vacio." << DEFECTO << endl;

      // Revisa que no se repita una alergia.
      for(int k = 0; k < i; k++) {
        if(strcmp(matricula.alergias[i].nombre, matricula.alergias[k].nombre) == 0) {
          alergiaRepetida = true;
          break;
        }
      }
      if(alergiaRepetida) cout << ROJO << "Ya esta alergia se ingreso." << DEFECTO << endl;
    } while(matricula.alergias[i].nombre[0] == '\0' || alergiaRepetida); 
  }
  matricula.estado = true;

  // Escribe en el archivo
  ofstream archivoEscritura("matriculas.txt", ios::app | ios::binary);
  if(archivoEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  }
  archivoEscritura.write(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
  archivoEscritura.close();
  cout << endl << VERDE << "Matricula ingresado exitosamente..." << DEFECTO << endl;
  system("pause");
}

void registrarAcudiente() {
  Acudiente acudiente;
  Matricula matricula;
  long id;

  // Lee los datos ingresados del usuario
  system("cls");
  cout << "INGRESAR ACUDIENTE" << endl << "Complete los campos." << endl << endl;
  cout << "Digite el  numero de la matricula del estudiante: "; cin >> id;
  
  // Verifica si la matricula no existe
  if(!existeMatricula(id)) {
    cout << ROJO << "Matricula no registrada." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Verifica si la matricula fue dada de baja
  ifstream archivoMatricula("matriculas.txt", ios::in | ios::binary);
	if(archivoMatricula.fail()) {
		cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
		system("pause");
		exit(0);
	}
  archivoMatricula.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
  while(!archivoMatricula.eof()) {
    if(id == matricula.id and !matricula.estado) {
      cout << ROJO << "El estudiante esta dado de baja" << DEFECTO << endl;
      system("pause");
      return;
    } else if (id == matricula.id and matricula.estado) {
      cout << endl << "ESTUDIANTE: " << matricula.nombre << endl;
      break;
    }
    archivoMatricula.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
  }
  archivoMatricula.close();

  acudiente.id_afilado = id;

  // Datos del acudiente
  cout << "DATOS DEL ACUDIENTE" << endl;
  do {
    cout << "ID: "; cin >> acudiente.id;
    if(acudiente.id <= 0) cout << ROJO << "Fuera de rango" << DEFECTO << endl;
    if(existeAcudienteId(acudiente.id)) cout << ROJO << "El acudiente ya ha sido registrado previamente" << DEFECTO << endl;
  } while(acudiente.id <= 0 or existeAcudienteId(acudiente.id));

  do {
    cout << "Nombre: "; fflush(stdin); gets(acudiente.nombre);    
    // Revisa que el nombre no este vacio
    if(acudiente.nombre[0] == '\0') cout << ROJO << "El nombre del acudiente no puede estar vacio." << DEFECTO << endl;
  } while(acudiente.nombre[0] == '\0');

  do {
    cout << "Parentesco: "; fflush(stdin); gets(acudiente.parentesco); 
    // Revisa que el parentesco no este vacio
    if(acudiente.parentesco[0] == '\0') cout << ROJO << "El parentesco del acudiente no puede estar vacio." << DEFECTO << endl;
  } while(acudiente.parentesco[0] == '\0');
  
  do {
    cout << "Direccion: "; fflush(stdin); gets(acudiente.direccion);    
    // Revisa que la direccion no este vacia
    if(acudiente.direccion[0] == '\0') cout << ROJO << "La dirrecion del acudiente no puede estar vacio." << DEFECTO << endl;
  } while(acudiente.direccion[0] == '\0');

  do {
    cout << "Telefono: "; cin >> acudiente.telefono;
    if(acudiente.telefono <= 0) cout << ROJO << "Digite un numero de telefono valido." << DEFECTO << endl;
  } while(acudiente.telefono <= 0);

  // Escribe en el archivo
  ofstream archivoEscritura("acudientes.txt", ios::app | ios::binary);
  if(archivoEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
    system("pause");
    exit(0); 
  }
  archivoEscritura.write(reinterpret_cast<char *>(&acudiente), sizeof(Acudiente));
  archivoEscritura.close();
  cout << endl << VERDE << "Acudiente ingresado exitosamente..." << DEFECTO << endl;
  system("pause");
}

void calcularMensualidad() {
  long id, facturacion, mensualidad;
  int contMatricula = 0, existeCosto = 0, indice;
  CostoFijo costoFijo;
  Matricula i;

  system("cls");
  // Verifica si no esta el coste fijo definido
  ifstream archivoa("costo.txt", ios::in | ios::binary);
  if(archivoa.fail()){
    do {
      cout << "Ingrese el coste fijo: $"; cin >> costoFijo.valor;
      if(costoFijo.valor < COSTO_FIJO_MIN) cout << ROJO << "El costo fijo no debe ser inferior a $" << COSTO_FIJO_MIN << "." << DEFECTO << endl;
    } while(costoFijo.valor < COSTO_FIJO_MIN); 

    // Guarda en el archivo el coste fijo
    ofstream archivo("costo.txt", ios::out | ios::binary);
    if(archivo.fail()) {
      cout << ROJO << "Se encontro un error en el archivo costo.txt." << endl;
      system("pause");
      exit(0); 
    } 
    archivo.write(reinterpret_cast<char *>(&costoFijo), sizeof(CostoFijo));
    archivo.close();
  }

  system("cls");
  // Lee el archivo del costo fijo
  ifstream archivoc("costo.txt", ios::in | ios::binary);
  if(archivoc.fail()) {
    cout << ROJO << "Se encontro un error en el archivo costo.txt." << endl;
    system("pause");
    exit(0); 
  } 
  archivoc.read(reinterpret_cast<char *>(&costoFijo), sizeof(CostoFijo));
  archivoc.close();

  // Lee los datos ingresados del usuario
  cout << "CALCULAR PAGO MENSUALIDAD DE ESTUDIANTE" << endl;
  cout << "Complete los campos." << endl << endl;
  cout << "Ingrese el numero de matricula del estudiante: "; cin >> id;

  // Verifica si la matricula no existe
  if(!existeMatricula(id)) {
    cout << ROJO << "Matricula no registrada." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Calcula la cantidad de matriculas. 
  ifstream archivot("matriculas.txt", ios::in | ios::binary);
  if(archivot.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  } 
  while(archivot.read(reinterpret_cast<char *>(&i), sizeof(Matricula))) contMatricula++;
  archivot.close();

  // Llena el arreglo de matriculas.
  ifstream archivoLecturab("matriculas.txt", ios::in | ios::binary);
  if(archivoLecturab.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  } 
  Matricula matriculas[contMatricula];
  for(int k = 0; k < contMatricula; k++){
    archivoLecturab.read(reinterpret_cast<char *>(&matriculas[k]), sizeof(Matricula));
    if(matriculas[k].id == id) indice = k;
  }
  archivoLecturab.close();

  // Verifica si la matricula fue dada de baja (Finaliza funcion)
  if(!matriculas[indice].estado) {
    cout << ROJO << "La matricula fue dada de baja." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Verifica si la matricula no hizo la facturacion (Finaliza funcion)
  if(!matriculas[indice].seCalculoFacturacion) {
    cout << ROJO << "Debe realizar la facturacion." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Si esta activo y tiene la facturacion ok, calculara la mensualidad
  matriculas[indice].pagoMensualidad = costoFijo.valor + matriculas[indice].facturacion;
  matriculas[indice].seCalculoMensualidad = true;

  // Guarda en el archivo
  ofstream archivoEscritura("matriculas.txt", ios::out | ios::binary);
  if(archivoEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  } 
  for(int i = 0; i < contMatricula; i++) {
    archivoEscritura.write(reinterpret_cast<char *>(&matriculas[i]), sizeof(Matricula));
  }
  archivoEscritura.close();
  
  cout << "ESTUDIANTE: " << matriculas[indice].nombre << endl;
  cout << "Costo de la mensualidad: $" << matriculas[indice].pagoMensualidad << endl;
  cout << ROJO << "[SALIR] " << DEFECTO; system("pause");  
}

void pagarMensualidad() {
  Matricula i;
  Acudiente acudiente, m;
  Consumo c;
  int contMatricula = 0, indice, indice1, cantidadConsumos = 0, cont = 0, contAcudientes = 0;
  long id, idAcudiente;

  // Lee los datos ingresados del usuario
  system("cls");
  cout << "PAGAR MENSUALIDAD DE ESTUDIANTE" << endl;
  cout << "Complete los campos." << endl << endl;
  cout << "Ingrese el numero de matricula del estudiante: "; cin >> id;
  
  // Verifica si la matricula no exite. (Finaliza funcion)
  if(!existeMatricula(id)) {
    cout << ROJO << "Matricula no registrada." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Cuenta la cantidad de matriculas
  ifstream archivot("matriculas.txt", ios::in | ios::binary);
  if(archivot.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  }
  while(archivot.read(reinterpret_cast<char *>(&i), sizeof(Matricula))) contMatricula++;
  archivot.close();

  // LLena el arreglo de matriculas 
  ifstream archivoLecturab("matriculas.txt", ios::in | ios::binary);
  if(archivoLecturab.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  } 
  Matricula matriculas[contMatricula];
  for(int k = 0; k < contMatricula; k++){
    archivoLecturab.read(reinterpret_cast<char *>(&matriculas[k]), sizeof(Matricula));
    if(matriculas[k].id == id) indice = k;
  }
  archivoLecturab.close();

  // Verifica si la matricula fue dada de baja. (Finaliza funcion)
  if(!matriculas[indice].estado) {
    cout << ROJO << "La matricula fue dada de baja." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Verifica si no se calculo la mensualidad. (Finaliza funcion)
  if(!matriculas[indice].seCalculoMensualidad) {
    cout << ROJO << "Debe calcular la mensualidad antes." << DEFECTO << endl;
    system("pause");
    return; 
  }

  // Verifica si ya esta paz y salvo (Finaliza funcion)
  if(matriculas[indice].sePagoMensualidad) {
    cout << ROJO << "El estudiante se encuentra paz y salvo." << DEFECTO << endl;
    system("pause");
    return;
  }

  cout << "ESTUDIANTE: " << matriculas[indice].nombre << endl;
  cout << "DATOS DEL ABONANTE" << endl;
  do {
    cout << "DNI: "; cin >> idAcudiente;   
    // Revisa que el ID sea un numero positivo
    if(idAcudiente <= 0) cout << ROJO << "El DNI tiene que ser mayor en 0." << DEFECTO << endl;
    if(validacionAbonanteId(idAcudiente, id) == 0) cout << ROJO << "El DNI ingresado esta relacionado con otra matricula." << DEFECTO << endl;
  } while(idAcudiente <= 0 or validacionAbonanteId(idAcudiente, id) == 0);
  
  // Si el DNI del acudiente no se encuentra registrado, registra los datos.
  if(validacionAbonanteId(idAcudiente, id) == -1) {
    acudiente.id = idAcudiente;
    acudiente.id_afilado = id;
    do {
      cout << "Nombre del abonante: "; fflush(stdin); gets(acudiente.nombre);   
      // Revisa que el nombre no este vacio
      if(acudiente.nombre[0] == '\0') cout << ROJO << "El nombre del abonante no puede estar vacio." << DEFECTO << endl;
    } while(acudiente.nombre[0] == '\0');
    
    do {
      cout << "Direccion del abonante: "; fflush(stdin); gets(acudiente.direccion);   
      // Revisa que la direccion no este vacia
      if(acudiente.direccion[0] == '\0') cout << ROJO << "La dirrecion del acudiente no puede estar vacio." << DEFECTO << endl;
    } while(acudiente.direccion[0] == '\0');

    do {
      cout << "Telefono del abonante: "; cin >> acudiente.telefono;
      if(acudiente.telefono <= 0) cout << ROJO << "Fuera de rango" << DEFECTO << endl;
    } while(acudiente.telefono <= 0);

    do {
      cout << "Numero de la cuenta corriente: "; cin >> acudiente.cuenta;
      if(acudiente.cuenta <= 0) {
        cout << ROJO << "Fuera de rango" << DEFECTO << endl;
      }
    } while(acudiente.cuenta <= 0);
    acudiente.abonante = true;

    // Guarda el acudiente  
    ofstream archivoEscrituraA("acudientes.txt", ios::app | ios::binary);
    if(archivoEscrituraA.fail()) {
      cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
      system("pause");
      exit(0); 
    }
    archivoEscrituraA.write(reinterpret_cast<char *>(&acudiente), sizeof(Acudiente));
    archivoEscrituraA.close();
  } else if(validacionAbonanteId(acudiente.id, id) == 1) { // Si el DNI del acudiente ya se encuentra relacionado con la matricula.
    cout << "El id ya se registro como acudiente previamente" <<endl;
    //Abre el archivo
    ifstream archivot("acudientes.txt", ios::in | ios::binary);
    if(archivot.fail()) {
      cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
      system("pause");
      exit(0); 
    }

    //Cuenta la cantidad de acudientes
    while(archivot.read(reinterpret_cast<char *>(&m), sizeof(Acudiente))) contAcudientes++;
    archivot.close();

    ifstream archivoLecturaC("acudientes.txt", ios::in | ios::binary);
    if(archivoLecturaC.fail()) {
      cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
      system("pause");
      exit(0); 
    } 
    //Asigna un array struct con la canitdad de acudientes
    Acudiente acudientes[contAcudientes];
    //Pasa los datos del archivo al array struct y encuentra la posicion del id
    for(int t = 0; t < contAcudientes; t++){
      archivoLecturaC.read(reinterpret_cast<char *>(&acudientes[t]), sizeof(Matricula));
      if(acudientes[t].id == idAcudiente) indice1 = t;
    }
    archivoLecturaC.close();

    //Mira si el acudiente es la primera vez que abona 
    if (!acudientes[indice1].abonante) {
      do {
        cout << "Digite el numero de la cuenta corriente: "; cin >> acudiente.cuenta;
        if(acudientes[indice1].cuenta <= 0) cout << ROJO << "Fuera de rango" << DEFECTO << endl;
      } while(acudientes[indice1].cuenta <= 0);
      acudientes[indice1].abonante = true;

      // Guarda los acudientes actualizados
      ofstream archivoEscritura("acudientes.txt", ios::out | ios::binary);
      if(archivoEscritura.fail()) {
        cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
        system("pause");
        exit(0); 
      } 
      for(int i = 0; i < contAcudientes; i++) {
        archivoEscritura.write(reinterpret_cast<char *>(&acudientes[i]), sizeof(Matricula));
      }
      archivoEscritura.close();
    }
  }

  matriculas[indice].dias = 0;
  matriculas[indice].pagoMensualidad = 0;
  matriculas[indice].sePagoMensualidad = true;
 
  // Guarda en el archivo las matriculas actualizadas
  ofstream archivoEscritura("matriculas.txt", ios::out | ios::binary);
  if(archivoEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
    system("pause");
    exit(0); 
  } 
  for(int i = 0; i < contMatricula; i++) {
    archivoEscritura.write(reinterpret_cast<char *>(&matriculas[i]), sizeof(Matricula));
  }
  archivoEscritura.close();

  // Elimina los consumos de la matricula paga
  // Cuenta la cantidad de consumos que no seran eliminados
  ifstream archivoConsumos("consumos.txt", ios::in | ios::binary);
  if(archivoConsumos.fail()) {
    cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
    system("pause");
    exit(0); 
  }
  while(archivoConsumos.read(reinterpret_cast<char *>(&c), sizeof(Consumo))) {
    if(c.idMatricula != id) cantidadConsumos++;
  }
  archivoConsumos.close();

  // LLena el arreglo de consumos
  Consumo consumos[cantidadConsumos];
  ifstream archivoConsumosLectura("consumos.txt", ios::in | ios::binary);
  if(archivoConsumosLectura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
    system("pause");
    exit(0); 
  }
  while(archivoConsumosLectura.read(reinterpret_cast<char *>(&c), sizeof(Consumo))) {
    if(c.idMatricula != id) {
      consumos[cont] = c;
      cont++;
    }
  }
  archivoConsumosLectura.close();

  // Guarda los consumos actualizados
  ofstream archivoConsumosEscritura("consumos.txt", ios::out | ios::binary);
  if(archivoConsumosEscritura.fail()) {
    cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
    system("pause");
    exit(0); 
  }
  for(int i = 0; i < cantidadConsumos; i++) {
    archivoConsumosEscritura.write(reinterpret_cast<char *>(&consumos[i]), sizeof(Consumo));
  }
  archivoConsumosEscritura.close();

  cout << endl << VERDE << "Pago exitoso..." << DEFECTO << endl;
  system("pause");
}

void consultasAcademica() {
  int entrada, opcion = 1;
  do {
    system("cls");
    cout << DEFECTO << "CONSULTAS (GESTION ACADEMICA)" << endl;
    cout << DEFECTO << "Utilice las flechas del teclado para desplazarse." << endl;
    cout << DEFECTO << "Utilice el enter para escoger su opcion." << endl << endl;
    cout << DEFECTO << "Seleccione una opcion: " << endl << endl;
    cout << (opcion == 1 ? AZUL : "") << (opcion == 1 ? "> " : "") << (opcion == 1 ? DEFECTO : GRIS) << "Listar estudiantes activos" << endl;
    cout << (opcion == 2 ? AZUL : "") << (opcion == 2 ? "> " : "") << (opcion == 2 ? DEFECTO : GRIS) << "Listar estudiantes con baja" << endl;
    cout << (opcion == 3 ? AZUL : "") << (opcion == 3 ? "> " : "") << (opcion == 3 ? DEFECTO : GRIS) << "Reporte de estado financiero de estudiantes" << endl; 
    cout << (opcion == 4 ? AZUL : "") << (opcion == 4 ? "> " : "") << (opcion == 4 ? DEFECTO : GRIS) << "Consulta por estudiante" << endl;
    cout << (opcion == 5 ? AZUL : "") << (opcion == 5 ? "> " : "") << (opcion == 5 ? DEFECTO : GRIS) << "Salir" << endl;
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
      if(entrada == 80 || entrada == 77) opcion = (opcion == 5) ? 1 : opcion + 1;
      if(entrada == 72 || entrada == 75) opcion = (opcion == 1) ? 5 : opcion - 1;
    }

    /**
     * Una vez confirmada la opción del usuario y teniendo en cuenta el codigo ASCII 
     * del enter (13) se gestiona la selección.
     */ 
    else if(entrada == 13) {
      switch(opcion) {
        case 1: listaActivos(); break;
        case 2: listaConBajas(); break;
        case 3: reporteEstadoFinanciero(); break;
        case 4: consultaPorEstudiante(); break;
        case 5: break;
      }
    }
  } while(opcion != 5 || entrada != 13);
}

void listaActivos() {
	Matricula matricula;
  Acudiente acudientes;
  bool bandera;
	
  ifstream archivop("matriculas.txt", ios::in | ios::binary);
	if(archivop.fail()){
		cout << ROJO << "Error al abrir el archivo matriculas.txt" << endl;
		system("pause");
		exit(0);
	}
  
  system("cls");
	cout << "----------- Lista de Estudiantes Activos -----------" << endl << endl;

	archivop.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
	while(!archivop.eof()){
		if(matricula.estado){
      bandera = false;
			cout << "Numero de matricula: " << matricula.id << endl;	
			cout << "Nombre del estudiante: " << matricula.nombre << endl;	

			ifstream archivo("acudientes.txt", ios::in | ios::binary);
	    if(archivo.fail()){
		    cout<<"Error al abrir el archivo acudientes.txt"<<endl;
		    system("pause");
		    exit(0);
	    }
		  archivo.read(reinterpret_cast<char *>(&acudientes), sizeof(Acudiente));	
      while (!archivo.eof()){
        if (matricula.id == acudientes.id_afilado){
          cout << "Nombre del acudiente: " << acudientes.nombre << endl;
          cout << "Telefono del acudiente: "<< acudientes.telefono << endl;
          bandera = true;
        }
        archivo.read(reinterpret_cast<char *>(&acudientes), sizeof(Acudiente));
      }
      archivo.close();
      if(!bandera) cout << "Acudiente aun no registrado" << endl;
	  }
    cout << "----------------------------------------------------" << endl;
    archivop.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
	}
  archivop.close();
  system("pause");
}

void listaConBajas() {
	Matricula matricula;
  Acudiente acudientes;
  bool bandera;
	
  ifstream archivop("matriculas.txt", ios::in | ios::binary);
	if(archivop.fail()){
		cout << ROJO << "Error al abrir el archivo matriculas.txt" << endl;
		system("pause");
		exit(0);
	}
	
  system("cls");
	cout << "----------- Lista de Estudiantes Con Bajas -----------" << endl << endl;
	archivop.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
	while(!archivop.eof()) {
		if(!matricula.estado) {
			cout << "Numero de matricula: " << matricula.id << endl;	
			cout << "Nombre del estudainte: " << matricula.nombre << endl;		
			cout << "Fecha de ingreso: " << matricula.ingreso.dia << "/" << matricula.ingreso.mes << "/" << matricula.ingreso.anio << endl;
      cout << "Fecha de baja: " << matricula.retiro.dia << "/" << matricula.retiro.mes << "/" << matricula.retiro.anio << endl;
      cout << "----------------------------------------------------" << endl;
	  }
    archivop.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
	}
  archivop.close();
  system("pause");
}

void reporteEstadoFinanciero() {
	Matricula m;
	Acudiente a;
	bool bandera;
	
  // Abrir archivos binarios
	ifstream archivom("matriculas.txt", ios::in | ios::binary);
	if(archivom.fail()){
		cout << "Error al abrir el archivo matriculas.txt." << endl;
		system("pause");
		exit(0);
	}
	system("cls");
	cout << "REPORTE DE ESTADO FINANCIERO DE ESTUDIANTES" << endl;
	//Recorrer el archivo y mostrar datos
	archivom.read(reinterpret_cast<char *>(&m), sizeof(Matricula));
	while(!archivom.eof()){
		if(m.estado){
			bandera = false;
			//Mostrar reporte
			cout << "Numero de matricula: " << m.id << endl;
			cout << "Nombre del estudiante: " << m.nombre << endl;
      cout << "Valor de la mensualidad: $" << m.pagoMensualidad << endl;
      cout << "Estado de pago: " << (m.sePagoMensualidad ? "Paz y salvo" : "Moroso") << endl;
			
			ifstream archivoa("acudientes.txt" , ios::in | ios::binary);
			if(archivoa.fail()){
				cout << "Error al abrir el archivo acudientes.txt." << endl;
				system("pause");
				exit(0);
			}
			archivoa.read(reinterpret_cast<char *>(&a), sizeof(Acudiente));
			while(!archivoa.eof()){
				if(m.id == a.id_afilado && a.abonante){
					cout << "Responsable de pago: " << a.nombre << endl;
					bandera = true;	
				}
				archivoa.read(reinterpret_cast<char *>(&a), sizeof(Acudiente));	
			}
			archivoa.close();
      if(!bandera) cout << "No cuenta con responsables de pago" << endl;
		}
    cout << "----------------------------------------------------" << endl;
		archivom.read(reinterpret_cast<char *>(&m), sizeof(Matricula));	
	}
	archivom.close();
	system("pause"); 
}

void consultaPorEstudiante() {
	Matricula m;
  Acudiente a;
  long id;

  system("cls");
  cout << "CONSULTA POR ESTUDIANTE" << endl;
  cout << "Digite el numero de matricula: "; cin >> id;
  cout << endl;

  // Verifica si la matricula no existe (Finaliza funcion)
  if(!existeMatricula(id)) {
    cout << ROJO << "La matricula no esta registrada." << DEFECTO << endl;
    system("pause");
    return;
  }

  // Halla la matricula
  ifstream archivoMatricula("matriculas.txt", ios::in | ios::binary);
  if(archivoMatricula.fail()){
		cout << "Error al abrir el archivo matriculas.txt." << endl;
		system("pause");
		exit(0);
	}
  archivoMatricula.read(reinterpret_cast<char *>(&m), sizeof(Matricula));
  while(!archivoMatricula.eof()) {
    // Imprime los datos de la matricula
    if(m.id == id) {
      cout << "Numero de matricula: " << m.id << endl;
			cout << "Nombre del estudiante: " << m.nombre << endl;
			cout << "Fecha de ingreso: " << m.ingreso.dia << "/" << m.ingreso.mes << "/" << m.ingreso.anio << endl;
			cout << "Edad: " << m.ingreso.anio - m.nacimiento.anio << endl;
      for(int i = 0 ; i < m.numeroAlergias; i++) {
				cout << "Alergia " << i + 1 << ": "<< m.alergias[i].nombre << endl;
			}

      ifstream archivoAcudiente("acudientes.txt" , ios::in | ios::binary);
			if(archivoAcudiente.fail()){
				cout << "Error al abrir el archivo acudientes.txt." << endl;
				system("pause");
				exit(0);
			}
			archivoAcudiente.read(reinterpret_cast<char *>(&a), sizeof(Acudiente));
			while(!archivoAcudiente.eof()) {
        if(a.id_afilado == id) cout << "Nombre del acudiente: " << a.nombre << endl;
        archivoAcudiente.read(reinterpret_cast<char *>(&a), sizeof(Acudiente));	
			}
			archivoAcudiente.close();
      cout << "Valor de mensualidad: $" << m.pagoMensualidad << endl; 
			cout << "Estado de pago: " << (m.sePagoMensualidad ? "Paz y salvo.": "Moroso.") << endl;
      break;
    }
    archivoMatricula.read(reinterpret_cast<char *>(&m), sizeof(Matricula));	
  }
	system("pause");
}

bool existeAcudienteId(long id) {
	Acudiente acudiente;
	ifstream archivo("acudientes.txt", ios::in | ios::binary);
	if(archivo.fail()) {
		cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
		system("pause");
		exit(0);
	}
	archivo.read(reinterpret_cast<char *>(&acudiente), sizeof(Acudiente));
	while(!archivo.eof()) {
		if(id == acudiente.id) {
      archivo.close();
      return true;
    }	
		archivo.read(reinterpret_cast<char *>(&acudiente), sizeof(Acudiente));	
	}	
	archivo.close();
	return false;
}

int validacionAbonanteId(long id, long id_afiliado) {
	Acudiente acudiente;
	ifstream archivo("acudientes.txt", ios::in | ios::binary);
	if(archivo.fail()) {
		cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
		system("pause");
		exit(0);
	}
	archivo.read(reinterpret_cast<char *>(&acudiente), sizeof(Acudiente));
	while(!archivo.eof()) {
		if(id == acudiente.id and id_afiliado == acudiente.id_afilado) {
      archivo.close();
      return 1;
    }
    if(id == acudiente.id){
      archivo.close();
      return 0;
    }
		archivo.read(reinterpret_cast<char *>(&acudiente), sizeof(Acudiente));	
	}	
	archivo.close();
	return -1;
}

bool existeMatricula(long id) {
	Matricula matricula;
	ifstream archivo("matriculas.txt", ios::in | ios::binary);
	if(archivo.fail()) {
		cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
		system("pause");
		exit(0);
	}
	archivo.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));
	while(!archivo.eof()) {
		if(id == matricula.id) {
      archivo.close();
      return true;
    }	
		archivo.read(reinterpret_cast<char *>(&matricula), sizeof(Matricula));	
	}	
	archivo.close();
	return false;
}

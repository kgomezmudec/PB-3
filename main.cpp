/**
 * Kevin Andres Gomez Meza - 0222220034
 * Boris David Bello del Rio - 0222220046
 * Juan Camilo Corrales Fonseca - 0222220044 
 * 
 * Descripcion: 
 * En esta guardería se matricularán varios niños con una edad mínima de 2 y máxima de 5, 
 * cada vez que se registra un niño se tomarán varios datos como nombre, fecha de nacimiento y la fecha de ingreso, 
 * adicionando para los que se dieron de baja, la fecha de salida. Además de esto en la guardería se registrarán 
 * acudientes que son personas que estarán autorizadas para recoger al niño de la guardería, 
 * se registrarán varios datos de ellos como el DNI, su nombre, la dirección y su número de teléfono. 
 * Para pagar la mensualidad el coste será abonado por una persona la cual será autorizada como acudiente y 
 * se le registraran los mismos datos sumando el número de la cuenta corriente. Para los niños, 
 * ellos tienen una selección de menús para que coman durante su estancia en la guardería, los cuales 
 * están compuestos de varios platos con sus propios ingredientes, para ahorrarnos problemas con las 
 * alergias de los niños cuando se registre la matrícula. Esta última, también debe registrar sus alergias, 
 * para cuando los estudiantes seleccionen el menú elegir los menús que tengan ingredientes a los cuales 
 * el niño no sea alérgico, y así no sean seleccionables. Para el valor del pago de la mensualidad se debe 
 * realizar varias opciones. Primero se debe crear un menú luego, seleccionar los ingredientes de los platos 
 * del menú, luego realizar la selección del menú que será uno por día, para luego facturar él costo de todos 
 * los menús hechos en el mes y después sumarle el costo fijo, para finalmente pagarlo. 
 * Un estudiante solo se puede dar de baja si no debe nada, es decir, ha pagado el valor de la mensualidad. 
 * Si ha registrado un menú tampoco puede, como es obvio los estudiantes dados de bajas no pueden registrar 
 * menús ni acudientes dado que ya no se encuentran en la guardería.
 */

#include <conio.h>
#include "operaciones.h"

int main() {
  // Inicializa los archivos requeridos
  ifstream archivoMenusLectura("menus.txt", ios::in | ios::binary);
  if(archivoMenusLectura.fail()) {
    ofstream archivoMenus("menus.txt", ios::out | ios::binary);
    if(archivoMenus.fail()) {
      cout << ROJO << "Se encontro un error en el archivo menus.txt." << endl;
      system("pause");
      exit(0); 
    }
    archivoMenus.close();
  } 
  archivoMenusLectura.close();

  ifstream archivoMatriculasLectura("matriculas.txt", ios::in | ios::binary);
  if(archivoMatriculasLectura.fail()) {
    ofstream archivoMatriculas("matriculas.txt", ios::out | ios::binary);
    if(archivoMatriculas.fail()) {
      cout << ROJO << "Se encontro un error en el archivo matriculas.txt." << endl;
      system("pause");
      exit(0); 
    }
    archivoMatriculas.close();
  } 
  archivoMatriculasLectura.close();

  ifstream archivoConsumosLectura("consumos.txt", ios::in | ios::binary);
  if(archivoConsumosLectura.fail()) {
    ofstream archivoConsumos("consumos.txt", ios::out | ios::binary);
    if(archivoConsumos.fail()) {
      cout << ROJO << "Se encontro un error en el archivo consumos.txt." << endl;
      system("pause");
      exit(0); 
    }
    archivoConsumos.close();
  } 
  archivoConsumosLectura.close();

  ifstream archivoAcudientesLectura("acudientes.txt", ios::in | ios::binary);
  if(archivoAcudientesLectura.fail()) {
    ofstream archivoAcudientes("acudientes.txt", ios::out | ios::binary);
    if(archivoAcudientes.fail()) {
      cout << ROJO << "Se encontro un error en el archivo acudientes.txt." << endl;
      system("pause");
      exit(0); 
    }
    archivoAcudientes.close();
  } 
  archivoAcudientesLectura.close();

  // MENU PRINCIPAL
  int entrada, opcion = 1;
  do {
    system("cls");
    cout << DEFECTO << "GUARDERIA MI POBRE ANGELITO" << endl;
    cout << DEFECTO << "Utilice las flechas del teclado para desplazarse." << endl;
    cout << DEFECTO << "Utilice el enter para escoger su opcion." << endl << endl;
    cout << DEFECTO << "Seleccione una opcion: " << endl << endl;
    cout << (opcion == 1 ? AZUL : "") << (opcion == 1 ? "> " : "") << (opcion == 1 ? DEFECTO : GRIS) << "Gestion Restaurante" << endl;
    cout << (opcion == 2 ? AZUL : "") << (opcion == 2 ? "> " : "") << (opcion == 2 ? DEFECTO : GRIS) << "Gestion Academica" << endl;
    cout << (opcion == 3 ? AZUL : "") << (opcion == 3 ? "> " : "") << (opcion == 3 ? DEFECTO : GRIS) << "Salir" << endl;
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
      if(entrada == 80 || entrada == 77) opcion = (opcion == 3) ? 1 : opcion + 1;
      if(entrada == 72 || entrada == 75) opcion = (opcion == 1) ? 3 : opcion - 1;
    }

    /**
     * Una vez confirmada la opción del usuario y teniendo en cuenta el codigo ASCII 
     * del enter (13) se gestiona la selección.
     */ 
    else if(entrada == 13) {
      switch(opcion) {
        case 1: gestionRestaurante(); break;
        case 2: gestionAcademica(); break;
        case 3: system("cls"); cout << VERDE << "Salida exitosa..."; break;
      }
    }
  } while(opcion != 3 || entrada != 13);
  return 0;
}
#include <conio.h>
#include "gestionRestaurante.h"

// TODO: Elaborar el menu principal aquí.
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
  gestionRestaurante();
  return 0;
}
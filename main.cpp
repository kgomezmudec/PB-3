#include <conio.h>
#include "gestionRestaurante.h"

// TODO: Elaborar el menu principal aquí.
int main() {
  // Inicializa los archivos requeridos
  ofstream archivoMenus("menus.txt", ios::out | ios::binary);
  if(archivoMenus.fail()) {
    cout << ROJO << "Se encontro un error en el archivo platos.txt." << endl;
    system("pause");
    exit(0); 
  }
  archivoMenus.close();

  gestionRestaurante();
  return 0;
}
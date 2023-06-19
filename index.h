#include <string.h>

// Codigo de colores
#define DEFECTO "\033[0m"     
#define GRIS "\033[90m"
#define AZUL "\033[34m"
#define ROJO "\033[1;31m"
#define VERDE "\033[1;32m"

// LIMITE DE PLATOS POR MENU
#define CANT_MAX_PLATOS 20

struct Plato {
  char nombre[50];
  char ingredientes[500];
};

struct Menu {
  int numero;
  int cantidadPlatos;
  Plato platos[CANT_MAX_PLATOS]; 
};

void mayusculas(char cadena[]) {
	for(int i = 0; cadena[i] != '\0'; i++) cadena[i] = toupper(cadena[i]);
}
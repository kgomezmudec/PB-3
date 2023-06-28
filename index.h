/**
 * Kevin Andres Gomez Meza - 0222220034
 * Boris David Bello del Rio - 0222220046
 * Juan Camilo Corrales Fonseca - 0222220044 
 */
#include <string>

// Codigo de colores
#define DEFECTO "\033[0m"     
#define GRIS "\033[90m"
#define AZUL "\033[34m"
#define ROJO "\033[1;31m"
#define VERDE "\033[1;32m"

// LIMITE DE PLATOS POR MENU
#define CANT_MAX_PLATOS 20

// COSTO MIN POR MENU
#define COSTO_MIN_MENU 5000

// LIMITE MAX DE DIAS (Lunes-Vieres en un Mes)
#define DIAS_MAX 22 

// MINIMO DEL COSTO FIJO ($100,000.00)
#define COSTO_FIJO_MIN 100000

struct Plato {
  char nombre[50];
  char ingredientes[500];
};

struct Menu {
  int numero;
  int cantidadPlatos;
  float coste;
  Plato platos[CANT_MAX_PLATOS]; 
  bool registroPlatos = false;
};

struct Fecha {
  int dia;
  int mes;
  int anio;
};

struct Ingrediente {
  char nombre[50];
};

struct Matricula {
  long id;
  char nombre[50];
  Fecha nacimiento;
  Fecha ingreso;
  Fecha retiro;
  bool estado;
  bool seCalculoFacturacion = false;
  bool seCalculoMensualidad = false;
  bool sePagoMensualidad = false; 
  float facturacion;
  float pagoMensualidad = 0;
  int dias = 0;
  int numeroAlergias;
  Ingrediente alergias[100];
};

struct Consumo {
  int dia;
  char nombreMatricula[50];
  long idMatricula;
  int numeroMenu;
  float costeMenu;
};

struct Acudiente {
  long id;
  char nombre[50];
  char direccion[70];
  long telefono;
  char parentesco[50];
  long id_afilado;
  long cuenta;
  bool abonante;
};

struct CostoFijo {
  float valor;
};

void mayusculas(char cadena[]) {
	for(int i = 0; cadena[i] != '\0'; i++) cadena[i] = toupper(cadena[i]);
}

int compararFechas(Fecha fecha1, Fecha fecha2) {
	if (fecha1.anio < fecha2.anio) return -1;
	else if (fecha1.anio > fecha2.anio) return 1;

	if (fecha1.mes < fecha2.mes) return -1;
	else if (fecha1.mes > fecha2.mes) return 1;

	if (fecha1.dia < fecha2.dia) return -1;
	else if (fecha1.dia > fecha2.dia) return 1;

	return 0;  // Las fechas son iguales
}
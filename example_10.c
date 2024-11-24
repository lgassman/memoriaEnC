
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct fecha {
	unsigned char dia;
	unsigned char mes;
	unsigned short anio;
} Fecha;


typedef struct persona Persona;
struct persona {
	char nombre[15];
	Fecha nacimiento;
	char genero;
	Persona * madre;
};




//Ahora el crear persona devuelve un puntero, porque va a asignar memoria en el heap y debe devolver donde está
Persona * crearPersona( char * nombre, char genero, unsigned char dia, unsigned char mes, unsigned short anio, Persona * madre) {

	//El malloc pide un cacho de memoria
	//La cantidad de memoria que se solicita tiene que ser del tamaño de una Persona
	//Malloc devuelve un puntero del tipo void, porque realmente no sabe a que cosa queres apuntar
	// Para poder tratar ese puntero como un puntero a una persona se realiza un casteo
	// Esto se hace poniendo entre parentesis el tipo con el que queres ver eso que devuelve.
	// En este caso se antepone`(Persona *)`a la llamada del malloc
	Persona * persona = (Persona *) malloc(sizeof(Persona));

	persona->genero = genero;
	strcpy( persona->nombre, nombre );
	persona->nacimiento.dia = dia;
	persona->nacimiento.mes = mes;
	persona->nacimiento.anio = anio;
	persona->madre = madre;
	return persona;
}

void imprimirFamilia(Persona * persona) {

	printf("Nombre: %s, Genero: %c, Nacimiento: (%d/%d/%d)\n", persona->nombre, persona->genero, persona->nacimiento.dia, persona->nacimiento.mes, persona->nacimiento.anio);
	if (persona->madre != NULL) {
		imprimirFamilia(persona->madre);
	}
}

void liberarMemoria(Persona * persona) {

	// Si la persona tiene madre, voy a liberar la memoria de la madre.
	// Esto recursivamente va a empezar a liberar desde el ancestro más lejano
	// hasta llegar a esta persona actual
	if (persona->madre != NULL) {
		liberarMemoria(persona->madre);
	}

	//Ahora que liberé a la madre, puedo liberar a esta persona
	free(persona);

}



int main(int argc, char **argv) {
	
	 Persona *  persona; //Solo necesito un puntero a una persona

	 //La primera persona no tiene madre
	 persona = crearPersona("Lina", 'f', 11,10,926, NULL);

	 //La segunda persona tiene como madre a la primera. solo necesito recordar
	 //a la última persona creada para no perder la cadena
	 persona = crearPersona("Mirta", 'f', 24,10,1956,persona);

	 //Repito lo mismo para la tercera persona.
	 persona = crearPersona("Leo", 'm', 1,11,1980,persona);

	 imprimirFamilia(persona);

	 //cuando ya no necesito la memoria que reservé en el heap,
	 //la devo liberar
	 liberarMemoria(persona);

	 //Ojo que ahora persona está apuntando a una dirección
	 //en el heap que ya no la tengo asignada
	 //si la uso se va a romper el programa


}


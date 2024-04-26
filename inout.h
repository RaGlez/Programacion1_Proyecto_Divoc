#ifndef INOUT_H
#define INOUT_H
#include "database.h"





void headline (char *cad, char c);
void stripe (char car,int TAMlinea);
int yes_or_no(char *cadena);
void get_string(char *mesaje , int min, int max , char *direcion);
int get_integer (char *mensaje, int min , int max);
char get_character (char *mensaje, char *palabra);
void display_patient (struct unPaciente *elpaciente);
int verify_DNI (char cadena[]);

#endif

#ifndef DATABASE_H
#define DATABASE_H



struct unPaciente
{
  char nombre[25];
  char DNI[10];
  int edad;
  int fiebre;
  int tos;
  char sintoma;
  struct unPaciente *sig;
};

void fichero_pacientes (char *nombrefichero,struct unPaciente **pacientes);
void p_register (struct unPaciente **paciente);
void p_search (struct unPaciente **paciente);
void p_list (struct unPaciente **paciente);
void p_mark(struct unPaciente **paciente);
void p_discharge (struct unPaciente **paciente);
void p_exit(char *nombrefichero,int *salir,struct unPaciente **paciente);


#endif

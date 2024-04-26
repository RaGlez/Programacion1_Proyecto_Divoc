#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "inout.h"
#include "database.h"


int main(){

 int salir;
  char c;

struct unPaciente *pacientes;
	pacientes=NULL; // pondra la lista vacia 
	fichero_pacientes("patients.txt",&pacientes);  //mandara el nombre del fichero y la direcion de la lista 
// estas funcione pinta la cartula del programa 
 stripe('-',50);
  headline("DIVOC_", '|');
  stripe('-',50);


  do{
    salir=0;  // nos daran a elegir la opcion que queremos hacer 

    printf("\n\nR) Register a patient\nS) Search for a patient\nD) Discharge a patient\nL) List patients by age\nP) Mark positive\n\nX )Exit the program\n\n\n");
   c= get_character ("\nChoose an option","RSDLPX");

    switch(c){
    case 'R': p_register(&pacientes);
      salir=0;
      break;
    case 'S': p_search(&pacientes);
      salir=0;
      break;
    case 'D': p_discharge(&pacientes);
      salir=0;
      break;
    case 'L': p_list(&pacientes);
      salir=0;
      break;
    case 'P': p_mark(&pacientes);
      salir=0;
      break;
    case 'X': p_exit("patients.txt",&salir,&pacientes);
      break;
   }
  }while (salir==0);  // hasta que el usuario no desee salir del progrma se seguira poneindo las opciones 

  return 0;
}
      
    

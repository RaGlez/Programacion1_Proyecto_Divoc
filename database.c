#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "database.h"
#include "inout.h"


void fichero_pacientes (char *nombrefichero,struct unPaciente **pacientes){  //los argumentos son el nombre del fichero y direcion de la lista 
  FILE *paciente;
  char cadena [256], edad[6], fiebre[3], tos[3];
  char sintoma;
  
  struct unPaciente *nodo;
  struct unPaciente *aux;
  paciente=fopen(nombrefichero,"r");  //abrir el fichero en modo lectura

  if (paciente!=NULL){       //si el fichero contiiene pacientes , estos se iran metiendo en la lista 
    while(fgets(cadena,sizeof(cadena),paciente)!=NULL){
      nodo=(struct unPaciente *)malloc(sizeof(struct unPaciente));

      sscanf(cadena,"%s %s %s %s %s %c",nodo->nombre,nodo->DNI,edad,fiebre,tos,&sintoma);
      nodo->edad=atoi(edad);     //convierte una cadena en un entero 
      nodo->fiebre=atoi(fiebre);
      nodo->tos=atoi(tos);
      nodo->sintoma=sintoma;
      nodo->sig = NULL;

      if(*pacientes==NULL){    //si la lista esta vacia ese nuevo nodo sera la cabecera
	*pacientes=nodo;
	aux=nodo;
      }
      else{     //si ya hay pacientes la direcion de aux siguiente será la direcion de nodo
	aux->sig=nodo;
	aux=nodo;
      }
    }
    fclose(paciente);  //se cierra el fichero
  }
  
}
  


void p_register (struct unPaciente **paciente){
  char cadena[25];
  char dni[10];
  int num,x,a,f,t;
  char c;
  struct unPaciente *aux;
  struct unPaciente *nodo;
  nodo=(struct unPaciente *) malloc (sizeof(struct unPaciente));
  aux=*paciente;
  printf ("\nRegister\n");
  get_string ("Name", 1, 24, cadena);  //pedira el nombre con un max y min de cracteres 

  do {
     get_string("DNI",9,9,dni);  //pedira el dni y comprobara que es valido 
     
 x=verify_DNI(dni);
 if(x==0){
   printf("\nInvalid DNI\n");
   a=0;
 }
 else{
   a=1;
 }
  }while(a==0);

 num=get_integer("\nDate",1900,2020);   
 f=yes_or_no("\nFever (y/n)");
 t=yes_or_no("\nCough (y/n)");
 c=get_character("\nSymptom","FSTMN");
 

  strcpy(nodo->nombre,cadena);    //guarda los datos pedidos en el nodo 
  strcpy(nodo->DNI,dni);
  nodo->edad=num;
  nodo->fiebre=f;
  nodo->tos=t;
  nodo->sintoma=c;
  nodo->sig=NULL;
  

  if (*paciente!=NULL){   //si la lista mo esta vacia e ira recorriendo la lista hasta el final y metera el nodo
    aux=*paciente;
    while(aux->sig!=NULL){
      aux=aux->sig;
    }
    aux->sig=nodo;
  }
  else{   //si esta vacia el nodo se metera como el primero 
    *paciente=nodo;
  }
  printf("\nNew patient : \n");
  display_patient(nodo);  // mostrara por pantalla el nuevo paciente 
}

void p_search (struct unPaciente **paciente){
  char dni[10];
  struct unPaciente *aux;
  struct unPaciente *igual;
  int a;
  aux=*paciente;

  
  printf("\nSearch\n");     // buscara el paciente mediente el dni que no hara flata comprbara que es valido 
  if (*paciente==NULL){
    printf("\nNo patients yet\n");
    return;
  }
  else{
     get_string("DNI",9,9,dni);
    do{
      a=0;
      if(aux==NULL){
	printf("\nUnknown patient\n");
	return;
      }
      else{   // comprobara si el dni de un nodo concreto es igual al buscado , si es cierto lo guardara para luego mostrarlo 
      if (strcmp(aux->DNI,dni)==0){
      igual=aux;
      a=1;
    }
    else{  // sino ira recorriendo la lista 
      aux=aux->sig;
      a=0;
    }
      }
    }while(a==0);
  }

    printf("\nPatient data :\n");
    display_patient(igual);

    return;
}

void p_list (struct unPaciente **paciente){
  struct unPaciente *aux;
  aux=*paciente;
  int num;
  printf("\nList\n");

  if(*paciente==NULL){
    printf ("\nNo patients yet");
    return;
  }
  else{

  num=get_integer ("Date",1900,2020);  // listara los pacientes nacidos antes del año dado
  printf("\nPatients born before %d :\n",num);

  do{  // busca los pacinetes o el pacinete nacidos entes de ese año 
    if(aux->edad<=num){
      display_patient(aux);
      aux=aux->sig;
    }
    else{
      aux=aux->sig;
    }
  }while(aux!=NULL);

  }

  return;
}


void p_mark(struct unPaciente **paciente){
  struct unPaciente *aux;


  aux=*paciente;
  printf("\nPositives\n");

  if(*paciente==NULL){
    printf("\nNo patients yet\n");
    return;
  }
  else{
    printf("\nPositive patients :\n");

    do{   // solo mostrara los paciente que tenga tos fiebre y algun sintoma 

      if (aux->fiebre==1 && aux->tos==1){
	if (aux->sintoma!='N'){
	  display_patient(aux);
	  aux=aux->sig;
	}
	  else{
	    aux=aux->sig;
	  }
      }
      else{
	aux=aux->sig;
      }
    }while(aux!=NULL);
  }
  return;
}
  
  
void p_discharge (struct unPaciente **paciente){
  struct unPaciente *aux;
  struct unPaciente *remove;
  char dni[10];
  aux=*paciente;
  printf("\nDischarge\n");

  if (*paciente==NULL){
    printf("\nNo patients yet\n");
    return;
  }
  else{
    get_string("DNI",9,9,dni);  // pedira el dni y buscara en la lista el paciente que tenga ese dni y lo borrara
    if (strcmp((*paciente)->DNI,dni)==0){
      remove=*paciente;  // ese el primero 
    }
    else{
      if(aux->sig==NULL){
	printf("\nUnknown patient");
	return;
      }
      while(strcmp(aux->sig->DNI,dni)!=0){  //buscra por toda la lista el paciente y lo guardara en remove
	aux=aux->sig;
	if(aux->sig==NULL){
	  printf("\nUnknown patient");
	  return;
	}
      }
    remove=aux->sig;
    }
  }
  

    if(remove==*paciente){   // si es el primeo de la lista movera la cabecera de la lista la siguiente paciente para no perderla y borrara el primero 
      *paciente=(*paciente)->sig;
      free(remove);
      printf("\nDischarged patient\n");
    }
    else{ //si es el ultimo o uno del medioo la direcion del anterior apuntara a la direcion del siguiente del que se quiere borrar 
      aux->sig=remove->sig;
      free(remove);
      printf("\nDischarged patient\n");
    }
    return;
}

void p_exit(char *nombrefichero,int *salir,struct unPaciente **paciente){
    

    printf("\nExit\n");

    *salir = yes_or_no("\nAre you sure you want to exit the program? (y/n)");  //si seleciona y se abrira el fichero y se guardara la lista , si es n no la gurdara 
    if(*salir==1){
      FILE *pacientes;
      pacientes=fopen(nombrefichero,"w");  //abre el fichero en modo escritura 
      while(*paciente!=NULL){  //metera todos los paciente de la lista hasta que se llegue al final 
	/*	fputs((*paciente)->nombre,pacientes);
		fputs((*paciente)->DNI,pacientes); */
	fprintf(pacientes,"%s ",(*paciente)->nombre);
        fprintf(pacientes,"%s ",(*paciente)->DNI);
	fprintf(pacientes,"%d ",(*paciente)->edad);
	fprintf(pacientes,"%d ",(*paciente)->fiebre);
	fprintf(pacientes,"%d ",(*paciente)->tos);
	fprintf(pacientes,"%c ",(*paciente)->sintoma);
	/*	fputc((*paciente)->sintoma,pacientes);*/
	fprintf(pacientes,"\n");
	*paciente=(*paciente)->sig;  //recorre la lista 
      }
      fclose(pacientes);
    }
    else{
      return;
    }

  }
	
    

    
      
      
			      
    
  
  

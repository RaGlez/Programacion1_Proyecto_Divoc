#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "inout.h"

void headline (char *cad , char c){  //pondra el titulo del progrma en el medio de la caratula  
  int i;

printf ("%c",c);

 for (i=0;i<21;i++)
   printf(" ");

 printf("%s",cad);

 for (i=0;i<21;i++)
   printf(" ");

 printf("%c\n",c);

 return;
}

void stripe (char car,int TAMlinea){  //pinta los 50 menos de la caraula 
  for (int i=0; i<TAMlinea; i++)
    printf("%c",car);

  printf("\n");

  return;
}

int yes_or_no (char *cadena){  //funcion que retornara un 1 o 0 

  char linea[256];
  char extra[256];
  char c;
  int i,x;
  char YN[]={'Y','N'};
  

  do {
    i=0;

    printf ("%s: ", cadena);
    fgets(linea,sizeof(linea),stdin); // gueda en linea los escrito por el usuario
    x=sscanf(linea,"%c%s\n",&c,extra);   
    if(x==1){
      c=toupper(c);
     
      if(strchr(YN,c)==NULL){  //comprueba q lo escrito por el usuario no pertenece a la cadena YN 
	i=0;}
      else{ //si pertenece sale del bucle while
	
	i=1;

      }
    }
  
    else{
      i=0;}
   
  }while (i==0);
  	  if(c=='Y'){  //si el usuario eligio y retornara un 1 
    return 1;
  }
  else{
      // sino un 0
	return 0;}
     

 
    return 0;
}

void get_string(char *mensaje, int min, int max , char *direcion){

  char linea[256];
  int i,x;
  char extra[256];
  char cad[256];
  do{
    i=0;
  printf("\n%s(%d-%d char): ", mensaje, min, max);  
    fgets(linea,sizeof(linea),stdin);
    x=sscanf(linea,"%s%s",cad,extra);
    if(x==1){ //comprueba que el usuario no haya puesto mas de dos palabras 
      if(strlen(cad)>=min && strlen(cad)<=max){ //saldra del bucle si lo escirto esta entra el min y el max 
	i=1;}
      else{
	i=0;}
    }
    else{
      i=0;
      
  }
  }while(i==0);
    strcpy(direcion,cad); //copia los escrito por el usuario en la direcion en la cual se usara 

    return;
}

int get_integer(char *mensaje, int min , int max){

  int i;
  int num,x;
  char linea [256];
  char extra [256];
  

  do {
    i=0;
    printf("\n%s [%d-%d]: ", mensaje, min, max);
    fgets (linea,sizeof(linea),stdin);
    x=sscanf(linea,"%d%s",&num,extra);
    if(x==1){
      if(num>=min && num<=max){  //saldra del bucle si el usuario ha introducio una longuitud correcta 
	i=1;}
      else{
	i=0;}
    }
    else{
      i=0;}
    
    
  }while(i==0);
  
  return num; //retorna el numero escrito por el usuario
}


char get_character (char *mensaje , char *palabra){

  char linea[256];
  char extra[256];
  char cad;
  int i,x;
  
  do {
    i=0;
    printf("%s (%s): ", mensaje, palabra);
    fgets(linea ,sizeof(linea),stdin);
    x=sscanf(linea,"%c%s",&cad,extra);
    
    if (x==1){
      cad=toupper(cad);

      if (strchr(palabra,cad)==NULL){  //no saldra del bucle hasta que el caracter dado por el usuario coincida con los caracteres pedidos 
	i=0;}
      else {
	
	i=1;}
    }
    else{
      i=0;}
 
  }while (i==0);

  return cad; // retorna el cracter dado por el usuario 
}

void display_patient (struct unPaciente *elpaciente){ //muestra por pantalla el paciente 
  printf (">%s;%s;%i;%i;%i;%c;\n", elpaciente->nombre, elpaciente->DNI,elpaciente->edad, elpaciente->fiebre, elpaciente->tos, elpaciente->sintoma);
  return;}


int verify_DNI (char *cadena){
  int x[10];
  int indice;
  char comprobacion[] ={'T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};
    

  for (int i=0; i<8 ; i++){
    
  x[i]=atoi(cadena); //combierte los 8 primeros caracteres a enterlo y lo guarda en x 
  }

  indice = *x%23; //error aqui pero si pongo *x no me da error pero ns si es correcto
  if (comprobacion[indice]==cadena[8]){  // comprueba que la letra del dni dado por el usuario sea una de la cadena comprobacion
    return 1;
  }
  else{
    return 0;}
  return 0;
}
  
    
  
  

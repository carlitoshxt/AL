/*
 * compi.c
 *
 *  Created on: Oct 31, 2015
 *      Author: calosh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* concat(char *s1, char *s2); //Declaracion del metodo para concatenar

char *simbolos[]={"if","else","while","do", "print", "for", "return", "int", "string", "double", "and", "or", "not"};
char *separadores[]={" ","{","}","(",")",";","\n","\t"};
char *operadores[]={"+","-","*","/","%","<",">","="};

int cont=0;	// Contador de tokens

int main(){
	FILE *archivo;
	int caracter;	// Variable que almacenara el caracter leido
	char *palabra="";	// Variable para concatenar y almacenar los tokens

	archivo = fopen("codigo.txt","r");	// Se abre el archivo en modo lectura

	if (archivo == NULL){	// Si no existe el archivo
		printf("\nError de apertura del archivo. \n\n");
    }else{	// Si el archivo existe
		caracter = fgetc(archivo);	// Se obtiene el primer caracter del archivo
		int estado=0;	// Se inicializa el estado a 0
		while (caracter!=EOF)	//Mientras el caracter leido sea diferente de EOF
		{
			switch(estado){
			case 0:
				if(isdigit(caracter)){
					estado=1;
				}else if(isalpha(caracter)){
					estado=5;
				}else if(isSeparador(&caracter)==1){
					estado=9;
				}else if(isOperador(&caracter)==1){
					estado=10;
				}else{
					printf("Error Case 0\n");
				}
				break;

			case 1:
				if(isdigit(caracter)){
					estado=1;
				}else{
					if(caracter==','){
						estado=2;
					}else{
						if(isSeparador(&caracter)==1||isOperador(&caracter)){
							estado=4;
						}else{
							printf("Error Case 1\n");
							estado=-1;
						}
					}
				}

				break;
			case 2:
				if(isdigit(caracter)){
					estado=3;
				}else{
					printf("Error Case 2\n");
				}
				break;

			case 3:
				if(isdigit(caracter)){
					estado=3;
				}else{
					if(isSeparador(&caracter)){
						estado=4;
					}else{
						printf("Error case 3");
					}
				}
				break;

			case 5:
				if(isalpha(caracter)){
					estado=5;
				}else{
					if(caracter=='_'){
						estado=6;
					}else{
						if(isdigit(caracter)){
							estado=7;
						}else{
							if(isSeparador(&caracter)==1){
								estado=8;
							}else{
								if(isOperador(&caracter)==1){
									estado=8;
								}else{
									printf("Error Case 5\n");
								}
							}
						}
					}
				}
				break;
			case 6:
				if (isalpha(caracter)){
					estado=5;
				}else{
					if (isdigit(caracter)){
						estado=7;
					}else{
						printf("Error Case 6\n");
					}
				}
				break;

			case 7:
				if (isdigit (caracter)){
					estado=7;
				}else{
					if(isSeparador(&caracter)){
						estado=8;
					}else{
						printf("Error Case 7\n");
					}
				}
				break;

			default:
				printf("ERROR");
			}
			// Verificamos si hay un estado de aceptacion
			if(estado==4||estado==8||estado==9||estado==10){
				if(estado==4){
					cont++;	// Incrementamos el contador de tokens
					printf("%d) %s Numero\n", cont, palabra);
					if(isOperador(&caracter)==1){
						cont++;
						printf("%d) %c Operador\n", cont, caracter);
					}else{
						cont++;
						printf("%d) %c Separador\n", cont, caracter);
					}
				}
				if(estado==8){
					if(inTDS(palabra)==1){
						cont++;
						printf("%d) %s Palabra Reservada\n", cont, palabra);
					}else{
						cont++;
						printf("%d) %s Identificador\n", cont,palabra);
					}

					if(isOperador(&caracter)==1){
						cont++;
						printf("%d) %c Operador\n",cont, caracter);
					}else{
						if(isSeparador(&caracter)==1 && caracter!=' ' ){
							cont++;
							printf("%d) %c Separador\n", cont, caracter);
						}
					}
				}
				//	Verificamos que no haya salato de linea, espacio en blanco y tabulador
				if(estado==9 && caracter!='\n' && caracter!=' ' && caracter!='\t'){
					cont++;
					printf("%d) %c Separador\n", cont, caracter);
				}

				if(estado==10){
					cont++;
					printf("%d) %c Operador\n", cont, caracter);
				}

				palabra="";	// Se fija a cadena vacia
				estado=0;	// Se reinicia el estado
			}else{
				// Se concatena el valor de palabra con el caracter leido
				palabra=concat(palabra, &caracter);
			}
			caracter = fgetc(archivo);	// Obtener el siguiente caracter
		}
	}
    fclose(archivo);	// Se cierra el archivo
	return 0;
}

// Metodo para buscar en un arreglo palabras reservadas
int inTDS(char *palabra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(simbolos) / sizeof(simbolos[0]);

	for(i = 0; i < asize; i++){
		if(strcmp(simbolos[i],palabra)==0){
			return 1;
		}
	}
	return 0;
}

// Metodo para buscar en un arreglo separadores
int isSeparador(char *letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(separadores) / sizeof(separadores[0]);

	for(i = 0; i < asize; i++){
		//printf("%d: %s\n", i, simbolos[i]);
		if(strcmp(separadores[i],letra)==0){
			return 1;
		}
	}
	return 0;
}

// Metodo para buscar en un arreglo operadores
int isOperador(char *letra){
	int i, asize, result;
	i = asize = result = 0;
	asize = sizeof(operadores) / sizeof(operadores[0]);

	for(i = 0; i < asize; i++){
		//printf("%d: %s\n", i, simbolos[i]);
		if(strcmp(operadores[i],letra)==0){
			return 1;
		}
	}
	return 0;
}

// Definicion del metodo para concatenar un string con un caracter
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


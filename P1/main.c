/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 18 / 03 / 24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

//Funcion auxiliar para pasar de string a enum.
tUserCategory stringToEnum(char *String){
    if(strcmp(String,"basic")==0) return basic;
    if(strcmp(String,"pro")==0) return pro;
}

//Funcion auxiliar para pasar de enum a string.
char* enumToString(tUserCategory categoria){
    switch( categoria ){

        case basic:
            return "basic";
            break;
        case pro:
            return "pro";
            break;
    }
}




void New(tUserName nombreUsuario, tUserCategory tipoUsuario,tList *lista){
    //Creamos un nuevo elemento de la lista.
    tItemL newItem;
    //Le asignamos a newItem un nombre de usuario.
    strcpy(newItem.userName, nombreUsuario);
    //Le asignamos a newItem un tipo de usuario.
    newItem.userCategory=tipoUsuario;
    //Se inicializa el número de plays a 0.
    newItem.numPlay=0;

    //Si el usuario ya se encuentra en la lista printeamos error.
    if(findItem(newItem.userName,*lista) == LNULL) {

        //Si el usuario no se encuentra en la lista lo insertamos
        if(insertItem(newItem,LNULL, lista))
            printf("* New: user %s category %s\n",newItem.userName, enumToString(newItem.userCategory));
        else
            printf("+ Error: New not possible\n");

    }else printf("+ Error: New not possible\n");

}



void Delete(char* name,tList *lista){

    //Si la lista está vacía ya salimos de la función y no se hace nada más.
    if (isEmptyList( *lista)) {
        printf ("+ Error: Delete not possible\n");
        return;
    }

    tPosL posicionItem = findItem(name,*lista);

    //Si la lista está vacía, o el usuario no se encuentra printea error y abandona la función.
    if (posicionItem == LNULL ) {
        printf ("+ Error: Delete not possible\n");
        return;
    }

    //Obtenemos el item para luego poder acceder en el printf a sus campos.
    tItemL itemBorrar = getItem(posicionItem,*lista);
    //Borramos en la posición que se encuentra el usuario.
    deleteAtPosition(posicionItem,lista);
    printf("* Delete: user %s category %s numplays %d\n",itemBorrar.userName, enumToString(itemBorrar.userCategory),itemBorrar.numPlay);

}



void Upgrade(char *name,tList *lista){

    //Si la lista está vacía ya salimos de la función y no se hace nada más.
    if (isEmptyList( *lista)) {
        printf ("+ Error: Upgrade not possible\n");
        return;
    }

    //Buscamos el usuario pasado por parámetro en la lista.
    tPosL posicionElementoBuscado = findItem(name,*lista);

    //Si no se encuentra el usuario que queremos modificar printea error y abandona la función.
    if(posicionElementoBuscado == LNULL ){
        printf("+ Error: Upgrade not possible\n");
        return;
    }
    //Obtenemos el item para luego poder acceder en el printf a sus campos.
    tItemL elementoBuscado = getItem(posicionElementoBuscado,*lista);

    //Si la categoria del usuario es basic se actualiza la categoria a pro.
    if(strcmp(enumToString(elementoBuscado.userCategory),"pro")!=0){
        //Cambiamos la categoria basic por pro
        elementoBuscado.userCategory = stringToEnum("pro");
        //Actualizamos el item de la lista
        updateItem(elementoBuscado,posicionElementoBuscado,lista);
        printf("* Upgrade: user %s category %s\n",elementoBuscado.userName, enumToString(elementoBuscado.userCategory));
    //Si la categoria del usuario no es basic, no se actualiza nada.
    }else printf("+ Error: Upgrade not possible\n");

}




void Play(tList *lista,char *name,char *cancion){

    //Si la lista está vacía salimos de la función y no se hace nada más.
    if (isEmptyList( *lista)) {
        printf ("+ Error: Play not possible\n");
        return;
    }

    //Buscamos la posicion del item buscado para luego usar getItem y asi poder acceder a este item.
    tPosL posicionItem = findItem(name,*lista);

    if(posicionItem == LNULL){
        printf("+ Error: Play not possible\n");
        return;
    }

    //Obtenemos el item.
    tItemL itemBuscado= getItem(posicionItem,*lista);
    //Aumentamos el numero de plays en 1.
    itemBuscado.numPlay+=1;
    //Actualizamos el item de la lista.
    updateItem(itemBuscado,posicionItem,lista);
    printf("* Play: user %s plays song %s numplays %d\n",itemBuscado.userName,cancion,itemBuscado.numPlay);

}


void Stats(tList lista){
    //Si la lista está vacía  salimos de la función y no se hace nada más.
    if (isEmptyList( lista)) {
        printf ("+ Error: Stats not possible\n");
        return;
    }

    tPosL posicionActual = first(lista);
    //Contadores necesarios para llevar la cuenta del numero de usuarios y plays
    int ContadorUsuariosPro = 0;
    int ContadorUsuariosBasic = 0;
    int PlaysPro = 0;
    int PlaysBasic = 0;
    float mediaBasic;
    float mediaPro;

//Recorremos la lista entera inicializando una variable tPosL como posición inicial y por cada iteración del bucle esta variable se actualiza a la siguiente posicion de la lista.
    while(posicionActual!=LNULL){
        tItemL itemActual= getItem(posicionActual,lista);
        printf("User %s category %s numplays %d\n",itemActual.userName, enumToString(itemActual.userCategory),itemActual.numPlay);
        posicionActual= next(posicionActual,lista);

        if(strcmp(enumToString(itemActual.userCategory),"basic")==0){
            //Si el usuario es basic se incrementa el contador de usuarios basic y el de plays
            ContadorUsuariosBasic++;
            PlaysBasic+=itemActual.numPlay;
        }
        else {
            //Si el usuario es pro se incrementa el contador de usuarios basic y el de plays
            ContadorUsuariosPro++;
            PlaysPro+=itemActual.numPlay;
        }
    }

    //Controlamos si el donominador es 0 por que si no a la hora de dividir podría dar fallo
    if(ContadorUsuariosBasic == 0) mediaBasic=0;
    else mediaBasic=(float) PlaysBasic/ (float)ContadorUsuariosBasic;

    if(ContadorUsuariosPro == 0) mediaPro=0;
    else mediaPro= (float) PlaysPro / (float)ContadorUsuariosPro;

                 printf("Category  Users  Plays  Average\n");
    printf("Basic     %5d %6d %8.2f\n",ContadorUsuariosBasic,PlaysBasic,mediaBasic);
    printf("Pro       %5d %6d %8.2f\n",ContadorUsuariosPro,PlaysPro,mediaPro);


}



void processCommand(char *commandNumber, char command, char *param1, char *param2,tList *lista) {
    printf("********************\n");

    switch (command) {
        case 'N':
            printf("%s %c: user %s category %s\n",commandNumber,command,param1,param2);
            New( param1, stringToEnum(param2),lista);
            break;
        case 'D':
            printf("%s %c: user %s\n",commandNumber,command,param1);
            Delete(param1,lista);
            break;
        case 'U':
            printf("%s %c: user %s\n",commandNumber,command,param1);
            Upgrade(param1,lista);

            break;
        case 'P':
            printf("%s %c: user %s song %s\n",commandNumber,command,param1,param2);
            Play(lista,param1,param2);

            break;
        case 'S':
            printf("%s %c:\n",commandNumber,command);
            Stats(*lista);

            break;
        default:
            break;
    }
}

void readTasks(char *filename,tList *lista) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2,lista);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
//Se crea la lista sobre la que se van a usar las funcionalidades del main
    tList lista;
    createEmptyList(&lista);

    char *file_name = "delete1.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name,&lista);

    return 0;
}
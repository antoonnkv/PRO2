/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 25 / 04 / 24
 */

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "user_list.h"
#include "stdlib.h"

#define MAX_BUFFER 255



//Funcion auxiliar para pasar de string a enum
tUserCategory  stringToEnum(char *String){
    if(strcmp(String,"basic")==0) return basic;
    if(strcmp(String,"pro")==0) return pro;
}

//Funcion auxiliar para pasar de enum a string
char* enumToString(tUserCategory categoria){
    switch(categoria){
        case basic:
            return "basic";
            break;
        case pro:
            return "pro";
            break;
    }
}

//Función axuliar parar pasar el param3 de string a entero
int StringToInt(char *numero){
    int resultado = 0;
    while(*numero!= '\0'){
        resultado = resultado * 10 +(*numero - '0');
        numero++;
    }
    return resultado;
}

//Funcion auxiliar para calcular media
float calcularMedia(int numeroUsers,int numeroPlays){
    if( numeroUsers == 0 ) return 0;
    else return (float)numeroPlays/(float)numeroUsers;
}


void new(tListU *listaUsuarios,tUserCategory categoriaUsuario,tUserName nombreUsuario){
    tItemU newUsuario;
    //Inicializamos las variables del nuevo item
    strcpy(newUsuario.userName,nombreUsuario);
    newUsuario.totalPlayTime = 0;
    newUsuario.userCategory = categoriaUsuario;
    //Creamos su respectiva lista de canciones
    createEmptyListS(&newUsuario.songList);

    //Si el usuario ya se encuentra en la lista printeamos error.
    if(findItemU(newUsuario.userName,*listaUsuarios)==NULLU){
        //Si no lo insertamos en la lista
        if(insertItemU(newUsuario,listaUsuarios)) printf("* New: user %s category %s\n",newUsuario.userName, enumToString(newUsuario.userCategory));
        else printf("+ Error: New not possible\n");

    }else printf("+ Error: New not possible\n");

}

void stats(tListU listaUsuarios){
    //Contadores necesarios para llevar la cuenta de los usuarios y el timePlay.
    int contBasic=0;
    int contPro=0;
    int timePro=0;
    int timeBasic=0;


    //Si la lista de usuarios está vacía printeamos error.
    if(isEmptyListU(listaUsuarios)){
        printf("+ Error: Stats not possible\n");
        return;
    }

    tPosU posActUser = firstU(listaUsuarios);
    //Con 2 bucles anidados recorremos las dos listas, primero la lista de usuarios y luego la de canciones de cada usuario.
    while(posActUser != NULLU){
        tItemU usuarioAct = getItemU(posActUser,listaUsuarios);
        tPosS posActCan = firstS(usuarioAct.songList);
        printf("User %s category %s totalplaytime %d\n",usuarioAct.userName, enumToString(usuarioAct.userCategory),usuarioAct.totalPlayTime);

        if(usuarioAct.userCategory == pro){
            //Si el usuario es pro, aumenta el contador de pro y el de prototalTime
            contPro++;
            timePro+=usuarioAct.totalPlayTime;
        }else {
            //Si el usuario es basic, aumenta el contador de basic y el de basictotaltime
            contBasic++;
            timeBasic+=usuarioAct.totalPlayTime;
        }

        //Si la lista de canciones esta vacía printeamos no songs
        if(isEmptyListS(usuarioAct.songList)){
            printf("No songs\n");
        }else{
            tItemS cancionAct;
            while(posActCan != NULLS){
                cancionAct = getItemS(posActCan,usuarioAct.songList);
                printf("Song %s playtime %d\n",cancionAct.songTitle,cancionAct.playTime);
                posActCan = nextS(posActCan,usuarioAct.songList);
            }
        }
        printf("\n");
        posActUser = nextU(posActUser,listaUsuarios);
    }

    printf("Category  Users  TimePlay  Average\n");
    printf("Basic     %5d %9d %8.2f\n",contBasic,timeBasic, calcularMedia(contBasic,timeBasic));
    printf("Pro       %5d %9d %8.2f\n",contPro,timePro, calcularMedia(contPro,timePro));

}

void add(tListU *listaUsuarios,tUserName nombreUsuario,tSongTitle nombreCancion){

    //Comprobamos si la lista de usuarios está vacía
    if(isEmptyListU(*listaUsuarios)){
        printf("+ Error: Add not possible\n");
        return;
    }

    tPosU posUserBus = findItemU(nombreUsuario,*listaUsuarios);

    //Comprobamos si ese usuario está presente en la lista
    if(posUserBus == NULLU) {
        printf("+ Error: Add not possible\n");
        return;
    }

    tItemU userBuscado = getItemU(posUserBus, *listaUsuarios);
    tPosS posCan = findItemS(nombreCancion,userBuscado.songList);

    //Comprobamos si esa cancion no está ya en la lista de canciones.
    if(posCan == NULLS) {
        //Creamos un nuevo item cancion inicializando sus variables.
        tItemS newCancion;
        newCancion.playTime = 0;
        strcpy(newCancion.songTitle,nombreCancion);
        //insertamos y actualizamos el usuario.
        if(!insertItemS(newCancion,NULLS,&userBuscado.songList)) printf("+ Error: Add not possible\n");
        else {
            updateItemU(userBuscado, posUserBus, listaUsuarios);
            printf("* Add: user %s adds song %s\n", userBuscado.userName, newCancion.songTitle);
        }
    }else printf("+ Error: Add not possible\n");;

}

void upgrade(tUserName nombre,tListU *listaUsuarios){

    //Si la lista está vacía salimos de la función y no se hace nada más.
    if(isEmptyListU(*listaUsuarios)){
        printf("+ Error: Upgrade not possible\n");
        return;
    }

    //Buscamos al usuario pasado por parámetro en la lista
    tPosU posicionBuscada = findItemU(nombre,*listaUsuarios);

    if(posicionBuscada == NULLU){
        printf("+ Error: Upgrade not possible\n");
        return;
    }

    //Obtenemos el item para luego poder acceder en el printf a sus campos.
    tItemU elementoBuscado = getItemU(posicionBuscada,*listaUsuarios);

    //Si el usuario es basic lo modificamos por pro
    if(strcmp(enumToString(elementoBuscado.userCategory),"pro")!=0){
        //Modificamos userCategory
        elementoBuscado.userCategory = stringToEnum("pro");
        //Actualizamos el item
        updateItemU(elementoBuscado,posicionBuscada,listaUsuarios);
        printf("* Upgrade: user %s category %s\n",elementoBuscado.userName, enumToString(elementoBuscado.userCategory));
    }else printf("+ Error: Upgrade not possible\n");
    //Si el usuario ya es pro no se actualiza nada
}

void play(tListU *listaUsuarios,tUserName nombreUsuario,tSongTitle nombreCancion,int minutos){

    //Si la lista esta vacía ya abandonamos la función.
    if(isEmptyListU(*listaUsuarios)){
        printf("+ Error: Play not possible\n");
        return;
    }

    //Buscamos al usuario pasado por parámetro
    tPosU posUser = findItemU(nombreUsuario,*listaUsuarios);

    //Si este no se encuentra printeamos error
    if(posUser == NULLU){
        printf("+ Error: Play not possible\n");
        return;
    }

    //Obtenemos el item para acceder a su lista de canciones.
    tItemU usuarioBuscado = getItemU(posUser,*listaUsuarios);

    //Si la lista de canciones esta vacía abandonamos la función.
    if(isEmptyListS(usuarioBuscado.songList)){
        printf("+ Error: Play not possible\n");
        return;
    }

    //Buscamos la canción pasada por parámetro
    tPosS posCancion = findItemS(nombreCancion,usuarioBuscado.songList);

    //si no se encuentra abandonamos la función
    if(posCancion == NULLS){
        printf("+ Error: Play not possible\n");
        return;
    }

    //Se obtiene la canción
    tItemS cancionBuscada = getItemS(posCancion,usuarioBuscado.songList);
    //Sumamos a playtime el numero de minutos
    cancionBuscada.playTime+=minutos;
    //Actualizamos el item
    updateItemS(cancionBuscada,posCancion,&usuarioBuscado.songList);
    //Sumamos a totalPLayTime el numero de minutos
    usuarioBuscado.totalPlayTime+=minutos;
    updateItemU(usuarioBuscado,posUser,listaUsuarios);
    printf("* Play: user %s plays song %s playtime %d totalplaytime %d\n",usuarioBuscado.userName,cancionBuscada.songTitle,cancionBuscada.playTime,usuarioBuscado.totalPlayTime);
}



void delete(tListU *listaUsuarios,tUserName nombreUsuario){
    //Si la lista esta vacía ya abandonamos la función.
    if(isEmptyListU(*listaUsuarios)){
        printf("+ Error: Delete not possible\n");
        return;
    }
    //Buscamos al usuario pasado por parámetro.
    tPosU posicionBuscada = findItemU(nombreUsuario,*listaUsuarios);

    //Si este no se encuentra printeamos error.
    if(posicionBuscada==NULLU){
        printf("+ Error: Delete not possible\n");
        return;
    }

    //Obtenemos el item, lo borramos .
    tItemU elementoBuscado = getItemU(posicionBuscada,*listaUsuarios);
    deleteAtPositionU(posicionBuscada,listaUsuarios);
    printf("* Delete: user %s category %s totalplaytime %d\n",elementoBuscado.userName, enumToString(elementoBuscado.userCategory),elementoBuscado.totalPlayTime);

}

void Remove(tListU *listaUsuarios, int maxTime){
    //Contador para llevar la cuenta de items eliminados.
    int eliminados = 0;
    tItemU itemActual;
    //Si la lista esta vacía abandonamos la función.
    if(isEmptyListU(*listaUsuarios)){
        printf("+ Error: Remove not possible\n");
        return;
    }

    tPosU posicionActual = firstU(*listaUsuarios);

    while(posicionActual!=NULLU){
        //Obtenemos el item de cada posición.
        itemActual = getItemU(posicionActual,*listaUsuarios);
        //Si se cumple la condición se elimina el ítem.
        if(itemActual.totalPlayTime>maxTime){
            deleteAtPositionU(posicionActual,listaUsuarios);
            printf("Removing user %s totalplaytime %d\n",itemActual.userName,itemActual.totalPlayTime);
            eliminados++;
        }
        //Avanzamos la posición.
        posicionActual = nextU(posicionActual,*listaUsuarios);
    }
    //Si el numero de eliminados es 0 printeamos error.
    if(eliminados==0) printf("+ Error: Remove not possible\n");
}



void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3,tListU *listaUsuarios) {
    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);
            new(listaUsuarios, stringToEnum(param2),param1);
            break;
        case 'D':
            printf("%s %c: user %s\n",commandNumber,command,param1);
            delete(listaUsuarios,param1);
            break;
        case 'A':
            printf("%s %c: user %s song %s\n",commandNumber,command,param1,param2);
            add(listaUsuarios,param1,param2);
            break;
        case 'U':
            printf("%s %c: user %s\n",commandNumber,command,param1);
            upgrade(param1,listaUsuarios);
            break;
        case 'P':
            printf("%s %c: user %s song %s minutes %s\n",commandNumber,command,param1,param2,param3);
            play(listaUsuarios,param1,param2, StringToInt(param3));
            break;
        case 'S':
            printf("%s %c:\n",commandNumber,command);
            stats(*listaUsuarios);
            break;
        case 'R':
            printf("%s %c: maxtime %s\n",commandNumber,command,param1);
            Remove(listaUsuarios, StringToInt(param1));
            break;
        default:
            break;
    }
}

void readTasks(char *filename,tListU listaUsuarios) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3,&listaUsuarios);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    //creamos la lista
    tListU listaUsuarios;
    createEmptyListU(&listaUsuarios);
    char *file_name = "new.txt";


    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name,listaUsuarios);

free(listaUsuarios);
    return 0;
}
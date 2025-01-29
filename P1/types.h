/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 18 / 03 / 24
 */


#ifndef PRO2_2023_P1_TYPES_H
#define PRO2_2023_P1_TYPES_H
#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>

typedef char tUserName[NAME_LENGTH_LIMIT];
typedef char tSongTitle[NAME_LENGTH_LIMIT];
typedef int tNumPlay;

typedef enum {basic, pro} tUserCategory;

typedef struct tItemL {
    tUserName userName;
    tNumPlay numPlay;
    tUserCategory userCategory;
} tItemL;

typedef struct tSong{
    tSongTitle songTitle;
} tSong;

#endif //PRO2_2023_P1_TYPES_H

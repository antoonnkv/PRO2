/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 25 / 04 / 24
 */


#ifndef PRO2_2023_P2_TYPES_H
#define PRO2_2023_P2_TYPES_H

#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>

typedef char tUserName[NAME_LENGTH_LIMIT];
typedef enum {basic, pro} tUserCategory;
typedef int tPlayTime;
typedef char tSongTitle[NAME_LENGTH_LIMIT];

typedef struct Song{
    tSongTitle songTitle;
    tPlayTime playTime;
} tSong;

#endif //PRO2_2023_P2_TYPES_H

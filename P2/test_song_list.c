#include <stdio.h>
#include <string.h>

#include "song_list.h"

void print_list(tListS list) {
    tPosS pos;
    tItemS item;

    printf("(");
    if (!isEmptyListS(list)) {
        pos = firstS(list);
        while (pos != NULLS) {
            item = getItemS(pos, list);
            printf(" %s playTime %d", item.songTitle, item.playTime);
            pos = nextS(pos, list);
        }
    }
    printf(")\n");
}

int main() {
    tListS list;
    tPosS pos;
    tItemS item1, item2;

    /* init */
    item1.playTime = 0;


    /* create */
    createEmptyListS(&list);
    print_list(list);


    /* insert */
    strcpy(item1.songTitle, "song3");
    insertItemS(item1, NULLS, &list);
    print_list(list);

    strcpy(item1.songTitle, "song1");
    insertItemS(item1, firstS(list), &list);
    print_list(list);

    strcpy(item1.songTitle, "song5");
    insertItemS(item1, NULLS, &list);
    print_list(list);

    strcpy(item1.songTitle, "song2");
    insertItemS(item1, nextS(firstS(list), list), &list);
    print_list(list);

    strcpy(item1.songTitle, "song4");
    insertItemS(item1, lastS(list), &list);
    print_list(list);


    /* find */
    pos = findItemS("song33", list);
    if (pos == NULLS) {
        printf("song33 Not found\n");
    }

    pos = findItemS("song3", list);
    item2 = getItemS(pos, list);
    printf("%s found\n", item2.songTitle);


    /* update */
    item2.playTime = 100;
    updateItemS(item2, pos, &list);
    item2 = getItemS(pos, list);
    printf("%s updated playTime %d\n", item2.songTitle, item2.playTime);
    print_list(list);


    /* remove */
    deleteAtPositionS(nextS(firstS(list),list), &list);
    print_list(list);

    deleteAtPositionS(previousS(lastS(list),list), &list);
    print_list(list);

    deleteAtPositionS(firstS(list),&list);
    print_list(list);

    deleteAtPositionS(lastS(list),&list);
    print_list(list);

    deleteAtPositionS(firstS(list),&list);
    print_list(list);

    insertItemS(item1, NULLS, &list);
    print_list(list);

}

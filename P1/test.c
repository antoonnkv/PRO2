#include <stdio.h>
#include <string.h>

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

void print_list(tList list) {
    tPosL pos;
    tItemL item;

    printf("(");
    if (!isEmptyList(list)) {
        pos = first(list);
        while (pos != LNULL) {
            item = getItem(pos, list);
            printf(" %s numPlays %d", item.userName, item.numPlay);
            pos = next(pos, list);
        }
    }
    printf(")\n");
}

int main() {
    tList list;
    tPosL pos;
    tItemL item1, item2;


    /* create */
    createEmptyList(&list);
    print_list(list);

    /* insert */
    strcpy(item1.userName, "user3");
    item1.numPlay = 0;
    item1.userCategory = basic;

    insertItem(item1, LNULL, &list);
    print_list(list);

    strcpy(item1.userName, "user1");
    insertItem(item1, first(list), &list);
    print_list(list);

    strcpy(item1.userName, "user5");
    insertItem(item1, LNULL, &list);
    print_list(list);

    strcpy(item1.userName, "user2");
    insertItem(item1, next(first(list),list), &list);
    print_list(list);

    strcpy(item1.userName, "user4");
    insertItem(item1, last(list), &list);
    print_list(list);


    /* find */
    pos = findItem("user33", list);
    if (pos == LNULL) {
        printf("user33 Not found\n");
    }


    pos = findItem("user3", list);
    item2 = getItem(pos, list);
    printf("%s\n", item2.userName);


    /* update */
    item2 = getItem(pos, list);
    item2.numPlay = 2;
    updateItem(item2,pos,&list);
    printf("%s\n", item2.userName);
    print_list(list);

    /* remove */
    deleteAtPosition(next(first(list),list), &list);
    print_list(list);

    deleteAtPosition(previous(last(list),list), &list);
    print_list(list);

    deleteAtPosition(first(list),&list);
    print_list(list);

    deleteAtPosition(last(list),&list);
    print_list(list);

    deleteAtPosition(first(list),&list);
    print_list(list);

    insertItem(item1, LNULL, &list);
    print_list(list);
}

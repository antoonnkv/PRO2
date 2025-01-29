#include <stdio.h>
#include <string.h>

#include "user_list.h"

void print_list(tListU list) {
    tPosU pos;
    tItemU item;

    printf("(");
    if (!isEmptyListU(list)) {
        pos = firstU(list);
        while (pos != NULLU) {
            item = getItemU(pos, list);
            printf(" %s totalPlayTime %d", item.userName, item.totalPlayTime);
            pos = nextU(pos, list);
        }
    }
    printf(")\n");
}

int main() {
    tListU list;
    tPosU pos;
    tItemU item1, item2;

    /* init */
    item1.totalPlayTime = 0;


    /* create */
    createEmptyListU(&list);
    print_list(list);


    /* insert */
    strcpy(item1.userName, "user3");
    insertItemU(item1, &list);
    print_list(list);

    strcpy(item1.userName, "user1");
    insertItemU(item1, &list);
    print_list(list);

    strcpy(item1.userName, "user5");
    insertItemU(item1, &list);
    print_list(list);

    strcpy(item1.userName, "user2");
    insertItemU(item1, &list);
    print_list(list);

    strcpy(item1.userName, "user4");
    insertItemU(item1, &list);
    print_list(list);

    /* find */

    pos = findItemU("user33", list);
    if (pos == NULLU) {
        printf("user33 Not found\n");
    }

    pos = findItemU("user3", list);
    item2 = getItemU(pos, list);
    printf("%s found\n", item2.userName);

    /* update */

    item2.totalPlayTime = 100;
    updateItemU(item2, pos, &list);
    item2 = getItemU(pos, list);
    printf("%s updated totalPlayTime %d\n", item2.userName, item2.totalPlayTime);
    print_list(list);


    /* remove */

    deleteAtPositionU(nextU(firstU(list),list), &list);
    print_list(list);

    deleteAtPositionU(previousU(lastU(list),list), &list);
    print_list(list);

    deleteAtPositionU(firstU(list),&list);
    print_list(list);

    deleteAtPositionU(lastU(list),&list);
    print_list(list);

    deleteAtPositionU(firstU(list),&list);
    print_list(list);

    insertItemU(item1, &list);
    print_list(list);

}

/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 18 / 03 / 24
 */


#include "dynamic_list.h"
#include "string.h"

//Funcion auxiliar para crear nodos, necesaria en la función insertar.
bool createNode(tPosL *p){
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}

void createEmptyList(tList *L){
    //Se crea una lista vacía , poniendo el puntero de la lista a nulo.
    *L=LNULL;
}

bool isEmptyList(tList L){
    //Devuelve true si la lista está vacía.
    return L==LNULL;
}

tPosL first(tList L){
    //Devuelve la primera posición de la lista
    return L;
}

tPosL last(tList L){
    tPosL p;
    //Se recorre la lista hasta llegar al ultimo elemento.
    for(p=L;(p->next!=LNULL);p=p->next);
    //Se devuelve la posición del ultimo elemento.
    return p;
}


tPosL next(tPosL pos, tList L){
    //Devuelve la posición siguiente.
    return pos->next;
}




tPosL previous(tPosL pos, tList L){
    tPosL q;
    //Si la posición pasada por parámetro es la primera se devuelve nulo, dado que no existe una posición anterior.
    if(pos==L) q=LNULL;
    else
        for(q=L;q->next!=pos;q=q->next);
        //Se devuelve la posicion anterior a la pasada por parámetro.
        return q;
}




 bool insertItem(tItemL item, tPosL pos, tList *L){
    tPosL q,r;
    //La funcion devuelve falso si no se puede crear un nodo correctamente.
    if(!createNode(&q)) return false;
    else {
        //Se almacena el item en el nodo q.
        q->data = item;
        //La siguiente posicion se pone a nulo.
        q->next = LNULL;
        if (*L == LNULL) *L = q;
        //Si la posicion es la ultima se recorre la lista con un bucle para insertar al final.
        else if (pos == LNULL) {
            for (r = *L; r->next != LNULL; r = r->next);
            r->next = q;
            // Si la posicion pasada por parametro es la primera se inserta al principio de la lista.
        } else if (pos == *L) {
            q->next= *L;
            *L=q;
            // Si la posicion no es la primea ni la ultima, se inserta en la posicion pasada por parametro desplazando el resto de elementos.
        } else {
            q->next = pos->next;
            pos->next = q;
            q->data = pos->data;
            pos->data = item;
        }
        //La funcion devuelve true si se insertó correctamente.
        return true;
    }
}




void deleteAtPosition(tPosL pos, tList *L){
    //Si la posicion es la primera, el puntero L se apunta a la siguiente posicion.
    if(pos == *L)
        *L =(*L)->next;
    else previous(pos,*L)->next = pos->next;
    //Se libera la memoria del nodo borrado
    free(pos);
}


tItemL getItem(tPosL pos, tList L){
    //Devuelve el item que se encuentra en la posición pasada por parámetro.
    return pos->data;
}

void updateItem(tItemL item, tPosL pos, tList *L){
    //Se modifica el item que se encuentra en la posición pasada por parámetro igualandola al item también pasado por parámetro.
    pos->data=item;
}


tPosL findItem(tUserName name,tList L) {
    tPosL p;
    //Se recorre toda la lista mediante un bucle for.
    for (p = L; (p != LNULL) && (strcmp(p->data.userName, name) != 0); p = p->next);
    //Si se encuentra un item con igual userName se devuelve su posición.
    if (p != LNULL && strcmp(p->data.userName, name) == 0) return p;
    //En caso contrario se devuelve LNULL.
    else return LNULL;
}

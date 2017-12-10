/* avl.c
 * Implementação das operações realizadas sobre o TAD para uma árvore AVL 
 * adaptada para representar um Tree Map
 *
 * 05/nov/2017
 * Ciro C. Trindade
 * Modified by Otavio Tarelho | Mariana Bispo | Guilherme Furtado
 */

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Rotaçao para a esquerda
void rotacao_esq(map_ptr * t) {
   	map_ptr p;
   	p = (*t)->dir;
   	(*t)->dir = p->esq;
   	p->esq = *t;
   	*t = p;
}

// Rotação para a direita
void rotacao_dir(map_ptr * t) {
	map_ptr p;
   	p = (*t)->esq;
   	(*t)->esq = p->dir;
   	p->dir = *t;
   	*t = p;
}

void search(map_ptr * t, map_key key, map_value val, bool * h) {
    if (*t == NULL) {
        if((*t = (map_ptr) malloc(sizeof(struct map_node))) == NULL) {
            fprintf(stderr,"Erro de alocação de memória!\n");
            exit(1);
        }
        if (((*t)->value = (map_value *) malloc(sizeof(map_value))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        *((*t)->value) = val;
        *h = true;
        (*t)->key = key;
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    }
    else if (key < (*t)->key) { // Inserir a esquerda
        search(&(*t)->esq, key, val, h);
        if (*h)  { // O ramo esquerdo cresceu
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                    *h = false;
                    break;
                case 0: (*t)->bal = -1;
                    break;
                case -1: // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotação simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotação dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = +1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == +1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
            } // fim do switch
        }
    } // fim do if
    else if (key > (*t)->key) { // Inserir a direita
        search(&(*t)->dir, key, val, h);
        if (*h) { // O ramo direito cresceu
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                    *h = false;
                    break;
                case  0: (*t)->bal = +1;
                    break;
                case +1:  // Rebalanceamento
                    if ((*t)->dir->bal == +1) { // Rotação simples p/ esquerda
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    }
                    else { // Rotação dupla para esquerda
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == +1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = +1;
                        else (*t)->dir->bal = 0;
                    } // fim do else
                    *h = false;
                    (*t)->bal = 0;
            } // fim do switch
        }
    } // fim do if
    else // a chave já está na árvore
        *((*t)->value) = val;
} // fim de search

map_value * avl_find(map_ptr t, map_key key) {
	if (t == NULL) 
		return NULL;
	if (key == t->key)
		return t->value; 
	if (key < t->key)
		return avl_find(t->esq, key);
	return avl_find(t->dir, key);
}

int avl_size(map_ptr t)
{
	int cont = 0;
	if (t != NULL) {
		cont += map_size(&t->esq);
		cont += map_size(&t->dir);
		cont++;
	}
	return cont;
}

bool avl_isempty(map_ptr t)
{
	return (t == NULL);
}

map_value * delete(map_ptr * t, map_key key, bool * h)
{
   	map_ptr p;
	map_value * result;
   	if (*t == NULL) // A chave não se encontra na árvore
      	return NULL;
   	else if (key == (*t)->key) { // a chave está neste nó
   		result = (*t)->value;
      	p = *t;
      	if ((*t)->esq == NULL) { // nó folha ou somente com subárvore direita
         	*t = p->dir;
         	*h = true;
      	} 
      	else if ((*t)->dir == NULL) { // nó com uma única subárvore esquerda
         	*t = p->esq;
         	*h = true;
      	}  
      	else { // nó com duas subávores
         	p = get_min(&(*t)->dir, h); 
         	(*t)->key = p->key;
         	(*t)->value = p->value;
         	if (*h) balance_dir(t, h);
      	}	 
      	free(p);
      	return result;
   	}
   	else if (key < (*t)->key) {
      	result = delete(&(*t)->esq, key, h);
      	if (*h) balance_esq(t, h);
      	return result;
   	}
   	else {
      	result = delete(&(*t)->dir, key, h);
      	if(*h) balance_dir(t, h);
		return result;
   	}
} // fim do delete

void balance_dir(map_ptr * t, bool * h) {
    map_ptr p1, p2;
    int b1, b2;

   	switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
                break;
        case 0: (*t)->bal = -1;
                *h = false;
                break;
        case -1: // rebalanceamento
                p1 = (*t)->esq;
                b1 = p1->bal;
                if (b1 <= 0) { // rotação simples
                    (*t)->esq = p1->dir;
                    p1->dir = *t;
                    if (b1 == 0) {
                        (*t)->bal = -1;
                        p1->bal = 1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->dir;
                    b2 = p2->bal;
                    p1->dir = p2->esq;
                    p2->esq = p1;
                    p1->esq = p2->dir;
                    p2->dir = *t;
                    if(b2 == -1) (*t)->bal = 1;
                    else (*t)->bal = 0;
                    if(b2 == 1) p1->bal = -1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}

void balance_esq(map_ptr * t, bool * h) {
    map_ptr p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotação simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}


map_ptr get_min(map_ptr * t, bool * h) {
    map_ptr q;
    if ((*t)->esq) {
        q = get_min(&((*t)->esq), h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
    	q = *t;
        *t = (*t)->dir;
        return q;
    }
}

void avl_print (map_ptr t)
{
    if (t != NULL) {
        avl_print(t->esq);
        printf("(%d, %d)\n", t->key, (*t->value));
        avl_print(t->dir);
    }
}

void avl_kill(map_ptr * t)
{
	if (*t != NULL) {
		avl_kill(&(*t)->esq);
		avl_kill(&(*t)->dir);
		free(*t);
		*t = NULL;	
	}
}

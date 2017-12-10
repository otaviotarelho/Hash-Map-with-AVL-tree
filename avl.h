/* avl.h
 * Definição do TAD para uma árvore AVL e protótipo de suas operações
 *
 * 05/nov/2017
 * Ciro C. Trindade
 * Modified by Otavio Tarelho | Mariana Bispo | Guilherme Furtado
 */

#ifndef _AVL_H
#define _AVL_H

#include <stdbool.h>
#include "hashmap.h"

/* função que devolve verdadeiro se a árvore AVL estiver vazia */
bool avl_isempty(map_ptr t);

/* função que devolve o número de nós da árvore AVL */
int avl_size(map_ptr t);

/* função de busca e inserção em uma árvore AVL */
void search(map_ptr * t, map_key key, map_value val, bool * h);

/* função que remove e devolve o o nó de menor valor de uma subárvore */
map_ptr get_min(map_ptr * t, bool * h);

/* função que realiza uma rotação para a esquerda na árvore AVL */
void rotacao_esq(map_ptr * t);

/* função que realiza uma rotação para a direita na árvore AVL */
void rotacao_dir(map_ptr * t);

/* função que remove um nó da árvore AVL e devolve seu valor, ou NULL,
   caso a chave associada ao valor não esteja na árvore */
map_value * delete(map_ptr * t, map_key key, bool * h);

/* função que realiza um balanceamento à direita de uma árvore AVL
 * após uma remoção */
void balance_dir(map_ptr * t, bool * h);

/* função que realiza um balanceamento à esquerda de uma árvore AVL
 * após uma remoção */
void balance_esq(map_ptr * t, bool * h);

/* função que imprime a árvore AVL em ordem */
void avl_print(map_ptr);
/* função que devolve um valor dada uma chave na árvore AVL, ou NULL, 
   caso a chave associada ao valor não esteja na árvore */
map_value * avl_find(map_ptr t, map_key key);

/* função que desaloca todos os nós da árvore AVL */
void avl_kill(map_ptr * t);

#endif // _AVL_H

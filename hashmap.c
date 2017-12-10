/* hashmap.c
 * Implementação das operações realizadas sobre o TAD hash_map
 *
 * 05/nov/2017
 * Ciro C. Trindade
 * Modified by Otavio Tarelho | Mariana Bispo | Guilherme Furtado
 */

#include "hashmap.h"
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void map_init(hash_map m)
{
    int i;
    for(i = 0; i < M; i++){
        m[i] = NULL;
    }
}

int map_size(hash_map m)
{
	int i, cont = 0;
	for (i = 0; i < M; i++) {
		cont += avl_size(m[i]);
	}
	return cont;
}

bool map_isempty(hash_map m)
{
	int i;
	for (i = 0; i < M; i++)
		if (m[i] != NULL)
			return false;
	return true;
}

map_value * map_get(hash_map m, map_key key)
{
	return avl_find(m[h(key)], key);
}

void map_put(hash_map m, map_key key, map_value val)
{
    bool balanceamento;
	search(&m[h(key)], key, val, &balanceamento);
}

map_value * map_remove(hash_map m, map_key key)
{
    bool balanceamento;
	return delete(&m[h(key)], key, &balanceamento);
}

void map_kill(hash_map m)
{
    int i;
    for (i = 0; i < M; i++) {
        avl_kill(&m[i]);
    }
}

void map_print(hash_map m)
{
    int i;
    for (i = 0; i < M; i++) {
        avl_print(m[i]);
    }
}

int h(map_key key)
{
	int soma = key;
    
	// meio do quadrado
	soma *= soma;
	int meio = log10(M) / log10(2);
	int desl = (16 - meio) / 2;
	soma >>= desl;
	return soma & (M - 1);
}

/* Libraries for fields, doubly-linked lists and red-black trees.
   Copyright (C) 2018 James S. Plank */
// dlist kütüphanesi de bir çift yönlü bağlı liste yönetmek için harika bir kütüphane
// bütün fonksiyonlar harika bir biçimde şekillendirilmiş ve kullanılması çok kolay..
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include "dllist.h"


// neden çalışmıyor anlamaya çalışıyorum.
// bu kütüphaneyi entegre etmeyi Abdullah hocaya bir soralım.
Dllist new_dllist()
{
  Dllist d;

  d = (Dllist) malloc (sizeof(struct dllist));
  d->flink = d;
  d->blink = d;
  return d;
}
 
void dll_insert_b(Dllist node, Jval v)       /* Inserts before a given node */
{
  Dllist newnode;

  newnode = (Dllist) malloc (sizeof(struct dllist));
  newnode->val = v;

  newnode->flink = node;
  newnode->blink = node->blink;
  newnode->flink->blink = newnode;
  newnode->blink->flink = newnode;
}

void dll_insert_a(Dllist n, Jval val)        /* Inserts after a given node */
{
  dll_insert_b(n->flink, val);
}

void dll_append(Dllist l, Jval val)     /* Inserts at the end of the list */
{
  dll_insert_b(l, val);
}

void dll_prepend(Dllist l, Jval val)    /* Inserts at the beginning of the list */
{
  dll_insert_b(l->flink, val);
}


void dll_delete_node(Dllist node)		/* Deletes an arbitrary iterm */
{
  node->flink->blink = node->blink;
  node->blink->flink = node->flink;
  free(node);
}

int dll_empty(Dllist l)
{
  return (l->flink == l);
}
 
void free_dllist(Dllist l)
{
  while (!dll_empty(l)) {
    dll_delete_node(dll_first(l));
  }
  free(l);
}

Jval dll_val(Dllist l)
{
  return l->val;
}
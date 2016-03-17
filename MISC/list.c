#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  int data;
  struct list *next;
} LIST;

void print_list( LIST *l )
{
  while (l != NULL) {
    printf("%d\n", l->data);
    l = l->next;
  }
}

LIST* append( LIST *l, int i)
{
  LIST *new = NULL;
  LIST *end = NULL;
  LIST *ret = NULL;

  if( (new = (LIST*)malloc(sizeof(LIST))) == NULL ) {
    fprintf(stderr, "Memory Allocation error.\n");
    exit(1);
  }
  if (l == NULL) {
    ret = new;
  } else {
    ret = l;
    end = l;
    while (end->next != NULL) end = end->next;
    end->next = new;
  }
  new->data = i;
  new->next = NULL;
  return ret;
}

LIST* delete( LIST *l, int i )
{
  if (l == NULL)
    return NULL;
  if (l->data == i) {
    LIST *n = l->next;
    free(l);
    return n;
  }
  l->next = delete(l->next, i);
  return l;
}

LIST* move( LIST *l )
{
  LIST *n = NULL;
  LIST *p = NULL;
  LIST *ret = NULL;

  p = l;
  n = l->next;
  ret = n;
  while ( (n != NULL) && (l->data > n->data) ) {
    p = n;
    n = n->next;
  }
  p->next = l;
  l->next = n;
  return ret;
}

LIST* sort( LIST *l )
{
  if (l == NULL) return NULL;
  l->next = sort(l->next);
  if (l->next != NULL && l->data > l->next->data) {
    l = move(l);
  }
  return l;
}

int main(int argc, char** argv)
{
  LIST *l = NULL;
  int i = 0;

  l = append(l, 5);
  l = append(l, 2);
  l = append(l, 9);
  l = append(l, 8);
  l = append(l, 1);
  l = append(l, 7);

  printf("Original list : \n");
  print_list(l);
  l = sort(l);
  printf("Sorted list : \n");
  print_list(l);
  l = delete(l, 5);
  l = delete(l, 1);
  l = delete(l, 9);
  printf("Removed list : \n");
  print_list(l);

  return 0;
}

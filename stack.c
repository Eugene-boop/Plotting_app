#include "s21_calculator.h"

void pushNumbers(Nums **list, double x) {
  Nums *p = malloc(sizeof(Nums));
  p->data = x;
  p->next = *list;
  *list = p;
}

void pushSymbols(Syms **list, char x) {
  Syms *p = malloc(sizeof(Syms));
  p->data = x;
  p->next = *list;
  *list = p;
}

double popNumbers(Nums **list) {
  Nums *p = *list;
  double data;
  data = p->data;
  *list = p->next;
  free(p);
  return data;
}

char sPop(Syms **list) {
  Syms *p = *list;
  char data;
  data = p->data;
  *list = p->next;
  free(p);
  return data;
}
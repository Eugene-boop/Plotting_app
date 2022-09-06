#ifndef SRC_S21_CALCULATOR_H_
#define SRC_S21_CALCULATOR_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************
                STACK                
*************************************/

typedef struct Nums {
  double data;
  struct Nums *next;
} Nums;

typedef struct Syms {
  char data;
  struct Syms *next;
} Syms;

void pushNumbers(Nums **list, double x);
void pushSymbols(Syms **list, char x);
double popNumbers(Nums **list);
char sPop(Syms **list);

/*************************************
                LEXEMS                
*************************************/

bool isRightBracket(char x);
bool isLeftBracket(char x);
bool isSymbol(char x);
bool isNumber(char x);
double toDoubleX(char *ins, int sign);
double toDouble(char *ins, int *i, int sign);
char toFunc(char *ins, int *i, int sign);
int isFunc(char x);
int isOper(char x);
void counts(Nums **nlist, Syms **slist);
int tier(char x);
int getSign(char *ins, int *i);
int s21_validate(char *ins, char *x);
char *s21_calculate(char *ins, char *x);

#endif  //  SRC_S21_CALCULATOR_H_

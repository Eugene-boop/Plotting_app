#include "s21_calculator.h"

int s21_validate(char *ins, char *x) {
  int flag = 0, fun = 0, lB = 0, oper = 0, num = 0, rB = 0;

  if (x[0] != '\0') {
    for (int i = 0; x[i] != '\0' && !flag; i++) {
      if (!i && (x[i] == '-' || x[i] == '+')) {
      } else if (x[i] == '.' && !fun) {
        fun = 1;
      } else if (isNumber(x[i])) {
      } else {
        flag = 1;
      }
    }
    fun = 0;
  }

  for (int i = 0; ins[i] != '\0' && !flag; i++) {
    if (ins[i] == '(') {
      lB++;
    } else if (ins[i] == ')' && lB <= 0) {
      flag = 1;
    } else if (ins[i] == ')' && lB > 0) {
      lB--;
    }
  }

  if (lB) {
    flag = 1;
  }

  for (int i = 0; ins[i] != '\0' && !flag; i++) {
    int sign;
    sign = getSign(ins, &i);
    if (ins[i] == 'x' && !num) {
      num = 1;
      oper = 0;
    } else if (isSymbol(ins[i]) || isRightBracket(ins[i])) {
      char s = toFunc(ins, &i, sign);
      if (isFunc(s) && !num && !oper && !lB && !rB) {
        fun = 1;
      } else if (isFunc(s) && !fun && !num && !rB) {
        fun = 1;
      } else if (isOper(s) && !oper && num && ins[i + 1] != '\0') {
        oper = 1;
        rB = 0;
        num = 0;
      } else if ((isLeftBracket(s) && oper) || (isLeftBracket(s) && fun)) {
        lB = 1;
        rB = 0;
        fun = 0;
      } else if (isLeftBracket(s) && !num && !oper && !rB) {
        lB = 1;
      } else if (isRightBracket(s) && num) {
        rB = 1;
        lB = 0;
      } else {
        flag = 1;
      }
    } else if (isNumber(ins[i])) {
      if (toDouble(ins, &i, sign) != NAN && !num) {
        num = 1;
        oper = 0;
      } else {
        flag = 1;
      }
    } else if (ins[i] == ' ') {
    } else {
      flag = 1;
    }
  }

  return flag;
}
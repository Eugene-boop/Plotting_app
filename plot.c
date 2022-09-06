#include "s21_calculator.h"

char *s21_calculate(char *ins, char *x) {
  static char res[333];
  if (!s21_validate(ins, x)) {
    Nums *listNums = NULL;
    Syms *listSyms = NULL;

    for (int i = 0; ins[i] != '\0'; i++) {
      int sign = getSign(ins, &i);
      if (isNumber(ins[i])) {
        pushNumbers(&listNums, toDouble(ins, &i, sign));
      } else if (ins[i] == 'x') {
        pushNumbers(&listNums, toDoubleX(x, sign));
      } else if (isSymbol(ins[i]) && listSyms == NULL) {
        pushSymbols(&listSyms, toFunc(ins, &i, sign));
      } else if (ins[i] == '^' || ins[i] == '(') {
        pushSymbols(&listSyms, toFunc(ins, &i, sign));
      } else if (isSymbol(ins[i]) && tier(ins[i]) > tier(listSyms->data)) {
        pushSymbols(&listSyms, toFunc(ins, &i, sign));
      } else if (isSymbol(ins[i]) && tier(ins[i]) <= tier(listSyms->data)) {
        while (listSyms != NULL && tier(ins[i]) <= tier(listSyms->data)) {
          counts(&listNums, &listSyms);
        }
        pushSymbols(&listSyms, toFunc(ins, &i, sign));
      } else if (isRightBracket(ins[i])) {
        if (listSyms->data == '(') {
          sPop(&listSyms);
          if (listSyms != NULL && isFunc(listSyms->data)) {
            counts(&listNums, &listSyms);
          }
        } else {
          while (listSyms->data != '(') {
            counts(&listNums, &listSyms);
          }
          sPop(&listSyms);
        }
      }
    }
    while (listSyms != NULL) {
      counts(&listNums, &listSyms);
    }
    snprintf(res, sizeof(res), "%.8lf", popNumbers(&listNums));
  } else {
    const char err[] = {"incorrect input"};
    for (int i = 0; i < 15; i++) {
      res[i] = err[i];
    }
    res[15] = '\0';
  }
  return res;
}

int isFunc(char x) {
  int flag = 0;
  const char ins[] = {"cstalqwerydfghzxvbn"};
  for (int i = 0; ins[i] != '\0'; i++) {
    if (x == ins[i]) flag = 1;
  }
  return flag;
}

int isOper(char x) {
  int flag = 0;
  const char ins[] = {"+-*/%^"};
  for (int i = 0; ins[i] != '\0'; i++) {
    if (x == ins[i]) flag = 1;
  }
  return flag;
}

int getSign(char *ins, int *i) {
  int sign = 0;
  if (ins[*i] == '-' && isSymbol(ins[*i - 1])) {
    sign = 1;
    *i += 1;
  } else if (ins[*i] == '-' && !ins[*i - 1]) {
    sign = 1;
    *i += 1;
  }
  if (ins[*i] == '+' && isSymbol(ins[*i - 1])) {
    *i += 1;
  } else if (ins[*i] == '+' && !ins[*i - 1]) {
    *i += 1;
  }
  return sign;
}

int tier(char x) {
  int tier = 0;
  switch (x) {
    case '+':
    case '-':
      tier = 1;
      break;
    case '*':
    case '/':
    case '%':
      tier = 2;
      break;
    case '^':
    case 'c':
    case 's':
    case 't':
    case 'a':
    case 'l':
    case 'q':
    case 'w':
    case 'e':
    case 'r':
    case 'y':
    case 'd':
    case 'f':
    case 'g':
    case 'h':
    case 'z':
    case 'x':
    case 'v':
    case 'b':
    case 'n':
      tier = 3;
      break;
  }
  return tier;
}

char toFunc(char *ins, int *i, int sign) {
  char tmp = '0';
  int j = *i;
  switch (ins[*i]) {
    case ')':
      tmp = ')';
      break;
    case '(':
      tmp = '(';
      break;
    case '+':
      tmp = '+';
      break;
    case '-':
      tmp = '-';
      break;
    case '*':
      tmp = '*';
      break;
    case '/':
      tmp = '/';
      break;
    case '%':
      tmp = '%';
      break;
    case '^':
      tmp = '^';
      break;
    case 'c':
      if (ins[j + 1] == 'o' && ins[j + 2] == 's') {
        if (sign) {
          tmp = 'r';  // -cos
          *i += 2;
        } else {
          tmp = 'q';  // cos
          *i += 2;
        }
      }
      break;
    case 's':
      if (ins[j + 1] == 'i' && ins[j + 2] == 'n') {
        if (sign) {
          tmp = 't';  // -sin
          *i += 2;
        } else {
          tmp = 'w';  // sin
          *i += 2;
        }
      }
      if (ins[j + 1] == 'q' && ins[j + 2] == 'r' && ins[j + 3] == 't') {
        if (sign) {
          tmp = 'v';  // -sqrt
          *i += 3;
        } else {
          tmp = 'z';  // sqrt
          *i += 3;
        }
      }
      break;
    case 't':
      if (ins[j + 1] == 'a' && ins[j + 2] == 'n') {
        if (sign) {
          tmp = 'y';  // -tan
          *i += 2;
        } else {
          tmp = 'e';  // tan
          *i += 2;
        }
      }
      break;
    case 'a':
      if (ins[j + 1] == 'c' && ins[j + 2] == 'o' && ins[j + 3] == 's') {
        if (sign) {
          tmp = 'f';  // -acos
          *i += 3;
        } else {
          tmp = 'a';  // acos
          *i += 3;
        }
      }
      if (ins[j + 1] == 's' && ins[j + 2] == 'i' && ins[j + 3] == 'n') {
        if (sign) {
          tmp = 'g';  // -asin
          *i += 3;
        } else {
          tmp = 's';  // asin
          *i += 3;
        }
      }
      if (ins[j + 1] == 't' && ins[j + 2] == 'a' && ins[j + 3] == 'n') {
        if (sign) {
          tmp = 'h';  // -atan
          *i += 3;
        } else {
          tmp = 'd';  // atan
          *i += 3;
        }
      }
      break;
    case 'l':
      if (ins[j + 1] == 'n') {
        if (sign) {
          tmp = 'b';  // -ln
          *i += 1;
        } else {
          tmp = 'x';  // ln
          *i += 1;
        }
      }
      if (ins[j + 1] == 'o' && ins[j + 2] == 'g') {
        if (sign) {
          tmp = 'n';  // -log
          *i += 2;
        } else {
          tmp = 'c';  // log
          *i += 2;
        }
      }
      break;
  }
  return tmp;
}

double toDoubleX(char *ins, int sign) {
  double tmp = 0, flag = 0;
  int signX = 0, i = 0;
  if (ins[i] == '-') {
    i++;
    signX++;
  }
  while (isNumber(ins[i]) || ins[i] == '.') {
    if (ins[i] == '.') {
      i++;
      flag = 1;
    }
    if (flag) flag *= 10;
    tmp += (ins[i] + '0' - 96);
    i++;
    if (isNumber(ins[i]) || ins[i] == '.') {
      tmp *= 10;
    }
  }
  if (flag) tmp /= flag;
  if ((sign && !signX) || (!sign && signX)) {
    tmp *= -1;
  }
  return tmp;
}

double toDouble(char *ins, int *i, int sign) {
  double tmp = 0;
  double flag = 0;
  int j = *i;
  while (isNumber(ins[j]) || ins[j] == '.') {
    if (ins[j] == '.' && !flag) {
      *i += 1;
      j += 1;
      flag = 1;
    } else if (ins[j] == '.' && flag) {
      tmp = NAN;
      break;
    }
    if (flag) flag *= 10;
    tmp += (ins[j] + '0' - 96);
    j += 1;
    if (isNumber(ins[j]) || ins[j] == '.') {
      tmp *= 10;
      *i += 1;
    }
  }
  if (flag) tmp /= flag;
  if (sign) tmp *= -1;
  return tmp;
}

void counts(Nums **nlist, Syms **slist) {
  double res = 0, one = 0, two = 0;
  char oper = sPop(slist);

  switch (oper) {
    case '+':
      two = popNumbers(nlist);
      one = popNumbers(nlist);
      res = one + two;
      break;
    case '-':
      two = popNumbers(nlist);
      one = popNumbers(nlist);
      res = one - two;
      break;
    case '*':
      two = popNumbers(nlist);
      one = popNumbers(nlist);
      res = one * two;
      break;
    case '/':
      two = popNumbers(nlist);
      one = popNumbers(nlist);
      res = one / two;
      break;
    case '%':
      two = popNumbers(nlist);
      one = popNumbers(nlist);
      res = fmod(one, two);
      break;
    case '^':
      two = popNumbers(nlist);
      one = popNumbers(nlist);
      res = pow(one, two);
      break;
    case 'q':  // cos
      one = popNumbers(nlist);
      res = cos(one);
      break;
    case 'r':  // -cos
      one = popNumbers(nlist);
      res = cos(one);
      res *= -1;
      break;
    case 'w':  // sin
      one = popNumbers(nlist);
      res = sin(one);
      break;
    case 't':  // -sin
      one = popNumbers(nlist);
      res = sin(one);
      res *= -1;
      break;
    case 'e':  // tan
      one = popNumbers(nlist);
      res = tan(one);
      break;
    case 'y':  // -tan
      one = popNumbers(nlist);
      res = tan(one);
      res *= -1;
      break;
    case 'a':  // acos
      one = popNumbers(nlist);
      res = acos(one);
      break;
    case 'f':  // -acos
      one = popNumbers(nlist);
      res = acos(one);
      res *= -1;
      break;
    case 's':  // asin
      one = popNumbers(nlist);
      res = asin(one);
      break;
    case 'g':  // -asin
      one = popNumbers(nlist);
      res = asin(one);
      res *= -1;
      break;
    case 'd':  // atan
      one = popNumbers(nlist);
      res = atan(one);
      break;
    case 'h':  // -atan
      one = popNumbers(nlist);
      res = atan(one);
      res *= -1;
      break;
    case 'z':  // sqrt
      one = popNumbers(nlist);
      res = sqrt(one);
      break;
    case 'v':  // -sqrt
      one = popNumbers(nlist);
      res = sqrt(one);
      res *= -1;
      break;
    case 'x':  // ln
      one = popNumbers(nlist);
      res = log(one);
      break;
    case 'b':  // -ln
      one = popNumbers(nlist);
      res = log(one);
      res *= -1;
      break;
    case 'c':  // log
      one = popNumbers(nlist);
      res = log10(one);
      break;
    case 'n':  // -log
      one = popNumbers(nlist);
      res = log10(one);
      res *= -1;
      break;
  }
  pushNumbers(nlist, res);
}

bool isRightBracket(char x) { return (x == ')'); }
bool isLeftBracket(char x) { return (x == '('); }
bool isSymbol(char x) {
  return (x == '(' || x == '+' || x == '-' || x == '*' || x == '/' ||
          x == '^' || x == '%' || x == 'c' || x == 's' || x == 't' ||
          x == 'a' || x == 'l');
}
bool isNumber(char x) { return (x >= '0' && x <= '9'); }


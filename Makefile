CC 						= gcc -std=c11
OS 						= $(shell uname)

# flags #
CFLAG 					= -Wall -Wextra -Werror -g
LDFLAGS 				= -lcheck 
GCOV 					= --coverage

ifeq ($(OS), Linux)
	LDFLAGS 			+= -lm -lrt -lpthread -lsubunit
	OPEN 				= xdg-open
else
	OPEN 				= open
endif

# names and extensions #
NAME 					= s21_calculator
TEX 					= ../docs/$(NAME).tex
LIB_NAME 				= $(NAME).a

T_NAME					= $(NAME)_test
T_SOURSE 				= ../tests/$(T_NAME).c
T_HEADER 				= ../tests/$(T_NAME).h
T_OBJECT 				= $(T_SOURCE:%.c=%.o)

SOURCES 				= $(filter-out $(T_SOURSE), $(wildcard *.c))
HEADERS 				= $(filter-out $(T_HEADER), $(wildcard *.h))
OBJECTS 				= $(SOURCES:%.c=%.o)

# targets #
all: install

$(LIB_NAME): $(OBJECTS) $(HEADERS)
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@rm -rf *.o
	@echo "The library was created."

# targets of installation #
install: build
	@mkdir $(HOME)/Desktop/SmartCalc
	@cp -rf ../build/Calculator.app $(HOME)/Desktop/SmartCalc/

build:
	@make all -C ../build
	@make clean -C ../build

uninstall:
	@rm -rf  $(HOME)/Desktop/SmartCalc
	@echo "Successfully. Smart Calc was deleted."

# targets for tests #
tests: $(LIB_NAME)
	@$(CC) $(CFLAG) $(T_SOURSE) -o $(T_NAME) $(SOURCES) $(LDFLAGS)
	@./$(T_NAME)

gcov_report:
	@$(CC) $(CFLAG) $(GCOV) $(T_SOURSE) $(SOURCES) $(LDFLAGS) -o coverage
	@./coverage
	@lcov --no-external -o report.info -c -q -d .
	@genhtml --legend --title "$(NAME)" report.info -o report
	@rm -rf *.gcda *.gcno *.gz *.out *.info coverage

# targets for documentation #
dvi:
	@makeinfo --html --no-split -o $(NAME).html $(TEX) --no-warn
	$(OPEN) $(NAME).html

# targets for distribution #
dist:
	tar -czvf SmartCalc.tar.gz ./*

# assembly #
clean:
	@rm -rf *.o *.a *.gcno *.gcda *.info *.out *.dSYM *.tar.gz coverage report $(NAME).html $(T_NAME)
	@echo "Successfully. Everything was deleted."

rebuild: clean uninstall all

open:
	$(OPEN) report/index.html

# for debug #
launch:
	@$(CC) $(CFLAG) $(SOURCES) -o $(T_NAME) -g -fsanitize=address -std=c11 -lm
	./$(T_NAME) "-2-3-x+3+(-23-3)"
	@rm -rf $(T_NAME)

check: lint cppcheck

lint:
	@echo "------------  Linter  ---------------"
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	@rm -rf ./CPPLINT.cfg

cppcheck:
	@echo "------------  CPPCheck  -------------"
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

ifeq ($(OS), Linux)
valg:
	@echo "------------  Valgrind  -------------"
	@CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(T_NAME)

else
leaks:
	@echo "-------------  Leaks  ---------------"
	@CK_FORK=no leaks --atExit -- ./$(T_NAME)
endif

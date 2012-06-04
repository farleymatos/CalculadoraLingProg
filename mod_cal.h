/*
  TRABALHO DE LINGUAGENS DE PROGRAMAÇÃO
  Calculadora em linha de comando 
              -Linguagem C++
              -Modularizada
              -Compartilhada pelo GitHub
  
  Professor: Leonardo Nunes
  Alunos: Bruno saraiva
          Farley Matos
          Laura Panzariello
          Stephanie Cancado
          Timon  Asch
   
   mod_cal.h
            Header com as definições da funções criadas.       
*/

# ifndef MOD_CAL

# define MOD_CAL "mod_cal.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctype.h>

using namespace std;

int parse(string expr);
void parse_tree(char **token, char *token_type, int token_count);
void eval1(char **token, char *token_type, int token_count);
double eval2(char **token, char *token_type, int token_count);
double eval3(char **token, char *token_type, int token_count);
double eval4(char **token, char *token_type, int token_count);
double eval5(char **token, char *token_type, int token_count);
double busca_variavel(char *variavel);
double atualiza_variavel(char *variavel,double valor);

# endif

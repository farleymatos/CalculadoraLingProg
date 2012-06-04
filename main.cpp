/*
  TRABALHO DE LINGUAGENS DE PROGRAMA��O
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
          
  Modulo Principal - Interface com o Usu�rio
         Faz a comunica��o inicial com o usu�rio e mant�m um loop para inser��o de express�es a serem calculadas.
*/


#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctype.h>

#include "mod_cal.h"

using namespace std;


int main(int argc, char *argv[])
{
	string expr;

	puts("Digite a expressao desejada e tecle enter");
	puts("Digite 'sair' para terminar o programa");

    
INICIO:
        try
        {
        
        	do
        	{               
        		printf("> ");
        		cin >> expr;
        		if (expr == "sair") break;  //sair do loop
        		else parse(expr);
        		
        		for(int i=0;i<100000;i++); // Para lerdar o computador. Porque eh rapido demais.
        		
        	} while (1);
        
        }
        catch (int e)
        {
             goto INICIO;  //se der algun erro, voltar pro inicio
        }

	return 1;  //soh pra sair do programa
}

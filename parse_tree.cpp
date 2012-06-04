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
          
  Modulo Parse Tree:
         Contem as funcoes com as regras de derivacao da parse-tree da Calculadora;
         Tambem possui funcoes de manipulacao das variaves armazenadas.
*/

#include "mod_cal.h"


int indice; 
int inicio; // novo inicio depois do ;
int count_variaveis = 0;
char **variaveis = NULL;
double *valor_variaveis = NULL;

//funcao que inicia a parse-tree
void parse_tree(char **token, char *token_type, int token_count)
{          //setando os indices usados para o inicio da expressao
        indice = 0;
        inicio = 0;
        eval1(token,token_type,token_count);  //derivacao propriamente dita
}

// REGRA: EXP_LIST = ATTRIB ; EXP_LIST | ATTRIB ;
void eval1(char **token, char *token_type, int token_count)
{
    double resposta = eval2(token,token_type,token_count);  //primeiro calcular a ATTRIB

       //no fim da ATRIB, depois de calcula-la
    if (indice == token_count)   //sem ';' no final da expressao
    {
               cout << "ERRO - FALTA DE PONTO E VIRGULA" << endl;
               throw 2;
    }
    else if (strcmp(token[indice],";"))  //se nao tem ';' depois da ATRIB == erro
    {
            cout << "ERRO SEMANTICO" << endl;
            throw 3;
    }

    cout << "RESPOSTA:" << resposta << endl;  //mostrando a resposta na tela
    
       //calculando a segunda EXPR_LIST
    indice ++;
    
    if (indice < token_count)  //se ainda nao tiver no final da expressao
    {
               inicio = indice;  //o inicio passa a ser o token apos o ';'
               eval1(token,token_type,token_count);  //recursao para calcular a EXPR_LIST
    }
}



// REGRA: ATRIB = WORD := EXPRESSION | EXPRESSION
double eval2(char **token, char *token_type, int token_count)
{
    double saida = 0;
    
        if (token_count - inicio > 2)  //REGRA:  WORD := EXPRESSION
        {
           if( token_type[inicio]=='V' && token_type[inicio+1]=='A')  //se o primeiro for uma variavel e o segundo for um ':='
           {
               indice = inicio+2;  //posionando o indice depois do ':='
               saida = eval3(token,token_type,token_count);  //calcular a EXPR
               return atualiza_variavel(token[inicio],saida);
           } 
        } 
        
           //REGRA:  EXPRESSION
        return eval3(token,token_type,token_count);  //calcular a EXPR
}



// REGRA: EXPR = TERM + EXPR | TERM - EXPR | TERM
double eval3(char **token, char *token_type, int token_count)
{
    double saida = 0;
    
    saida = eval4(token,token_type,token_count);  //primeiro calcula o TERM
    
       //calculo da EXPR
    if (indice < token_count)  //nao chegou no final da expressao ainda
    {
        char *cur_token = token[indice];

        if (!strcmp(cur_token,"+"))
        { 
                                   indice++;
                                   saida = saida+eval3(token,token_type,token_count);  //recurssao para calcular a EXPR
                                   return saida;
        }
        else if (!strcmp(cur_token,"-"))
        { 
                                   indice++;
                                   saida = saida-eval3(token,token_type,token_count);  //recurssao para calcular a EXPR
                                   return saida;
        }
    }
    
       //jah chegou no final da expressao
    return saida;
}



// REGRA: TERM = PRIMARY / TERM | PRIMARY * TERM | PRIMARY
double eval4(char **token, char *token_type, int token_count)
{
    double saida = 0;
    
    saida = eval5(token,token_type,token_count);  //primeiro calcula o PRIMARY
    
       //calculo do TERM
    if (indice < token_count)  //nao chegou no final da expressao ainda
    {
        char *cur_token = token[indice];

        if (!strcmp(cur_token,"*"))
        { 
                                   indice++;
                                   saida = saida*eval4(token,token_type,token_count);  //recursao para calcular o TERM
                                   return saida;
        }
        else if (!strcmp(cur_token,"/"))
        { 
                                   indice++;
                                   saida = saida/eval4(token,token_type,token_count);  //recursao para calcular o TERM
                                   return saida;
        }
    }
    
       //jah chegou no final da expressao
    return saida;
}



// REGRA: PRIMARY = NUMBER | WORD | ( EXPR )
double eval5(char **token, char *token_type, int token_count)
{
    char *cur_token = token[indice];
    double saida = 0;
    indice++;
    
    if (!strcmp(cur_token,"("))  //se tiver um '('
    {
         saida = eval3(token,token_type,token_count);  //enviar para a regra de EXPRESSION
         
         if (indice == token_count)  //chegou no final sem achar ')' == erro
         {
            cout << "ERRO - SEM FECHA PARENTESES" << endl;
            throw 6;
         }
         else if (strcmp(token[indice],")"))  //nao achou ')' == erro
         {
            cout << "ERRO - SEM FECHA PARENTESES" << endl;
            throw 6;
         }
         indice++;
         return saida;
         
    }
    
       //convertendo os tokens que sao numeros, de char para double
    else if (token_type[indice-1]=='D')  //indice-1 pois o indice foi incrementado
    {
         return atof(cur_token);
    }
    else if (token_type[indice-1]=='I')
    {
         return atof(cur_token);
    }
    else if (token_type[indice-1]=='V')  //se for uma variavel, substituir pelo valor dela
    {
         return busca_variavel(cur_token);
    }
    
    cout << "ERRO SEMANTICO" << endl;
    throw 3;
}


//funcao para buscar uma variavel
double busca_variavel(char *variavel)
{
       double saida = 0;
       
       for (int i =0; i < count_variaveis; i++)
       {
           if(!strcmp(variaveis[i],variavel))  //ela existe na lista
           {
               saida = valor_variaveis[i];
           }
       }
          //retorna o valor da variável; ou 0, se ela não existir na lista
       return saida;
}


//funcao para atualizar as variaveis do "vetor de variaveis"
double atualiza_variavel(char *variavel,double valor)
{
          //buscar a variavel no vetor
       for (int i =0; i < count_variaveis; i++)
       {
           if(!strcmp(variaveis[i],variavel))  //ela existe na lista
           {
               valor_variaveis[i] = valor;
               return valor;  //retornar o valor para ser usado
           }
       }
       
          //se nao encontrar a variavel no vetor, precisamos cria-la
       count_variaveis++;  //mais uma variavel no vetor
       
       if (count_variaveis == 1)  //se for a primeira a ser criada
       {       //alocando memoria para o "variaveis" e para o "*variaveis"
            variaveis = (char **) malloc (sizeof(char *));  
            variaveis[0] = (char *) malloc (strlen(variavel)*sizeof(char));
            
            strcpy(variaveis[0],variavel);  //copiando a variavel para o vetor
            valor_variaveis = (double *) malloc (sizeof(double));  //alocando memoria para o "vetor de valores"
            valor_variaveis[0] = valor;  //guardando o valor no vetor
       }
       
       else  //se nao for a primeira variavel, basta realocar a memoria para o "variaveis" e para o "valor_variaveis", e alocar normalmente para o "*variaveis"
       {
            variaveis = (char **) realloc (variaveis,count_variaveis*sizeof(char *));
            variaveis[count_variaveis-1] = (char *) malloc (strlen(variavel)*sizeof(char));

            strcpy(variaveis[count_variaveis-1],variavel);  //colocando no fim do vetor
            valor_variaveis = (double *) realloc (valor_variaveis,count_variaveis*sizeof(double));
            valor_variaveis[count_variaveis-1] = valor;
       }
       
       return valor;  //retornando o valor para ser usado por quem a chama
}

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
          
  Modulo Parse Tree e Regras
*/

#include "mod_cal.h"


int indice; 
int inicio; // novo inicio depois do ;
int count_variaveis = 0;
char **variaveis = NULL;
double *valor_variaveis = NULL;

int parse_tree(char **token, char *token_type, int token_count)
{       
        indice = 0;
        inicio = 0;
        eval1(token,token_type,token_count);      
}

// REGRA: EXP_LIST = ATTRIB ; EXP_LIST | ATTRIB ;
int eval1(char **token, char *token_type, int token_count)
{
    double resposta = eval2(token,token_type,token_count);

    
    if (indice == token_count)
    {
               cout << "ERRO - FALTA DE PONTO E VIRGULA" << endl;
               throw 2;
    }
    else if (strcmp(token[indice],";"))
    {
            cout << "ERRO SEMANTICO" << endl;
            throw 3;
    }

    cout << "RESPOSTA:" << resposta << endl;
    
    indice ++;
    
    if (indice < token_count)
    {
               inicio = indice;
               eval1(token,token_type,token_count);
    }

       
    return 1;
}



// REGRA: ATRIB = WORD := EXPRESSION | EXPRESSION
double eval2(char **token, char *token_type, int token_count)
{
    double saida = 0;
    
        if (token_count - inicio > 2)
        {
           if( token_type[inicio]=='V' && token_type[inicio+1]=='A')
           {
               indice = inicio+2;
               saida = eval3(token,token_type,token_count);
               return atualiza_variavel(token[inicio],saida);
           } 
        } 
        
        return eval3(token,token_type,token_count);
}



// REGRA: EXPR = TERM + EXPR | TERM - EXPR | TERM
double eval3(char **token, char *token_type, int token_count)
{
    double saida = 0;
    
    saida = eval4(token,token_type,token_count);
    
    
    if (indice < token_count) 
    {
        char *cur_token = token[indice];

        if (!strcmp(cur_token,"+"))
        { 
                                   indice++;
                                   saida = saida+eval3(token,token_type,token_count);
                                   //cout << "EXPR " << saida << " - INDICE " << indice << endl;
                                   return saida;
        }
        else if (!strcmp(cur_token,"-"))
        { 
                                   indice++;
                                   saida = saida-eval3(token,token_type,token_count);
                                   //cout << "EXPR " << saida << " - INDICE " << indice << endl;
                                   return saida;
        }
    }
    
    //cout << "EXPR " << saida << " - INDICE " << indice << endl;
    return saida;
}



// REGRA: TERM = PRIMARY / TERM | PRIMARY * TERM | PRIMARY
double eval4(char **token, char *token_type, int token_count)
{
    double saida = 0;
    
    saida = eval5(token,token_type,token_count);
    
    
    if (indice < token_count) 
    {
        char *cur_token = token[indice];

        if (!strcmp(cur_token,"*"))
        { 
                                   indice++;
                                   saida = saida*eval4(token,token_type,token_count);
                                   //cout << "TERM " << saida << " - INDICE " << indice << endl;
                                   return saida;
        }
        else if (!strcmp(cur_token,"/"))
        { 
                                   indice++;
                                   saida = saida/eval4(token,token_type,token_count);
                                   //cout << "TERM " << saida << " - INDICE " << indice << endl;
                                   return saida;
        }
    }
    
    //cout << "TERM " << saida << " - INDICE " << indice << endl;
    return saida;
}



// REGRA: PRIMARY = NUMBER | WORD | ( EXPR )
double eval5(char **token, char *token_type, int token_count)
{
    char *cur_token = token[indice];
    double saida = 0;
    indice++;
    
    if (!strcmp(cur_token,"("))
    {
         //cout << "PRIMARY " << cur_token << " - INDICE " << indice << endl;
         saida = eval3(token,token_type,token_count);
         
         if (indice == token_count)
         {
            cout << "ERRO - SEM FECHA PARENTESES" << endl;
            throw 6;
         }
         else if (strcmp(token[indice],")"))
         {
            cout << "ERRO - SEM FECHA PARENTESES" << endl;
            throw 6;
         }
         indice++;
         return saida;
         
    }
    else if (token_type[indice-1]=='D')
    {
         //cout << "PRIMARY " << atof(cur_token) << " - INDICE " << indice << endl;
         return atof(cur_token);
    }
    else if (token_type[indice-1]=='I')
    {
         //cout << "PRIMARY " << atof(cur_token) << " - INDICE " << indice << endl;
         return atof(cur_token);
    }
    else if (token_type[indice-1]=='V')
    {
         //cout << "PRIMARY " << cur_token << " - INDICE " << indice << endl;
         return busca_variavel(cur_token);
    }
    
    cout << "ERRO SEMANTICO" << endl;
    throw 3;
    //cout << "ERRO - REDIGITE A EXPRESSAO" << " - INDICE " << indice << endl;
    
    return 0;
}


double busca_variavel(char *variavel)
{
       double saida = 0;
       
       for (int i =0; i < count_variaveis; i++)
       {
           if(!strcmp(variaveis[i],variavel))
           {
               saida = valor_variaveis[i];
           }
       }
       
       return saida;
}

double atualiza_variavel(char *variavel,double valor)
{
       for (int i =0; i < count_variaveis; i++)
       {
           if(!strcmp(variaveis[i],variavel))
           {
               valor_variaveis[i] = valor;
               //cout << "ENCONTRADO: " <<  variaveis[i] << " = " << valor_variaveis[i] << endl;
               return valor;
           }
       }
       
       count_variaveis++;
       
       if (count_variaveis == 1)
       {
            variaveis = (char **) malloc (sizeof(char *));
            variaveis[0] = (char *) malloc (strlen(variavel)*sizeof(char));
            strcpy(variaveis[0],variavel);
            valor_variaveis = (double *) malloc (sizeof(double));
            valor_variaveis[0] = valor;
            //cout << "ADICIONADO: " << count_variaveis << " - " << variaveis[0] << " = " << valor_variaveis[0] << endl; 
       }
       else
       {
            variaveis = (char **) realloc (variaveis,count_variaveis*sizeof(char *));
            variaveis[count_variaveis-1] = (char *) malloc (strlen(variavel)*sizeof(char));
            strcpy(variaveis[count_variaveis-1],variavel);
            valor_variaveis = (double *) realloc (valor_variaveis,count_variaveis*sizeof(double));
            valor_variaveis[count_variaveis-1] = valor;
            //cout << "ADICIONADO: " << count_variaveis << " - " <<  variaveis[count_variaveis-1] << " = " << valor_variaveis[count_variaveis-1] << endl;
       }
       
       return valor;
}

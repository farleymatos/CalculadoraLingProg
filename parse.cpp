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
          
  Modulo Parse:
         Separa a expressao inserida pelo usuario em tokens, para passa-los pela parse-tree.
*/


#include "mod_cal.h"


int parse(string expr)
{
      // converte para string c
      char *expr_c = new char[expr.size()+1];
      strcpy(expr_c,expr.c_str());
      
      // array de tokens após a quebra
      char **token;
      int token_count = 0;
      char *token_type;
      
      // buffer temporario
      char *buffer = NULL;
      char tipo_buffer = -1;
      
      // quebra o texto de entrada em tokens
      for (int i =0; i < expr.size() ; i++)
      {
          
          //separador espaço
          if(expr_c[i] == ' ')
          {               //se tem algo no buffer
                       if(buffer != NULL)
                       {            //e eh um '.' sozinho == erro
                                 if(!strcmp(buffer,"."))
                                 {
                                      cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                                      throw 1; //jogar um erro do tipo 1 - o catch vai receber 1 na variavel e
                                 }
                                 token_count++; //se esta tudo ok, entao fechamos um token
                                 
                                    //se eh o primeiro token que encontramos, precisamos alocar a memoria para o "token" e para o "token_type"
                                 if (token_count == 1) 
                                 {
                                                 token = (char **) malloc(sizeof(char *));
                                                 token_type = (char *) malloc(sizeof(char));
                                 }
                                 else            //senao, apenas realocamos
                                 {
                                                 token = (char **) realloc(token,token_count*sizeof(char *));
                                                 token_type = (char *) realloc(token_type,token_count*sizeof(char));
                                 }
                                 
                                 token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));  //alocando memoria para o "*token"
                                 strcpy(token[token_count-1],buffer);  //armazenando o token no "vetor de tokens"
                                 token_type[token_count-1] = tipo_buffer;  //armazenando o tipo do token no "vetor de tipos de token"
                                 
                                    //resetando o buffer, para procurarmos outro token
                                 free(buffer);
                                 buffer = NULL;
                                 tipo_buffer = -1;
                       }
          }
          
          //separador de sinais
          else if(expr_c[i] == '(' || expr_c[i] == ')' || expr_c[i] == '+' || expr_c[i] == '-' || expr_c[i] == '*' || expr_c[i] == '/' || expr_c[i] == ';')
          {               //se tem algo no buffer
                       if(buffer != NULL)
                       {            //e eh um '.' sozinho == erro
                                 if(!strcmp(buffer,"."))
                                 {
                                      cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                                      throw 1;
                                 }    
                                 token_count++;  //se esta tudo ok, entao fechamos um token
                                 
                                    //se eh o primeiro token que encontramos, precisamos alocar a memoria para o "token" e para o "token_type"
                                 if (token_count == 1) 
                                 {
                                                 token = (char **) malloc(sizeof(char *));
                                                 token_type = (char *) malloc(sizeof(char));
                                 }
                                 else            //senao, apenas realocamos
                                 {
                                                 token = (char **) realloc(token,token_count*sizeof(char *));
                                                 token_type = (char *) realloc(token_type,token_count*sizeof(char));
                                 }
                                 
                                 token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
                                 strcpy(token[token_count-1],buffer);
                                 token_type[token_count-1] = tipo_buffer;

                                    //resetando o buffer, para procurarmos outro token
                                 free(buffer);
                                 buffer = NULL;
                                 tipo_buffer = -1;
                       }
                       
                          //armazenando os sinais no "vetor de tokens"
                       token_count++;
                       if (token_count == 1) 
                       {
                                   token = (char **) malloc(sizeof(char *));
                                   token_type = (char *) malloc(sizeof(char));
                       }
                       else
                       {
                                   token = (char **) realloc(token,token_count*sizeof(char *));
                                   token_type = (char *) realloc(token_type,token_count*sizeof(char));
                       }
                       
                       
                       token[token_count-1] = (char *) malloc(2*sizeof(char));
                       token[token_count-1][0] = expr_c[i];
                       token[token_count-1][1] = '\0';
                       token_type[token_count-1] = 'S';  //tipo "sinal"
          }
          
          //separador :=
          else if(expr_c[i] == ':' && expr.size() != (i+1))  //se eh ':'
          {                 
                       if(expr_c[i+1] == '=')  //e depois vem '=', entao ok
                       {         //se tem algo no buffer
                              if(buffer != NULL)
                               {            //e eh um '.' sozinho == erro
                                         if(!strcmp(buffer,"."))
                                         {
                                              cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                                              throw 1;
                                         }
                                         token_count++;  //se esta tudo ok, entao fechamos um token
                                         
                                            //se eh o primeiro token que encontramos, precisamos alocar a memoria para o "token" e para o "token_type"
                                         if (token_count == 1) 
                                         {
                                                         token = (char **) malloc(sizeof(char *));
                                                         token_type = (char *) malloc(sizeof(char));
                                         }
                                         else            //senao, apenas realocamos
                                         {
                                                         token = (char **) realloc(token,token_count*sizeof(char *));
                                                         token_type = (char *) realloc(token_type,token_count*sizeof(char));
                                         }
                                         
                                         token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
                                         strcpy(token[token_count-1],buffer);
                                         token_type[token_count-1] = tipo_buffer;
        
                                            //resetando o buffer, para procurarmos outro token
                                         free(buffer);
                                         buffer = NULL;
                                         tipo_buffer = -1;
                               }  
                               
                                  //armazenando o simbolo de atribuicao no "vetor de tokens"
                               token_count++;
                               if (token_count == 1) 
                               {
                                               token = (char **) malloc(sizeof(char *));
                                               token_type = (char *) malloc(sizeof(char));
                               }
                               else
                               {
                                               token = (char **) realloc(token,token_count*sizeof(char *));
                                               token_type = (char *) realloc(token_type,token_count*sizeof(char));
                               }
                               
                               
                               token[token_count-1] = (char *) malloc(2*sizeof(char));
                               token[token_count-1][0] = '=';
                               token[token_count-1][1] = '\0';
                               token_type[token_count-1] = 'A';  //tipo "atribuicao"
                               
                               i++;  //incrementa o i para pular o caracter '=' que vem depois do ':' 
                       }
                       else  //senao == erro
                       {
                           cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                           throw 1;
                       }
          }
          
          // monta variaveis e numeros
          else if(isalnum(expr_c[i]) || expr_c[i] == '.')
          {                       //se encontrou algo que nao eh sinal, entao eh variavel ou numero
                              if(buffer == NULL)
                              {
                                         buffer = (char *) malloc(2*sizeof(char));
                                         buffer[1] = '\0';
                                         buffer[0] =  expr_c[i];
                                         if (isalpha(expr_c[i])) tipo_buffer = 'V';  //eh uma variavel
                                         else if (expr_c[i] == '.') tipo_buffer = 'D';  //se tiver o caracter '.', eh um decimal
                                         else tipo_buffer = 'I';  //eh um int
                              }
                              //a variavel/numero pode ter mais de um caracter, entao o buffer soh fecha quando encontrar um sinal/espaco
                              
                                  //continuando a montar a variavel/numero
                              else
                              { 
                                          if(tipo_buffer == 'I' && isalpha(expr_c[i]))  //inteiro seguido de letra == erro
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                         
                                          }
                                          if(tipo_buffer == 'D' && isalpha(expr_c[i]))  //decimal seguido de letra == erro
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                        
                                          }
                                           
                                          if(tipo_buffer == 'V' && expr_c[i] == '.')  //variavel seguida de '.' == erro
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                         
                                          } 
                                          if(tipo_buffer == 'D' && expr_c[i] == '.')  //decimal seguido de '.' == erro
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                        
                                          } 
                                          if(tipo_buffer == 'I' && expr_c[i] == '.')  //inteiro seguido de '.' == decimal
                                          {
                                                         tipo_buffer = 'D';                        
                                          } 
                                          
                                            //juntar esta "parte" da variavel/numero com a que ja tinhamos
                                          buffer = (char *) realloc(buffer,(strlen(buffer)+2)*sizeof(char));
                                          buffer[strlen(buffer)+1] = '\0'; 
                                          buffer[strlen(buffer)] =  expr_c[i]; 
                              }    
                                       
          }
          
             //se nao for nenhuma dos anteriores == erro
          else
          {
              cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
              throw 1;
          }
          
          
      }
      
         //para guardarmos o ultimo token armazenado no buffer
             //se tem algo no buffer
      if(buffer != NULL)
      {         //e eh um '.' sozinho  == erro
           if(!strcmp(buffer,"."))
           {
                cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                throw 1;
           }
           token_count++;  //se esta tudo ok, entao fechamos um token
           
              //se eh o primeiro token que encontramos, precisamos alocar a memoria para o "token" e para o "token_type"
           if (token_count == 1) 
           {
                           token = (char **) malloc(sizeof(char *));
                           token_type = (char *) malloc(sizeof(char));
           }
           else            //senao, apenas realocamos
           {
                           token = (char **) realloc(token,token_count*sizeof(char *));
                           token_type = (char *) realloc(token_type,token_count*sizeof(char));
           }
                                         
           token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
           strcpy(token[token_count-1],buffer);
           token_type[token_count-1] = tipo_buffer;
        
              //resetando o buffer para procurarmos outro token
           free(buffer);
           buffer = NULL;
           tipo_buffer = -1;
      }
  
      parse_tree(token,token_type,token_count);  //passando o "vetor de tokens" pela parse-tree
      
      return 1;
}

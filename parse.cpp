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
          
  Modulo Parse 
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
          {
                       if(buffer != NULL)
                       {
                                 if(!strcmp(buffer,"."))
                                 {
                                      cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                                      throw 1; //jogar um erro do tipo 1 - o catch vai receber 1 na variavel e
                                 }
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
                                 
                                 token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
                                 strcpy(token[token_count-1],buffer);
                                 token_type[token_count-1] = tipo_buffer;

                                 free(buffer);
                                 buffer = NULL;
                                 tipo_buffer = -1;
                                 
                                 //cout << "TOKEN [" << token[token_count-1] << "] - " << token_type[token_count-1] << " - " << token_count << endl;
                       }
          }
          
          //separador demais
          else if(expr_c[i] == '(' || expr_c[i] == ')' || expr_c[i] == '+' || expr_c[i] == '-' || expr_c[i] == '*' || expr_c[i] == '/' || expr_c[i] == ';')
          {
                       if(buffer != NULL)
                       {         
                                 if(!strcmp(buffer,"."))
                                 {
                                      cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                                      throw 1;
                                 }    
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
                                 
                                 token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
                                 strcpy(token[token_count-1],buffer);
                                 token_type[token_count-1] = tipo_buffer;

                                 free(buffer);
                                 buffer = NULL;
                                 tipo_buffer = -1;
                                 
                                 //cout << "TOKEN [" << token[token_count-1] << "] - " << token_type[token_count-1] << " - " << token_count << endl;
                       }
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
                       token_type[token_count-1] = 'S';
                        
                       //cout << "TOKEN [" << token[token_count-1] << "] - " << token_type[token_count-1] << " - " << token_count << endl;
          }
          
          //separador :=
          else if(expr_c[i] == ':' && expr.size() != (i+1))
          {
                       if(expr_c[i+1] == '=')
                       {
                              if(buffer != NULL)
                               {    
                                         if(!strcmp(buffer,"."))
                                         {
                                              cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                                              throw 1;
                                         }
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
                                         
                                         token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
                                         strcpy(token[token_count-1],buffer);
                                         token_type[token_count-1] = tipo_buffer;
        
                                         free(buffer);
                                         buffer = NULL;
                                         tipo_buffer = -1;
                                         
                                         //cout << "TOKEN [" << token[token_count-1] << "] - " << token_type[token_count-1] << " - " << token_count << endl;
                               }  
                               
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
                               token_type[token_count-1] = 'A';
                                
                               //cout << "TOKEN [" << token[token_count-1] << "] - " << token_type[token_count-1] << " - " << token_count << endl;  
                               
                               i++;    
                       }
                       else
                       {
                           cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                           throw 1;
                       }
          }
          // monta variaveis e numeros
          else if(isalnum(expr_c[i]) || expr_c[i] == '.')
          {
                              if(buffer == NULL)
                              {
                                         buffer = (char *) malloc(2*sizeof(char));
                                         buffer[1] = '\0'; 
                                         buffer[0] =  expr_c[i];
                                         if (isalpha(expr_c[i])) tipo_buffer = 'V';
                                         else if (expr_c[i] == '.') tipo_buffer = 'D';
                                         else tipo_buffer = 'I';
                              }
                              else
                              { 
                                          if(tipo_buffer == 'I' && isalpha(expr_c[i]))
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                         
                                          }
                                          if(tipo_buffer == 'D' && isalpha(expr_c[i]))
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                        
                                          }
                                           
                                          if(tipo_buffer == 'V' && expr_c[i] == '.')
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                         
                                          } 
                                          if(tipo_buffer == 'D' && expr_c[i] == '.')
                                          {
                                                         cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
                                                         throw 1;                        
                                          } 
                                          if(tipo_buffer == 'I' && expr_c[i] == '.')
                                          {
                                                         tipo_buffer = 'D';                        
                                          } 
                                          buffer = (char *) realloc(buffer,(strlen(buffer)+2)*sizeof(char));
                                          buffer[strlen(buffer)+1] = '\0'; 
                                          buffer[strlen(buffer)] =  expr_c[i]; 
                              }    
                                       
          }
          else
          {
              cout << "ERRO - REDIGITE A EXPRESSAO" << endl;
              throw 1;
          }
          
          
      }
      
      if(buffer != NULL)
      {    
           if(!strcmp(buffer,"."))
           {
                cout << "ERRO - REDIGITE A EXPRESSAO" << endl; 
                throw 1;
           }
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
                                         
           token[token_count-1] = (char *) malloc(strlen(buffer)*sizeof(char));
           strcpy(token[token_count-1],buffer);
           token_type[token_count-1] = tipo_buffer;
        
           free(buffer);
           buffer = NULL;
           tipo_buffer = -1;
                                         
        //cout << "TOKEN [" << token[token_count-1] << "] - " << token_type[token_count-1] << " - " << token_count << endl;
        }
  
      parse_tree(token,token_type,token_count);
      
      return 1;
}

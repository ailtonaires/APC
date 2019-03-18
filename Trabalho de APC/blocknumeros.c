
//bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//para utilizar o getch()
#include <ctype.h>//para utilizar o isdigit()

void bloqueia_num (char *disciplina)
{
    char c;//armazena cada caractere digitado pelo usuário
    int i=0;//variável para controlar o índice do vetor de caracteres

do{
        do
        {
       c=getch();//captura o caractere digitado pelo usuário
           if (isalpha(c)!=0 || c==32 || isdigit(c)!=0)//se for uma letra
           {
          disciplina[i] = c;//armazena na string
          i++;//incrementa o índice do vetor de caracteres
          printf ("%c", c);//exibe o caractere digitado
       }
       else if(c==8&&i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados
       {
          disciplina[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
          i--;//o índice do vetor de caracteres é decrementado
          printf("\b \b");//o caractere digitado é apagado da tela
       }
    }while(c!=13);//o loop vai ser executado até que a tecla pressionada seja o ENTER (código 13 na tabela ASCII)
}while(disciplina[0]=='\0');
    disciplina[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string

}







//bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//para utilizar o getch()
#include <ctype.h>//para utilizar o isdigit()

void bloqueia_num (char *disciplina)
{
    char c;//armazena cada caractere digitado pelo usu�rio
    int i=0;//vari�vel para controlar o �ndice do vetor de caracteres

do{
        do
        {
       c=getch();//captura o caractere digitado pelo usu�rio
           if (isalpha(c)!=0 || c==32 || isdigit(c)!=0)//se for uma letra
           {
          disciplina[i] = c;//armazena na string
          i++;//incrementa o �ndice do vetor de caracteres
          printf ("%c", c);//exibe o caractere digitado
       }
       else if(c==8&&i)//se for pressionada a tecla BACKSPACE e houver caracteres j� digitados
       {
          disciplina[i]='\0';//o �ndice atual do vetor de caracteres recebe a termina��o da string
          i--;//o �ndice do vetor de caracteres � decrementado
          printf("\b \b");//o caractere digitado � apagado da tela
       }
    }while(c!=13);//o loop vai ser executado at� que a tecla pressionada seja o ENTER (c�digo 13 na tabela ASCII)
}while(disciplina[0]=='\0');
    disciplina[i]='\0';//o �ndice atual do vetor de caracteres recebe a termina��o da string

}






#include "blocknumeros.h" // Biblioteca criada para bloquear n�meros
#include <conio.h> // Para usar fun��es como getch e getchar
#include <ctype.h> // Para usar fun��es como isdigit e isalpha
#include <locale.h> // Para corrigir erros de acentua��o e portugu�s
#include <stdio.h> // Para utilizar fun��es padr�o, como printf e scanf
#include <stdlib.h> // Para utilizar fun��es como atoi, itoa e exit
#include <string.h> // Para usar fun��es para strings, como strcpy e strcmp
#include <windows.h> // Para utilizar fun��es como Sleep
#define TAM_MAX 100

int opcao_escolhida;   // Vari�vel global, utilizada para as op��es do menu
char disciplinas[TAM_MAX]; // Vari�vel global, utilizada para armazenar nomes de disciplinas
char nomeArquivo[TAM_MAX]; // Vari�vel global, utilizada para armazenar nome do documento da disciplina
char apagar_nome_disc[TAM_MAX];
int total_alunos;
FILE *todas_disc; // Ponteiro Onde fica salva nome-codigo das disciplinas
FILE *relatorio;  // Ponteiro do arquivo de relatorio por disciplina

void bloquear_teclas(int menor_opcao,int maior_opcao) { // Procedimento que s� aceita n�meros

	int i = 0;
	char b;
	char opcao[50];

	do { /* Estrutura que verifica se o valor digitado est� entre
		 "menor_opcao" e "maior_opcao" com rela��o ao menu de op��es
		 e de acordo com cada par�metro*/

		do { /* Estrutura para aceitar apenas n�meros, bloqueando
			 a digita��o de quaisquer outros caracteres, exceto backspace e
			 enter*/

			b = getch();
			if (isdigit(b) != 0) { // Se for uma letra, retorna diferente de 0, ou seja, entra dentro da condicional
				opcao[i] = b; // string passa a receber o valor de "b" caso seja um caracter diferente de um n�mero
				i++;
				printf("%c", b); // printa na tela se for uma letra
			}

			else if (b == 8 && i) { // Caso "b" seja igual a backspace, ele ira retirar um caracter da string
				opcao[i] = '\0';

				i--;             // o "i" ser� decrementado para seguir a ordem da string
				printf("\b \b"); // Remove um caracter da tela, caso "b" seja 8 // 8 = backspace na tabela ASCII
			}
		} while (b != 13); // Fazer enquanto "b" for diferente de 13 // 13 = Enter na tabela ASCII

		opcao[i] = '\0'; // Quando enter for digitado, ele coloca um "\0" no final da string, indicando o final da mesma

		opcao_escolhida = atoi(opcao); // Transforma um char para inteiro

	} while (opcao_escolhida < menor_opcao || opcao_escolhida > maior_opcao); // Fazer enquanto "opcao_Escolhida" for maior ou menor que os par�metros
}

int main() {

	FILE *arq_geral;   // Ponteiro para abertura do arquivo geral
	FILE *melhor_disc; // Ponteiro para abertura do arquivo com maior aprova��o
	FILE *pior_disc;   // Ponteiro para abertura do arquivo de menor aprova��o

	setlocale(LC_ALL, "Portuguese"); // Corre��o de erros na parte escrita
									 // apresentada na execu��o do programa

	arq_geral = fopen("geral.txt", "r");
	fclose(arq_geral);

	if (arq_geral == NULL) { // Verificar se o arquivo geral existe. Caso n�o
							 // exista, ele ser� criado.
		arq_geral = fopen("geral.txt", "w");

		fprintf(arq_geral, "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n");

		fclose(arq_geral);
	}

	todas_disc = fopen("todas_disc.txt", "r");
	fclose(todas_disc);

	if (todas_disc == NULL) { // Verificar se o arquivo com o nome das
							  // disciplinas existe. Caso n�o exista, ele ser�
							  // criado.

		todas_disc = fopen("todas_disc.txt", "w");
		fclose(todas_disc);
	}

	melhor_disc = fopen("melhor_disc.txt", "r");

	if (melhor_disc == NULL) { // Verificar se o arquivo da disciplina com o
							   // melhor indice de aprova��o existe.
							   // Caso n�o exista, ele ser� criado.
		melhor_disc = fopen("melhor_disc.txt", "w");
		fprintf(melhor_disc, "0\n0");
		fclose(melhor_disc);
	}
	fclose(melhor_disc);

	pior_disc = fopen("pior_disc.txt", "r");

	if (pior_disc == NULL) { // Verificar se o arquivo da disciplina com o
							 // melhor indice de aprova��o existe.
							 // Caso n�o exista, ele ser� criado.

		pior_disc = fopen("pior_disc.txt", "w");
		fprintf(pior_disc, "101\n0");
		fclose(pior_disc);
	}
	fclose(pior_disc);

	system("cls");

	menu_principal();

	return 0;
}

void atualizar_disc(char nome_disciplina[],int alunos_SS,int alunos_MS,int alunos_MM,int alunos_MI,int alunos_II,int alunos_SR,int alunos_matriculados,int trancamentos,char *nome_disc) {
	fflush(stdin);
	int i;
	int armazenar[11];
	float percentual_total;
	char disc_geral[TAM_MAX];
	int percentual[3] = {0, 0, 0};
	FILE *relatorio;

	snprintf(disc_geral, 100, "geral_%s", nome_disciplina);

	relatorio = fopen(disc_geral, "r");
	fclose(relatorio);

	if (relatorio == NULL) {
		relatorio = fopen(disc_geral, "w");
		fprintf(relatorio, "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0");
		fclose(relatorio);
	}

	relatorio = fopen(disc_geral, "r");

	for (i = 0; i < 11; i++) {
		fscanf(relatorio, "%d", &armazenar[i]);
	}

	fclose(relatorio);

	percentual_total =
		((alunos_SS + alunos_MS + alunos_MM) * 100) / alunos_matriculados;

	alunos_matriculados += armazenar[0];
	trancamentos = trancamentos + armazenar[1];
	alunos_SS = alunos_SS + armazenar[2];
	alunos_MS = alunos_MS + armazenar[3];
	alunos_MM = alunos_MM + armazenar[4];
	alunos_MI = alunos_MI + armazenar[5];
	alunos_II = alunos_II + armazenar[6];
	alunos_SR = alunos_SR + armazenar[7];

	if (percentual_total < 30) {
		percentual[0] = 1;
	}

	if (percentual_total >= 30 && percentual_total < 50) {
		percentual[1] = 1;
	}
	if (percentual_total >= 50) {
		percentual[2] = 1;
	}

	for (i = 0; i < 3; i++) {
		percentual[i] = percentual[i] + armazenar[8 + i];
	}

	relatorio = fopen(disc_geral, "w");

	fprintf(relatorio,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d",alunos_matriculados,trancamentos,alunos_SS,alunos_MS,alunos_MM,alunos_MI,alunos_II,alunos_SR,percentual[0],percentual[1],percentual[2]);
	fclose(relatorio);

	// TESTE KKK pior_melhor(disc_geral, nome_disc);
}

void decrementar_arq_geral(char disc_geral[]) {

	int i;
	int atualizar[12], decrementar[12], resultado[12];
	FILE *deletar_disc;
	FILE *cod3;

	deletar_disc = fopen(disc_geral, "r");

	if (deletar_disc == NULL) {
		printf(" Deu errado!");
		system("pause");
	}
	for (i = 0; i < 11; i++) {
		fscanf(deletar_disc, "%d", &atualizar[i]);
	}
	fclose(deletar_disc);

	cod3 = fopen("geral.txt", "r");
	if (cod3 == NULL) {
		printf(" Deu errado");
		system("pause");
	}
	for (i = 0; i < 11; i++) {
		fscanf(cod3, "%d", &decrementar[i]);
	}
	fclose(cod3);

	for (i = 0; i < 11; i++) {
		resultado[i] = decrementar[i] - atualizar[i];
	}

	cod3 = fopen("geral.txt", "w");

	for (i = 0; i < 11; i++) {
		fprintf(cod3, "%d\n", resultado[i]);
	}

	fclose(cod3);
}

void verificar_disc(char *nome_disc) {

	char encontrar_disc[200];
	char encontrar_disc0[200];
	char nome[TAM_MAX], encontrar[200];
	char opcao[2];
	int cont = 0;
	int maior_opcao, menor_opcao;
	int i, j = 0;

	FILE *ARQ_TEMP;

	strcpy(nome, nome_disc);

	todas_disc = fopen("todas_disc.txt", "r");
	ARQ_TEMP = fopen("arquivo_temporario.txt", "w");

	do {
		fgets(encontrar_disc, 200, todas_disc);

		strcpy(apagar_nome_disc, encontrar_disc); // UTILIZADO PARA QUANDO A
												  // FUN��O FOR CHAMADA PARA
												  // APAGAR DISCIPLINA

		if (strstr(encontrar_disc, nome) != NULL) {

			for (i = 0; i < 200; i++) {
				nome_disc[i] = encontrar_disc[i];
				if (encontrar_disc[i] == '-') {
					nome_disc[i] = '\0';

					if (strcmp(encontrar_disc0, nome_disc) != 0) {
                        cont++;                                         // Cont Para saber quantas disciplinas existem com parte do nome digitado
						fprintf(ARQ_TEMP, "\n%d)%s", cont, nome_disc); // Printa as disciplinas encontradas com parte do nome dentro do arquivo tempor�rio
						strcpy(encontrar_disc0, nome_disc); // Para n�o repetir a �ltima disciplina
					}
				}
			}
		}

	} while (!feof(todas_disc));
	fclose(todas_disc);
	fclose(ARQ_TEMP);

	if (cont == 0) {
		printf("\n Desculpe, a disciplina que voc� procura com o nome %s n�o existe!\n\n",nome);

		printf(" 1) Ir para o menu inicial\n");
		printf(" 2) Ver disciplinas cadastradas\n");
		printf(" 3) Encerrar o programa\n\n");
		printf(" Op��o: ");
		bloquear_teclas(menor_opcao = 1, maior_opcao = 3); // Chamada de Procedimento que s� aceita n�meros

		switch (opcao_escolhida) {
		case 1:
			system("cls");
			menu_principal();
			break;

		case 2:
			system("cls");
			opcao8();
			break;

		case 3:
			system("cls");
			opcao7();
			break;
		}
	}

	if (cont != 0) {
		system("type arquivo_temporario.txt");

		printf("\n\n %d disciplina(s) que contenha \"%s\" como parte do nome ou do c�digo foram\n encontrada(s).",cont,nome);
		printf("\n Por favor, Indique o n�mero correspondente a disciplina que voc� procura.\n\n");
		printf(" Caso a disciplina que voc� procura n�o tenha sido encontrada, ela n�o existe.\n");
		printf("\n Digite 0 para voltar ao menu principal.\n\n");

		printf(" Op��o: ");
		bloquear_teclas(menor_opcao = 0, maior_opcao = cont);

		itoa(opcao_escolhida, opcao, 10); // Transformar inteiro em char

		if (opcao_escolhida == 0) {
			system("cls");
			menu_principal();
		}

		else {
			ARQ_TEMP = fopen("arquivo_temporario.txt", "r");

			do {
				fgets(encontrar, 200, ARQ_TEMP);

				if (strstr(encontrar, opcao) != NULL) {
					for (i = 2; i < 200; i++) {
						nome_disc[j] = encontrar[i];
						j++;
						if (nome_disc[j - 1] == '\n') {
							nome_disc[j - 1] = '\0';
						}
					}
					goto parar;
				}

			} while (!feof(ARQ_TEMP));
		}
	}

parar:
	fclose(ARQ_TEMP);
	system("cls");
}

void disc_e_codigos(char *nome_disc) {
	char encontrar_disc[300];
	int menor_opcao, maior_opcao;
	int i, x, j, z;

	x = strlen(nome_disc);

	for (i = 0; i < x; i++) {
		nome_disc[i] = toupper(nome_disc[i]); // Transformar todas as letras em mai�sculas
	}

	todas_disc = fopen("todas_disc.txt", "r");

	fseek(todas_disc, 0, SEEK_SET);

	do {
		fgets(encontrar_disc, 300, todas_disc);

		z = strlen(encontrar_disc);

		for (i = 0; i < z; i++) {
			if (encontrar_disc[i] == '-') {
				for (j = 0; j < z - i; j++) {
					encontrar_disc[j] = encontrar_disc[i + j + 1];
				}

				break;
			}
		}

		z = strlen(encontrar_disc);
		if (encontrar_disc[z - 1] =='\n') { // ELIMINAR "\n" DA STRING CASO EXISTA
			encontrar_disc[z - 1] = '\0';
		}

		if (strcmp(nome_disc, encontrar_disc) == 0) {
			printf("\n A disciplina e/ou c�digo j� existe(m)!!!\n\n");

			system("pause");

			printf("\n 1)Encerrar o cadastramento\n");
			printf(" 2)Voltar para o menu de cadastramento de disciplinas\n");
			printf(" 3)Cadastrar turma\n\n");
			printf(" Op��o: ");

			bloquear_teclas(menor_opcao = 1,maior_opcao =3); // Chamada de Procedimento que s� aceita n�meros

			switch (opcao_escolhida) {
			case 1:

				opcao7();

				break;
			case 2:

				opcao1();

				break;
			case 3:

				opcao2();

				break;
			}
		}

	} while (!feof(todas_disc));

	fclose(todas_disc);
}

void cod_turma(char *codigo, char *Turma, char *nome_disciplina) {

	char encontrar_cod[20];
	int z, y, i;

	FILE *codTurma;

	y = strlen(codigo);
	for (i = 0; i < y; i++) {
		codigo[i] =toupper(codigo[i]); // Transformar todas as letras em mai�sculas
	}

	codTurma = fopen(nome_disciplina, "r");

	fseek(codTurma, 0, SEEK_SET);

	do {
		fgets(encontrar_cod, 20, codTurma);

		z = strlen(encontrar_cod);
		if (encontrar_cod[z - 1] == '\n') {
			encontrar_cod[z - 1] = '\0'; // ELIMINAR "\n" DA STRING
		}

		if (strcmp(codigo, encontrar_cod) == 0) {
			strcpy(Turma, codigo);

			z = strlen(Turma);
			if (Turma[z - 1] == '\n') {
				Turma[z - 1] = '\0';
			}

			break;
		}

	} while (!feof(codTurma));

	fclose(codTurma);
}

void disc_procurar(char *nome_disc) {

	char encontrar_disc[300];
	char encontrar_disc2[300];
	char encontrar_disc3[300];
	int i, x, j, z;

	x = strlen(nome_disc);

	for (i = 0; i < x; i++) {
		nome_disc[i] =toupper(nome_disc[i]); // Transformar todas as letras em mai�sculas
	}

	todas_disc = fopen("todas_disc.txt", "r");

	fseek(todas_disc, 0, SEEK_SET);

	do {
		fgets(encontrar_disc, 300, todas_disc);

		z = strlen(encontrar_disc);

		for (i = 0; i < z; i++) {
			encontrar_disc3[i] = encontrar_disc[i]; // PEGAR NOME

			if (encontrar_disc[i] == '-') {
				encontrar_disc3[i] = '\0'; // TIRAR H�FEN DA STRING

				for (j = 0; j < z - i; j++) {
					encontrar_disc2[j] =
						encontrar_disc[i + j + 1]; // PEGAR C�DIGO
				}

				break;
			}
		}

		z = strlen(encontrar_disc2);
		if (encontrar_disc2[z - 1] == '\n') {
			encontrar_disc2[z - 1] = '\0'; // ELIMINAR "\n" DA STRING;
		}

		if (strcmp(nome_disc, encontrar_disc2) == 0) {
			strcpy(apagar_nome_disc, encontrar_disc); // UTILIZADO PARA QUANDO A
													  // FUN��O FOR CHAMADA PARA
													  // APAGAR DISCIPLINA

			for (i = 0; i < 300; i++) {
				nome_disc[i] = encontrar_disc[i];
				encontrar_disc2[i] = encontrar_disc[i];

				if (encontrar_disc[i] == '-') {
					nome_disc[i] = '\0';
					encontrar_disc2[i] = '\0';

					goto VAI;
				}
			}
		}

		if (strcmp(nome_disc, encontrar_disc3) == 0) {
			strcpy(apagar_nome_disc, encontrar_disc); // UTILIZADO PARA QUANDO A
													  // FUN��O FOR CHAMADA PARA
													  // APAGAR DISCIPLINA

			for (i = 0; i < 300; i++) {
				nome_disc[i] = encontrar_disc[i];
				encontrar_disc2[i] = encontrar_disc[i];

				if (encontrar_disc[i] == '-') {
					nome_disc[i] = '\0';
					encontrar_disc2[i] = '\0';

					goto VAI;
				}
			}
		}

	} while (!feof(todas_disc));

VAI:
	fclose(todas_disc);

	if (strcmp(nome_disc, encontrar_disc2) !=0) { // SE N�O ENCONTRAR COM STRCMP ELE PESQUISA POR PARTE
		verificar_disc(nome_disc);
	}
}

void pior_melhor() {

	float armazenar[5];
	char encontrar_disc[200], encontrar_disc2[200];
	char nome_disc[200], disc_geral[200];
	float armazenar2, armazenar3, perc_tot;
	int i, z = 0;

	FILE *melhor_disc;
	FILE *pior_disc;
	FILE *relatorio;
	fflush(stdin);

	todas_disc = fopen("todas_disc.txt", "r");

	do {
		fgets(encontrar_disc, 200, todas_disc);

		if (encontrar_disc[0] != '\n') {
			z = strlen(encontrar_disc);

			for (i = 0; i < z; i++) {
				encontrar_disc2[i] = encontrar_disc[i]; // PEGAR NOME

				if (encontrar_disc[i] == '-') {
					encontrar_disc2[i] = '\0'; // TIRAR H�FEN DA STRING
					strcpy(nome_disc, encontrar_disc2);
				}
			}

			z = strlen(encontrar_disc2);
			if (encontrar_disc2[z - 1] == '\n') {
				encontrar_disc2[z - 1] = '\0'; // ELIMINAR "\n" DA STRING;
			}

			snprintf(disc_geral, 200, "geral_disciplina_%s.txt", nome_disc);

			relatorio = fopen(disc_geral, "r");

			for (i = 0; i < 5; i++) {
				fscanf(relatorio, "%f", &armazenar[i]);
			}
			fclose(relatorio);

			perc_tot = ((armazenar[2] + armazenar[3] + armazenar[4]) * 100) /
				armazenar[0];

			melhor_disc = fopen("melhor_disc.txt", "r");

			fscanf(melhor_disc, "%f", &armazenar2);
			fclose(melhor_disc);

			if (armazenar[0] != 0) {
				if (perc_tot > armazenar2) {
					melhor_disc = fopen("melhor_disc.txt", "w");
					fprintf(melhor_disc, "%.2f\n%s", perc_tot, nome_disc);
					fclose(melhor_disc);
				}

				pior_disc = fopen("pior_disc.txt", "r");
				fscanf(pior_disc, "%f", &armazenar3);

				fclose(pior_disc);

				if (perc_tot < armazenar3) {
					pior_disc = fopen("pior_disc.txt", "w");
					fprintf(pior_disc, "%.2f\n%s", perc_tot, nome_disc);
					fclose(pior_disc);
				}
				fclose(pior_disc);
			}
		}
	} while (!feof(todas_disc));
}

void apagar_disc() {

	char apagar_nome[200];
	char duplicar[TAM_MAX];
	int i, j;
	FILE *temporario;

	todas_disc = fopen("todas_disc.txt", "r");
	temporario = fopen("temporario.txt", "w");

	do {
		fgets(apagar_nome, 200, todas_disc);

		i = strlen(apagar_nome);
		j = strlen(apagar_nome_disc);

		if (apagar_nome[i - 1] == '\n') {
			apagar_nome[i - 1] == '\0';
		}
		if (apagar_nome_disc[j - 1] == '\n') {
			apagar_nome_disc[j - 1] == '\0';
		}

		if (strcmp(apagar_nome, apagar_nome_disc) != 0) {
			fprintf(temporario, "%s", apagar_nome);
		}

	} while (!feof(todas_disc));

	fclose(todas_disc);
	fclose(temporario);

	todas_disc = fopen("todas_disc.txt", "w");
	temporario = fopen("temporario.txt", "r");

	do {
		fgets(apagar_nome, 200, temporario);

		i = strlen(apagar_nome);

		if (apagar_nome[i - 1] == '\n') {
			apagar_nome[i - 1] == '\0';
		}

		if (strcmp(apagar_nome, duplicar) != 0 && apagar_nome != '\n') {
			fprintf(todas_disc, "%s", apagar_nome);

			strcpy(duplicar, apagar_nome); // EVITA QUE O ARQUIVO PRINTA A MESMA
										   // DISCIPLINA DUAS VEZES
		}

	} while (!feof(temporario));

	fclose(todas_disc);
	fclose(temporario);

	remove("temporario.txt");
}

void deletar_turma(char *turma, char *nome_disciplina, char *codigo_turma) {

	char encontrar_turma[20];
	int menor_opcao, maior_opcao;
	int i, x, z;

	FILE *apagar_turma;

	x = strlen(turma);

	for (i = 0; i < x; i++) {
		turma[i] =toupper(turma[i]); // Transformar todas as letras em mai�sculas
	}

	apagar_turma = fopen(nome_disciplina, "r");

	fseek(apagar_turma, 0, SEEK_SET);

	do {
		fgets(encontrar_turma, 20, apagar_turma);

		z = strlen(encontrar_turma);
		if (encontrar_turma[z - 1] == '\n') {
			encontrar_turma[z - 1] = '\0'; // ELIMINAR "\n" DA STRING;
		}

		if (strcmp(turma, encontrar_turma) == 0) {
			for (i = 0; i < 20; i++) {
				turma[i] = encontrar_turma[i];

				if (encontrar_turma[i] == '\0') {
					turma[i] = '\0';
					encontrar_turma[i] = '\0';
					goto sai;
				}
			}
		}

	} while (!feof(apagar_turma));

sai:
	fclose(apagar_turma);

	if (strcmp(turma, encontrar_turma) != 0) {
		printf("\n Desculpe, a turma que voc� procura com o nome %s n�o existe!\n\n",codigo_turma);

		printf(" 1)Ir para o menu inicial\n");
		printf(" 2)Cadastrar turma\n");
		printf(" 3)Encerrar o programa\n\n");
		printf(" Op��o: ");
		bloquear_teclas(menor_opcao = 1, maior_opcao = 3); // Chamada de Procedimento que s� aceita n�meros

		switch (opcao_escolhida) {
		case 1:
			system("cls");
			menu_principal();
			break;

		case 2:
			system("cls");
			opcao2();
			break;

		case 3:
			system("cls");
			opcao7();
			break;
		}
	}
}

void decrementar_turma_arq_geral(int info_arq[]) {
	int i;
	int decrementar[12], resultado[12];
	float percentual;
	int perc[3] = {0, 0, 0};

	FILE *cod3;

	cod3 = fopen("geral.txt", "r");

	if (cod3 == NULL) {
		printf(" Deu errado");
		system("pause");
	}
	for (i = 0; i < 11; i++) {
		fscanf(cod3, "%d", &decrementar[i]);
	}
	fclose(cod3);

	percentual = ((info_arq[2] + info_arq[3] + info_arq[4]) * 100) /
		info_arq[0]; // PARA SABER O PERCENTUAL DE APROVA��O DA TURMA

	if (percentual >= 0 && percentual < 30) {
		perc[0] = 1;
	}
	if (percentual >= 30 && percentual < 50) {
		perc[1] = 1;
	}

	if (percentual >= 50) {
		perc[2] = 1;
	}

	for (i = 0; i < 8; i++) {
		resultado[i] = decrementar[i] - info_arq[i];
	}

	resultado[8] = decrementar[8] - perc[0];
	resultado[9] = decrementar[9] - perc[1];
	resultado[10] = decrementar[10] - perc[2];

	cod3 = fopen("geral.txt", "w");

	for (i = 0; i < 11; i++) {
		fprintf(cod3, "%d\n", resultado[i]);
	}

	fclose(cod3);
}

void decrementar_turma_disc(char nome_disciplina[],int alunos_SS, int alunos_MS, int alunos_MM, int alunos_MI, int alunos_II,int alunos_SR,int alunos_matriculados,int trancamentos,char *nome_disc) {

	fflush(stdin);
	int i;
	int armazenar[11];
	float percentual_total;
	char disc_geral[TAM_MAX];
	int percentual[3] = {0, 0, 0};
	FILE *relatorio;

	snprintf(disc_geral, 100, "geral_%s", nome_disciplina);

	relatorio = fopen(disc_geral, "r");
	fclose(relatorio);
	if (relatorio == NULL) {
		relatorio = fopen(disc_geral, "w");
		fprintf(relatorio, "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0");
		fclose(relatorio);
	}

	relatorio = fopen(disc_geral, "r");

	for (i = 0; i < 11; i++) {
		fscanf(relatorio, "%d", &armazenar[i]);
	}

	fclose(relatorio);

	percentual_total =
		((alunos_SS + alunos_MS + alunos_MM) * 100) / alunos_matriculados;

	alunos_matriculados = armazenar[0] - alunos_matriculados;
	trancamentos = armazenar[1] - trancamentos;
	alunos_SS = armazenar[2] - alunos_SS;
	alunos_MS = armazenar[3] - alunos_MS;
	alunos_MM = armazenar[4] - alunos_MM;
	alunos_MI = armazenar[5] - alunos_MI;
	alunos_II = armazenar[6] - alunos_II;
	alunos_SR = armazenar[7] - alunos_SR;

	if (percentual_total < 30) {
		percentual[0] = 1;
	}

	if (percentual_total >= 30 && percentual_total < 50) {
		percentual[1] = 1;
	}
	if (percentual_total >= 50) {
		percentual[2] = 1;
	}

	armazenar[8] = armazenar[8] - percentual[0];
	armazenar[9] = armazenar[9] - percentual[1];
	armazenar[10] = armazenar[10] - percentual[2];

	relatorio = fopen(disc_geral, "w");

	fprintf(relatorio,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d",alunos_matriculados,trancamentos,alunos_SS,alunos_MS,alunos_MM,alunos_MI,alunos_II,alunos_SR,armazenar[8],armazenar[9],armazenar[10]);
	fclose(relatorio);
}

void opcao1() { // Par�metro para cadastramento de disciplinas

	fflush(stdin);

	int menor_opcao = 1, maior_opcao = 2;
	int x, y, i;
	char nome_disc[TAM_MAX];
	char codigoArquivo[TAM_MAX];
	char disc_geral[TAM_MAX];
	FILE *ver_arq;  // Ponteiro para abertura do arquivo
	FILE *cadastro; // Ponteiro para abertura do arquivo da disciplina que ser� cadastrada

	system("cls"); // Apagar informa��es anteriores

	printf("\n 1)Cadastrar disciplina \n");
	printf(" 2)Voltar para o menu inicial \n\n");
	printf(" Op��o: ");

	bloquear_teclas(menor_opcao=1,maior_opcao=2); // Chamada de Procedimento que s� aceita n�meros

	switch (opcao_escolhida) { // Fazer caso o n�mero digitado seja v�lido e esteja no intervalo proposto
	case 1:

	refazer: // Volta para esse ponto caso a disciplina tenha o mesmo nome do c�digo

		do {
			system("cls");
			printf("\n Digite o nome da disciplina: ");
			bloqueia_num(disciplinas);
			printf("\n Digite o c�digo da disciplina: "); // Fazer enquanto s�
														  // for digitado apenas
														  // enter, sem outras
														  // informa��es
			fgets(nome_disc, 100, stdin);
		} while (disciplinas[0] == '\0' || nome_disc[0] == '\n');

		fflush(stdin);

		x = strlen(disciplinas); // Verificar o tamanho da string
		y = strlen(nome_disc);   // Verificar o tamanho da string

		if (nome_disc[y - 1] == '\n') {
			nome_disc[y - 1] = '\0';
		}

		for (i = 0; i < x; i++) {
			disciplinas[i] = toupper(disciplinas[i]); // Transformar todas as letras em mai�sculas
		}

		y = strlen(nome_disc);

		for (i = 0; i < y; i++) {
			nome_disc[i] = toupper(nome_disc[i]); // Transformar todas as letras em mai�sculas
		}

		if (strcmp(disciplinas, nome_disc) ==0) { // Condi��o para saber se o c�digo tem o mesmo nome da disciplina (evitar conflito)

			printf("\n ERRO! A DISCIPLINA N�O PODE TER O MESMO NOME DO C�DIGO.\n");
			printf(" Por favor, digite corretamente os dados...\n\n");

			system("pause");
			system("cls");
			fflush(stdin);

			goto refazer; // Retorna para um ponto espec�fico, no caso, pedir�
						  // as informa��es da disciplina novamente
		}

		disc_e_codigos(nome_disc);

		snprintf(nomeArquivo,100,"disciplina_%s.txt",disciplinas); // Fun��o que concatena as informa��es com a string
		cadastro = fopen(nomeArquivo, "r");
		fclose(cadastro);

		snprintf(codigoArquivo,100,"disciplina_%s.txt",nome_disc); // Fun��o que concatena as informa��es com a string
		ver_arq = fopen(codigoArquivo, "r");
		fclose(ver_arq);

		if (cadastro == NULL && ver_arq == NULL) { // Verifica se a disciplina j� existe

			x = strlen(disciplinas);
			for (i = 0; i < x; i++) {
				disciplinas[i] = toupper(disciplinas[i]); // Transformar todasas letras em mai�sculas
			}

			printf("\n Voc� realmente deseja cadastrar \"%s\" como uma disciplina?\a\a\a",disciplinas);
			printf("\n\n 1)Sim\n");
			printf(" 2)N�o\n\n");
			printf(" Op��o:");

			bloquear_teclas(menor_opcao=1,maior_opcao=2); // Chamada de Procedimento que s� aceita n�meros

			if (opcao_escolhida == 1) {
				cadastro = fopen(nomeArquivo, "a");
				fclose(cadastro);

				snprintf(disc_geral, 100, "geral_%s", nomeArquivo); // Fun��o que concatena as informa��es com a string que servir�
                                                                    // para o arquivo geral
				ver_arq = fopen(codigoArquivo, "r");                // das disciplinas

				relatorio = fopen(disc_geral, "r");
				fclose(relatorio);

				if (relatorio == NULL) {
					relatorio = fopen(disc_geral, "w");
					fprintf(relatorio, "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\n0");
					fclose(relatorio);
				}

				for (i = 0; i < x;i++) { // para printar as disciplinas dentro do todas_disc
                                        // como mai�sculas para com o intuito de n�o deixar
                                        // criar disciplinas com o mesmo nome

					disciplinas[i] = toupper(disciplinas[i]); // Transformar todas as letras em mai�sculas
				}

				todas_disc = fopen("todas_disc.txt", "a");
				fprintf(todas_disc,"\n%s-%s",disciplinas,nome_disc); // Abre o arquivo e printa o nome e o codigo da disciplina no arquivo
				fclose(todas_disc);                                  // com o nome de todas as disciplinas

				printf("\n\n Disciplina cadastrada com sucesso!!!\n\n");
				system("pause");
				system("cls");
				menu_principal(); // Procedimento para retornar ao menu principal
			}

			if (opcao_escolhida == 2) {
				system("cls");
				menu_principal(); // Procedimento para retornar ao menu principal
			}
		}

		else { // Se a disciplina j� existir, a mensagem abaixo ser� apresentada

			printf("\n A disciplina e/ou c�digo j� existe(m)!!!\n\n");

			system("pause");

			printf("\n 1)Encerrar o cadastramento\n");
			printf(" 2)Voltar para o menu de cadastramento de disciplinas\n");
			printf(" 3)Cadastrar turma\n\n");
			printf(" Op��o: ");

			bloquear_teclas(menor_opcao = 1, maior_opcao = 3); // Chamada de Procedimento que s� aceita n�meros

			switch (opcao_escolhida) {
			case 1:

				opcao7();

				break;
			case 2:

				opcao1();

				break;
			case 3:

				opcao2();

				break;
			}

			if (opcao_escolhida == 2) {
				system("cls");
				opcao1();
			}

			break;

		case 2:
			system("cls");
			menu_principal();
			break;
		}
	}
}

void opcao2() { // Procedimento para o cadastramento de turmas

	system("cls");
	int menor_opcao = 1, maior_opcao = 2;
	int i, p = 0, x = 0, z = 0;
	int perc1 = 0, perc2 = 0, perc3 = 0;
	float info_arq[12], perctotal;
	int alunos_SS_2 = 0, alunos_MS_2 = 0, alunos_MM_2 = 0, alunos_matriculados_2;
	int ano = 0, semestre, decremento = 0;
	char codigo[20], codigo2[20], nome_disciplina[TAM_MAX], nome_disc[TAM_MAX];
	char Turma[20];

	struct mencao { // Struct para informa��es de turma
		int alunos_matriculados;
		int trancamentos;
		int alunos_SS;
		int alunos_MS;
		int alunos_MM;
		int alunos_MI;
		int alunos_II;
		int alunos_SR;
	};

	struct mencao aluno;

	FILE *cod;  // Ponteiro para
	FILE *cod2; // Ponteiro para
	FILE *cod3; // Ponteiro para

	printf(" \n Para qual disciplina deseja fazer o cadastro da turma?\n\n");
	printf(" Nome ou c�digo da disciplina:");
	setbuf(stdin, NULL); // pesquisar sobre isso
	do {
		fgets(nome_disc, 100, stdin);
	} while (nome_disc[0] == '\n');
	x = strlen(nome_disc);

	if (nome_disc[x - 1] == '\n') {
		nome_disc[x - 1] = '\0';
	}

	for (i = 0; i < x; i++) {
		nome_disc[i] = toupper(nome_disc[i]); // Transformar todas as letras em mai�sculas
	}

	disc_procurar(nome_disc); // PESQUISAR NOME OU PARTE DELE E VER SE J� EXISTE
							  // ESSA DISCIPLINA CADASTRADA

	snprintf(nome_disciplina, 50, "disciplina_%s.txt", nome_disc);

	cod = fopen(nome_disciplina, "r");
	fclose(cod);
	if (cod == NULL) { // Se a disciplina n�o existir, a mensagem abaixo ser�
					   // apresentada
		printf("\n Disciplina n�o encontrada!\n\n");
		system("pause");
		system("cls");
		printf(" 1)Encerrar o cadastramento\n");
		printf(" 2)Voltar para o menu de cadastramento de turmas\n");
		printf(" 3)Cadastrar disciplinas\n\n");
		printf(" Op��o: ");

		bloquear_teclas(menor_opcao = 1, maior_opcao = 3); // Chamada de Procedimento que s� aceita n�meros

		switch (opcao_escolhida) {
		case 1:

			opcao7();

			break;
		case 2:

			opcao2();

			break;
		case 3:

			opcao1();

			break;
		}
	}

	printf("\n Nome da disciplina: %s\n", nome_disc);

	printf("\n 1)Inserir informa��es da turma\n");
	printf(" 2)Voltar para o menu inicial\n");
	printf(" Op��o: ");

	bloquear_teclas(menor_opcao, maior_opcao); // Chamada de Procedimento que s� aceita n�meros

	switch (opcao_escolhida) {
	case 1:

		system("cls");

		printf(" Informe o ano: ");

		bloquear_teclas(
        menor_opcao = 1, maior_opcao =2020); // Chamada de Procedimento que s� aceita n�meros
		ano = opcao_escolhida;

		printf("\n Informe o semestre: ");

		bloquear_teclas(menor_opcao = 1, maior_opcao = 2); // Chamada de Procedimento que s� aceita n�meros
		semestre = opcao_escolhida;
		printf("�");

		do {
			printf("\n Informe o c�digo da turma: ");
			fgets(codigo2, 20, stdin);
		} while (codigo2[0] == '\n');

		x = strlen(codigo2);
		if (codigo2[x - 1] == '\n') {
			codigo2[x - 1] = '\0';
		}
		snprintf(codigo, 20, "COD%s#%d%d", codigo2, ano, semestre);
		cod_turma(codigo, Turma, nome_disciplina);

		if (strcmp(codigo, Turma) == 0) {
			p++;

			do {
				do {
					system("cls");
					printf(" C�digo de turma j� existente! Por favor, informe um c�digo v�lido!\n\n");
					printf(" Informe o c�digo da turma: ");
					fgets(codigo2, 20, stdin);
				} while (codigo2[0] == '\n');

				x = strlen(codigo2);
				if (codigo2[x - 1] == '\n') {
					codigo2[x - 1] = '\0';
				}
				snprintf(codigo, 20, "COD%s#%d%d", codigo2, ano, semestre);
				cod_turma(codigo, Turma, nome_disciplina);

			} while ((strcmp(codigo, Turma) == 0));
		}

		printf("\n Informe a quantidade de alunos matriculados: ");

		bloquear_teclas(menor_opcao = 1,maior_opcao =1000); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_matriculados = opcao_escolhida;
		decremento = decremento + aluno.alunos_matriculados;

		printf("\n Informe os trancamentos: ");
		bloquear_teclas(menor_opcao = 0,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.trancamentos = opcao_escolhida;
		decremento = aluno.alunos_matriculados - aluno.trancamentos;

		printf("\n Informe os alunos com mens�o SS: ");
		bloquear_teclas(menor_opcao = 0,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_SS = opcao_escolhida;
		decremento = decremento - aluno.alunos_SS;

		printf("\n Informe os alunos com mens�o MS: ");
		bloquear_teclas(menor_opcao = 0,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_MS = opcao_escolhida;
		decremento = decremento - aluno.alunos_MS;

		printf("\n Informe os alunos com mens�o MM: ");
		bloquear_teclas(menor_opcao = 0,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_MM = opcao_escolhida;
		decremento = decremento - aluno.alunos_MM;

		printf("\n Informe os alunos com mens�o MI: ");
		bloquear_teclas(menor_opcao = 0,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_MI = opcao_escolhida;
		decremento = decremento - aluno.alunos_MI;

		printf("\n Informe os alunos com mens�o II: ");
		bloquear_teclas(menor_opcao = 0,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_II = opcao_escolhida;
		decremento = decremento - aluno.alunos_II;

		printf("\n Informe os alunos com mens�o SR: ");
		bloquear_teclas(menor_opcao = decremento,maior_opcao =decremento); // Chamada de Procedimento que s� aceita n�meros
		aluno.alunos_SR = opcao_escolhida;
		decremento = decremento - aluno.alunos_SR;

		z = strlen(codigo);
		for (i = 0; i < z; i++) {
			codigo[i] =toupper(codigo[i]); // Transformar todas as letras em mai�sculas
		}

		cod = fopen(nome_disciplina, "a");
		fprintf(cod,"\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d",codigo,aluno.alunos_matriculados,aluno.trancamentos,aluno.alunos_SS,aluno.alunos_MS,aluno.alunos_MM,aluno.alunos_MI,aluno.alunos_II,aluno.alunos_SR);
		fclose(cod);

		atualizar_disc(nome_disciplina,aluno.alunos_SS,aluno.alunos_MS,aluno.alunos_MM,aluno.alunos_MI,aluno.alunos_II,aluno.alunos_SR,aluno.alunos_matriculados,aluno.trancamentos,nome_disc);

		cod3 = fopen("geral.txt", "r");
		for (i = 0; i < 11; i++) {
			fscanf(cod3, "%f", &info_arq[i]);
		}

		fclose(cod3);

		alunos_SS_2 = aluno.alunos_SS;
		alunos_MS_2 = aluno.alunos_MS;
		alunos_MM_2 = aluno.alunos_MM;
		alunos_matriculados_2 = aluno.alunos_matriculados;
		perctotal = ((alunos_SS_2 + alunos_MS_2 + alunos_MM_2) * 100) /alunos_matriculados_2; // PARA SABER O PERCENTUAL DE APROVA��O DA TURMA

		if (perctotal >= 0 && perctotal < 30) {
			perc1 = 1;
		}
		if (perctotal >= 30 && perctotal < 50) {
			perc2 = 1;
		}

		if (perctotal >= 50) {
			perc3 = 1;
		}

		aluno.alunos_matriculados += info_arq[0];
		aluno.trancamentos += info_arq[1];
		aluno.alunos_SS += info_arq[2];
		aluno.alunos_MS += info_arq[3];
		aluno.alunos_MM += info_arq[4];
		aluno.alunos_MI += info_arq[5];
		aluno.alunos_II += info_arq[6];
		aluno.alunos_SR += info_arq[7];
		perc1 = info_arq[8] + perc1;
		perc2 = info_arq[9] + perc2;
		perc3 = info_arq[10] + perc3;

		cod3 = fopen("geral.txt", "w");

		fprintf(cod3, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",aluno.alunos_matriculados,aluno.trancamentos,aluno.alunos_SS,aluno.alunos_MS,aluno.alunos_MM,aluno.alunos_MI,aluno.alunos_II,aluno.alunos_SR,perc1,perc2,perc3);
			fclose(cod3);

		printf("\n\n Alunos matriculados com sucesso!\n\n");
		system("pause \n\n");

		system("cls");

		menu_principal();

		break;
	case 2:

		system("cls");
		menu_principal();
		break;
	}
}

void opcao3() {

	char disc_geral[TAM_MAX];
	char disc_txt[TAM_MAX];
	char nome_disc[TAM_MAX];
	int menor_opcao = 1, maior_opcao = 2;
	int x;

	FILE *deletar_disc;		 // Ponteiro para abertura do arquivo para deletar disciplina
	FILE *deletar_relatorio; // Ponteiro para abertura do arquivo para deletar relat�rio deral da disciplina que ser� excluida

	fflush(stdin);

	do {
		system("cls");
		printf(" Informe o nome ou c�digo da disciplina que deseja excluir: ");
		fgets(nome_disc, 100, stdin);

	} while (nome_disc[0] == '\n');

	x = strlen(nome_disc);
	if (nome_disc[x - 1] == '\n') {
		nome_disc[x - 1] = '\0';
	}

	disc_procurar(nome_disc); // VERIFICAR SE A DISCIPLINA J� EXISTE DENTRO DO ARQUIVO COM TODAS AS DISCIPLINAS

	snprintf(disc_txt, 100, "disciplina_%s.txt", nome_disc);
	snprintf(disc_geral, 100, "geral_%s", disc_txt);

	deletar_disc = fopen(disc_txt, "r");
	fclose(deletar_disc);
	deletar_relatorio = fopen(disc_geral, "r");
	fclose(deletar_relatorio);

	if (deletar_disc == NULL) {
		printf("\n Disciplina n�o encontrada!");
		printf("\n Por favor, verifique se os dados foram digitados corretamente.\n");

		fflush(stdin);
		Sleep(3000);
		system("cls");
		menu_principal();
	}

	else {
		printf("\n\a\a\a Tem certeza que deseja apagar \"%s\" das disciplinas cadastradas?\n\n",nome_disc);
		printf(" 1) Excluir disciplina\n");
		printf(" 2) Voltar para o menu inicial\n\n");

		printf(" Op��o: ");

		bloquear_teclas(menor_opcao, maior_opcao); // Chamada de Procedimento que s� aceita n�meros

		switch (opcao_escolhida) {
		case 1:

			decrementar_arq_geral(disc_geral); // DECREMENTAR VALORES DO ARQUIVO GERAL AP�S EXCLUS�O DE DISCIPLINA

			apagar_disc(); // APAGAR NOME E CODIGO DA DISCIPLINA

			remove(disc_txt);
			remove(disc_geral);

			printf("\n Disciplina apagada com sucesso!!\n\n");
			system("pause");

			menu_principal();

			break;

		case 2:

			system("cls");

			menu_principal();

			break;
		}
	}
}

void opcao4() {
	char nome_disc[TAM_MAX];
	int ano, semestre;
	char nome_disciplina[TAM_MAX];
	char apagar[20];
	int info_arq[15];
	char procurar[20];
	char turma[20], codigo_turma[20];
	int menor_opcao = 0, maior_opcao = 0;
	int x = 0, i = 0, j = 0, k = 2, l = 0, m = 0;

	FILE *apagar_turma; // Ponteiro para abertura do arquivo de disciplina para apagar turma
	FILE *Temporario;   // Ponteiro para abertura do arquivo tempor�rio
	system("cls");

	do {
		system("cls");
		printf(" Informe o nome ou c�digo da disciplina na qual a turma est� cadastrada: ");
		fgets(nome_disc, 100, stdin);

	} while (nome_disc[0] == '\n'); // Far� enquanto for digitado apenas enter

	x = strlen(nome_disc);

	if (nome_disc[x - 1] == '\n') {
		nome_disc[x - 1] = '\0';
	}

	disc_procurar(nome_disc);

	snprintf(nome_disciplina, 100, "disciplina_%s.txt", nome_disc); // snprintf(disc_geral, 100, "geral_%s", nome_disciplina);

	apagar_turma = fopen(nome_disciplina, "r");
	fclose(apagar_turma);

	if (apagar_turma == NULL) {                         // Se a disciplina n�o existir, a mensagem abaixo ser� apresentada
		printf("\n Disciplina n�o encontrada!\n\n");
		system("pause");
		system("cls");
		printf(" 1)Encerrar o cadastramento\n");
		printf(" 2)Pesquisar disciplina novamente\n");
		printf(" 3)Cadastrar disciplinas\n\n");
		printf(" Op��o: ");

		bloquear_teclas(menor_opcao = 1, maior_opcao = 3); // Chamada de Procedimento que s� aceita n�meros

		switch (opcao_escolhida) {
		case 1:

			opcao7();

			break;
		case 2:

			opcao4();

			break;
		case 3:

			opcao1();

			break;
		}
	}

	do {
		system("cls");
        printf(" Informe a turma que quer apagar da disciplina %s:", nome_disc);
		fgets(codigo_turma, 20, stdin);

	} while (codigo_turma[0] == '\n');

	x = strlen(codigo_turma);

	if (codigo_turma[x - 1] == '\n') {
		codigo_turma[x - 1] = '\0';
	}

	printf(" Informe o ano ao qual a turma est� cadastrada: ");

	bloquear_teclas(menor_opcao = 0, maior_opcao = 2020); // Chamada de Procedimento que s� aceita n�meros
	ano = opcao_escolhida;

	printf("\n Informe o semestre da disciplina: ");

	bloquear_teclas(menor_opcao = 1, maior_opcao = 2); // Chamada de Procedimento que s� aceita n�meros
	semestre = opcao_escolhida;

	snprintf(turma, 20, "COD%s#%d%d", codigo_turma, ano, semestre); // Concatena��o para encontrar a turma

	deletar_turma(turma, nome_disciplina, codigo_turma);
	apagar_turma = fopen(nome_disciplina, "r");

	printf("\n\a\a\a Tem certeza que deseja apagar \"%s\" das turmas cadastradas?\n\n", codigo_turma);
	printf(" 1) Sim\n");
	printf(" 2) N�o - Voltar para o menu inicial\n\n");
	printf(" Op��o: ");

	bloquear_teclas(menor_opcao = 1, maior_opcao = 2); // Chamada de Procedimento que s� aceita n�meros

	switch (opcao_escolhida) {
	case 1:

		Temporario = fopen("arq_temporario.txt", "w"); // Arquivo tempor�rio para armazenar todas as turmas, menos a que ser� apagada
		do {
			i++; // Incrementa��o que servir� para encontrar o c�digo
			k++;

			fgets(procurar, 20, apagar_turma); // Pega todas as informa��es da turma

			x = strlen(procurar);
			if (procurar[x - 1] == '\n') {
				procurar[x - 1] = '\0';
			}

			if (strcmp(procurar, turma) != 0 && k > i) { // Enquanto ele n�o encontrar a turma, ele ir� printar as informa��es dentro do arquivo tempor�rio
				fprintf(Temporario, "%s\n", procurar);
			}

			if (strcmp(procurar, turma) == 0) { // Se ele encontrar a turma, ele ir� pular as informa��es da turma que ser� apagada
				m++;
				k = k - 10; // Decrementa o contador para pular as informa��es da turma que ser� apagada
			}

			if (m > 0) {
				m++;
				if (m > 2) {
					if (j < 8) {
						info_arq[j] = atoi(procurar); // "info_arq" servir� para decrementar os dados da turma apagada
                                                    // no arquivo geral e no arquivo geral da disciplina

						j++; // Incrementa para salvar em uma nova posi��o do vetor "info_arq"
					}
				}

				k++; // Para ir incrementando at� ultrapassar "i". Servir� para pular as linhas que n�o se quer.
			}

		} while (!feof(apagar_turma)); // Far� enquanto n�o chegar no final do arquivo
		fclose(apagar_turma);
                                // Fechamento dos ponteiros
		fclose(Temporario);

		decrementar_turma_disc(nome_disciplina,info_arq[2],info_arq[3],info_arq[4],info_arq[5],info_arq[6],info_arq[7],info_arq[0],info_arq[1],nome_disc); // Chamada de fun��o para decrementar a turma apagada do arquivo geral
		decrementar_turma_arq_geral(info_arq); // Chamada de fun��o para decrementar a turma apagada do arquivo geral

		apagar_turma = fopen(nome_disciplina, "w"); // Abre a disciplina com "w" para pegar as turmas do "arq_temporario" que n�o foram apagadas e reprintar
		Temporario = fopen("arq_temporario.txt", "r"); // Pegar� as informa��es das turmas que est�o nesse arquivo e printar� na disciplina

		l = 0; // Indicar� as
		do {
			fgets(apagar, 20, Temporario);

			i = strlen(apagar);
			if (apagar[i - 1] == '\n') {
				apagar[i - 1] = '\0';
			}

			if (!feof(Temporario)) {
				if (l == 0) {
					fprintf(apagar_turma, "%s", apagar);
					l++;
				} else {
					fprintf(apagar_turma, "\n%s", apagar);
				}
			}

		} while (!feof(Temporario));

		fclose(Temporario);
		fclose(apagar_turma);
		remove("arq_temporario.txt");

		system("cls");
		printf("\n                  TURMA APAGADA COM SUCESSO!\n\n");
		system("pause");
		menu_principal();

		break;

	case 2:
		system("cls");
		menu_principal();
		break;
	}
}

void opcao5() {
	int menor_opcao, maior_opcao;
	int x, i;
	float info_arq[8];
	float perc_evasao, perc_SS, perc_MS, perc_MM, perc_alunos_aprovados;
	char Disciplina[TAM_MAX];
	FILE *encontrar_disc; // Ponteiro para abertura do arquivo para encontrar disciplina

	char nome_disc[TAM_MAX];
	setbuf(stdin, NULL);

	system("cls");
	printf("\n\n 1)Gerar relat�rio de disciplina\n");
	printf(" 2)Voltar ao menu inicial\n");
	printf(" Op��o:");
	bloquear_teclas(menor_opcao = 1, maior_opcao = 2); // Chamada de Procedimento que s� aceita n�meros

	switch (opcao_escolhida) {
	case 1:

		printf("\n\n Informe o c�digo ou nome da disciplina que deseja gerar o relat�rio:");

		do {
			fgets(nome_disc, 100, stdin);
		} while (nome_disc[0] == '\n');

		x = strlen(nome_disc);
		if (nome_disc[x - 1] == '\n') {
			nome_disc[x - 1] = '\0';
		}

		for (i = 0; i < x; i++) {
			nome_disc[i] = toupper(nome_disc[i]); // Transformar todas as letras em mai�sculas
		}

		disc_procurar(nome_disc);

		snprintf(Disciplina, 100, "geral_disciplina_%s.txt", nome_disc);

		encontrar_disc = fopen(Disciplina, "r");
		fclose(encontrar_disc);

		if (encontrar_disc == NULL) {
		nenhuma_turma:

			printf("\n Disciplina n�o encontrada ou nenhuma turma cadastrada!\n\n");
			printf(" 1)Encerrar programa\n");
			printf(" 2)Voltar para o menu anterior\n\n");
			printf(" Op��o: ");

			bloquear_teclas(menor_opcao = 1,maior_opcao = 2); // Chamada de Procedimento que s� aceita n�meros

			switch (opcao_escolhida) {
			case 1:

				opcao7();

				break;
			case 2:

				opcao5();

				break;
			}
		}

		encontrar_disc = fopen(Disciplina, "r");
		for (i = 0; i < 8; i++) {
			fscanf(encontrar_disc, "%f", &info_arq[i]);
		}
		fclose(encontrar_disc);
		setbuf(stdin, NULL);

		if (info_arq[0] == 0) {
			goto nenhuma_turma;
		}

		perc_evasao = ((info_arq[1] + info_arq[7]) * 100) / info_arq[0];
		perc_SS = (info_arq[2] * 100) / info_arq[0];
		perc_MS = (info_arq[3] * 100) / info_arq[0];
		perc_MM = (info_arq[4] * 100) / info_arq[0];
		perc_alunos_aprovados += (perc_SS + perc_MS + perc_MM);

		printf("\n               RELAT�RIO DA DISCIPLINA %s\n\n", nome_disc);

		printf("\n Percentual de evas�o (trancamentos + alunos_SR): %.2f%%\n",perc_evasao);
		printf(" Percentual de alunos aprovados: %.2f%%\n", perc_alunos_aprovados);
		printf(" Percentual de alunos aprovados com SS: %.2f%%\n", perc_SS);
		printf(" Percentual de alunos aprovados com MS: %.2f%%\n", perc_MS);
		printf(" Percentual de alunos aprovados com MM: %.2f%%\n\n\n", perc_MM);

		system("pause");
		system("cls");

		menu_principal();

	case 2:
		system("cls");
		menu_principal();

		break;
	}
}

void opcao6() {
	float perc_turmas = 0, perc_SS = 0, perc_MS = 0, perc_MM = 0,perc_alunos_aprovados = 0, perc_evasao = 0;
	float perc_menor_30 = 0, perc_entre_30_50 = 0, perc_maior_50 = 0;
	float info_arq[12];
	char pior1[TAM_MAX];
	char melhor1[TAM_MAX];
	char pior2[TAM_MAX];
	char melhor2[TAM_MAX];
	int i, x = 0;

	FILE *melhor_disc; // Ponteiro para abertura do arquivo com maior �ndice de aprova��o
	FILE *pior_disc;   // Ponteiro para abertura do arquivo com menor �ndice de aprova��o
	FILE *cod3;		   // Ponteiro para abertura do arquivo geral

	cod3 = fopen("geral.txt", "r"); // Abre o arquivo geral

	for (i = 0; i < 11; i++) {
		fscanf(cod3, "%f", &info_arq[i]);
	}

	fclose(cod3);

	if (info_arq[0] == 0) {
		system("cls"); // Caso o arquivo esteja criado, por�m sem dados, a mensagem abaixo
                        // ser� apresentada na tela, com o int�ito de evitar que o programa
                        // imprima LIXO DE  MEM�RIA na tela

		printf("\n\n\n O relat�rio n�o pode ser gerado.\n");
		printf(" Verifique se h� turmas cadastradas.\n\n");

		system("pause");
		system("cls");
		menu_principal();
	}

	setbuf(stdin, NULL);

	perc_turmas = info_arq[8] + info_arq[9] + info_arq[10];
	perc_menor_30 = (info_arq[8] * 100) / perc_turmas;
	perc_entre_30_50 = (info_arq[9] * 100) / perc_turmas;   // C�lculos para ver o percentual de aprova��o das turmas
	perc_maior_50 = (info_arq[10] * 100) / perc_turmas;

	perc_evasao = ((info_arq[1] + info_arq[7]) * 100) / info_arq[0];
	perc_SS = (info_arq[2] * 100) / info_arq[0];
	perc_MS = (info_arq[3] * 100) / info_arq[0];
	perc_MM = (info_arq[4] * 100) / info_arq[0];

	perc_alunos_aprovados += perc_SS + perc_MS + perc_MM;

	system("cls");

	printf("                    RELAT�RIO GERAL\n\n");

	printf("\n Percentual de evas�o (trancamentos + alunos_SR): %.2f%%\n",perc_evasao);
	printf(" Percentual de alunos aprovados: %.2f%%\n", perc_alunos_aprovados);
	printf(" Percentual de alunos aprovados com SS: %.2f%%\n", perc_SS);
	printf(" Percentual de alunos aprovados com MS: %.2f%%\n", perc_MS);                        //RELAT�RIO GERAL
	printf(" Percentual de alunos aprovados com MM: %.2f%%\n", perc_MM);
	printf(" Percentual de turmas com aprova��o entre 0%% e 30%%: %.2f%%\n",perc_menor_30);
	printf(" Percentual de turmas com aprova��o entre 30%% e 50%%: %.2f%%\n",perc_entre_30_50);
	printf(" Percentual de turmas com aprova��o maior ou igual � 50%%: %.2f%%\n\n",perc_maior_50);

	pior_melhor();

	pior_disc = fopen("pior_disc.txt", "r");

	i = 0;

	do {
		if (i == 0) {
			fgets(pior2, 100, pior_disc);
			x = strlen(pior2);
			if (pior2[x - 1] == '\n') { // Tira "\n" da string e coloca "\0"
				pior2[x - 1] = '\0';
			}
		}

		if (i == 1) {
			fgets(pior1, 100, pior_disc);
			x = strlen(pior1);
			if (pior1[x - 1] == '\n') { // Tira "\n" da string e coloca "\0"
				pior1[x - 1] = '\0';
			}
		}

		i++;

	} while (!feof(pior_disc));
	fclose(pior_disc);

	i = 0;

	melhor_disc = fopen("melhor_disc.txt", "r");

	do {
		if (i == 0) {
			fgets(melhor2, 100, melhor_disc);

			x = strlen(melhor2);
			if (melhor2[x - 1] == '\n') { // Tira "\n" da string e coloca "\0"
				melhor2[x - 1] = '\0';
			}
		}

		if (i == 1) {
			fgets(melhor1, 100, melhor_disc);

			x = strlen(melhor1);
			if (melhor1[x - 1] == '\n') { // Tira "\n" da string e coloca "\0"
				melhor1[x - 1] = '\0';
			}
		}

		i++;

	} while (!feof(melhor_disc));

	fclose(melhor_disc);

	printf(" MELHOR DISCIPLINA: ");

	if (melhor1[0] == '0' && melhor2[0] == '0') { // Caso seja 0 nas duas strings, indica que n�o existe turmas cadastradas

		printf(" NENHUMA DISCIPLINA CADASTRADA!\n\n"); // Printa essa mensagem caso n�o tenha turma cadastrada
	} else {
		printf(" %s - %s%%\n\n", melhor1, melhor2); // Printa a melhor disciplina e porcentagem, respectivamente
	}

	printf(" PIOR DISCIPLINA: ");

	if (pior1[0] == '0' && pior2[0] == '1') { // Caso seja 0 e 1 nas strings, indica que n�o existe turmas cadastradas

		printf(" NENHUMA DISCIPLINA CADASTRADA!\n"); // Printa essa mensagem caso n�o tenha turma cadastrada
	} else {
		printf(" %s - %s%%\n\n", pior1, pior2); // Printa a pior disciplina e porcentagem, respectivamente
	}

	system("pause");

	melhor_disc = fopen("melhor_disc.txt", "w"); // Zera as informa��es para gerar os relat�rios de pior e melhor disciplina novamente
	fprintf(melhor_disc, "0\n0");
	fclose(melhor_disc);

	pior_disc = fopen("pior_disc.txt", "w"); // Zera as informa��es para gerar os relat�rios de pior e melhor disciplina novamente
	fprintf(pior_disc, "101\n0");
	fclose(pior_disc);

	menu_principal();
}

void opcao7() {
	int menor_opcao, maior_opcao;

	system("cls");
	printf("\a\a\a\n Voc� realmente deseja SAIR do programa?\n\n");
	printf(" 1)Sim\n");
	printf(" 2)N�o - Voltar para o menu inicial\n\n");
	printf(" Op��o: ");

	bloquear_teclas(menor_opcao=1, maior_opcao=2); // Chamada de Procedimento que s� aceita n�meros

	switch (opcao_escolhida) {
	case 1:

		system("cls");
		printf("\n Obrigado por utilizar nossos servi�os! Tenha um �timo dia!\n\n");
		system("type aqui.txt ");
		exit(0);
		break;
	case 2:

		system("cls");
		menu_principal();
		break;
	}
}

void opcao8() {
	system("cls");
	printf("\n");
	printf("                    DISCIPLINAS J� CADASTRADAS\n");
	printf("                        DISCIPLINA - C�DIGO\n");
	system("type todas_disc.txt");
	printf("\n\n");
	system("pause");
	menu_principal();
}

void menu_principal() { // Menu principal

	int menor_opcao, maior_opcao;
	system("cls");
	system("type aqui2.txt");

	printf(" Digite a op��o desejada\n\n");

	printf(" Menu de op��es:\n\n");
	printf(" 1)Cadastrar uma disciplina\n");
	printf(" 2)Cadastrar uma turma\n");
	printf(" 3)Excluir disciplina\n");
	printf(" 4)Excluir turma\n");
	printf(" 5)Gerar relat�rio por disciplina\n");
	printf(" 6)Gerar relat�rio geral\n");
	printf(" 7)Sair do programa\n");
	printf(" 8)Disciplinas j� cadastradas\n\n");

	printf(" Op��o:");
	bloquear_teclas(menor_opcao=1, maior_opcao=8); // Chamada de Procedimento que s� aceita n�meros

	switch (opcao_escolhida) {
	case 1:
		opcao1(); // Chamada de Par�metro para cadastrar disciplina
		break;

	case 2:
		opcao2(); // Chamada de Par�metro para cadastrar uma turma
		break;

	case 3:
		opcao3(); // Chamada de Par�metro para excluir disciplina
		break;

	case 4:
		opcao4(); // Chamada de Par�metro para excluir turma
		break;

	case 5:
		opcao5(); // Chamada de Par�metro para gerar relat�rio por disciplina
		break;

	case 6:
		opcao6(); // Chamada de Par�metro para gerar relat�rio geral
		break;

	case 7:
		opcao7(); // Chamada de Par�metro para sair do programa
		break;

	case 8:
		opcao8(); // Chamada de Par�metro para apresentar todas as disciplinas cadastradas
	}
}

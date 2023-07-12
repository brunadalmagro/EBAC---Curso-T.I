#include <stdio.h> // biblioteca de comunica��o do usu�rio
#include <stdlib.h> // biblioteca para aloca��o de mem�ria
#include <locale.h> // biblioteca para aloca��o de texto por regi�o
#include <string.h> // biblioteca respons�vel por manipular strings
#include <ctype.h> // biblioteca respos�vel pela valida��o de caracteres de entrada

void registro()
{
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    printf("Digite o CPF a ser cadastrado (somente n�meros): ");
    scanf("%s", cpf);

    // Valida��o do CPF
    for (int i = 0; cpf[i] != '\0'; i++)
    {
        if (!isdigit(cpf[i]))
        {
            printf("CPF inv�lido. Digite apenas n�meros.\n");
            getchar();
            return;
        }
    }

    strcpy(arquivo, "BD.txt");

    FILE *file;
    file = fopen(arquivo, "a");
    fprintf(file, "%s", cpf);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o nome que deseja cadastrar: ");
    scanf("%s", nome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", nome);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o sobrenome que deseja cadastrar: ");
    scanf("%s", sobrenome);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", sobrenome);
    fclose(file);

    file = fopen(arquivo, "a");
    fprintf(file, ",");
    fclose(file);

    printf("Digite o cargo desejado: ");
    scanf("%s", cargo);

    file = fopen(arquivo, "a");
    fprintf(file, "%s", cargo);
    fprintf(file, "\n");
    fclose(file);

    printf("Pressione Enter para sair.");
    getchar();
}


void consulta()
{
    setlocale(LC_ALL, "Portuguese"); // Definindo idioma

    char cpf[40]; // CPF a ser consultado
    int encontrado = 0; // Vari�vel para indicar se o usu�rio foi encontrado

    printf("Digite o CPF ou nome completo para verificar: ");
    scanf("%s", cpf);

    FILE *file;
    file = fopen("BD.txt", "r");

    if (file == NULL) // verifica se o arquivo existe
    {
        printf("O arquivo n�o foi encontrado.\n");
        return;
    }

    char linha[150];
    while (fgets(linha, 150, file) != NULL)
    {
        if (strstr(linha, cpf) != NULL)
        {
            printf("\nEssas s�o as informa��es do usu�rio: %s\n\n", linha);
            encontrado = 1;
            break;
        }
    }

    fclose(file);

    if (!encontrado)
    {
        printf("Usu�rio n�o cadastrado.\n");
    }

    printf("Pressione Enter para sair.");
    getchar();
}

void deleta()
{
    char arquivo[40];
    char cpf[40];
    int encontrado = 0; // vari�vel para indicar se o registro foi encontrado

    printf("Digite o CPF do registro a ser exclu�do: ");
    scanf("%s", cpf);

    strcpy(arquivo, "BD.txt");

    FILE *file, *temp;
    file = fopen(arquivo, "r");
    temp = fopen("temp.txt", "w");

    if (file == NULL)
    {
        printf("O arquivo n�o foi encontrado.\n");
        return;
    }

    char linha[150];
    while (fgets(linha, 150, file) != NULL)
    {
        if (strstr(linha, cpf) == NULL)
        {
            fputs(linha, temp);
        }
        else
        {
            encontrado = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (encontrado == 1)
    {
        remove(arquivo); // remove o arquivo original
        rename("temp.txt", arquivo); // renomeia o arquivo tempor�rio para o nome original
        printf("O registro foi exclu�do com sucesso.\n");
    }
    else
    {
        remove("temp.txt"); // remove o arquivo tempor�rio
        printf("A exclus�o foi cancelada pelo usu�rio.\n");
    }

    printf("Pressione Enter para sair.");
    getchar();
}

void sair()
{
    printf("Voc� escolheu Sair do sistema. \n");
    exit(0);
}

int main()
{
    int opcao = 0; // Definindo vari�veis
    int laco = 1;

    for (laco = 1; laco == 1;)
    {
        system("cls");

        setlocale(LC_ALL, "Portuguese"); // Definindo idioma

        printf("### Cart�rio da EBAC ###\n\n"); // In�cio do menu
        printf("Escolha a op��o desejada do menu:\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t4 - Sair do sistema\n");
        printf("Op��o: "); // Fim do menu

        scanf("%d", &opcao); // Armazenamento da escolha do usu�rio

        system("cls");

        switch (opcao)
        {
        case 1:
            printf("Voc� escolheu registrar um nome!\n");
            registro();
            getchar();
            break;

        case 2:
            printf("Voc� escolheu consultar nomes!\n");
            consulta();
            getchar();
            break;

        case 3:
            printf("Voc� escolheu deletar nomes!\n");
            deleta();
            getchar();
            break;

        case 4:
            printf("Obrigad@, volte sempre!\n");
            sair();
            break;

        default:
            printf("Essa op��o n�o est� dispon�vel.\n");
            getchar();
            break;
        } // Fim da sele��o
    }

    printf("Pressione Enter para sair.");
    getchar();
    return 0;

}

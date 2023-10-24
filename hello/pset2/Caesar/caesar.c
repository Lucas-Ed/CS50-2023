/**
* Caesar50.c
* Este programa criptografa textos usando a cifra de César.
* deslocando as letras k vezes de acordo com o que o usuário insere.
* os argumentos da linha de comando devem ter apenas 2 argumentos, caso contrário não funcionará
 * */




#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Verifica se há exatamente 2 argumentos (nome do programa e chave).
    if (argc != 2)
    {
        printf("Uso: ./Caesar50 chave\n");
        return 1;
    }

    // Verifica se o argumento da linha de comando é numérico
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Por favor, insira um número válido como chave\n");
            return 1;
        }
    }

    // Converta o segundo argumento (a chave) em um inteiro.
    int k = atoi(argv[1]);

    // Verifica se a chave é um número não negativo.
    if (k < 0)
    {
        printf("Por favor, insira um número válido como chave\n");
        return 1;
    }

    // Solicita ao usuário que insira o texto a ser criptografado.
    string text = get_string("Por favor, digite seu texto: ");

    printf("Ciphertext: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Verifica se o caractere é uma letra.
        if (isalpha(text[i]))
        {
            // Verifica se a letra está maiúscula.
            if (isupper(text[i]))
            {
                // Converte a letra em número e cifra-a.
                char cipher_num_capital = ((text[i] - 'A' + k) % 26) + 'A';

                // Imprime a letra do número como um caractere.
                printf("%c", cipher_num_capital);
            }

            // Verifica se a letra está minúscula.
            if (islower(text[i]))
            {
                // Converte a letra em número e cifra-a.
                char cipher_num_small = ((text[i] - 'a' + k) % 26) + 'a';

                // Imprime a letra do número como um caractere.
                printf("%c", cipher_num_small);
            }
        }
        else
        {
            // Caso o caractere não seja uma letra, imprima-o como está.
            printf("%c", text[i]);
        }
    }

    printf("\n");
    return 0;
}

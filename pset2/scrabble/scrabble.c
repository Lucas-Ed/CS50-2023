#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Pontos atribuídos a cada letra do alfabeto
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Obtém palavras de entrada de ambos os jogadores
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Pontue ambas as palavras
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Mostre o vencedor
    //if score 1 > score 2 - player 1 wins
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    //se pontuação 2 > pontuação 1 = jogador 2 vence
    else if (score2 > score1)
    {
        printf("Player 2 wins!!\n");
    }
    else
    {
        //se a mesma pontuação para ambos os jogadores, então imprime o empate
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Calcula e retorna pontuação para string
    int score = 0;
    //i inicial é 0, conta o comprimento da string usando loop)
    for (int i = 0; i < strlen(word); i++)
    {
        //função isupper verifica se C é a letra maiúscula de 'A' a 'Z'. Verifica se o valor ASCII está entre 65 e 90.
        if (isupper(word[i]))
        {
            //se for maiúsculo, armazena os pontos na pontuação e soma todos os pontos atribuídos a cada caractere respectivo, menos o valor ASCII 65.
            score = score + POINTS[(word[i]) - 65];
        }
        //a função islower verifica se C é uma letra minúscula de 'a' a 'z'. Verifica se o valor ASCII está entre 97 - 122.
        if (islower(word[i]))
        {
            //se for minúsculo, soma todos os pontos atribuídos a cada caractere, menos o valor ASCII 97.
            score = score + POINTS [(word[i]) - 97];
        }
    }
    return score;
}
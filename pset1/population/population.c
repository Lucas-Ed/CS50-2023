#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Solicitar tamanho inicial
    int start_size;
    do
    {
        start_size = get_int("Start size:: ");
    }
    while (start_size < 9);

    // TODO: Solicitar tamanho final
    int end_size;
    do
    {
        end_size = get_int("End size:: ");
    }
    while (end_size < start_size);
    // TODO: Calcular o número de anos até atingirmos o limite
    int year = 0;
    int n = start_size;
    int calculator = 0;

    // if else retorna 0 se o tamanho final e inicial for 0
    if (start_size == end_size)
    {
        printf("Years: 0");
    }

    // executa loops while para calcular a população
    // usa a fórmula da pergunta onde n é a população inicial
     // adiciona o ano em um até n >= tamanho final da população
    do
    {
        n = round(n + (n / 3) - (n / 4));
        year += 1;

    }
    while (n < end_size);
    printf("Years: %i",  year);

}
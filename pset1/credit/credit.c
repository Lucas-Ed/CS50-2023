#include <cs50.h>
#include <stdio.h>

void type_number(int last_digits, int count);

void check_number(long number);

int main(void)
{
    long number = get_long("Number: ");
    check_number(number);
}

void check_number(long number)
{
    // Variável para controlar o dígito de todos os outros
    bool every_other = false;
    // Countador
    int i = 0;
    // Últimos dois dígitos
    int last_digits = 0;
    // O var que armazena a soma de verificação
    int sum_check = 0;
    while (0 < number)
    {
        //  Obtém o último dígito do número
        int digit = number % 10;

        // Se for todo o outro número
        if (every_other == true)
        {
            // Dobra o dígito
            int doubled_digit = digit * 2;
            // Obtém o primeiro dígito
            int first_digit = doubled_digit % 10;
            // Obtém o segundo dígito
            int second_digit = doubled_digit / 10;
            // Somar os dois dígitos ao sum_check
            sum_check += first_digit + second_digit;
        }
        // Se não estiver, basta somar o último dígito coletado
        else
        {
            sum_check += digit;
        }

        // Coleta os dois primeiros dígitos
        if (number < 100 && number > 10)
        {
            last_digits = number;
        }

        // Remove o último dígito do número
        // Então, no próximo loop, o último dígito é o próximo
        number = number / 10;

        // Alterna a condição
        every_other = !every_other;

        i++;
    }

    // Se o sum_check não for divisível por 10 impressões INVÁLIDAS
    if ((sum_check % 10) != 0)
    {
        printf("INVALID\n");
    }
    // Se for continuar verificando
    else
    {
        type_number(last_digits, i);
    }

}


void type_number(int last_digits, int count)
{

    switch (last_digits)
    {
        // American Express começa com 34 ou 37; Duração: 15
       // MasterCard começar com 51, 52, 53, 54 ou 55 comprimento: 16
       // Visa começar com 4 comprimentos: 13 ou 16
        case 34:
        case 37:
            if (count == 15)
            {
                printf("AMEX\n");
            }
            break;

        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            if (count == 16)
            {
                printf("MASTERCARD\n");
            }
            break;

        default:
            // Verifique se o último número é 4 e o comprimento é 13 ou 16
            if ((last_digits / 10 == 4) && ((count == 13) || (count == 16)))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }

    }
}
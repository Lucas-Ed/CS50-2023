def type_number(last_digits, count):
    if last_digits in [34, 37]:
        if count == 15:
            print("AMEX")
    elif last_digits in [51, 52, 53, 54, 55]:
        if count == 16:
            print("MASTERCARD")
    else:
        if (last_digits // 10 == 4) and ((count == 13) or (count == 16)):
            print("VISA")
        else:
            print("INVALID")


def check_number(number):
    # Variável para controlar o dígito de todos os outros
    every_other = False
    # Countador
    i = 0
    # Últimos dois dígitos
    last_digits = 0
    # O var que armazena a soma de verificação
    sum_check = 0
    while number > 0:
        #  Obtém o último dígito do número
        digit = number % 10

        # Se for todo o outro número
        if every_other:
            # Dobra o dígito
            doubled_digit = digit * 2
            # Obtém o primeiro dígito
            first_digit = doubled_digit % 10
            # Obtém o segundo dígito
            second_digit = doubled_digit // 10
            # Somar os dois dígitos ao sum_check
            sum_check += first_digit + second_digit
        else:
            sum_check += digit

        # Coleta os dois primeiros dígitos
        if number < 100 and number > 10:
            last_digits = number

        # Remove o último dígito do número
        # Então, no próximo loop, o último dígito é o próximo
        number = number // 10

        # Alterna a condição
        every_other = not every_other

        i += 1

    # Se o sum_check não for divisível por 10 impressões INVÁLIDAS
    if sum_check % 10 != 0:
        print("INVALID")
    # Se for continuar verificando
    else:
        type_number(last_digits, i)


def main():
    number = input("Número: ")
    number = int(number)
    check_number(number)


if __name__ == "__main__":
    main()

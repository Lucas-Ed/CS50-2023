#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool validity(string key);
string encipher(string input, string index);

int main(int argc, string argv[])
{
    //only takes 2 command-line argument
    if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }

    //Função para testar a validade da chave
    if (!validity(argv[1]))
    {
        return 1;
    }
    //Obtém entrada do usuário
    string input = get_string("Plaintext: ");

    //chave = segundo argumento da linha de comando
    string key = argv[1];

    //printf("Ciphertext: ");
    {
        string output = encipher(input, key);
    }
}

//Checks validity of key(second command-line argument)
bool validity(string key)
{
    //se a chave não for = 26, não prossiga
    if (strlen(key) != 26)
    {
        printf("A chave deve conter 26 caracteres.\n");
        return false;
    }
    //1º loop for para garantir que todas as chaves sejam alfabéticas
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("A chave deve conter apenas caracteres alfabáticos\n");
            return false;
        }
        //2º loop for para verificar duplicações do alfabeto na chave
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[j] == key[i])
            {
                printf("A chave não deve conter caracteres repetidos.\n");
                return false;
            }
        }
    }
    return true;
}

string encipher(string input, string key)
{
    int length = strlen(input);
    int index;
    char ciphertext[length + 1];

    //Loop para priorizar letras maiúsculas/minúsculas do texto simples
    for (int i = 0; i < strlen(input); i++)
    {
        if (isupper(input[i]))
        {
            //printf("%c\n",(key[input[i] - 65]));
            index = ((input[i]) - 65);
            ciphertext[i] = key[index];
            if (islower(ciphertext[i]))
            {
                ciphertext[i] -= 32;
            }
        }
        else if (islower(input[i]))
        {
            //printf("%c", tolower(chave[entrada[i] - 97]));
            index = ((input[i]) - 97);
            ciphertext[i] = key[index];
            if (isupper(ciphertext[i]))
            {
                ciphertext[i] += 32;
            }
        }
        else
        {
            //printf("%c", input[i]);
            ciphertext[i] = input[i];
        }
    }
    //print nul = o texto cifrado chegou ao fim
    ciphertext[length] = '\0';

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}
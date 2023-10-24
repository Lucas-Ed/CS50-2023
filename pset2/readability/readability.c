#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) // int argc, string argv[]
{
    // faz o usuário analisar
    string string = get_string("What is the string to analyze? \n");

        int letterCount = 0, wordCount = 0, sentenceCount = 0;

    // conta letras, palavras e sentenças
    // assume que a..z e A..Z são uma letra
    for (int i = 0, stringLength = strlen(string); i < stringLength + 1; i++)
        {
            if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z'))
            {
                letterCount++;
            }


    // qualquer caractere separado por espaço é uma palavra, verifica o final da string conta a última palavra
    if (string[i] == ' ' || string[i] == '\0')
            {
                wordCount++;

            }
   // quando você vê um . ! ou ? contar como sentença
   if (string[i] == '!' || string[i] == '.'|| string[i] == '?')
        {
            sentenceCount++;
        }

    }

    // calcula o índice de leitura da nota
    float averageWordsPer100 = (100 / (float) wordCount) * (float) letterCount;
    float averageSentencePer100 = (100 / (float) wordCount) * (float) sentenceCount;
    int readingIndex = round(0.0588 * averageWordsPer100 - 0.296 * averageSentencePer100 - 15.8);

    if (readingIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readingIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", readingIndex);
    }

    return 0;
}
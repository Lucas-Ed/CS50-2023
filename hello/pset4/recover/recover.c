#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    //Configura 2 argumentos
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE.\n");
        return 1;
    }
    //Abre o arquivo de entrada (imagem forense)
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 2;
    }
    //arquivo de saída definido como NULL por padrão
    FILE *outptr = NULL;

    //matriz de 512 elementos para armazenar 512 bytes
    BYTE buffer[512];

    //armazena o nome do arquivo
    char filename[8];

    //conta a quantidade de arquivos jpeg encontrados
    int jpeg = 0;

    //lê a memória até o final do arquivo
    while (fread(buffer, sizeof(BYTE) * 512, 1, inptr) == 1)
    {
        //encontrando o arquivo jpeg, se a memória jpeg for atendida
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //fecha outptr se jpeg foi encontrado antes e escrito em ###.jpg
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            //cria um arquivo começando com 001.jpg e ++
            sprintf(filename, "%03i.jpg", jpeg);
            //abre arquivo para escrever o novo jpeg encontrado
                        outptr = fopen(filename, "w");
            jpeg++;
        }
        //continua gravando no arquivo jpeg se o novo jpeg não for encontrado
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outptr);
        }
    }

    fclose(outptr);
    fclose(inptr);



}


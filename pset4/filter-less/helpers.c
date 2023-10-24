#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Dividindo 3, para não ter R + G + B > 255
            int pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            //Fazendo R = G = B = valor x. Para ter ponto de cor cinza
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //itera pelas linhas
    for (int i = 0; i < height; i++)
    {
        //itera pelas colunas
        for (int j = 0; j < width; j++)
        {
            float blue = 0, green = 0, red = 0;
            float counter = 0;

            //itera pelos pixels ao redor do eixo x do pixel atual
            for (int x = -1; x < 2; x++)
            {
                //itera pelos pixels ao redor do eixo y do pixel atual
                for (int y = -1;  y < 2; y ++)
                {
                    //se estiver fora do eixo x
                    if (i + x < 0 || i + x > height - 1)
                    {
                        continue;
                    }
                    //se estiver fora do eixo y
                    if (j + y < 0 || j + y > width - 1)
                    {
                        continue;
                    }
                    //Armazena o valor R , G , B
                    blue += image[i + x][j + y].rgbtBlue;
                    green += image[i + x][j + y].rgbtGreen;
                    red += image[i + x][j + y].rgbtRed;

                    //armazena as contagens de pixels válidas
                    counter++;
                }
            }
            //armazena o valor R , G , B na matriz temporária
            temp[i][j].rgbtBlue = round(blue / counter);
            temp[i][j].rgbtGreen = round(green / counter);
            temp[i][j].rgbtRed = round(red / counter);

            //**Não pode estar dentro do mesmo loop, pois o procedimento abaixo significa editar o pixel atual, o que afetará o próximo cálculo do pixel.**//
            //image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            //image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            //image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    //itera pela matriz e substitui os pixels da imagem do valor temporário
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
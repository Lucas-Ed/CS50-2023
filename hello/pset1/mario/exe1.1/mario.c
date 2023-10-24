#include <stdio.h>

void desenharPiramide(int altura) {
    for (int i = 1; i <= altura; i++) {
        for (int j = 1; j <= altura - i; j++) {
            printf(" ");
        }
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf("  ");  // Largura da "lacuna"
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }
}

int main() {
    int altura = -1;

    while (altura < 1 || altura > 8) {
        printf("Altura: ");
        scanf("%d", &altura);
        if (altura < 1 || altura > 8) {
            printf("Altura fora do intervalo permitido. Tente novamente.\n");
        }
    }

    desenharPiramide(altura);

    return 0;
}
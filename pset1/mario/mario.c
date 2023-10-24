#include <stdio.h>

int main() {
    int altura;

    do {
        printf("Digite a altura da pirâmide (entre 1 e 8): ");
        scanf("%d", &altura);
    } while (altura < 1 || altura > 8);

    for (int i = 1; i <= altura; i++) {
        // Espaços à esquerda
        for (int j = altura - i; j > 0; j--) {
            printf(" ");
        }

        // Tijolos da pirâmide
        for (int k = 0; k < i; k++) {
            printf("#");
        }

        printf("\n");
    }

    return 0;
}

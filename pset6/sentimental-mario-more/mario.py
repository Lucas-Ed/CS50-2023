from cs50 import get_int

# Obtém e valida se a altura de blocos informada pelo usuário é válida
while True:
    height = get_int("Digite a altura entre 1 e 8: ")
    if height < 1 or height > 8:
        height = get_int("Digite a altura entre 1 e 8: ")
    else:
        break

# Imprime os blocos com base na altura
for i in range(height):
    print((height - 1 - i) * " ", end="")
    print((i + 1) * "#", end="")
    # Segunda pirâmide
    print("  ", end="")
    print((i + 1) * "#")
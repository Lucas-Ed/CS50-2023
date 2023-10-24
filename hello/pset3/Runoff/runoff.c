#include <cs50.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

// Máximo de eleitores e candidatos
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferências[i][j] é a j-ésima preferência do eleitor i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidatos têm nome, contagem de votos, status eliminado
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Matriz de candidatos
candidate candidates[MAX_CANDIDATES];

// Número de eleitores e candidatos
int voter_count;
int candidate_count;

// Protótipos de função
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Verifique se há uso inválido
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Preencher matriz de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Continue consultando votos
    for (int i = 0; i < voter_count; i++)
    {

        // Consulta para cada classificação
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Voto registrado, a menos que seja inválido
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Continue realizando o segundo turno até que haja um vencedor
    while (true)
    {
        // Calcular os votos dados aos candidatos restantes
        tabulate();

        // Verifique se a eleição foi vencida
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Elimine os candidatos em último lugar
        int min = find_min();
        bool tie = is_tie(min);

        // Se empatar, todos ganham
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Elimine qualquer pessoa com número mínimo de votos
        eliminate(min);

        // Redefinir contagem de votos para zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Registrar preferência se o voto for válido
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabular votos para candidatos não eliminados
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Imprima o vencedor da eleição, se houver
bool print_winner(void)
{
    // TODO
    int winning_vote = (voter_count / 2);

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winning_vote)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Retorne o número mínimo de votos que qualquer candidato restante possui
int find_min(void)
{
    // TODO
    int min_vote = MAX_VOTERS;

    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes < min_vote) && (!candidates[i].eliminated))
        {
            min_vote = candidates[i].votes;
        }
    }
    return min_vote;
}

// Retorna verdadeiro se a eleição estiver empatada entre todos os candidatos, falso caso contrário
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes != min) && (!candidates[i].eliminated))
        {
            return false;
        }
    }
    return true;
}

// Eliminar o candidato (ou candidatos) em último lugar
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == min) && (!candidates[i].eliminated))
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

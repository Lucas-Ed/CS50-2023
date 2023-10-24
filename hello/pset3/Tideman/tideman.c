#include <cs50.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

// Número máximo de candidatos
#define MAX 9

// preferências[i][j] é o número de eleitores que preferem i a j
int preferences[MAX][MAX];

// bloqueado[i][j] significa que i está bloqueado em j
bool locked[MAX][MAX];

// Cada par tem um vencedor, um perdedor
typedef struct
{
    int winner;
    int loser;
}
pair;

// Matriz de candidatos
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Protótipos de função
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Verifique se há uso inválido
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Preencher matriz de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Gráfico claro de pares bloqueados
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Consulta de votos
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] é a preferência do eleitor
        int ranks[candidate_count];

        // Consulta para cada classificação
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Atualizar classificações com uma nova votação
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Atualizar preferências de acordo com a classificação de um eleitor
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Registre pares de candidatos onde um é preferido ao outro
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair new_pair = {i, j};
                pairs[pair_count] = new_pair;
                pair_count++;
            }
        }
    }
    return;
}

// Classifique os pares em ordem decrescente por força de vitória
void sort_pairs(void)
{
    // TODO
    pair temp;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0 ; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

bool cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Bloqueie pares no gráfico candidato em ordem, sem criar ciclos
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Imprima o vencedor da eleição
void print_winner(void)
{
    // TODO
    int false_count = 0;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
            }
            else
            {
                break;
            }

            if (false_count == pair_count)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }

    return;
}


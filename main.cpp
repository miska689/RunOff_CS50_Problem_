#include <iostream>
#include <stdio.h>
#include <string.h>


// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Verificare pentru utilizare incorectă
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Popularea vectorului de candidați
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

    // Continuă să ceri voturi
    for (int i = 0; i < voter_count; i++)
    {

        // Interogare pentru fiecare rang
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Înregistrează votul, cu excepția cazului în care este invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Continuă să ții runde de votare până când există un câștigător
    while (true)
    {
        // Calculează voturile pentru candidații rămași
        tabulate();

        // Verifică dacă alegerile au fost câștigate
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Elimină candidații de pe ultimele locuri
        int min = find_min();
        bool tie = is_tie(min);

        // Dacă este egalitate, toți câștigă
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

        // Elimină pe oricine cu număr minim de voturi
        eliminate(min);

        // Resetarea numărului de voturi la zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
}

bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}


int find_min(void)
{
    int voteCount = voter_count;
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes < voteCount && candidates[c].eliminated == false)
        {
            voteCount = candidates[c].votes;
        }
    }
    return voteCount;
}


bool is_tie(int min)
{
    int eg = 0;
    int go = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            eg++;
            go++;
        }
        else if (candidates[i].eliminated == false)
        {
            go++;
        }
    }
    if (eg == go)
    {
        return true;
    }
    return false;
}


void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

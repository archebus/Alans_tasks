// Write a function that:
// - Accepts a path to a list of bird names.
// - Has an argument for length of sets (--n)
// - Flag for combination vs permutation output
// - Flag for replacement allowed, or not (--with, --without)
// - Constraint 1 --> No dynamic data structures.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BIRDS 100
#define MAX_NAME_LENGTH 50
#define MAX_N 10

// Helper function for combination with replacement
void generate_combination_with_replacement(char birdNames[][MAX_NAME_LENGTH], int numBirds, int n, int indices[])
{
    printf("Generating combinations with replacement (n=%d):\n", n);

    bool done = false;

    // Initialize first combination
    for (int i = 0; i < n; i++)
    {
        indices[i] = 0;
    }

    while (!done)
    {
        // Print current combination
        for (int i = 0; i < n; i++)
        {
            printf("%s", birdNames[indices[i]]);
            if (i < n - 1)
                printf(",");
        }
        printf("\n");

        // Generate next combination
        int i = n - 1;
        while (i >= 0 && indices[i] == numBirds - 1)
        {
            i--;
        }

        if (i < 0)
        {
            done = true;
        }
        else
        {
            indices[i]++;
            for (int j = i + 1; j < n; j++)
            {
                indices[j] = indices[i];
            }
        }
    }
}

// Helper function for combination without replacement
void generate_combination_without_replacement(char birdNames[][MAX_NAME_LENGTH], int numBirds, int n, int indices[])
{
    printf("Generating combinations without replacement (n=%d):\n", n);

    bool done = false;

    // Initialize first combination
    for (int i = 0; i < n; i++)
    {
        indices[i] = i;
    }

    while (!done)
    {
        // Print current combination
        for (int i = 0; i < n; i++)
        {
            printf("%s", birdNames[indices[i]]);
            if (i < n - 1)
                printf(",");
        }
        printf("\n");

        // Generate next combination
        int i = n - 1;
        while (i >= 0 && indices[i] == numBirds - n + i)
        {
            i--;
        }

        if (i < 0)
        {
            done = true;
        }
        else
        {
            indices[i]++;
            for (int j = i + 1; j < n; j++)
            {
                indices[j] = indices[j - 1] + 1;
            }
        }
    }
}

// Helper function for permutation with replacement
void generate_permutation_with_replacement(char birdNames[][MAX_NAME_LENGTH], int numBirds, int n, int indices[])
{
    printf("Generating permutations with replacement (n=%d):\n", n);

    bool done = false;

    // Initialize first permutation
    for (int i = 0; i < n; i++)
    {
        indices[i] = 0;
    }

    while (!done)
    {
        // Print current permutation
        for (int i = 0; i < n; i++)
        {
            printf("%s", birdNames[indices[i]]);
            if (i < n - 1)
                printf(",");
        }
        printf("\n");

        // Generate next permutation
        int i = n - 1;
        while (i >= 0 && indices[i] == numBirds - 1)
        {
            i--;
        }

        if (i < 0)
        {
            done = true;
        }
        else
        {
            indices[i]++;
            for (int j = i + 1; j < n; j++)
            {
                indices[j] = 0;
            }
        }
    }
}

// Helper function for permutation without replacement
void generate_permutation_without_replacement(char birdNames[][MAX_NAME_LENGTH], int numBirds, int n, int indices[], bool used[])
{
    printf("Generating permutations without replacement (n=%d):\n", n);

    // Initialize first permutation
    for (int i = 0; i < n; i++)
    {
        indices[i] = i;
        used[i] = true;
    }

    bool done = false;

    while (!done)
    {
        // Print current permutation
        for (int i = 0; i < n; i++)
        {
            printf("%s", birdNames[indices[i]]);
            if (i < n - 1)
                printf(",");
        }
        printf("\n");

        // Find the rightmost position that can be increased
        int i = n - 1;

        // Move to the next permutation
        // First, try to increment the last position
        bool found = false;

        // Look for next unused number for the last position
        int pos = indices[i] + 1;
        while (pos < numBirds && !found)
        {
            if (!used[pos])
            {
                found = true;
                used[indices[i]] = false;
                indices[i] = pos;
                used[pos] = true;
            }
            pos++;
        }

        if (!found)
        {
            // Need to backtrack
            while (i > 0 && !found)
            {
                used[indices[i]] = false;
                i--;

                pos = indices[i] + 1;
                while (pos < numBirds && !found)
                {
                    if (!used[pos])
                    {
                        found = true;
                        used[indices[i]] = false;
                        indices[i] = pos;
                        used[pos] = true;
                    }
                    pos++;
                }
            }

            if (!found)
            {
                done = true;
            }
            else
            {
                // Reset positions to the right
                for (int j = i + 1; j < n; j++)
                {
                    for (pos = 0; pos < numBirds; pos++)
                    {
                        if (!used[pos])
                        {
                            indices[j] = pos;
                            used[pos] = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

// Main bird set generation function
void burds(const char *FILE_PATH, int n, bool isCombination, bool withReplacement)
{

    // Some thoughts on this one.
    // Not 100% happy with my solution, there are still some large limitations.
    // I went with a static buffer and static array for storage, clamping the memory overheard.
    // If any file exceeds the array size though this program will not run ... which I'm not happy with.
    // I started looking into implentation of streaming in C to move the overhead away from memory and into IO.
    // Also starting wondered if I could store an index to each unique line in memory, instead of storing the name itself, which would decrease the overhead by a lot.
    // I would like to submit something though, and fear I don't have the time to properly explore the above before Wednesday :(

    // Open input file
    FILE *file = fopen(FILE_PATH, "r");
    if (!file)
    {
        printf("No burds in here mate ....[ERROR OPENING FILE]\n");
        return;
    }

    // Static arrays for our storage.
    // MAX overhead of 100 * 50 = 5000 bytes of storage.
    char birdNames[MAX_BIRDS][MAX_NAME_LENGTH];
    // MAX overhead of 50 bytes.
    char buffer[MAX_NAME_LENGTH];
    int numBirds = 0;

    // While we haven't reached EOF, and we still have birds left.
    while (fgets(buffer, MAX_NAME_LENGTH, file) != NULL && numBirds < MAX_BIRDS)
    {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Copy to static array
        strncpy(birdNames[numBirds], buffer, MAX_NAME_LENGTH - 1);
        birdNames[numBirds][MAX_NAME_LENGTH - 1] = '\0';

        numBirds++;
    }

    fclose(file);

    // Arrays for tracking current indices and used elements
    int indices[MAX_N];
    bool used[MAX_BIRDS];

    // Initialize tracking arrays
    for (int i = 0; i < MAX_N; i++)
    {
        indices[i] = 0;
    }

    for (int i = 0; i < MAX_BIRDS; i++)
    {
        used[i] = false;
    }

    // Execute appropriate algorithm based on parameters
    printf("<:)}}}><  Bird Set Generator  ><{{{(:>\n\n");

    switch ((isCombination ? 2 : 0) + (withReplacement ? 1 : 0))
    {
    case 0: // isCombination: 0, withReplacement: 0
        generate_permutation_without_replacement(birdNames, numBirds, n, indices, used);
        break;
    case 1: // isCombination: 0, withReplacement: 1
        generate_permutation_with_replacement(birdNames, numBirds, n, indices);
        break;
    case 2: // isCombination: 1, withReplacement: 0
        generate_combination_without_replacement(birdNames, numBirds, n, indices);
        break;
    case 3: // isCombination: 1, withReplacement: 1
        generate_combination_with_replacement(birdNames, numBirds, n, indices);
        break;
    default:
        printf("Case broke, no burds here.\n");
        break;
    }

    printf("\nDone! <:)}}}><\n");
}

// Example usage in main function
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <input_file> <n> [--combination|--permutation] [--with|--without]\n", argv[0]);
        return 1;
    }

    const char *INPUT_FILE = argv[1];
    int n = atoi(argv[2]);
    bool isCombination = true;
    bool withReplacement = false;

    // Parse optional flags
    for (int i = 3; i < argc; i++)
    {
        if (strcmp(argv[i], "--combination") == 0)
        {
            isCombination = true;
        }
        else if (strcmp(argv[i], "--permutation") == 0)
        {
            isCombination = false;
        }
        else if (strcmp(argv[i], "--with") == 0)
        {
            withReplacement = true;
        }
        else if (strcmp(argv[i], "--without") == 0)
        {
            withReplacement = false;
        }
    }

    burds(INPUT_FILE, n, isCombination, withReplacement);

    return 0;
}
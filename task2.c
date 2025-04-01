// The Plan:
// - Figure out how many combinations to generate using maths (will need to research this...)
// - For each iteration number, convert it to a specific set of indices for streaming
// - Then for each index, use fseek to jump to the correct file position
// - Read and output the bird names directly from the file, meaning we don't need memory
// - Computational overhead ... instead of memory ovehead.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


int count_birds (FILE *file)
{
	if (!file) return 0;
	
	long start_pos = ftell(file);

	fseek(file, 0, SEEK_SET);

	int count = 0;
	int c;
	bool new_line = true;

	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			count++;
			new_line = true;
		}
		else if (new_line)
		{
			new_line = false;
		}
	}

	// Need to make sure last line is counted.
	if (!new_line)
	{
		count++;
	}

	fseek(file, start_pos, SEEK_SET);
	return count;
}

void print_bird_at_index(FILE *file, int target_index)
{
	if (!file) return;

	long start_pos = ftell(file);

	fseek(file, 0, SEEK_SET);

	int current_index = 0;
	int c;
	long line_start = 0;

	while (current_index < target_index)
	{
		c = fgetc(file);
		if (c == EOF)
		{
			fseek(file, start_pos, SEEK_SET);
			return;
		}

		if (c == '\n')
		{
			current_index++;
			line_start = ftell(file);
		}
	}

	while ((c = fgetc(file)) != EOF && c != '\n')
	{
		putchar(c);
	}

	fseek(file, start_pos, SEEK_SET);
}

uint64_t calc_total_iterations(int n, int num_birds, bool is_combination, bool with_replacement)
{
	uint64_t total = 1;

	if (is_combination)
	{
		if (with_replacement)
		{
			// Combinations with replacement: (num_birds+n-1)! / (n! * (num_birds-1)!)
			for (int i = 0; i < n; i++)
			{ 
				total = total * (num_birds + i) / (i + 1);
			}
		}
		else
		{
			// Combination without replacement: num_birds! / (n! * (num_birds=n)!)
			if (n > num_birds)
			{
				return 0;
			}
			for (int i = 0; i < n; i++)
			{
				total = total * (num_birds - i) / (i + 1);
			}
		}
	}
	else
	{
		if (with_replacement)
		{
			// Permutations with replacement: num_birds^n
			for (int i = 0; i < n; i++)
			{
				total *= num_birds;
			}
		}
		else
		{
			// Permutations without replacement: num_birds! / (num_birds-n)!
			if (n > num_birds)
			{
				return 0;
			}
			for (int i = 0; i < n; i++)
			{
				total *= (num_birds - i);
			}
		}
	}

	return total;
}

void calculate_line_positions(FILE *file, int num_birds, long *line_positions)
{
	if (!file) return;

	long start_pos = ftell(file);

	fseek(file, 0, SEEK_SET);
	line_positions[0] = 0;

	int line_count = 1;
	int c;

	while (line_count < num_birds && (c = fgetc(file)) != EOF)
	{
		if (c == '\n')
		{
			line_positions[line_count] = ftell(file);
			line_count++;
		}
	}

	fseek(file, start_pos, SEEK_SET);
}

void iteration_to_indice(uint64_t iteration, int n, int num_birds, bool is_combination, bool with_replacement, int *indices)
{
	if (is_combination)
	{
		if (with_replacement)
		{
			int pos = n - 1;
			int val = 0;

			for (int i = 0; i < n; i++)
			{
				indices[i] = 0;
			}

			while (pos >= 0)
			{
				uint64_t count = 1;
				for (int i = 0; i < pos; i++)
				{
					count = count * (num_birds + pos - i - 1) / (i + 1);
				}

				while (iteration >= count && val < num_birds)
				{
					iteration -= count;
					val++;
				}

				indices[n - pos - 1] = val;
				pos--;
			}
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				indices[i] = i;
			}

			for (int i = 0; i < n; i++)
			{
				uint64_t count = 1;
				for (int j = 1; j <= n - i - 1; j++)
				{
					count = count * (num_birds - indices[i] - j) / j;
				}

				while (iteration >= count && indices[i] < num_birds - n + i)
				{
					iteration -= count;
					indices[i]++;
					if (i < n - 1)
					{
						count = 1;
						for (int j = 1; j <= n - 1; j++)
						{
							count = count * (num_birds - indices[i] -j) / j;
						}
					}
				}

				if (i < n - 1)
				{
					indices[i+1] = indices[i] + 1;
				}
			}
		}
	}
	else
	{
		if (with_replacement)
		{
			uint64_t temp = iteration;
			
			for (int i = 0; i < n; i++)
			{
				indices[i] = temp % num_birds;
				temp /= num_birds;
			}
		}
		else
		{
			bool used[num_birds];
			for (int i = 0; i < num_birds; i++)
			{
				used[i] = false;
			}

			for (int i = 0; i < n; i++)
			{
				uint64_t factorial = 1;
				for (int j = 1; j <= num_birds - i - 1; j++)
				{
					factorial *= j;
				}

				int idx = iteration / factorial;
				iteration %= factorial;

				int count =0;
				for (int j = 0; j < num_birds; j++)
				{
					if (!used[j])
					{
						if (count == idx)
						{
							indices[i] = j;
							used[j] = true;
							break;
						}
						count++;
					}
				}
			}
		}
	}
}

// Main bird set generation function
void burds(const char *file_path, int n, bool is_combination, bool with_replacement) {
	printf("<:)}}}><  Bird Set Generator  ><{{{(:>\n\n");
    
    	FILE *file = fopen(file_path, "r");
    	if (!file) 
	{
        	printf("No burds in here mate ....[ERROR OPENING FILE]\n");
        	return;
    	}
    
    	int num_birds = count_birds(file);
    	
	if (num_birds <= 0) {
        	printf("No burds here mate ...\n");
        	fclose(file);
        	return;
    	}
    
    	// TOTAL ITERATIONS COUNT
	uint64_t total_iterations = calc_total_iterations(n, num_birds, is_combination, with_replacement);
    	if (total_iterations == 0) {
        	printf("Cannot generate sets....\n");
        	fclose(file);
        	return;
    	}
    
    	const char *type = is_combination ? "combinations" : "permutations";
    	const char *replacement = with_replacement ? "with" : "without";
    	printf("Generating %s %s replacement (n=%d):\n", type, replacement, n);
    
    	// Stack-allocated indices array with a reasonable maximum
	// While I've eliminated arrays for bird storage, I still need a minimal array 
	// to track the current set of indices. This small, fixed-size array:
	// 1. Uses only O(n) memory regardless of the number of birds
	// 2. Is allocated on the stack for efficiency
	// 3. Has a practical upper limit that balances usability with constraints
	int indices[10]; 
    
    	if (n > 10) 
	{
        	printf("Set size n is too large (maximum: 10)\n");
        	fclose(file);
        	return;
    	}
    
    	// For efficiency, I pre-calculate line positions using fseek
    	// Middle ground approach - using a small fixed array but taking
    	// advantage of fseek to avoid repeated scanning of the file
    	long line_positions[num_birds];
    	calculate_line_positions(file, num_birds, line_positions);
    
    	// Generate and print each set
    	for (uint64_t iter = 0; iter < total_iterations; iter++) 
	{
        	iteration_to_indice(iter, n, num_birds, is_combination, with_replacement, indices);
        
        	for (int i = 0; i < n; i++) 
		{
            		fseek(file, line_positions[indices[i]], SEEK_SET);
            		int c;
            		
			while ((c = fgetc(file)) != EOF && c != '\n') 
			{
                		putchar(c);
        		}
            
            		if (i < n - 1) 
			{
                		printf(",");
            		}
        	}
	
	printf("\n");
    	}
    
    	fclose(file);
    	printf("\nDone! <:)}}}><\n");
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: %s <input_file> <n> [--combination|--permutation] [--with|--without]\n", argv[0]);
        	return 1;
	}

	const char *input_file = argv[1];
	int n = atoi(argv[2]);

	// Defaults
	bool is_combination = true;
	bool with_replacement = false;

	for (int i = 3; i < argc; i++)
	{
		if (strcmp(argv[i], "--combination") == 0)
		{
			is_combination = true;
		}
		else if (strcmp(argv[i], "--permutation") == 0)
		{
			is_combination = false;
		}
		else if (strcmp(argv[i], "--with") == 0)
		{
			with_replacement = true;
		}
		else if (strcmp(argv[i], "--without") == 0)
		{
			with_replacement = false;
		}
	}

	burds(input_file, n, is_combination, with_replacement);

	return 0;
}




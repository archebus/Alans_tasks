// Implement Malloc
// - No cheating (try to avoid looking at the actual source library for malloc)
// - Read through man pages of brk and sbrk
// LOL --> "Avoid  using brk() and sbrk(): the malloc(3) memory allocation package is the portable and comfortable way of allocating memory."

/**

HISTORY
V0.1    | simple allocation, returned pointer with sbrk. No idea how to free the memory.
V0.2    | Implemented metadata, allowing program to track allocation. 
V0.21   | Read about and added pointer arithmetic -> automatic type size scaling! Super cool.
V0.3    | Added linked list structure for managing multiple blocks of memory.
V0.4    | Added simple testing and output and print memory function.
V0.5	| Convention to snake_case and added doubly linked list.
v0.6	| Merge free function added -> attempt to merge avail blocks on free.
v0.7	| Mem stats func for more output options.
v0.8	| Testing in main method expanded.

*/

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>


typedef struct josh_meta_data {
    size_t size;
    bool free;
    struct josh_meta_data *next; 		// Pointer to next block of memory.
    struct josh_meta_data *prev;		// Now doubly linked.
} josh_meta_data;

static josh_meta_data *head = NULL; // Head of linked list of mem blocks.


void merge_free()
{
	josh_meta_data *current = head;

	while (current && current->next)
	{
		if (current->free && current->next->free)
		{
			current->size += sizeof(josh_meta_data) + current->next->size;

			josh_meta_data *remove_me = current->next;
			current->next = remove_me->next;

			if (remove_me->next)
			{
				remove_me->next->prev = current;
			}
		}
		else
		{
			current = current->next;
		}
	}
}

void *josh_give(size_t size) { 

	josh_meta_data *current = head;

	// First-fit: is there an existing free block that fits?	
	while (current)
	{
		if (current->free && current->size >= size)
		{
			if (current->size >= size + sizeof(josh_meta_data) + 8) // 8 min for new alloc.
			{
				josh_meta_data *new_block = (josh_meta_data*)((char*)(current+1) + size);
				new_block->size = current->size - size -sizeof(josh_meta_data);
				new_block->free = true;
				new_block->next = current->next;
				new_block->prev = current;
				
				if (current->next)
				{
					current->next->prev = new_block;
				}
				current->next = new_block;

				current->size = size;
			}

			current->free = false;
			return (void*)(current + 1);
		}
		current = current->next;
	}
	
	
	// If here, no blocks found, allocate a new one.
	josh_meta_data *new_block = sbrk(sizeof(josh_meta_data) + size);
	
	if (new_block == (void*)-1)
	{
		return NULL;
	}

	new_block->size = size;
	new_block->free = false;
	new_block->next = NULL;
	new_block->prev = NULL;

	if (head == NULL)
	{
		head = new_block;
	}
	else
	{
		current = head;

		while (current->next)
		{
			current = current->next;
		}
		current->next = new_block;
		new_block->prev = current;
	}

	return (void*)(new_block+1);
}
	

void josh_take(void *mem_pointer) 
{
	if  (mem_pointer == NULL) return;

	josh_meta_data *mem_block = ((josh_meta_data*)mem_pointer) - 1;
    
    	mem_block->free = true;

	// Merge attempt!
	merge_free();	
	
}

void print_map() {
	josh_meta_data *current = head;
	
	int i = 0;
    
	printf("\n--- MEMORY MAP ---\n");
    		while (current) 
		{
        		printf("Block %d: address=%p, size=%zu, free=%s\n", 
               		i++, 
               		(void*)(current + 1),
               		current->size, 
               		current->free ? "true" : "false");
        		current = current->next;
    		}
    	printf("-----------------\n\n");
}

void print_stats()
{
	josh_meta_data *current = head;
	size_t total_alloc = 0;
	size_t total_free = 0;
	int free_blocks = 0;
	int used_blocks = 0;

	while (current)
	{
		if (current->free)
		{
			total_free += current->size;
			free_blocks++;
		}
		else
		{
			total_alloc += current->size;
			used_blocks++;
		}

		current = current->next;
	}

	printf("\n --- JOSH ALLOC STATS ---\n");
	printf("Total mem allocated: 	%zu bytes\n", total_alloc);
	printf("Total mem free:		%zu bytes\n", total_free);
	printf("Number used blocks:	%d\n", used_blocks);
	printf("Number free blocks:	%d\n", free_blocks);
	printf("-------------------------\n\n");
}

int main() 
{
    
    	printf("=== Testing Type Allocations ===\n");
    
   	 // Allocate different types of memory
    	int *nums = (int*)josh_give(3 * sizeof(int));
    	char *str = (char*)josh_give(20);
    	double *dbl = (double*)josh_give(sizeof(double));
    
    	// Use the memory
    	nums[0] = 100;
    	nums[1] = 200;
    	nums[2] = 300;
    
    	strcpy(str, "Hello mario");

    	*dbl = 1.111111;
    
    	// Print values
    	printf("nums: %d, %d, %d\n", nums[0], nums[1], nums[2]);
    	printf("str: %s\n", str);
    	printf("dbl: %f\n", *dbl);
    
    	// Show memory map + stats
    	print_map();
	print_stats();

	// Free in different order to test the free list
	printf("\nFreeing nums\n");
   	josh_take(nums);
	print_map();

	printf("\nFreeing dbl\n");
   	josh_take(dbl);
	print_map();

	printf("\nFreeing str\n");
   	josh_take(str);
	print_map();
	
	printf("\n -- Allocating new memory block after freeing -- \n");
	int *new_nums = (int*)josh_give(5 * sizeof(int));
	for (int i = 0; i < 5; i++)
	{
		new_nums[i] = i * 100;
	}

	printf("Look! New nums: %d %d %d %d %d\n",
			new_nums[0], new_nums[1], new_nums[2], new_nums[3],  new_nums[4]);

	print_map();
	print_stats();

    	// Block splitting
    	printf("\nTesting block splitting\n");
    	josh_take(new_nums);
    
	char *small_str = (char*)josh_give(10);
    	strcpy(small_str, "Small");
    	printf("small_str: %s\n", small_str);
    
    	print_map();
    	print_stats();
    
    	printf("\nAll done\n");

    	return 0;
}

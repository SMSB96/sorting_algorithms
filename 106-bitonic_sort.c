#include "sort.h"

/**
 * swap_ints - Swaps two integers in an array.
 * @a: First integer to swap.
 * @b: Second integer to swap.
 */
void swap_ints(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * bitonic_merge - Sorts a bitonic sequence inside an array of integers.
 * @array: Array of integers.
 * @size: Size of the array.
 * @start: Starting index of the sequence in array to sort.
 * @seq: Size of the sequence to sort.
 * @flow: Direction to sort in.
 */
void bitonic_merge(int *array, size_t size, size_t start, size_t seq,
		char flow)
{
	size_t a, jump = seq / 2;

	if (seq > 1)
	{
		for (a = start; a < start + jump; a++)
		{
			if ((flow == UP && array[a] > array[a + jump]) ||
			    (flow == DOWN && array[a] < array[a + jump]))
				swap_ints(array + a, array + a + jump);
		}
		bitonic_merge(array, size, start, jump, flow);
		bitonic_merge(array, size, start + jump, jump, flow);
	}
}

/**
 * bitonic_seq - Converts an array of integers into a bitonic sequence.
 * @array: Array of integers.
 * @size: Size of the array.
 * @start: Starting index of a block of the building bitonic sequence.
 * @seq: Size of a block of the building bitonic sequence.
 * @flow: Direction to sort the bitonic sequence block in.
 */
void bitonic_seq(int *array, size_t size, size_t start, size_t seq, char flow)
{
	size_t cut = seq / 2;
	char *str = (flow == UP) ? "UP" : "DOWN";

	if (seq > 1)
	{
		printf("Merging [%lu/%lu] (%s):\n", seq, size, str);
		print_array(array + start, seq);

		bitonic_seq(array, size, start, cut, UP);
		bitonic_seq(array, size, start + cut, cut, DOWN);
		bitonic_merge(array, size, start, seq, flow);

		printf("Result [%lu/%lu] (%s):\n", seq, size, str);
		print_array(array + start, seq);
	}
}

/**
 * bitonic_sort - Sorts an array of integers in ascending
 * @array: Array of integers.
 * @size: Size of the array.
 * Description: Prints the array after each swap and only works for
 * size = 2^k where k >= 0 (ie. size equal to powers of 2).
 */
void bitonic_sort(int *array, size_t size)
{
	if (array == NULL || size < 2)
		return;

	bitonic_seq(array, size, 0, size, UP);
}

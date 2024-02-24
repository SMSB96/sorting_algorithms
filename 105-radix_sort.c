#include "sort.h"

/**
 * get_max - Gets the maximum value in an array of integers.
 * @array: Array of integers.
 * @size: Size of the array.
 * Return: Maximum integer in the array.
 */
int get_max(int *array, int size)
{
	int maxi, k;

	for (maxi = array[0], k = 1; k < size; k++)
	{
		if (array[k] > maxi)
			maxi = array[k];
	}

	return (maxi);
}

/**
 * radix_counting_sort - Sorts the significant digits of an array of integers
 *                       in ascending order using the counting sort algorithm.
 * @array: Array of integers.
 * @size: Size of the array.
 * @sig: Significant digit to sort on.
 * @buff: Buffer to store the sorted array.
 */
void radix_counting_sort(int *array, size_t size, int sig, int *buff)
{
	int count[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	size_t k;

	for (k = 0; k < size; k++)
		count[(array[k] / sig) % 10] += 1;

	for (k = 0; k < 10; k++)
		count[k] += count[k - 1];

	for (k = size - 1; (int)k >= 0; k--)
	{
		buff[count[(array[k] / sig) % 10] - 1] = array[k];
		count[(array[k] / sig) % 10] -= 1;
	}

	for (k = 0; k < size; k++)
		array[k] = buff[k];
}

/**
 * radix_sort - Sorts an array of integers in ascending
 *              order using the radix sort algorithm.
 * @array: Array of integers.
 * @size: Size of the array.
 * Description: Implements the LSD radix sort algorithm and prints
 * the array after each significant digit increase.
 */
void radix_sort(int *array, size_t size)
{
	int maxi, sig, *buff;

	if (array == NULL || size < 2)
		return;

	buff = malloc(sizeof(int) * size);
	if (buff == NULL)
		return;

	maxi = get_max(array, size);
	for (sig = 1; maxi / sig > 0; sig *= 10)
	{
		radix_counting_sort(array, size, sig, buff);
		print_array(array, size);
	}

	free(buff);
}

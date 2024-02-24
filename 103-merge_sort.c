#include "sort.h"

/**
 * merge_subarr - Sort a subarray of integers.
 * @subarr: Subarray of an array of integers to sort.
 * @buff: Buffer to store the sorted subarray.
 * @front: Front index of the array.
 * @mid: Middle index of the array.
 * @back: Back index of the array.
 */
void merge_subarr(int *subarr, int *buff, size_t front, size_t mid,
		size_t back)
{
	size_t a, j, k = 0;

	printf("Merging...\n[left]: ");
	print_array(subarr + front, mid - front);

	printf("[right]: ");
	print_array(subarr + mid, back - mid);

	for (a = front, j = mid; a < mid && j < back; k++)
		buff[k] = (subarr[a] < subarr[j]) ? subarr[a++] : subarr[j++];
	for (; a < mid; a++)
		buff[k++] = subarr[a];
	for (; j < back; j++)
		buff[k++] = subarr[j];
	for (a = front, k = 0; a < back; a++)
		subarr[a] = buff[k++];

	printf("[Done]: ");
	print_array(subarr + front, back - front);
}

/**
 * merge_sort_recursive - Implements the merge sort algorithm
 * through recursion.
 * @subarr: Subarray of an array of integers to sort.
 * @buff: Buffer to store the sorted result.
 * @front: Front index of the subarray.
 * @back: Back index of the subarray.
 */
void merge_sort_recursive(int *subarr, int *buff, size_t front, size_t back)
{
	size_t mid;

	if (back - front > 1)
	{
		mid = front + (back - front) / 2;
		merge_sort_recursive(subarr, buff, front, mid);
		merge_sort_recursive(subarr, buff, mid, back);
		merge_subarr(subarr, buff, front, mid, back);
	}
}

/**
 * merge_sort - Sort an array of integers in ascending
 *              order using the merge sort algorithm.
 * @array: An array of integers.
 * @size: The size of the array.
 * Description: Implements the top-down merge sort algorithm.
 */
void merge_sort(int *array, size_t size)
{
	int *buffr;

	if (array == NULL || size < 2)
		return;

	buffr = malloc(sizeof(int) * size);
	if (buffr == NULL)
		return;

	merge_sort_recursive(array, buffr, 0, size);

	free(buffr);
}

/* Created by uwelekezo on 3/6/23.*/
#include "main.h"

/**
 * peek- retrieves the first item in the queue
 * @array: array queue to process
 *
 * Return: A pointer to the string of the first array queue item to be processd
 */
char *peek(op_t *array)
{
	if (is_empty(array))
	{
		/*strerror("logic_error");*/
		/*fprintf(stderr,"logic_error");*/
		perror("logic_error");
		return (NULL);
	}
	/*throw std::logic_error("logic_error");*/
	return (array->arr[0]);
}

/**
 * is_empty- verifies if the array queue is empty
 * @array: array queue to process
 *
 * Return: true if is empty else false
 */
bool is_empty(op_t *array)
{
	if (array->_size == 0)
		return (true);
	return (false);
}
/**
 * enqueue- adds array items to the array queue
 * @array: array queue to add items to
 * @str: string to be appended to array queue
 *
 * Return: true if item is successfully added to queue else false
 */
bool enqueue(op_t *array, char *str)
{
	if (!str)
		return (false);

	if (array->_capacity == 0)
	{
		array->arr = (char **) malloc((array->_capacity = 20) * sizeof(char *));
		if (!array->arr)
			return (false);
		array->arr[array->_size++] = str;
		return (true);
	}
	else if (array->_capacity == array->_size)
	{
		array->arr = (char **) realloc(array->arr,
				(array->_capacity *= 1.5) * sizeof(char *));
		if (!array->arr)
			return (false);
		array->arr[array->_size++] = str;
		return (true);
	}
	array->arr[array->_size++] = str;
	return (true);
}
/**
 * dequeue- removes array items from the array queue
 * @array: array queue to remove items from
 *
 * Return: true if item is successfully removed from queue else false
 */
bool dequeue(op_t *array)
{
	unsigned int i, index;
	bool status;

	status = is_empty(array);
	if (status)
		return (false);
	index = 0;
	for (i = index; i < array->_size; ++i)
		array->arr[i] = array->arr[i + 1]; /* copy next element left*/
	array->_size--;

	return (true);

}

/**
 * reset- deletes all items in the array
 * @pArray: array queue to delete all items from
 *
 * Return: void
 */
void reset(op_t *pArray)
{
	while (pArray->_size)
	{
		dequeue(pArray);
	}
}

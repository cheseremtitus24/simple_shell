#include "main.h"

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



bool is_full(op_t *array)
{
	if (array->_size >= array->_capacity)
		return (true);
	return (false);
}

bool is_empty(op_t *array)
{
	if (array->_size == 0)
		return (true);
	return (false);
}

bool enqueue(op_t *array, char *str)
{
	if (!str)
		return (false);

	if (array->_capacity == 0)
	{
		array->arr = (char **) malloc((array->_capacity = 3) * sizeof(char *));
		if (!array->arr)
			return (false);
		array->arr[array->_size++] = str;
		return (true);
	} else if (array->_capacity == array->_size)
	{
		array->arr = (char **) realloc(array->arr, (array->_capacity *= 1.5) * sizeof(char *));
		if (!array->arr)
			return (false);
		array->arr[array->_size++] = str;
		return (true);
	} else
	{
		array->arr[array->_size++] = str;
		return (true);
	}
}

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

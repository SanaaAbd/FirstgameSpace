#pragma once

#include <stdlib.h>
#include <assert.h>

#include "array_list.h"

array_list* array_list_create()
{
	array_list* al = (array_list*)malloc(sizeof(array_list));
	
	al->length = 0;
	al->data = (void**)malloc(sizeof(void*));
	
	assert(al->data);
	
	return al;
}
void array_list_destroy(array_list* al)
{
	free(al->data);
	free(al);
}
void array_list_push(array_list* al, void* element)
{
	__array_list_allocate(al, al->length + 1);
	al->data[al->length - 1] = element;
}
void* array_list_get(array_list* al, unsigned int index)
{
	if (index >= al->length)
		return NULL;
		
	return al->data[index];
}
void array_list_clear(array_list* al)
{
	free(al->data);
	al->data = (void**)malloc(sizeof(void*));
	al->length = 0;
	
	assert(al->data);
}
array_list* array_list_remove(array_list* al, unsigned int index)
{
	array_list* newArr = array_list_create();
	
	for (int i = 0; i < al->length; i++)
	{
		if (i != index)
			array_list_push(newArr, array_list_get(al, i));
	}
	array_list_destroy(al);
	
	assert(newArr->data);
	
	return newArr;
}

// "private" functions
void __array_list_allocate(array_list* al, size_t newsize)
{
	if (newsize > al->length)
	{
		al->data = (void**)realloc(al->data, sizeof(void*) * newsize);
		al->length++;
		
		assert(al->data);
	}
}

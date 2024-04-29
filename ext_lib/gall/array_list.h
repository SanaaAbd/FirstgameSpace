#pragma once

typedef struct
{
	unsigned int length;
	void** data;
} array_list;

// initialization and deinitialization
array_list* array_list_create();
void array_list_destroy(array_list* al);

// array operations
void array_list_push(array_list* al, void* element);
array_list* array_list_remove(array_list* al, unsigned int index);
void* array_list_get(array_list* al, unsigned int index);
void array_list_clear(array_list* al);

// private functions
void __array_list_allocate(array_list* al, size_t newsize);

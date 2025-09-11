#pragma once

#include <stdlib.h>
#include <string.h>

void StringListInit(char*** list);

int StringListSize(char** list);

int StringListCapacity(char** list);

void StringListDestroy(char*** list);

void StringListAdd(char*** list, const char* str);

void StringListRemove(char** list, const char* str);

int StringListIndexOf(char** list, const char* str);

void StringListRemoveDuplicates(char** list);

void StringListReplaceInStrings(char** list, const char* before, const char* after);

int string_compare(const void* a, const void* b);

void StringListSort(char** list);

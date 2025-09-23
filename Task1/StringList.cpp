#define _CRT_SECURE_NO_WARNINGS
#include "StringList.h"



#define koef_capacity 2  

/* Initializes list */
void StringListInit(char*** list) {
    //[size][capacity] <- list -> [ref->[string], ref->[string]]
    if (list == nullptr) return;
    char** temp = (char**)malloc(sizeof(char*) * 3);
    if (temp != nullptr) {
        temp[0] = (char*)(intptr_t)0;  // size = 0
        temp[1] = (char*)(intptr_t)1;  // capacity = 1
        *list = temp + 2;
    }
    else {
        *list = nullptr;
    }
}

/* Returns the number of items in the list. */
int StringListSize(char** list) {
    if (list == nullptr) return 0;
    return (int)(intptr_t)list[-2];
}

/* Returns capacity in the list. */
int StringListCapacity(char** list) {
    if (list == nullptr) return 0;
    return (int)(intptr_t)list[-1];
}

/* Destroy list and set pointer to NULL. */
void StringListDestroy(char*** list) {
    if (list && *list != nullptr) {
        int size = StringListSize(*list);
        for (int i = 0; i < size; ++i) {
            free((*list)[i]);
        }
        free(*list - 2);
        *list = nullptr;
    }
}

/* Inserts value at the end of the list. */
void StringListAdd(char*** list, const char* str) {
    if (str == nullptr || list == nullptr) return;

    if (*list == nullptr) {
        StringListInit(list);
        if (*list == nullptr) return;
    }

    int list_size = StringListSize(*list);
    int list_capacity = StringListCapacity(*list);
    char** full_array = *list - 2;

    if (list_size >= list_capacity) {
        int new_capacity = list_capacity * koef_capacity;
        char** new_list = (char**)realloc(full_array, (2 + new_capacity) * sizeof(char*));
        if (new_list == nullptr) {
            return;
        }
        full_array = new_list;
        *list = new_list + 2;
        (*list)[-1] = (char*)(intptr_t)new_capacity;
    }

    size_t str_len = strlen(str) + 1;
    (*list)[list_size] = (char*)malloc(str_len);
    if ((*list)[list_size] == nullptr) {
        return;
    }

    strcpy((*list)[list_size], str);
    (*list)[-2] = (char*)(intptr_t)(list_size + 1);
}

/* Removes all occurrences of str in the list. */
void StringListRemove(char** list, const char* str) {
    if (list == nullptr || str == nullptr) return;

    int size = StringListSize(list);
    int write_pos = 0;

    for (int read_pos = 0; read_pos < size; ++read_pos) {
        if (strcmp((list)[read_pos], str) == 0) {
            free((list)[read_pos]);
        }
        else {
            if (write_pos != read_pos) {
                (list)[write_pos] = list[read_pos];
            }
            write_pos++;
        }
    }
    (list)[-2] = (char*)(intptr_t)write_pos;
}

/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(char** list, const char* str) {  
    if (list == nullptr || str == nullptr) return -1;  

    int size = StringListSize(list);
    for (int i = 0; i < size; ++i) {
        if (strcmp(list[i], str) == 0) {
            return i;
        }
    }
    return -1;
}

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char** list) {
    char** exsist_word;
    StringListInit(&exsist_word);
    int size = StringListSize(list);
    int write_pos = 0;
    for (int i = 0; i < size; ++i) {
        if (StringListIndexOf(exsist_word, list[i]) != -1) {
            free(list[i]);
        }
        else {
            if (write_pos != i) {
                list[write_pos] = list[i];
            }
            StringListAdd(&exsist_word, list[i]);
            write_pos++;
        }
    }
    list[-2] = (char*)(intptr_t)write_pos;
    StringListDestroy(&exsist_word);
}

/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(char** list, const char* before, const char* after) {
    int size = StringListSize(list);

    for (int i = 0; i < size; ++i) {
        char* src = list[i];

        //find first compare
        char* pos = strstr(src, before); 

        if (!pos) continue; 

        //size between two pointers
        int prefix_len = pos - src;

        int new_len = strlen(src) - strlen(before) + strlen(after);

        char* replace_word = (char*)malloc(new_len + 1);

        if (!replace_word) continue;

        strncpy(replace_word, src, prefix_len);
        replace_word[prefix_len] = '\0';

        //replace after
        strcat(replace_word, after);

        // tail 
        strcat(replace_word, pos + strlen(before));

        free(list[i]);

        list[i] = replace_word;
    }
}


/* Comparison function for qsort */
int string_compare(const void* a, const void* b) { 
    char* str1 = *((char**)a);  
    char* str2 = *((char**)b);  
    return strcmp(str1, str2); 
}

/* Sorts the list of strings in ascending order */
void StringListSort(char** list) {
    if (list == nullptr) return;

    int size = StringListSize(list);
    if (size <= 1) return; 

    // use qsort from stdlib.h
    qsort(list, size, sizeof(char*), string_compare);
}




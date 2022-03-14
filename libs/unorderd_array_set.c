//
// Created by Donpad on 22.12.2021.
//

#include "unorderd_array_set.h"

unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
}

static void unordered_array_set_shrinkToFit(unordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

unordered_array_set unordered_array_set_create_from_array(const int *a,
                                                          size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);
    unordered_array_set_shrinkToFit(&set);
    return set;
}

size_t unordered_array_set_in(unordered_array_set set, int value) {
    return linearSearch_(set.data, set.size, value);
}

int compareInts(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size)
        return 0;
    qsort(set1.data, set1.size, sizeof(int), compareInts);
    qsort(set2.data, set2.size, sizeof(int), compareInts);
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert (set->size < set->capacity);
}

void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(*set, value) == set->size) {
        unordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}

void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t pos = unordered_array_set_in(*set, value);
    if (pos != set->size) {
        deleteByPosSaveOrder_(set->data, &set->size, pos - 1);
    }
}

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    size_t size1 = set1.size;
    int data1[size1];
    arrayCopy(set1.data, data1, set1.size);

    for (int i = 0; i < set2.size; ++i) {
        if (unordered_array_set_in(set1, set2.data[i]) == set1.size)
            append_(data1, &size1, set2.data[i]);
    }
    return unordered_array_set_create_from_array(data1, size1);
}

unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    size_t resSize = set1.size;
    int* dataRes = (int*) malloc(sizeof(int)* set1.size);
    resSize = 0;

    for (int i = 0; i < set2.size; ++i) {
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size)
            append_(dataRes, &resSize, set1.data[i]);
    }

    return unordered_array_set_create_from_array(dataRes, resSize);
}

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    size_t resSize = set1.size;
    int* dataRes = (int*) malloc(sizeof(int)* set1.size);
    resSize = 0;

    for (int i = 0; i < set2.size; ++i) {
        if (unordered_array_set_in(set2, set1.data[i]) == set2.size)
            append_(dataRes, &resSize, set1.data[i]);
    }

    return unordered_array_set_create_from_array(dataRes, resSize);
}

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set difference1 = unordered_array_set_difference(set1, set2);
    unordered_array_set difference2 = unordered_array_set_difference(set2, set1);
    unordered_array_set symmetricDifference = unordered_array_set_union(difference1, difference2);
    unordered_array_set_delete(difference1);
    unordered_array_set_delete(difference2);
    return symmetricDifference;
}


unordered_array_set unordered_array_set_complement(
        unordered_array_set set, unordered_array_set universumSet
) {
    return unordered_array_set_difference(set, universumSet);
}

unordered_array_set get_universumSet(size_t capacity) {
    int universum[capacity];
    for (int i = 0; i < capacity; ++i) {
        universum[i] = i;
    }
    return unordered_array_set_create_from_array(universum, capacity);
}

void unordered_array_set_print(unordered_array_set set) {
    outputArray_(set.data, set.size);
}

void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
}




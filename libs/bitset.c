//
// Created by Donpad on 21.12.2021.
//

#include "bitset.h"
#include <assert.h>
#include <iso646.h>
#include <stdio.h>

bitset bitset_create(unsigned maxValue) {
    assert(maxValue < 32);
    return (bitset) {0, maxValue};
}

uint32_t bitset_get_maxValue(uint32_t values) {
    unsigned count = 1;
    while (values > 0) {
        count++;
        values /= 2;
    }
    return count;
}

bool bitset_in(bitset set, unsigned int value) {
    assert(value < 32);
    return (set.values >> (value)) bitand 1;
}

bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values;
}

bool bitset_isSubset(bitset subset, bitset set) {
    return (set.values bitor subset.values) == set.values;
}

void bitset_insert(bitset *set, unsigned int value) {
    assert(value < 32);
    set->values = (set->values) bitor (1 << value);
}

void bitset_deleteElement(bitset *set, unsigned int value) {
    assert(value < 32);
    set->values = (set->values) bitand ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    return (bitset) {set1.values bitor set2.values,
                     set1.maxValue > set2.maxValue ? set1.maxValue : set2.maxValue};
}

bitset bitset_intersection(bitset set1, bitset set2) {
    uint32_t values = set1.values bitand set2.values;
    return (bitset) {values, bitset_get_maxValue(values)};
}

bitset bitset_difference(bitset set1, bitset set2) {
    uint32_t values = set1.values bitand ~set2.values;
    return (bitset) {values, bitset_get_maxValue(values)};
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    uint32_t values = set1.values xor set2.values;
    return (bitset) {values, bitset_get_maxValue(values)};
}

bitset bitset_complement(bitset set) {
    return (bitset) {((~set.values << (32 - set.maxValue)) >> (32 - set.maxValue)) bitor set.values, set.maxValue};
}

int bitset_strictInclusion(bitset set1, bitset set2) {
    return bitset_nonStrictInclusion(set1, set2) and !bitset_isEqual(set1, set2);
}

int bitset_nonStrictInclusion(bitset set1, bitset set2){
    return bitset_isSubset(set2, set1);
}

void bitset_print(bitset set) {
    printf("{");
    int isEmpty = 1;
    for (int i = 0; i <= set.maxValue; ++i) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            isEmpty = 0;
        }
    }
    if (isEmpty)
        printf("}\n");
    else
        printf("\b\b}\n");
}

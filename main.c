#include <stdio.h>
#include "libs/bitset.h"
#include <assert.h>

void test_bitset_strictInclusion_smokeTest(){
    bitset set1 = bitset_create(4);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 4);
    bitset set2 = bitset_create(4);
    bitset_insert(&set2, 2);
    bitset_insert(&set2, 3);
    bitset_insert(&set2, 4);
    bitset set3 = bitset_create(4);
    bitset_insert(&set3, 1);
    bitset_insert(&set3, 2);
    bitset_insert(&set3, 3);
    bitset_insert(&set3, 4);
    assert(bitset_strictInclusion(set1,set2) and !bitset_strictInclusion(set1, set3));
}


int main() {
    test_bitset_strictInclusion_smokeTest();
    return 0;
}

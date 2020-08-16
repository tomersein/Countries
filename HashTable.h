//
// Created by tomer on 29/11/2018.
//

#ifndef EX2ADVANCEDCODING_HASHTABLE_H
#define EX2ADVANCEDCODING_HASHTABLE_H


#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "Defs.h"

typedef struct hashTable_s *hashTable;

hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue, freeFunction freeValue, printFunction printValue, equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber);
status destroyHashTable(hashTable);
status addToHashTable(hashTable, Element key, Element value);
Element lookupInHashTable(hashTable, Element key);
status removeFromHashTable(hashTable, Element key);
status displayHashElements(hashTable);

#endif /* HASH_TABLE_H */


#endif //EX2ADVANCEDCODING_HASHTABLE_H

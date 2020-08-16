//
// Created by tomer on 01/12/2018.
//
#include "Defs.h"
#include "HashTable.h"
#include "keyValuePair.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

struct hashTable_s{
    copyFunction copyKey;
    freeFunction freeKey;
    printFunction printKey;
    copyFunction copyValue;
    freeFunction freeValue;
    printFunction printValue;
    equalFunction equalKey;
    transformIntoNumberFunction transformKeyIntoNumber;
    int hashNumber;
    List* hashTable;
};

hashTable createHashTable (copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue, freeFunction freeValue,
                           printFunction printValue, equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber){
    if (copyKey==NULL||freeKey==NULL||printKey==NULL||copyValue==NULL||freeValue==NULL||
        printValue==NULL|| equalKey==NULL||transformKeyIntoNumber==NULL){
        return NULL;
    }
    hashTable table = (hashTable)malloc(sizeof(struct hashTable_s));
    if(table==NULL){
        return NULL;
    }
    table->copyKey=copyKey;
    table->freeKey=freeKey;
    table->printKey=printKey;
    table->copyValue=copyValue;
    table->freeValue=freeValue;
    table->printValue=printValue;
    table->equalKey=equalKey;
    table->transformKeyIntoNumber=transformKeyIntoNumber;
    table->hashNumber=hashNumber;
    //here we create the hash table
    table->hashTable = (List*)calloc(hashNumber, sizeof(List));
    if(table->hashTable==NULL){
        free(table);
        return NULL;
    }
    for(int i=0; i<hashNumber; i++){
        table->hashTable[i] = createLinkedList(copyPer, destroyKeyValuePair, displayValue, isEqualKey);
        if(table->hashTable[i] == NULL){
            destroyHashTable(table);
            return NULL;
        }
    }
    return table;
}

status destroyHashTable(hashTable table){
    if(table==NULL){
        return failure;
    }
    for(int i=0; i<table->hashNumber; i++){
        destroyList(table->hashTable[i]);
    }
    free(table->hashTable);
    free(table);
    return success;
}

status addToHashTable(hashTable table, Element key, Element value){
    if(table == NULL || key == NULL || value == NULL){
        return failure;
    }
    keyValuePair Pair = createKeyValuePair(table->copyValue,table->copyKey, table->freeValue,table->freeKey,
                                           table->printValue,table->printKey,table->equalKey,key,value);
    if (Pair==NULL){
        return failure;
    }
    int keyValue = table->transformKeyIntoNumber(key);
    int whereInHash = keyValue%(table->hashNumber);
    /*
    if(table->hashTable[whereInHash]==NULL) {//if there is no initialized list
        table->hashTable[whereInHash] = createLinkedList(copyPer, destroyKeyValuePair, displayValue, isEqualKey);
        if (table->hashTable[whereInHash] == NULL) {
            return failure;
        }
    }
    */
    if(!appendNode(table->hashTable[whereInHash], (Element)Pair)){
        destroyKeyValuePair((Element)Pair);
        return failure;
    }
    destroyKeyValuePair((Element)Pair);
    return success;
}

Element lookupInHashTable(hashTable table, Element key){
    if(table==NULL || key==NULL){
        return NULL;
    }
    keyValuePair tempPair = createKeyValuePair(table->copyValue, table->copyKey, table->freeValue, table->freeKey,
                                               table->printValue, table->printKey, table->equalKey, key, NULL);
    int keyValue = table->transformKeyIntoNumber(key);
    int whereInHash = keyValue%(table->hashNumber);
    if(table->hashTable[whereInHash]==NULL){
        return NULL;
    }
    Element returnToUser = searchInList(table->hashTable[whereInHash], tempPair);
    returnToUser = getValue(returnToUser);
    destroyKeyValuePair(tempPair);
    return returnToUser;
}

status removeFromHashTable(hashTable table, Element key){
    if(table==NULL||key==NULL){
        return failure;
    }
    keyValuePair tempPair = createKeyValuePair(table->copyValue, table->copyKey, table->freeValue, table->freeKey,
                                               table->printValue, table->printKey, table->equalKey, key, NULL);
    if(tempPair==NULL){
        return failure;
    }
    int keyValue = table->transformKeyIntoNumber(key);
    int whereInHash = keyValue%(table->hashNumber);
    if(table->hashTable[whereInHash]==NULL){ //if the list is empty the key was not in the ADT
        destroyKeyValuePair((Element)tempPair);
        return failure;
    }
    if(deleteNode(table->hashTable[whereInHash], tempPair)==failure){
        destroyKeyValuePair((Element)tempPair);
        return failure;
    }
    destroyKeyValuePair((Element)tempPair);
    return success;
}

status displayHashElements(hashTable table){
    if (table==NULL){
        return failure;
    }
    for(int i=0;i<table->hashNumber;i++){
        displayList(table->hashTable[i]);
    }
    return success;
}

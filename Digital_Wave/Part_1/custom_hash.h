//
// Created by Alessandro on 31.08.2024.
//

#ifndef CUSTOM_HASH_H
#define CUSTOM_HASH_H
#include "custom_doubly_linked_list.h"


class custom_hash {
private:
    typedef struct KVPair {
        char *key;
        int value;
        char *queueNode;
    } KVPair;
    typedef struct Table {
        KVPair **data;
        int size;
        int count;
        char *insertionQueue;
    };

    static void freePair(const Table *table, KVPair *pair);
    static void freeTable(Table *table);
    static int searchTable(const Table *table, const char *key);

public:
    static KVPair *createPair(const char *key, int value);
    static Table *createTable(int size);
    static void insert(Table *table, const char *key, int value);
    static void remove(const Table *table, const char *key);
    static int get(const Table *table, const char *key);
    static KVPair* get_last(const Table *table);
    static KVPair* get_first(const Table *table);
};



#endif //CUSTOM_HASH_H

//
// Created by Alessandro on 31.08.2024.
//

#include "custom_hash.h"

#include <functional>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "custom_doubly_linked_list.h"

custom_hash::KVPair *custom_hash::createPair(const char *key, const int value) {
    // create a pointer to a new key-value pair
    KVPair *pair = static_cast<KVPair *>(malloc(sizeof(KVPair)));
    pair->key = static_cast<char *>(malloc(strlen(key) + 1));
    strcpy(pair->key, key);
    pair->value = value;
    pair->queueNode = NULL;
    return pair;
}

custom_hash::Table *custom_hash::createTable(const int size) {
    // create a new hash table
    auto *table = static_cast<Table *>(malloc(sizeof(Table)));
    table->size = size;
    table->count = 0;
    table->data = static_cast<KVPair **>(calloc(table->size, sizeof(KVPair *)));

    for (int i = 0; i < table->size; i++)
        table->data[i] = NULL;

    table->insertionQueue = custom_doubly_linked_list::createLinkedList();
    return table;
}

void custom_hash::freePair(const Table *table, KVPair *pair) {
    custom_doubly_linked_list::remove(table->insertionQueue, pair->queueNode);
    free(pair->key);
    free(pair);
}

void custom_hash::freeTable(Table *table) {
    for (int i = 0; i < table->size; i++)
        if (table->data[i] != NULL)
            freePair(table, table->data[i]);

    free(table->data);
    free(table->insertionQueue);
    free(table);
}

int custom_hash::searchTable(const Table *table, const char *key) {
    if (table == NULL) throw std::invalid_argument("table is null");
    if (table->data == NULL) throw std::invalid_argument("data in table is null");

    int idx = std::hash<std::string>{}(key) % table->size;
    // implement linear probing:
    // move along one space if data with a different key exists at current index
    while (table->data[idx] != NULL || strcmp(table->data[idx]->key, key) != 0) {
        idx++;
    }
    return idx;
}


void custom_hash::insert(Table *table, const char *key, const int value) {
    if (static_cast<float>(table->size) / static_cast<float>(table->count + 1) > .5f) {
        // Table load reached threshold.
        // To keep the load balanced, we double the table's size.
        Table *newTable = createTable(table->size * 2);
        for (int i = 0; i < table->size; i++)
            newTable->data[i] = table->data[i];
        freeTable(table);
        table = newTable;
    }

    if (const int idx = searchTable(table, key); table->data[idx] == NULL) {
        const auto pair = createPair(key, value);
        table->data[idx] = pair;
        custom_doubly_linked_list::append(table->insertionQueue, pair->queueNode);
    } else {
        table->data[idx]->value = value;
    }
}
void custom_hash::remove(const Table *table, const char *key) {
    if (int idx = searchTable(table, key); table->data[idx] != NULL) {
        // Remove the pair from data.
        freePair(table, table->data[idx]);
        // To ensure that searching for a key works, we have to create one coherent data-block.
        // To that end, we try to find next pair in data with a key with hash value <= idx.
        int nextIdx = idx + 1;
        while(nextIdx < table->size && table->data[nextIdx] != NULL) {
            if (std::hash<std::string>{}(table->data[nextIdx]->key) % table->size <= idx) {
                table->data[idx] = table->data[nextIdx];
                table->data[nextIdx] = NULL;
                idx = nextIdx;
            }
            // Repeat process until data-block is coherent again.
            // So either hitting a null entry or the end of the hash table.
            nextIdx++;
        }
    }
}

int custom_hash::get(const Table *table, const char *key) {
    if (const int idx = searchTable(table, key); table->data[idx] == NULL)
        throw std::invalid_argument("key not found");
    else
        return table->data[idx]->value;
}

custom_hash::KVPair *custom_hash::get_last(const Table *table) {
    if (table == NULL) throw std::invalid_argument("table is null");
    if (table->insertionQueue == NULL)
        return NULL;

    return reinterpret_cast<KVPair *>(custom_doubly_linked_list::get_tail(table->insertionQueue));
}
custom_hash::KVPair *custom_hash::get_first(const Table *table) {
    if (table == NULL) throw std::invalid_argument("table is null");
    if (table->insertionQueue == NULL)
        return NULL;

    return reinterpret_cast<KVPair *>(custom_doubly_linked_list::get_head(table->insertionQueue));
}







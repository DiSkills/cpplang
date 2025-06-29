#include <string.h>

#include "hash_table.hpp"

HashTable::HashTable() : size(0), capacity(INIT_HASH_TABLE_SIZE)
{
    max_size = capacity / 4 * 3;
    p = new Item*[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        p[i] = 0;
    }
}

HashTable::~HashTable()
{
    for (unsigned int i = 0; i < capacity; i++) {
        if (p[i]) {
            delete p[i];
        }
    }
    delete[] p;
}

const Value *HashTable::Get(const char *key) const
{
    Item *t = p[Hash(key, capacity)];
    return t && 0 == strcmp(t->GetKey(), key) ? t->GetValue() : 0;
}

unsigned int HashTable::Hash(const char *s, unsigned int capacity)
{
    unsigned int h = 0;
    for (; *s; s++) {
        h = 31 * h + *s;
    }
    return h % capacity;
}

void HashTable::Resize()
{
    unsigned int new_capacity = capacity * 2;
    Item **new_p = new Item*[new_capacity];
    for (unsigned int i = 0; i < new_capacity; i++) {
        new_p[i] = 0;
    }
    for (unsigned int i = 0; i < capacity; i++) {
        if (!p[i]) {
            continue;
        }
        unsigned int h = Hash(p[i]->GetKey(), new_capacity);
        if (new_p[h]) {
            delete new_p[h];
        }
        new_p[h] = p[i];
    }
    delete[] p;
    p = new_p;
    capacity = new_capacity;
    max_size = capacity / 4 * 3;
}

void HashTable::Put(const char *key, Value *value)
{
    unsigned int h = Hash(key, capacity);
    if (!p[h]) {
        if (size >= max_size) {
            Resize();
        }
        p[h] = new Item(key, value);
        size++;
    } else if (0 != strcmp(p[h]->GetKey(), key)) {
        delete p[h];
        p[h] = new Item(key, value);
    } else {
        p[h]->SetValue(value);
    }
}

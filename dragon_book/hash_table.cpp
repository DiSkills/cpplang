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
    Item **t = Position(key, capacity, p);
    return *t ? (*t)->GetValue() : 0;
}

unsigned int HashTable::Hash(const char *s, unsigned int capacity)
{
#ifdef COLLISION
    unsigned int h = 0;
#else
    unsigned long int h = 5381;
#endif
    for (; *s; s++) {
#ifdef COLLISION
        h += *s;
#else
        h = 33 * h + *s;
#endif
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
        if (p[i]) {
            Item **t = Position(p[i]->GetKey(), new_capacity, new_p);
            *t = p[i];
        }
    }
    delete[] p;
    p = new_p;
    capacity = new_capacity;
    max_size = capacity / 4 * 3;
}

void HashTable::Put(const char *key, Value *value)
{
    Item **t = Position(key, capacity, p);
    if (*t) {
        (*t)->SetValue(value);
        return;
    }
    size++;
    *t = new Item(key, value);
    if (size >= max_size) {
        Resize();
    }
}

HashTable::Item **HashTable::Position(const char *key,
        unsigned int capacity, Item **p)
{
    unsigned int h = Hash(key, capacity);
    for (unsigned int i = 0; i < capacity; i++) {
        unsigned int pos = (h + i) % capacity;
        if (!p[pos] || 0 == strcmp(p[pos]->GetKey(), key)) {
            return p + pos;
        }
    }
    return p + h;
}

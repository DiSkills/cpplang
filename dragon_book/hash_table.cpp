#include <string.h>

#include "hash_table.hpp"

HashTable::HashTable() : size(0), capacity(INIT_HASH_TABLE_SIZE)
{
    max_size = capacity / 4 * 3;
    items = new Item*[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        items[i] = 0;
    }
}

HashTable::~HashTable()
{
    for (unsigned int i = 0; i < capacity; i++) {
        if (items[i]) {
            delete items[i];
        }
    }
    delete[] items;
}

const Value *HashTable::Get(const char *key) const
{
    Item *&t = Position(key, items, capacity);
    return t ? t->GetValue() : 0;
}

void HashTable::Put(const char *key, Value *value)
{
    Item *&t = Position(key, items, capacity);
    if (t) {
        t->SetValue(value);
        return;
    }
    size++;
    t = new Item(key, value);
    if (size >= max_size) {
        Resize();
    }
}

void HashTable::Resize()
{
    unsigned int new_capacity = capacity * 2;
    Item **new_items = new Item*[new_capacity];
    for (unsigned int i = 0; i < new_capacity; i++) {
        new_items[i] = 0;
    }
    for (unsigned int i = 0; i < capacity; i++) {
        if (items[i]) {
            Position(items[i]->GetKey(), new_items, new_capacity) = items[i];
        }
    }
    delete[] items;
    items = new_items;
    capacity = new_capacity;
    max_size = new_capacity / 4 * 3;
}

HashTable::Item *&HashTable::Position(const char *key, Item **items,
        unsigned int size)
{
    unsigned int h = Hash(key, size);
    for (unsigned int i = 0; i < size; i++) {
        unsigned int pos = (h + i) % size;
        if (!items[pos] || 0 == strcmp(items[pos]->GetKey(), key)) {
            return items[pos];
        }
    }
    return items[h];
}

unsigned int HashTable::Hash(const char *s, unsigned int size)
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
    return h % size;
}

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
    Item *&t = GetSlot(key);
    return t ? t->GetValue() : 0;
}

void HashTable::Put(const char *key, Value *value)
{
    Item *&t = GetSlot(key);
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
    unsigned int old_capacity = capacity;
    capacity *= 2;
    max_size = capacity / 4 * 3;

    Item **old_items = items;
    items = new Item*[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        items[i] = 0;
    }
    for (unsigned int i = 0; i < old_capacity; i++) {
        if (old_items[i]) {
            GetSlot(old_items[i]->GetKey()) = old_items[i];
        }
    }
    delete[] old_items;
}

HashTable::Item *&HashTable::GetSlot(const char *key) const
{
    unsigned int h = Hash(key, capacity);
    for (unsigned int i = 0; i < capacity; i++) {
        unsigned int pos = (h + i) % capacity;
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

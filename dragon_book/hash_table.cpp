#include <string.h>

#include "hash_table.hpp"

HashTable::HashTable(unsigned int c) : size(0), capacity(c)
{
    max_size = capacity / 4 * 3;
    items = new Item*[capacity];
    removed = new bool[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        items[i] = 0;
        removed[i] = false;
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
    delete[] removed;
}

const Value *HashTable::Get(const char *key) const
{
    unsigned int pos = GetSlot(key, &HashTable::MatchForSearch);
    return items[pos] ? items[pos]->GetValue() : 0;
}

void HashTable::Put(const char *key, Value *value)
{
    unsigned int pos = GetSlot(key, &HashTable::MatchForInsert);
    if (items[pos]) {
        items[pos]->SetValue(value);
        return;
    }
    size++;
    removed[pos] = false;
    items[pos] = new Item(key, value);
    if (size >= max_size) {
        Resize();
    }
}

bool HashTable::Remove(const char *key)
{
    unsigned int pos = GetSlot(key, &HashTable::MatchForSearch);
    if (!items[pos]) {
        return false;
    }
    size--;
    removed[pos] = true;
    delete items[pos];
    items[pos] = 0;
    return true;
}

void HashTable::Resize()
{
    unsigned int old_capacity = capacity;
    capacity *= 2;
    max_size = capacity / 4 * 3;

    Item **old_items = items;
    items = new Item*[capacity];
    delete[] removed;
    removed = new bool[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        items[i] = 0;
        removed[i] = false;
    }
    for (unsigned int i = 0; i < old_capacity; i++) {
        if (old_items[i]) {
            unsigned int pos = GetSlot(old_items[i]->GetKey(),
                    &HashTable::MatchForInsert);
            items[pos] = old_items[i];
        }
    }
    delete[] old_items;
}

bool HashTable::MatchForSearch(unsigned int pos, const char *key) const
{
    return !removed[pos] && MatchForInsert(pos, key);
}

bool HashTable::MatchForInsert(unsigned int pos, const char *key) const
{
    return !items[pos] || 0 == strcmp(items[pos]->GetKey(), key);
}

unsigned int HashTable::GetSlot(const char *key, MatchFunc match) const
{
    unsigned int h = Hash(key, capacity);
    for (unsigned int i = 0; i < capacity; i++) {
        unsigned int pos = (h + i) % capacity;
        if ((this->*match)(pos, key)) {
            return pos;
        }
    }
    return h;
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

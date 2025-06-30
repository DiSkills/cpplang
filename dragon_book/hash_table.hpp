#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#ifndef INIT_HASH_TABLE_SIZE
#define INIT_HASH_TABLE_SIZE 1024
#endif

/**
 * A generic hash table using open addressing with linear probing.
 *  Supports: Put, Get, Remove. It automatically resizes when the load
 *  factor >= 0.75
 * 
 * @tparam Key the type used for keys.
 *   Requirements:
 *     - copy constructor
 *     - destructor
 *     - unsigned int Hash() const
 *     - bool operator==(const Key &) const
 * 
 * @tparam Value the type of values stored in the table.
 *   Requirements:
 *     - copy constructor
 *     - destructor
 *     - assignment (normal)
 */
template <class Key, class Value>
class HashTable {
    unsigned int size, capacity, max_size;
    bool *removed;
    class Item {
        Key key;
        Value value;
    public:
        Item(const Key &k, const Value &v) : key(k), value(v) {}
        const Key &GetKey() const { return key; }
        const Value &GetValue() const { return value; }
        void SetValue(const Value &v) { value = v; }
    };
    Item **items;
public:
    HashTable(unsigned int c = INIT_HASH_TABLE_SIZE);
    ~HashTable();
    const Value *Get(const Key &key) const;
    void Put(const Key &key, const Value &value);
    bool Remove(const Key &key);
private:
    void Resize();

    bool MatchForSearch(unsigned int pos, const Key &key) const;
    bool MatchForInsert(unsigned int pos, const Key &key) const;

    typedef bool (HashTable::*MatchFunc)(unsigned int, const Key &) const;
    unsigned int GetSlot(const Key &key, MatchFunc match) const;
private:
    HashTable(const HashTable &);
    void operator=(const HashTable &);
};

template <class Key, class Value>
HashTable<Key, Value>::HashTable(unsigned int c) : size(0), capacity(c)
{
    max_size = capacity / 4 * 3;
    items = new Item*[capacity];
    removed = new bool[capacity];
    for (unsigned int i = 0; i < capacity; i++) {
        items[i] = 0;
        removed[i] = false;
    }
}

template <class Key, class Value>
HashTable<Key, Value>::~HashTable()
{
    for (unsigned int i = 0; i < capacity; i++) {
        if (items[i]) {
            delete items[i];
        }
    }
    delete[] items;
    delete[] removed;
}

template <class Key, class Value>
const Value *HashTable<Key, Value>::Get(const Key &key) const
{
    unsigned int pos = GetSlot(key, &HashTable::MatchForSearch);
    return items[pos] ? &items[pos]->GetValue() : 0;
}

template <class Key, class Value>
void HashTable<Key, Value>::Put(const Key &key, const Value &value)
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

template <class Key, class Value>
bool HashTable<Key, Value>::Remove(const Key &key)
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

template <class Key, class Value>
void HashTable<Key, Value>::Resize()
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

template <class Key, class Value>
bool HashTable<Key, Value>::MatchForSearch(unsigned int pos,
        const Key &key) const
{
    return !removed[pos] && MatchForInsert(pos, key);
}

template <class Key, class Value>
bool HashTable<Key, Value>::MatchForInsert(unsigned int pos,
        const Key &key) const
{
    return !items[pos] || items[pos]->GetKey() == key;
}

template <class Key, class Value>
unsigned int HashTable<Key, Value>::GetSlot(const Key &key,
        MatchFunc match) const
{
    unsigned int h = key.Hash() % capacity;
    for (unsigned int i = 0; i < capacity; i++) {
        unsigned int pos = (h + i) % capacity;
        if ((this->*match)(pos, key)) {
            return pos;
        }
    }
    return h;
}

#endif

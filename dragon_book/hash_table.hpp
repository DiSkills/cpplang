#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#ifndef INIT_HASH_TABLE_SIZE
#define INIT_HASH_TABLE_SIZE 1024
#endif

typedef int Value;

class HashTable {
    unsigned int size, capacity, max_size;
    bool *removed;
    class Item {
        const char *key;
        Value *value;
    public:
        Item(const char *k, Value *v) : key(k), value(v) {}
        const char *GetKey() const { return key; }
        const Value *GetValue() const { return value; }
        void SetValue(Value *v) { value = v; }
    };
    Item **items;
public:
    HashTable(unsigned int c = INIT_HASH_TABLE_SIZE);
    ~HashTable();
    const Value *Get(const char *key) const;
    void Put(const char *key, Value *value);
    bool Remove(const char *key);
private:
    void Resize();

    bool MatchForSearch(unsigned int pos, const char *key) const;
    bool MatchForInsert(unsigned int pos, const char *key) const;

    typedef bool (HashTable::*MatchFunc)(unsigned int, const char *) const;
    unsigned int GetSlot(const char *key, MatchFunc match) const;

    static unsigned int Hash(const char *s, unsigned int size);
private:
    HashTable(const HashTable &);
    void operator=(const HashTable &);
};

#endif

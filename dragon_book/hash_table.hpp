#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#ifndef INIT_HASH_TABLE_SIZE
#define INIT_HASH_TABLE_SIZE 1024
#endif

typedef int Value;

class HashTable {
    unsigned int size, capacity, max_size;
    class Item {
        const char *key;
        Value *value;
    public:
        Item(const char *k, Value *v) : key(k), value(v) {}
        /* ~Item() { delete value; } */
        const char *GetKey() const { return key; }
        const Value *GetValue() const { return value; }
        void SetValue(Value *v) { /* delete value; */ value = v; }
    };
    Item **items;
public:
    HashTable();
    ~HashTable();
    const Value *Get(const char *key) const;
    void Put(const char *key, Value *value);
private:
    void Resize();
    static Item *&Position(const char *key, Item **items, unsigned int size);
    static unsigned int Hash(const char *s, unsigned int size);
private:
    HashTable(const HashTable &);
    void operator=(const HashTable &);
};

#endif

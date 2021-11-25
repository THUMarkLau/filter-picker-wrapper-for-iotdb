//
// Created by marklau on 2021/11/25.
//

#ifndef FILTERPICKER_VALUECACHE_H
#define FILTERPICKER_VALUECACHE_H


#include <cstdint>
#include <cassert>
#include <cstring>

class ValueCache {
private:
    ValueCache(): currentCount(0), cache(nullptr){
        cache = new int64_t[CACHE_SIZE];
    };
    static ValueCache* instance;
    int32_t currentCount;
    int64_t *cache;
public:
    const static int32_t CACHE_SIZE = 2048;
public:
    ValueCache(ValueCache&)=delete;
    ValueCache& operator=(const ValueCache&)=delete;
    ~ValueCache(){
        // TODO: release the cache buffer
    }
    static ValueCache* getInstance() {
        if (instance == nullptr) {
            instance = new ValueCache();
        }
        return instance;
    }

    void add(int64_t *data, int length);
    int64_t get(int32_t index) const;
    int32_t size() const;
};


#endif //FILTERPICKER_VALUECACHE_H

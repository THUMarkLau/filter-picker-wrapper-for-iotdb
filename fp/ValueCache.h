//
// Created by marklau on 2021/11/25.
//

#ifndef FILTERPICKER_VALUECACHE_H
#define FILTERPICKER_VALUECACHE_H


#include <cstdint>
#include <cassert>
#include <cstring>
#include <unordered_map>

class ValueCache {
private:
    int32_t currentCount;
    int64_t *cache;
public:
    const static int32_t CACHE_SIZE = 2048;
public:
    ValueCache(): currentCount(0), cache(nullptr){
        cache = new int64_t[CACHE_SIZE];
    };
    ValueCache(ValueCache&)=delete;
    ValueCache& operator=(const ValueCache&)=delete;
    ~ValueCache(){
        // TODO: release the cache buffer
    }

    void add(int64_t *data, int length);
    int64_t get(int32_t index) const;
    int32_t size() const;
};

class ValueCacheManager {
private:
    ValueCacheManager() {}
    std::unordered_map<std::string, ValueCache*> cacheMap;
    static ValueCacheManager* instance;
public:
    ValueCacheManager(ValueCacheManager&)=delete;
    ValueCacheManager& operator=(const ValueCacheManager&)=delete;
    ~ValueCacheManager(){
        // release all cache
    }

    static ValueCacheManager* getInstance() {
        if (instance == nullptr) {
            instance = new ValueCacheManager();
        }
        return instance;
    }

    ValueCache* getValueCache(std::string deviceId, std::string channel);
};

#endif //FILTERPICKER_VALUECACHE_H

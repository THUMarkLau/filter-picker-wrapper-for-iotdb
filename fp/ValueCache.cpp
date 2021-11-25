//
// Created by marklau on 2021/11/25.
//

#include "ValueCache.h"

ValueCacheManager* ValueCacheManager::instance = nullptr;

void ValueCache::add(int64_t *data, int length) {
    assert(length == 100);
    if (currentCount + length > CACHE_SIZE) {
        // if we add the new data to cache, the total size is larger than max size
        // move the CACHE-length items forward
        for (int i = 0; i < CACHE_SIZE - length; ++i) {
            *(cache + i) = *(cache + i + length);
        }
        currentCount = CACHE_SIZE - length;
    }

    assert(currentCount <= CACHE_SIZE);

    // add the data to cache
    for(int i = 0; i < length; ++i) {
        *(cache + currentCount + i) = *(data + i);
    }
    currentCount += length;
}

int64_t ValueCache::get(int32_t index) const {
    assert(index <= currentCount);
    return *(cache + index);
}

int32_t ValueCache::size() const {
    return this->currentCount;
}

ValueCache *ValueCacheManager::getValueCache(std::string deviceId, std::string channel) {
    auto iterator = cacheMap.find(deviceId + "." + channel);
    ValueCache* result = nullptr;
    if (iterator != cacheMap.end()) {
        result = iterator->second;
    } else {
        result = new ValueCache();
        cacheMap.insert(std::make_pair(deviceId + "." + channel, result));
    }
    assert(result != nullptr);
    return result;
}

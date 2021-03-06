//
// Created by marklau on 2021/11/25.
//

#include "FilterPickerWrapper.h"


void FilterPickerWrapper::initParams() {
    filterWindow = 300.0 * dt;
    long iFilterWindow = (long) (0.5 + filterWindow * 1000.0);
    if (iFilterWindow > 1) {
        filterWindow = (double) iFilterWindow / 1000.0;
    }

    longTermWindow = 500.0 * dt;
    long ilongTermWindow = (long) (0.5 + longTermWindow * 1000.0);
    if (ilongTermWindow > 1) {
        longTermWindow = (double) ilongTermWindow / 1000.0;
    }

    tUpEvent = 20.0 * dt;
    long itUpEvent = (long) (0.5 + tUpEvent * 1000.0);
    if (itUpEvent > 1) {
        tUpEvent = (double) itUpEvent / 1000.0;
    }
}

void FilterPickerWrapper::pick(DataMessage *message) {
    FilterPicker5_Memory *mem = nullptr;
    PickData **resultList = NULL;
    int pickNum = 0;
    ValueBufferManager* valueBufferManager = ValueBufferManager::getInstance();
    ValueBufferManager::getInstance()->add(message->deviceId, message->channel, int2float(message->values, message->length), message->startTime, message->length);
    float *toPickedData = nullptr;
    int64_t startTime = -1;
    valueBufferManager->getIfEnough(message->deviceId, message->channel, &toPickedData, &startTime);
    if (toPickedData != nullptr) {
        Pick(dt, toPickedData, PROCESS_NUM, filterWindow, longTermWindow, threshold1, threshold2, tUpEvent, &mem,
             useMemory,
             &resultList, &pickNum, "TEST");
        processResult(message->deviceId, message->channel, resultList, pickNum);
    }
    ValueCache* valueCache = ValueCacheManager::getInstance()->getValueCache(message->deviceId, message->channel);
    valueCache->add(getTimeArray(message->startTime, (int32_t) (dt * 1000), PROCESS_NUM), PROCESS_NUM);
}

void
FilterPickerWrapper::processResult(std::string deviceId, std::string channel, PickData **pickList, int listLength) {
    for (int i = 0; i < listLength; ++i) {
        PickData *pickData = *(pickList + i);
        int index = (int) ((pickData->indices[0] + pickData->indices[1]) / 2.0);
        if (index < 0) {
            // index is less than 0 means earthquakes occurs in history data
            int64_t timestamp = searchFromCache(deviceId, channel, index);
            if (timestamp < 0) {
                // cannot search result from history
                std::cout << "Cannot get data from cache, index is " << index << std::endl;
            } else {
                // TODO: write it to session
            }
        } else {
            // TODO: write it to session
        }
    }
}

int64_t FilterPickerWrapper::searchFromCache(std::string deviceId, std::string channel, int index) {
    ValueCache *cache = ValueCacheManager::getInstance()->getValueCache(deviceId, channel);
    int64_t result = 0;
    if (index + cache->size() < 0) {
        // data item is not cached in ValueCache
        result = -1;
    } else {
        result = cache->get(index + cache->size());
    }
    return result;
}

float* int2float(int32_t* data, int32_t length) {
    assert(length > 0);
    float* result = new float[length];
    for(int i = 0; i < length; ++i) {
        result[i] = (float)data[i];
    }
    return nullptr;
}

int64_t* getTimeArray(int64_t startTime, int64_t dt, int32_t count) {
    assert(count > 0);
    int64_t * result = new int64_t[count];
    for(int64_t i = 0; i < count; ++i) {
        // Can we visit array using int64_t ?
        result[i] = startTime + dt * i;
    }
    return result;
}

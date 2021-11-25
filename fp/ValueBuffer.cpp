//
// Created by marklau on 2021/11/25.
//

#include "ValueBuffer.h"

void ValueBufferManager::add(const std::string &deviceId, const std::string &channel, float *data, int64_t startTime) {
    auto valueBufferIterator = bufferMap.find(deviceId + "." + channel);
    ValueBuffer *buffer = nullptr;
    if (valueBufferIterator != bufferMap.end()) {
        buffer = valueBufferIterator->second;
    } else {
        buffer = new ValueBuffer();
        bufferMap.insert(std::make_pair(deviceId + "." + channel, buffer));
    }
    assert(buffer != nullptr);
    buffer->add(data, startTime);
}

void
ValueBufferManager::getIfEnough(const std::string &deviceId, const std::string &channel, float **dataDst,
                                int64_t *startTimeDst) {
    auto valueBufferIterator = bufferMap.find(deviceId + "." + channel);
    if (valueBufferIterator != bufferMap.end()) {
        ValueBuffer *buffer = valueBufferIterator->second;
        buffer->getIfEnough(dataDst, startTimeDst);
    } else {
        // buffer does not exist
        *dataDst = nullptr;
        *startTimeDst = -1;
    }
}

void ValueBuffer::add(float *data, int64_t startTime) {
    // TODO: fill it
}

void ValueBuffer::getIfEnough(float **dataDst, int64_t *startTimeDst) {
    // TODO: fill it
}

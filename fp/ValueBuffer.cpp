//
// Created by marklau on 2021/11/25.
//

#include "ValueBuffer.h"

ValueBufferManager* ValueBufferManager::instance = nullptr;

void ValueBufferManager::add(const std::string &deviceId, const std::string &channel, float *data, int64_t startTime, int32_t length) {
    auto valueBufferIterator = bufferMap.find(deviceId + "." + channel);
    ValueBuffer *buffer = nullptr;
    if (valueBufferIterator != bufferMap.end()) {
        buffer = valueBufferIterator->second;
    } else {
        buffer = new ValueBuffer();
        bufferMap.insert(std::make_pair(deviceId + "." + channel, buffer));
    }
    assert(buffer != nullptr);
    buffer->add(data, startTime, length);
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

void ValueBuffer::add(float *data, int64_t startTime, int32_t length) {
    assert(length > 0);
    assert(currentCount + length <= MAX_SIZE);
    std::memcpy(dataBuffer + currentCount, data, length);
    currentCount += length;
    if (this->startTime == 0) {
        this->startTime = startTime;
    }
}

void ValueBuffer::getIfEnough(float **dataDst, int64_t *startTimeDst) {
    assert(dataDst != nullptr);
    assert(startTimeDst != nullptr);
    if (currentCount >= 100) {
        std::memset(*dataDst, 0, 100 * sizeof(float));
        std::memcpy(*dataDst, dataBuffer, 100 * sizeof(float));
        *startTimeDst = startTime;
        // this.startTime increase 10 * 100 milliseconds
        this->startTime = startTime + 10 * 100;
        // move the left data forward
        for(int i = 0; i < currentCount - 100; ++i) {
            dataBuffer[i] = dataBuffer[i + 100];
        }
        currentCount -= 100;
    } else {
        *dataDst = nullptr;
        *startTimeDst = -1;
    }
}

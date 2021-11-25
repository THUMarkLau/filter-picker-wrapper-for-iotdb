//
// Created by marklau on 2021/11/25.
//

#ifndef FILTERPICKER_VALUEBUFFER_H
#define FILTERPICKER_VALUEBUFFER_H


#include <cstdint>
#include <string>
#include <cassert>
#include <cstring>
#include <unordered_map>

class ValueBufferManager;

class ValueBuffer {
private:
    int32_t currentCount;
    float* dataBuffer;
    int64_t startTime;
protected:
    ValueBuffer():currentCount(0), startTime(-1) {
        dataBuffer = new float[MAX_SIZE];
    };
public:
    const int32_t MAX_SIZE = 256;
    static const int32_t TARGET_SIZE = 100;
    void add(float* data, int64_t startTime, int32_t length);
    void getIfEnough(float** dataDst, int64_t* startTimeDst);
    friend ValueBufferManager;
};

class ValueBufferManager {
private:
    ValueBufferManager() {}
    static ValueBufferManager* instance;
    std::unordered_map<std::string, ValueBuffer*> bufferMap;
public:
    ValueBufferManager(ValueBufferManager&)=delete;
    ValueBufferManager& operator=(const ValueBufferManager&)=delete;
    ~ValueBufferManager() {
        // TODO: release buffer
    }
    static ValueBufferManager* getInstance() {
        if (instance == nullptr) {
            instance = new ValueBufferManager();
        }
        return instance;
    }

    void add(const std::string& deviceId, const std::string& channel, float* data, int64_t startTime, int32_t length);

    void getIfEnough(const std::string& deviceId, const std::string& channel, float** dataDst, int64_t* startTimeDst);
};

#endif //FILTERPICKER_VALUEBUFFER_H

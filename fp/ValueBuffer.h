//
// Created by marklau on 2021/11/25.
//

#ifndef FILTERPICKER_VALUEBUFFER_H
#define FILTERPICKER_VALUEBUFFER_H


#include <cstdint>
#include <string>

class ValueBuffer {
private:
    ValueBuffer() {}
    static ValueBuffer* instance;
public:
    static const int32_t TARGET_SIZE = 100;
    ValueBuffer(ValueBuffer&)=delete;
    ValueBuffer& operator=(const ValueBuffer&)=delete;
    ~ValueBuffer() {
        // TODO: release buffer
    }
    static ValueBuffer* getInstance() {
        if (instance == nullptr) {
            instance = new ValueBuffer();
        }
        return instance;
    }

    void add(std::string deviceId, std::string channel, float* data, int64_t startTime);

    void getIfEnough(std::string deviceId, std::string channel, float** dataDst, int64_t* startTimeDst);
};


#endif //FILTERPICKER_VALUEBUFFER_H

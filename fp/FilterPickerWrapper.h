//
// Created by marklau on 2021/11/25.
//

#ifndef FILTERPICKER_FILTERPICKERWRAPPER_H
#define FILTERPICKER_FILTERPICKERWRAPPER_H

#include <cstdint>
#include <string>
#include <iostream>
#include "FilterPicker5.h"
#include "PickData.h"
#include "ValueCache.h"
#include "ValueCache.h"
#include "ValueBuffer.h"

struct DataMessage {
    std::string deviceId;
    std::string channel;
    int64_t startTime;
    int32_t *values;
    int32_t length;
};

class FilterPickerWrapper {
public:
    double longTermWindow = 10.0;
    double threshold1 = 8.0;
    double threshold2 = 8.0;
    double tUpEvent = 0.5;
    double filterWindow = 4.0;
    double dt = 0.01;
    bool useMemory = true;
    const int PROCESS_NUM = 100;

    FilterPickerWrapper()= default;

    /**
     * Init parameters for FilterPicker
     */
    void initParams();

    /**
     * run filter picker, if any data is picked, picked timestamp will be written to IoTDB
     */
    void pick(DataMessage* message);

    void processResult(std::string deviceId, std::string channel, PickData** pickList, int listLength);

    int64_t searchFromCache(std::string deviceId, std::string channel, int index);
};

float* int2float(int32_t*);

int64_t* getTimeArray(int64_t startTime, int64_t dt, int32_t count);

#endif //FILTERPICKER_FILTERPICKERWRAPPER_H

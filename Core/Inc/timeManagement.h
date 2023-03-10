#ifndef DOODLEJUMP_TIMEMANAGEMENT_H
#define DOODLEJUMP_TIMEMANAGEMENT_H

#include "requisite.h"

typedef struct {
    RTC_DateTypeDef dateVar;
    RTC_TimeTypeDef timeVar;
} __attribute__((aligned(32))) dateTimeType;

extern dateTimeType dateTime;

dateTimeType getDateTime();

void updateDateTime();



#endif

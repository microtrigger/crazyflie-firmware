#ifndef UTILIZATION_H_
#define UTILIZATION_H_

#include <stdbool.h>

#define UTILIZATION_UPDATE_RATE 100
#define MEMORY_UPDATE_RATE_DIVIDER  50

void utilizationInit(void);
bool utilizationTest(void);
void taskSwitchedIn(signed char* pcTaskName);
void taskSwitchedOut(signed char* pcTaskName);

void utilizationTask(void *param);


#endif /* UTILIZATION_H_ */

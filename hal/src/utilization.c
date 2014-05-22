#include "stm32f10x_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "log.h"
#include "param.h"
#include "usec_time.h"
#include "system.h"
#include "utilization.h"

static bool isInit;
static uint16_t freeMemory = 0;

// CPU utilization meassurement
static float idleTime = 0.;
static float cpuUsage = 30.;
static uint32_t duration = 0;
// static uint64_t old = 0;
static uint64_t switchedIn = 0;

static float updateLPF     = 0.88;

static uint32_t test[80];

// Params for altitude hold
PARAM_GROUP_START(utilization)
PARAM_ADD(PARAM_FLOAT, updateLPF, &updateLPF)
PARAM_GROUP_STOP(utilization)


void taskSwitchedIn(signed char* pcTaskName) {
    int count = 0;

    while (pcTaskName[count]) {
        count++;
    }

    if (count == 4 && pcTaskName[0] == 'I' && 
                      pcTaskName[1] == 'D' && 
                      pcTaskName[2] == 'L' && 
                      pcTaskName[3] == 'E') {
        switchedIn = usecTimestamp();
    }
}

void taskSwitchedOut(signed char* pcTaskName) {
    int count = 0;

    while (pcTaskName[count]) {
        count++;
    }

    if (count == 4 && pcTaskName[0] == 'I' && 
                      pcTaskName[1] == 'D' && 
                      pcTaskName[2] == 'L' && 
                      pcTaskName[3] == 'E') {
        duration += usecTimestamp() - switchedIn;
    }
}


void utilizationInit(void) {
    if (isInit) {
        return;
    }

    xTaskCreate(utilizationTask, (const signed char * const)"utility",
                2*configMINIMAL_STACK_SIZE, NULL, /*Piority*/3, NULL);

    isInit = TRUE;
}

bool utilizationTest(void) {
    return isInit;
}

void utilizationTask(void* param) {
    uint32_t lastWakeTime;
    uint32_t memoryMeasurementCounter = 0;
    //Wait for the system to be fully started to start utilization loop
    systemWaitStart();
    lastWakeTime = xTaskGetTickCount();

    {
    	int i;
    	for (i=0; i<80; ++i){
    		test[i]=i;
    	}

    }

    while (1) {
        vTaskDelayUntil(&lastWakeTime, F2T(UTILIZATION_UPDATE_RATE)); // 100Hz
        idleTime = duration / 10000.;
        cpuUsage = cpuUsage * updateLPF + (1-idleTime)*100.f*(1.f-updateLPF) ;
        duration = 0;
        if (++memoryMeasurementCounter >= MEMORY_UPDATE_RATE_DIVIDER) { // 2Hz
            // TODO
            freeMemory = xPortGetFreeHeapSize();
            memoryMeasurementCounter = 0;
        }
    }
}

LOG_GROUP_START(utilization)
LOG_ADD(LOG_FLOAT, idle, &idleTime)
LOG_ADD(LOG_FLOAT, cpuUsage, &cpuUsage)
LOG_ADD(LOG_INT16, freeMemory, &freeMemory)
LOG_GROUP_STOP(utilization)




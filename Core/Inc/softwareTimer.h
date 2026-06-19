#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#include <stdint.h>

typedef struct
{
    uint32_t startMs;
    uint32_t periodMs;
    uint8_t running;
} SoftwareTimer_t;

void SoftwareTimer_Start(SoftwareTimer_t* timer, uint32_t periodMs);
void SoftwareTimer_Restart(SoftwareTimer_t* timer);
void SoftwareTimer_Stop(SoftwareTimer_t* timer);
uint8_t SoftwareTimer_IsRunning(const SoftwareTimer_t* timer);
uint32_t SoftwareTimer_GetElapsedMs(const SoftwareTimer_t* timer);
uint8_t SoftwareTimer_IsExpired(const SoftwareTimer_t* timer);
uint8_t SoftwareTimer_CheckAndRestart(SoftwareTimer_t* timer);
uint32_t SoftwareTimer_GetPhaseMs(uint32_t periodMs);

#endif /* SOFTWARE_TIMER_H */

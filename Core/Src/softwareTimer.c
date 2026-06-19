#include "software_timer.h"
#include "main.h"

void SoftwareTimer_Start(SoftwareTimer_t* timer, uint32_t periodMs)
{
    if (timer == 0)
    {
        return;
    }

    timer->startMs = HAL_GetTick();
    timer->periodMs = periodMs;
    timer->running = 1U;
}

void SoftwareTimer_Restart(SoftwareTimer_t* timer)
{
    if (timer == 0)
    {
        return;
    }

    timer->startMs = HAL_GetTick();
    timer->running = 1U;
}

void SoftwareTimer_Stop(SoftwareTimer_t* timer)
{
    if (timer == 0)
    {
        return;
    }

    timer->running = 0U;
}

uint8_t SoftwareTimer_IsRunning(const SoftwareTimer_t* timer)
{
    if (timer == 0)
    {
        return 0U;
    }

    return timer->running;
}

uint32_t SoftwareTimer_GetElapsedMs(const SoftwareTimer_t* timer)
{
    if ((timer == 0) || (timer->running == 0U))
    {
        return 0U;
    }

    return (uint32_t)(HAL_GetTick() - timer->startMs);
}

uint8_t SoftwareTimer_IsExpired(const SoftwareTimer_t* timer)
{
    if ((timer == 0) || (timer->running == 0U))
    {
        return 0U;
    }

    return (SoftwareTimer_GetElapsedMs(timer) >= timer->periodMs) ? 1U : 0U;
}

uint8_t SoftwareTimer_CheckAndRestart(SoftwareTimer_t* timer)
{
    if (SoftwareTimer_IsExpired(timer) == 0U)
    {
        return 0U;
    }

    SoftwareTimer_Restart(timer);
    return 1U;
}

uint32_t SoftwareTimer_GetPhaseMs(uint32_t periodMs)
{
    if (periodMs == 0U)
    {
        return 0U;
    }

    return (uint32_t)(HAL_GetTick() % periodMs);
}

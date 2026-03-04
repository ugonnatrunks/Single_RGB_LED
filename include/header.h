#ifndef _DEFINES_H
#define _DEFINES_H

#include <zephyr/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h> 
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/gpio.h>

#define MY_PRIORITY                 5
#define MY_STACK_SIZE               1024
#define NUMBER_OF_CHANNELS          3
#define DEADZONE_THRESHOLD          25
#define MAX_RAW_READ                4095.0f
#define PWM_PERIOD                  20000000.0f

void peripheral_thread_entry(void *p1, void *p2, void *p3);

extern struct k_mutex my_mutex;
extern uint16_t last_stable_buf[];

// -----------------------------
// Logic Levels and Booleans
// -----------------------------
#define ON              (1u)
#define OFF             (0u)

#define TRUE            (1u)
#define FALSE           (0u)

#define ENABLED         (1u)
#define DISABLED        (0u)

#define HIGH            (1u)
#define LOW             (0u)
    
// -----------------------------
// Timing Constants
// -----------------------------
#define ONE_SECOND          (1000u)
#define HALF_SECOND         (500u)
#define QUARTER_SECOND      (250u)

#define MS_TO_NS(ms)        ((uint64_t)(ms) * 1000000ULL);
#define PWM_PERIOD_NS       10000000

#endif


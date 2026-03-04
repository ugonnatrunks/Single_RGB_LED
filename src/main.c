#include "header.h"
// [0] For Red, [1] For Green, [2] For Green
static const struct pwm_dt_spec pwm_led[NUMBER_OF_CHANNELS] = {
        PWM_DT_SPEC_GET(DT_NODELABEL(pwm_led0)),
        PWM_DT_SPEC_GET(DT_NODELABEL(pwm_led1)),
        PWM_DT_SPEC_GET(DT_NODELABEL(pwm_led2)),
};

static uint8_t idx, err;
static uint32_t pulse_width[3];
float percent_PW[3];

int main (void) {
        for (idx = 0; idx < NUMBER_OF_CHANNELS; idx++) {
                if (!pwm_is_ready_dt(&pwm_led[idx])) {
                        printk("PWM %d Module is not ready!\n", idx);
                }
        }

        while (true) {
                k_mutex_lock(&my_mutex, K_FOREVER);
                
                for (idx = 0; idx < NUMBER_OF_CHANNELS; idx++) {
                        percent_PW[idx] = last_stable_buf[idx] / MAX_RAW_READ;
                        pulse_width[idx] = percent_PW[idx] * PWM_PERIOD;
                        err = pwm_set_dt(&pwm_led[idx], PWM_PERIOD, pulse_width[idx]);
                        if (err < 0) {
                                printk("Error setting Pulse Width for Module: %d.", err);
                        };
                }
                printk("\033[2;1HActuated: Channel 1 Raw = %d, Channel 2 Raw = %d, Channel 4 Raw = %d.", last_stable_buf[0], last_stable_buf[1], last_stable_buf[2]);
                k_mutex_unlock(&my_mutex);
                k_msleep(100);
        }
        return 0;
}
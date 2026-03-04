#include "header.h"
K_THREAD_DEFINE(pot_thread_id, MY_STACK_SIZE, peripheral_thread_entry, NULL, NULL, NULL, MY_PRIORITY, 0, 0);
uint16_t last_stable_buf[NUMBER_OF_CHANNELS] = {0,0,0};
struct k_mutex my_mutex;

void peripheral_thread_entry(void *p1, void *p2, void *p3) {

k_mutex_init(&my_mutex);

static uint8_t idx;
int16_t buf[NUMBER_OF_CHANNELS];
int16_t diff[NUMBER_OF_CHANNELS];

static const struct adc_dt_spec adc_channel[NUMBER_OF_CHANNELS] = {
    ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 0),
    ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 1),
    ADC_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), 2),
};

static const struct adc_dt_spec* p_adc_channel[NUMBER_OF_CHANNELS] = {
    &adc_channel[0], &adc_channel[1], &adc_channel[2]
};

struct adc_sequence sequence = {
        .channels = 0b10110,
        .buffer = &buf,
	    .buffer_size = sizeof(buf),
        .calibrate = true,
        .resolution  = 12,
};   

for (idx = 0; idx < NUMBER_OF_CHANNELS; idx++) {
        if (!adc_is_ready_dt(p_adc_channel[idx])) {
            printk("ADC channel %d is not ready.", idx+1);
            return;
        }

        if (adc_channel_setup_dt(p_adc_channel[idx]) != 0) {
            printk("Could not setup channel %d.", idx+1);
            return;
        }
}  

while (true) {
        int err = (adc_read_dt(p_adc_channel[0], &sequence));
        if (err != 0) {
            printk("Could not read channel! Error Code %d.", err);
            return;
        }

        k_mutex_lock(&my_mutex, K_FOREVER);
        for (idx = 0; idx < NUMBER_OF_CHANNELS; idx++) {
                diff[idx] = abs(buf[idx] - last_stable_buf[idx]);
                if (diff[idx] > DEADZONE_THRESHOLD) {
                        last_stable_buf[idx] = buf[idx];
                        if (last_stable_buf[idx] < 12) {
                            last_stable_buf[idx] = 0;
                        } 
                        if (last_stable_buf[idx] > 3430) {
                            last_stable_buf[idx] = MAX_RAW_READ;
                        }
                }
        }
        printk("\033[1;1HSent: Channel 1 Raw = %d, Channel 2 Raw = %d, Channel 4 Raw = %d.", last_stable_buf[0], last_stable_buf[1], last_stable_buf[2]);
        k_mutex_unlock(&my_mutex);
        k_msleep(100);
        }
    return;
}

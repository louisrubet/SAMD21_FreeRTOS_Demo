#include <FreeRTOS.h>
#include <task.h>

static TaskHandle_t xDemotask;

#include "driver_init.h"

static void demo_task(void *p)
{
    gpio_set_pin_direction(GPIO(GPIO_PORTA, 22), GPIO_DIRECTION_OUT);
    gpio_set_pin_level(GPIO(GPIO_PORTA, 22), false);
    for(;;)
    {
        gpio_toggle_pin_level(GPIO(GPIO_PORTA, 22));
        vTaskDelay(1000);
    }
}

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    system_init();

    xTaskCreate(demo_task, "Demo", configMINIMAL_STACK_SIZE, NULL, 1, xDemotask);

    vTaskStartScheduler();
}

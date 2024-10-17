#include <FreeRTOS.h>
#include <task.h>

#include "driver_init.h"
// #include "cdcdf_acm.h"
// #include "composite_desc.h"

static void demo_task(void *p)
{
    gpio_set_pin_direction(GPIO(GPIO_PORTA, 22), GPIO_DIRECTION_OUT);
    gpio_set_pin_level(GPIO(GPIO_PORTA, 22), false);
    for(;;)
    {
        for(int i = 0; i < 2; i++)
        {
            gpio_set_pin_level(GPIO(GPIO_PORTA, 22), true);
            vTaskDelay(60);
            gpio_set_pin_level(GPIO(GPIO_PORTA, 22), false);
            vTaskDelay(440);
        }
        // gpio_toggle_pin_level(GPIO(GPIO_PORTA, 22));
        vTaskDelay(1000);
    }
}

#if 0
/* Max LUN number */
#define CONF_USB_MSC_MAX_LUN 0

#if 0
#define COMPOSITE_DEV_DESC                                                                                             \
	USB_DEV_DESC_BYTES(CONF_USB_COMPOSITE_BCDUSB,                                                                      \
	                   0xEF,                                                                                           \
	                   0x02,                                                                                           \
	                   0x01,                                                                                           \
	                   CONF_USB_COMPOSITE_BMAXPKSZ0,                                                                   \
	                   CONF_USB_COMPOSITE_IDVENDER,                                                                    \
	                   CONF_USB_COMPOSITE_IDPRODUCT,                                                                   \
	                   CONF_USB_COMPOSITE_BCDDEVICE,                                                                   \
	                   CONF_USB_COMPOSITE_IMANUFACT,                                                                   \
	                   CONF_USB_COMPOSITE_IPRODUCT,                                                                    \
	                   CONF_USB_COMPOSITE_ISERIALNUM,                                                                  \
	                   CONF_USB_COMPOSITE_BNUMCONFIG)

#define COMPOSITE_CFG_DESC                                                                                             \
	USB_CONFIG_DESC_BYTES(CONF_USB_COMPOSITE_TOTAL_LEN,                                                                \
	                      CONF_USB_COMPOSITE_IFC_NUM,                                                                  \
	                      CONF_USB_COMPOSITE_BCONFIGVAL,                                                               \
	                      CONF_USB_COMPOSITE_ICONFIG,                                                                  \
	                      CONF_USB_COMPOSITE_BMATTRI,                                                                  \
	                      CONF_USB_COMPOSITE_BMAXPOWER)

#define COMPOSITE_IFACE_DESCES                                                                                         \
	CONF_CDC_ACM_IFC_DESC                                                                                              \
	CONF_HID_MOUSE_IFC_DESC                                                                                            \
	CONF_HID_KEYBOARD_IFC_DESC                                                                                         \
	CONF_HID_GENERIC_IFC_DESC                                                                                          \
	CONF_MSC_IFC_DESC

#define COMPOSITE_STR_DESCESS                                                                                          \
	CONF_USB_COMPOSITE_LANGID_DESC                                                                                     \
	CONF_USB_COMPOSITE_IMANUFACT_STR_DESC                                                                              \
	CONF_USB_COMPOSITE_IPRODUCT_STR_DESC                                                                               \
	CONF_USB_COMPOSITE_ISERIALNUM_STR_DESC                                                                             \
	CONF_USB_COMPOSITE_ICONFIG_STR_DESC
#endif

#define COMPOSITE_DESCES_LS_FS COMPOSITE_DEV_DESC, COMPOSITE_CFG_DESC, COMPOSITE_IFACE_DESCES COMPOSITE_STR_DESCESS

static uint8_t multi_desc_bytes[] = {
    /* Device descriptors and Configuration descriptors list. */
    COMPOSITE_DESCES_LS_FS};
static struct usbd_descriptors multi_desc[] = {{multi_desc_bytes, multi_desc_bytes + sizeof(multi_desc_bytes)}};
static uint8_t ctrl_buffer[64];

static void usb_cdc_task(void *p)
{
    /* usb stack init */
    usbdc_init(ctrl_buffer);
    cdcdf_acm_init();

	usbdc_start(multi_desc);
	usbdc_attach();

    for(;;)
    {
        vTaskDelay(1000);
    }
}

#endif

static TaskHandle_t xDemotask;
// static TaskHandle_t xUSBCDCtask;

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    system_init(); // lru

    xTaskCreate(demo_task, "Demo", configMINIMAL_STACK_SIZE, NULL, 1, xDemotask);
    // xTaskCreate(usb_cdc_task, "USB_CDC", configMINIMAL_STACK_SIZE, NULL, 1, xUSBCDCtask);

    vTaskStartScheduler();
}

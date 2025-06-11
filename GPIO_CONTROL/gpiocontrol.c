/*GPIO LKM*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/gpio/consumer.h>

static struct gpio_desc *led, *button;

#define IO_LED 21
#define IO_BUTTON 20

#define IO_OFFSET 512

/*Meta info*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Simple Gpio control linux kernel module");

/*init function*/
static int __init my_init(void)
{
        int status;

        led = gpio_to_desc(IO_LED + IO_OFFSET);
        if(!led)
        {
                printk("gpiocontrol - Error getting pin 21\n");
                return -ENODEV;
        }
        button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
        if(!button)
        {
                printk("gpiocontrol - Error getting pin 20\n");
                return -ENODEV;
        }

        status = gpiod_direction_output(led, 0);
        if(status) {
                printk("gpiocontrol - Error setting pin 20\n");
                return -ENODEV;
        }
        status = gpiod_direction_input(button);
        if(status) {
                printk("gpiocontrol - Error setting pin 21\n");
                return -ENODEV;
        }

        gpiod_set_value(led,1);
        printk("gpiocontrol - Button is %spressed\n", gpiod_get_value(button) ? "" : "not ");

        return 0;
}

/*exit function */
static void __exit my_exit(void)
{
        gpiod_set_value(led,0);
        printk("Goodbye, Creata!");
}

module_init(my_init);
module_exit(my_exit);

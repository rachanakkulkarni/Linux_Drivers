#include<linux/module.h>
#include<linux/init.h>

static int __init my_init(void)
{
        printk("Hello, World!\n");
        return 0;
}

static void __exit my_exit(void)
{
        printk("Goodbye!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Hello World Linux Kernel Module");

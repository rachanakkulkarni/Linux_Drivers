/*hello world LKM*/
#include<linux/module.h>
#include<linux/init.h>

/*Meta info*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Hello World Linux Kernel Module");

/*init function*/
static int __init my_init(void)
{
        printk("Hello, Creata!\n");
        return 0;
}

/*exit function*/
static void __exit my_exit(void)
{
        printk("Goodbye, Creata!\n");
}

module_init(my_init);
module_exit(my_exit);

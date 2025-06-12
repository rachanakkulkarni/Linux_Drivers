/*kernel logs LKM*/
#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Linux Kernel Module");

/*init function*/
static int __init my_init(void)
{
        printk(KERN_INFO "kernel_logs - This is an info\n");

        printk(KERN_WARNING "kernel_logs - This is a warning\n");
        printk(KERN_ALERT "kernel_logs - This is an alert\n");
        printk(KERN_DEBUG "kernel_logs - Debug: %d\n",42);
        return 0;
}

/*exit function*/
static void __exit my_exit(void)
{
        pr_emerg("kernel_logs - Module removed");
        pr_err("kernel_logs - Error");
        pr_info("kernel_logs - the last info...\n");
}

module_init(my_init);
module_exit(my_exit);

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachana Kulkarni");
MODULE_DESCRIPTION("Read Write  - LKM");

static int major;
static char text[64];

static ssize_t my_read(struct file *filep, char __user *user_buf, size_t len, loff_t *off)
{
        int not_copied, delta, to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

        pr_info("read_write - Read was called, we want to read %ld bytes, but  only copying %d bytes. The offset is %lld\n", len, to_copy, *off);

        if (*off >= sizeof(text))
                return 0;

        not_copied = copy_to_user(user_buf, &text[*off], to_copy);
        delta = to_copy - not_copied;
        if (not_copied)
                pr_warn("read_write - Could only copy %d bytes\n", delta);

        *off += delta;

        return delta;
}

static ssize_t my_write(struct file *filep, const char __user *user_buf, size_t len, loff_t *off)
{
        int not_copied, delta, to_copy = (len + *off) < sizeof(text) ? len : (sizeof(text) - *off);

        pr_info("read_write - Write was called, we want to write %ld bytes, but only writing %d bytes. The offset is %lld\n", len, to_copy, *off);

        if (*off >= sizeof(text))
                return 0;

        not_copied = copy_from_user(&text[*off], user_buf, to_copy);
        delta = to_copy - not_copied;
        if (not_copied)
                pr_warn("read_write - Could only copy %d bytes\n", delta);

        *off += delta;
        return delta;
}

static struct file_operations fops = {
        .read = my_read,
        .write = my_write
};

static int __init my_init(void)
{
        major = register_chrdev(0, "char_dev", &fops);
        if (major < 0) {
                pr_err("read_write - Error registering character device\n");
                return major;
        }
        printk("read_write - Device registered, Major Device NO: %d\n", major);
        return 0;
}

static void __exit my_exit(void)
{
        unregister_chrdev(major, "char_dev");
        printk("Goodbye, Creata!\n");
}

module_init(my_init);
module_exit(my_exit);

#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/file.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

#define PROC_DIRNAME "myproc_dir"
#define PROC_FILENAME "myproc_file"

static struct proc_dir_entry *proc_dir;
static struct proc_dir_entry *proc_file;

static ssize_t custom_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *ppos) {
    //custom write 함수 구현부
		printk(KERN_ALERT "Write File!\n");
}

static const struct file_operations custom_proc_fops = {
    .owner = THIS_MODULE,
    .write = custom_write,
};

static int __init my_module_init(void) {
    printk(KERN_ALERT "module up...\n");
    proc_dir = proc_mkdir(PROC_DIRNAME, NULL);
    proc_file = proc_create(PROC_FILENAME, 0600, proc_dir, &custom_proc_fops);
    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_ALERT "module down...\n");
    return;
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_AUTHOR("Jin&Cho");
MODULE_DESCRIPTION("System Programming");
MODULE_LICENSE("GPL");
MODULE_VERSION("NEW");
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

// root@asad-VirtualBox:/home/asad/kerDev# insmod code.ko myInt=5 myIntArray=-1 myShortArray=-1,-2
int count;

//////////////////////////////////////////////////// MODULE PARAMS FOLLOW /////////////////////////////////////////////////
int myInt=3;
module_param(myInt, int, 0);

int myIntArray[2];
module_param_array(myIntArray, int, NULL, 0);

short myShortArray[4];
module_param_array(myShortArray, short, &count, 0);

int value;
module_param(value, int, S_IWUSR|S_IRUSR);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
												
static int notify_param(const char* val, const struct kernel_param *kp);

dev_t dev = MKDEV(235, 0);

const struct kernel_param_ops my_param_ops = {
	.set = &notify_param,
	.get = &param_get_int
};

int cb_value;
module_param_cb(cb_value, &my_param_ops, &cb_value, S_IWUSR|S_IRUSR);

static int __init my_init(void){
	int i;
	
	register_chrdev_region(dev, 1, "code_dev");
	printk(KERN_INFO "Hello Virtual World, I am Kernel Rick.\n");
	printk(KERN_INFO "Major: %d, Minor %d\n", MAJOR(dev), MINOR(dev));
	
	printk(KERN_INFO "count: %d\n", count);
	printk(KERN_INFO "myInt: %d\n", myInt);
	printk(KERN_INFO "value: %d\n", value);
	
	for(i=0; i < sizeof myIntArray / sizeof(int); i++)
		printk(KERN_INFO "myIntArray[%d]: %d\n", i, myIntArray[i]);
	
	for(i=0; i < sizeof myShortArray / sizeof(short); i++)
		printk(KERN_INFO "myShortArray[%d]: %d\n", i, myShortArray[i]);
		
	return 0;
}

static void __exit my_exit(void){
	printk(KERN_NOTICE "Kernel Rick instance dying.\nRecommend making new allegiances with Galactic Federation.\n");
	return;
}

static int notify_param(const char* val, const struct kernel_param *kp){
	param_set_int(val, kp);
	printk(KERN_INFO "Some Change in value detected. %d\n", cb_value);
	return 0;
}

/************************************************ EXPOSURE MACROS FOLLOW ************************************************/
MODULE_LICENSE("GPL");

module_init(my_init);
module_exit(my_exit);

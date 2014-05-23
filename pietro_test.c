#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define PRINTPERROR printk(KERN_ERR "Error at %s %s %d", __FILE__, __FUNCTION__, __LINE__);

static void *buffer_dma;

static int __init pietrodma_init(void)
{
   printk(KERN_DEBUG "Initalizing %s\n", KBUILD_MODNAME);
   buffer_dma = (void *) __get_free_pages(GFP_ATOMIC | __GFP_DMA, 3);
   if (!buffer_dma) {
   	PRINTPERROR
	return -ENOMEM;
   }
   /* Register a net device */
   /* IRQ handler */
   /* start kthread */
   return 0;
}


void pietrodma_exit(void)
{
  printk(KERN_ALERT "Goodbye world 1.\n");
}

MODULE_LICENSE("GPL");
module_init(pietrodma_init);
module_exit(pietrodma_exit);


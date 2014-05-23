#define LINUX

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>

#define DNAME "pdmahwsim"


static int pdmahwsim_open(struct net_device *net)
{
	return 0;
}

static int pdmahwsim_stop(struct net_device *net)
{
	return 0;
}

static int pdmahwsim_xmit(struct sk_buff *skb, struct net_device *net)
{
	return 0;
}

static const struct net_device_ops pdmshwsim_ops = {
	.ndo_open = pdmahwsim_open,
	.ndo_stop = pdmahwsim_stop,
	.ndo_start_xmit = pdmahwsim_xmit,
};

static void pdmahwsim_init(struct net_device *net)
{
	ether_setup(net);
	net->netdev_ops = &pdmshwsim_ops;
	printk(KERN_DEBUG "Initalizing %s\n", __FUNCTION__);
	return;

}

/* Split in two files */
static void *buffer_dma;
static struct net_device *pdmahw_d;
static int __init pdmahwsim_init_module(void)
{
	int result;
	printk(KERN_DEBUG "Initalizing %s\n", KBUILD_MODNAME);
	buffer_dma = (void *) __get_free_pages(GFP_ATOMIC | __GFP_DMA, 3);
	if (!buffer_dma) {
		printk(KERN_ERR "%s %s %d", __FILE__, __FUNCTION__, __LINE__);
		return -ENOMEM;
	}
	pdmahw_d = alloc_netdev(64, "pdmahwsim%d", pdmahwsim_init);
	if (!pdmahw_d)
		return ENODEV;
	if ((result = register_netdev(pdmahw_d))) {
		printk(KERN_ERR "%s %s %d", __FILE__, __FUNCTION__, __LINE__);
		return result;
	}
	/* IRQ handler */
	/* start kthread */
	return 0;
}


void pdmahwsim_exit_module(void)
{
	unregister_netdev(pdmahw_d);
	free_netdev(pdmahw_d);
	printk(KERN_ALERT "Goodbye %s\n", KBUILD_MODNAME);
}

MODULE_LICENSE("GPL");
module_init(pdmahwsim_init_module);
module_exit(pdmahwsim_exit_module);


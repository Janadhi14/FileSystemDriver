#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x4cf819e6, "module_layout" },
	{ 0xf9418c06, "param_ops_int" },
	{ 0x37a0cba, "kfree" },
	{ 0x15659e9d, "device_destroy" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xb3f0559, "class_destroy" },
	{ 0x70eb7a97, "device_create" },
	{ 0x11eb121f, "cdev_del" },
	{ 0x52ea150d, "__class_create" },
	{ 0x646eac6, "cdev_add" },
	{ 0xd90cd7e6, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x92997ed8, "_printk" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xb8b9f817, "kmalloc_order_trace" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0xcf2a6966, "up" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6bd0e573, "down_interruptible" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "37B2E3CC39BD4EE94EA1A0A");

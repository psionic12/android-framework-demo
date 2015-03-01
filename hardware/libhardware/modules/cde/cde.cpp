#include <hardware/hardware.h>
#include <fcntl.h>
#include <errno.h>
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <hardware/cde.h>
// #include <android/log.h>

#define DEVICE_NAME "/dev/char_device_example"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "libnav", __VA_ARGS__) 




static int cde_device_open(const struct hw_module_t* module, const char* id, struct hw_device_t** device);
static int cde_device_close(struct hw_device_t* device);

static int read_mem(struct cde_device_t* dev, char* mem);
static int write_mem(struct cde_device_t* dev, char* mem);

static struct hw_module_methods_t cde_module_methods = {
	open :cde_device_open
};

struct cde_module_t HAL_MODULE_INFO_SYM = {
	cdev: {
		tag: HARDWARE_MODULE_TAG,
		version_major: 1,
		version_minor: 0,
		id: "cde",
		name: "cde",
		author:"liuyafei",
		methods: &cde_module_methods,

	}
};

static int cde_device_open(const struct hw_module_t* module, const char* id, struct hw_device_t** device){
	if(!strcmp(id, "cde")){
		struct cde_device_t* dev;

		dev = (struct cde_device_t*)malloc(sizeof(struct cde_device_t));
		memset(dev, 0, sizeof(struct cde_device_t));

		dev->cdev.tag = HARDWARE_DEVICE_TAG;
		dev->cdev.version = 0;
		dev->cdev.module = (hw_module_t*)module;
		dev->cdev.close = cde_device_close;
		dev->write_mem = write_mem;
		dev->read_mem = read_mem;

		if((dev->fd = open(DEVICE_NAME, O_RDWR)) == -1) {
			LOGE("Cannot open /dev/char_device_example.");
			free(dev);
			return -EFAULT;
		}
		*device = &(dev->cdev);
		LOGI("open successfully");
		return 0;
	}
	return -EFAULT;
}

static int cde_device_close(struct hw_device_t* device) {
	struct cde_device_t* cde_device = (struct cde_device_t*)device;
	if (cde_device) {
		close(cde_device->fd);
		free(cde_device);
	}
	return 0;
}

static int read_mem(struct cde_device_t* dev, char* mem) {
	if (!dev)
	{
		return -EFAULT;
	}
	read(dev->fd, mem, 0x10);
	return 0;
}
static int write_mem(struct cde_device_t* dev, char* mem) {
	if(!dev) {
		return -EFAULT;
	}
	write(dev->fd, mem, 0x10);
	return 0;
}









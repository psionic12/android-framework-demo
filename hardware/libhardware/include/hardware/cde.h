struct cde_module_t
{
	struct hw_module_t cdev;
};
struct cde_device_t
{
	struct hw_device_t cdev;
	int fd;
	int (*write_mem)(struct cde_device_t* dev, char* mem);
	int (*read_mem)(struct cde_device_t* dev, char* mem);
};
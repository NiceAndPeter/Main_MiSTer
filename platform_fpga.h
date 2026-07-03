#ifndef PLATFORM_FPGA_H
#define PLATFORM_FPGA_H

#include <stddef.h>
#include <stdint.h>

typedef struct platform_fpga_ops {
	const char *name;
	int (*load_bitstream)(const void *rbf_data, size_t rbf_size);
	void (*set_bridge)(uint32_t enable);
	int (*is_ready)();
} platform_fpga_ops;

void platform_fpga_set_ops(const platform_fpga_ops *ops);
const platform_fpga_ops *platform_fpga_get_ops();

int platform_fpga_load_bitstream(const void *rbf_data, size_t rbf_size);
void platform_fpga_set_bridge(uint32_t enable);
int platform_fpga_is_ready();
const char *platform_fpga_backend_name();

#endif
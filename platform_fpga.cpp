#include <errno.h>

#include "platform_fpga.h"

static const platform_fpga_ops *g_platform_fpga_ops = NULL;

void platform_fpga_set_ops(const platform_fpga_ops *ops)
{
	g_platform_fpga_ops = ops;
}

const platform_fpga_ops *platform_fpga_get_ops()
{
	return g_platform_fpga_ops;
}

int platform_fpga_load_bitstream(const void *rbf_data, size_t rbf_size)
{
	if (!g_platform_fpga_ops || !g_platform_fpga_ops->load_bitstream) return -ENOSYS;
	return g_platform_fpga_ops->load_bitstream(rbf_data, rbf_size);
}

void platform_fpga_set_bridge(uint32_t enable)
{
	if (!g_platform_fpga_ops || !g_platform_fpga_ops->set_bridge) return;
	g_platform_fpga_ops->set_bridge(enable);
}

int platform_fpga_is_ready()
{
	if (!g_platform_fpga_ops || !g_platform_fpga_ops->is_ready) return 0;
	return g_platform_fpga_ops->is_ready();
}
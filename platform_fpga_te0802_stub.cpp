#include <errno.h>
#include <stddef.h>
#include <stdint.h>

#include "platform_fpga_te0802_stub.h"

static int te0802_stub_load_bitstream(const void *rbf_data, size_t rbf_size)
{
	(void)rbf_data;
	(void)rbf_size;
	return -ENOSYS;
}

static void te0802_stub_set_bridge(uint32_t enable)
{
	(void)enable;
}

static int te0802_stub_is_ready()
{
	return 0;
}

const platform_fpga_ops *platform_fpga_te0802_stub_ops()
{
	static const platform_fpga_ops ops = {
		.load_bitstream = te0802_stub_load_bitstream,
		.set_bridge = te0802_stub_set_bridge,
		.is_ready = te0802_stub_is_ready,
	};

	return &ops;
}
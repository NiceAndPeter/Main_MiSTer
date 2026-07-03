#include <stddef.h>
#include <stdint.h>

#include "platform_fpga_socfpga_backend.h"

extern int socfpga_load(const void *rbf_data, size_t rbf_size);
extern void do_bridge(uint32_t enable);
extern int fpgamgr_test_fpga_ready(void);

static int socfpga_backend_load_bitstream(const void *rbf_data, size_t rbf_size)
{
	return socfpga_load(rbf_data, rbf_size);
}

static void socfpga_backend_set_bridge(uint32_t enable)
{
	do_bridge(enable);
}

static int socfpga_backend_is_ready()
{
	return fpgamgr_test_fpga_ready();
}

const platform_fpga_ops *platform_fpga_socfpga_ops()
{
	static const platform_fpga_ops ops = {
		.name = "socfpga",
		.load_bitstream = socfpga_backend_load_bitstream,
		.set_bridge = socfpga_backend_set_bridge,
		.is_ready = socfpga_backend_is_ready,
	};

	return &ops;
}
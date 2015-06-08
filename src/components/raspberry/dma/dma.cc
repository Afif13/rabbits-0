#include "dma.h"

#include "rabbits-common.h"
#define MODNAME "rpi-dma"
#include "utils/utils.h"

/* === rpi_dma::dma_channel === */

uint32_t rpi_dma::dma_channel::read_reg(int reg)
{
    return 0;
}

void rpi_dma::dma_channel::write_reg(int reg, uint32_t v)
{

}

/* === rpi_dma === */

rpi_dma::rpi_dma(sc_module_name modname) :
        slave_device(modname)
{

}

void rpi_dma::bus_cb_write_32(uint64_t addr, uint32_t *data, bool &bErr)
{
}

void rpi_dma::bus_cb_read_32(uint64_t addr, uint32_t *data, bool &bErr)
{
    *data = 0;
}


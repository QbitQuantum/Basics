int spi_xfer(struct spi_slave *slave, unsigned int bitlen, const void *dout,
		void *din, unsigned long flags)
{
	volatile spi8xxx_t *spi = &((immap_t *) (CONFIG_SYS_IMMR))->spi;
	unsigned int tmpdout, tmpdin, event;
	int numBlks = bitlen / 32 + (bitlen % 32 ? 1 : 0);
	int tm, isRead = 0;
	unsigned char charSize = 32;

	debug("spi_xfer: slave %u:%u dout %08X din %08X bitlen %u\n",
	      slave->bus, slave->cs, *(uint *) dout, *(uint *) din, bitlen);

	if (flags & SPI_XFER_BEGIN)
		spi_cs_activate(slave);

	spi->event = 0xffffffff;	/* Clear all SPI events */

	/* handle data in 32-bit chunks */
	while (numBlks--) {
		tmpdout = 0;
		charSize = (bitlen >= 32 ? 32 : bitlen);

		/* Shift data so it's msb-justified */
		tmpdout = *(u32 *) dout >> (32 - charSize);

		/* The LEN field of the SPMODE register is set as follows:
		 *
		 * Bit length             setting
		 * len <= 4               3
		 * 4 < len <= 16          len - 1
		 * len > 16               0
		 */

		spi->mode &= ~SPI_MODE_EN;

		if (bitlen <= 16) {
			if (bitlen <= 4)
				spi->mode = (spi->mode & 0xff0fffff) |
				            (3 << 20);
			else
				spi->mode = (spi->mode & 0xff0fffff) |
				            ((bitlen - 1) << 20);
		} else {
			spi->mode = (spi->mode & 0xff0fffff);
			/* Set up the next iteration if sending > 32 bits */
			bitlen -= 32;
			dout += 4;
		}

		spi->mode |= SPI_MODE_EN;

		spi->tx = tmpdout;	/* Write the data out */
		debug("*** spi_xfer: ... %08x written\n", tmpdout);

		/*
		 * Wait for SPI transmit to get out
		 * or time out (1 second = 1000 ms)
		 * The NE event must be read and cleared first
		 */
		for (tm = 0, isRead = 0; tm < SPI_TIMEOUT; ++tm) {
			event = spi->event;
			if (event & SPI_EV_NE) {
				tmpdin = spi->rx;
				spi->event |= SPI_EV_NE;
				isRead = 1;

				*(u32 *) din = (tmpdin << (32 - charSize));
				if (charSize == 32) {
					/* Advance output buffer by 32 bits */
					din += 4;
				}
			}
			/*
			 * Only bail when we've had both NE and NF events.
			 * This will cause timeouts on RO devices, so maybe
			 * in the future put an arbitrary delay after writing
			 * the device.  Arbitrary delays suck, though...
			 */
			if (isRead && (event & SPI_EV_NF))
				break;
		}
		if (tm >= SPI_TIMEOUT)
			puts("*** spi_xfer: Time out during SPI transfer");

		debug("*** spi_xfer: transfer ended. Value=%08x\n", tmpdin);
	}

	if (flags & SPI_XFER_END)
		spi_cs_deactivate(slave);

	return 0;
}
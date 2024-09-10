void ng_at86rf2xx_reset(ng_at86rf2xx_t *dev)
{
#if CPUID_ID_LEN
    uint8_t cpuid[CPUID_ID_LEN];
    eui64_t addr_long;
#endif

    /* trigger hardware reset */
    gpio_clear(dev->reset_pin);
    hwtimer_wait(HWTIMER_TICKS(RESET_DELAY));
    gpio_set(dev->reset_pin);
    /* reset options and sequence number */
    dev->seq_nr = 0;
    dev->options = 0;
    /* set short and long address */
#if CPUID_ID_LEN
    cpuid_get(cpuid);

#if CPUID_ID_LEN < 8
    /* in case CPUID_ID_LEN < 8, fill missing bytes with zeros */
    for (int i = CPUID_ID_LEN; i < 8; i++) {
        cpuid[i] = 0;
    }
#else
    for (int i = 8; i < CPUID_ID_LEN; i++) {
        cpuid[i & 0x07] ^= cpuid[i];
    }
#endif
    /* make sure we mark the address as non-multicast and not globally unique */
    cpuid[0] &= ~(0x01);
    cpuid[0] |= 0x02;
    /* copy and set long address */
    memcpy(&addr_long, cpuid, 8);
    ng_at86rf2xx_set_addr_long(dev, NTOHLL(addr_long.uint64.u64));
    ng_at86rf2xx_set_addr_short(dev, NTOHS(addr_long.uint16[0].u16));
#else
    ng_at86rf2xx_set_addr_long(dev, NG_AT86RF2XX_DEFAULT_ADDR_LONG);
    ng_at86rf2xx_set_addr_short(dev, NG_AT86RF2XX_DEFAULT_ADDR_SHORT);
#endif
    /* set default PAN id */
    ng_at86rf2xx_set_pan(dev, NG_AT86RF2XX_DEFAULT_PANID);
    /* set default channel */
    ng_at86rf2xx_set_chan(dev, NG_AT86RF2XX_DEFAULT_CHANNEL);
    /* set default TX power */
    ng_at86rf2xx_set_txpower(dev, NG_AT86RF2XX_DEFAULT_TXPOWER);
    /* set default options */
    ng_at86rf2xx_set_option(dev, NG_AT86RF2XX_OPT_AUTOACK, true);
    ng_at86rf2xx_set_option(dev, NG_AT86RF2XX_OPT_CSMA, true);
    ng_at86rf2xx_set_option(dev, NG_AT86RF2XX_OPT_TELL_RX_START, false);
    ng_at86rf2xx_set_option(dev, NG_AT86RF2XX_OPT_TELL_RX_END, true);
    /* set default protocol */
#ifdef MODULE_NG_SIXLOWPAN
    dev->proto = NG_NETTYPE_SIXLOWPAN;
#else
    dev->proto = NG_NETTYPE_UNDEF;
#endif
    /* enable safe mode (protect RX FIFO until reading data starts) */
    ng_at86rf2xx_reg_write(dev, NG_AT86RF2XX_REG__TRX_CTRL_2,
                          NG_AT86RF2XX_TRX_CTRL_2_MASK__RX_SAFE_MODE);
#ifdef MODULE_NG_AT86RF212B
    ng_at86rf2xx_set_freq(dev,NG_AT86RF2XX_FREQ_915MHZ);
#endif

    /* don't populate masked interrupt flags to IRQ_STATUS register */
    uint8_t tmp = ng_at86rf2xx_reg_read(dev, NG_AT86RF2XX_REG__TRX_CTRL_1);
    tmp &= ~(NG_AT86RF2XX_TRX_CTRL_1_MASK__IRQ_MASK_MODE);
    ng_at86rf2xx_reg_write(dev, NG_AT86RF2XX_REG__TRX_CTRL_1, tmp);

    /* enable interrupts */
    ng_at86rf2xx_reg_write(dev, NG_AT86RF2XX_REG__IRQ_MASK,
                          NG_AT86RF2XX_IRQ_STATUS_MASK__TRX_END);
    /* clear interrupt flags */
    ng_at86rf2xx_reg_read(dev, NG_AT86RF2XX_REG__IRQ_STATUS);

    /* go into RX state */
    ng_at86rf2xx_set_state(dev, NG_AT86RF2XX_STATE_RX_AACK_ON);

    DEBUG("ng_at86rf2xx_reset(): reset complete.\n");
}
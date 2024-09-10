int    broadcast_fc8300_drv_if_set_channel(struct broadcast_dmb_set_ch_info *udata)
{
    signed long frequency = 214714; /*tmm*/
    int ret;
#ifndef BBM_I2C_TSIF
    fci_irq_disable();
#endif
    setTimer();

    if(OnAir == 0 || udata == NULL) {
        print_log(NULL, "[1seg] broadcast_drv_if_set_channel error [!OnAir]\n");
        return ERROR;
    }

    /* uhf 1segment */
    currentSelectedChannel = udata->channel;

    if(udata->segment == 13) {
        currentBroadCast = UHF_13SEG;
    } else {
        currentBroadCast = UHF_1SEG;
    }
    #ifdef CONFIG_LGE_BROADCAST_BRAZIL_FREQ
    if(udata->channel<14 || udata->channel>69) {
        print_log(NULL, "[1seg] channel information error\n");
        return ERROR;
    }
    frequency = frequencyTable[udata->channel-14];
    #else
    if(udata->channel<13 || udata->channel>62) {
        print_log(NULL, "[1seg] channel information error\n");
        return ERROR;
    }
    frequency = frequencyTable[udata->channel-13];
    #endif

    /* Scan mode(udata->mode==1) & need lock check */

#ifndef BBM_I2C_TSIF
    fci_irq_enable();
#endif
    ret = tunerbb_drv_fc8300_set_channel(frequency, udata->mode, udata->subchannel);

    //broadcast_fci_ringbuffer_flush();

    if(ret)
        return ERROR;

    print_log(NULL, "[fc8300] channel channel : %d, %d, %d, scan OK\n", udata->channel, udata->mode, udata->subchannel);

    return OK;
}
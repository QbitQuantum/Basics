void charging_algorithm_step(void)
{
#if IMX233_SUBTARGET >= 3700
    bool is_5v_present = usb_detect() == USB_INSERTED;

    /* initial state & 5v -> battery transition */
    if(!is_5v_present && charge_state != DISCHARGING)
    {
        logf("pwrmgmt: * -> discharging");
        logf("pwrmgmt: disable charger and 4p2"); 
        charge_state = DISCHARGING;
        /* 5V has been lost: disable 4p2 power rail */
        BF_SET(POWER_CHARGE, PWD_BATTCHRG);
#if IMX233_SUBTARGET >= 3780
        BF_WR(POWER_DCDC4P2, ENABLE_DCDC(0));
        BF_WR(POWER_DCDC4P2, ENABLE_4P2(0));
        BF_WR(POWER_5VCTRL, CHARGE_4P2_ILIMIT(0));
        BF_SET(POWER_5VCTRL, PWD_CHARGE_4P2);
#endif
    }
    /* battery -> 5v transition */
    else if(is_5v_present && charge_state == DISCHARGING)
    {
        logf("pwrmgmt: discharging -> trickle");
        logf("pwrmgmt: begin charging 4p2");
#if IMX233_SUBTARGET >= 3780
        /* 5V has been detected: prepare 4.2V power rail for activation
         * WARNING we can reach this situation when starting after Freescale bootloader
         * or after RoLo in a state where the DCDC is running. In this case,
         * we must *NOT* disable it or this will shutdown the device. This procedure
         * is safe: it will never disable the DCDC and will not reduce the charge
         * limit on the 4P2 rail. */
        BF_WR(POWER_DCDC4P2, ENABLE_4P2(1));
        BF_SET(POWER_CHARGE, ENABLE_LOAD);
        BF_WR(POWER_5VCTRL, CHARGE_4P2_ILIMIT(0)); /* start by drawing 0mA */
        BF_CLR(POWER_5VCTRL, PWD_CHARGE_4P2);// FIXME: manual error ?
        BF_WR(POWER_DCDC4P2, ENABLE_DCDC(1));
        /* the tick task will take care of slowly ramping up the current in the rail
         * every 10ms (since it runs at HZ and HZ=100) */
#endif
        charge_state = TRICKLE;
    }
    /* trickle -> charging transition */
    else if(charge_state == TRICKLE)
    {
#if IMX233_SUBTARGET >= 3780
        /* If 4.2V current limit has not reached 780mA, don't do anything, the
         * DPC is still running */
        /* If we've reached the maximum, take action */
        if(BF_RD(POWER_5VCTRL, CHARGE_4P2_ILIMIT) == MAX_4P2_ILIMIT)
#endif
        {
            logf("pwrmgmt: enable dcdc and charger");
            logf("pwrmgmt: trickle -> charging");
#if IMX233_SUBTARGET >= 3780
            /* adjust arbitration between 4.2 and battery */
            BF_WR(POWER_DCDC4P2, CMPTRIP(0)); /* 85% */
            BF_WR(POWER_DCDC4P2, DROPOUT_CTRL(0xe)); /* select greater, 200 mV drop */
#endif
            /* switch to DCDC */
            BF_CLR(POWER_5VCTRL, DCDC_XFER);
            BF_SET(POWER_5VCTRL, ENABLE_DCDC);
            /* enable battery charging */
            BF_CLR(POWER_CHARGE, PWD_BATTCHRG);
            charge_state = CHARGING;
            timeout_charging = current_tick + IMX233_CHARGING_TIMEOUT;
        }
    }
    /* charging -> error transition */
    else if(charge_state == CHARGING && TIME_AFTER(current_tick, timeout_charging))
    {
        /* we have charged for a too long time, declare charger broken */
        logf("pwrmgmt: charging timeout exceeded!");
        logf("pwrmgmt: charging -> error");
        /* stop charging, note that we leave the 4.2 rail active so that the DCDC
         * keep drawing current from the 4.2 only and leave the battery untouched */
        BF_SET(POWER_CHARGE, PWD_BATTCHRG);
        /* goto error state */
        charge_state = CHARGE_STATE_ERROR;
    }
    /* charging -> topoff transition */
    else if(charge_state == CHARGING && !BF_RD(POWER_STS, CHRGSTS))
    {
        logf("pwrmgmt: topping off");
        logf("pwrmgmt: charging -> topoff");
        charge_state = TOPOFF;
        timeout_topping_off = current_tick + IMX233_TOPOFF_TIMEOUT;
    }
    /* topoff -> disabled transition */
    else if(charge_state == TOPOFF && TIME_AFTER(current_tick, timeout_topping_off))
    {
        logf("pwrmgmt: charging finished");
        logf("pwrmgmt: topoff -> disabled");
        /* stop charging, note that we leave the 4.2 rail active so that the DCDC
         * keep drawing current from the 4.2 only and leave the battery untouched */
        BF_SET(POWER_CHARGE, PWD_BATTCHRG);
        charge_state = CHARGE_STATE_DISABLED;
    }
#endif
}
/*
 * ReInitModem()
 *
 * This function will reinitialize the modem at a high speed.
 */
void ReInitModem()
{
    if (strLen(cfg.DepData.HiSpeedInit) != 0 && !gotCarrier()) {
	setNetCallBaud(cfg.sysBaud);
	OutString(cfg.DepData.HiSpeedInit);
    }
}
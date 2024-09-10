/*
 * Handle open from generic layer.
 *
 * This is called by the diskslice code on first open in order to get the 
 * basic device geometry paramters.
 */
static int
aac_disk_open(struct disk *dp)
{
	struct aac_disk	*sc;

	fwprintf(NULL, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	sc = (struct aac_disk *)dp->d_drv1;
	
	if (sc == NULL) {
		printf("aac_disk_open: No Softc\n");
		return (ENXIO);
	}

	/* check that the controller is up and running */
	if (sc->ad_controller->aac_state & AAC_STATE_SUSPEND) {
		printf("Controller Suspended controller state = 0x%x\n",
		       sc->ad_controller->aac_state);
		return(ENXIO);
	}

	sc->ad_flags |= AAC_DISK_OPEN;
	return (0);
}
int mmc_std_inquiry( SIM_HBA *hba, CCB_SCSIIO *ccb )
{
	SIM_MMC_EXT		*ext;
	SCSI_INQUIRY	*iptr;
	char			buf[8];

	ext		= (SIM_MMC_EXT *)hba->ext;
	iptr	= (SCSI_INQUIRY *)ccb->cam_data.cam_data_ptr;

	memset(iptr, 0, sizeof(*iptr));

	iptr->peripheral	= D_DIR_ACC;
	iptr->rmb			= ext->normval ? CAM_FALSE : CAM_TRUE;
	iptr->version		= INQ_VER_SPC3;			// SPC-3
	iptr->adlen			= 32;

	if (ext->version < MMC_VERSION_1) {
		/* Vendor ID */
		strcpy((char *)&iptr->vend_id[0], "SD:");
		ultoa(ext->cid.sd_cid.mid, buf, 10);
		iptr->vend_id[3] = buf[0];
		iptr->vend_id[4] = buf[1];
		iptr->vend_id[5] = buf[2];

		/* Product ID */
		strcpy((char *)&iptr->prod_id[0], (char *)ext->cid.sd_cid.pnm);

		/* Product revision level, BCD code */
		iptr->prod_rev[0] = (ext->cid.sd_cid.prv >> 4) + '0';
		iptr->prod_rev[1] = '.';
		iptr->prod_rev[2] = (ext->cid.sd_cid.prv & 0x0F) + '0';
	} else {
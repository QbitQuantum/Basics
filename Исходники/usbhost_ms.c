/*********************************************************************//**
 * @brief 			Inquiry the mass storage device.
 * @param[in]		None.
 * @return 		MS_FUNC_OK       if Success
 *				ERR_MS_CMD_FAILED if failed
 **********************************************************************/
int32_t MS_Inquire (uint8_t *response)
{
    int32_t rc;
	uint32_t i;

    Fill_MSCommand(0, 0, 0, MS_DATA_DIR_IN, SCSI_CMD_INQUIRY, 6);
    rc = Host_ProcessTD(EDBulkOut, TD_OUT, TDBuffer, CBW_SIZE);
    if (rc == MS_FUNC_OK) {
        rc = Host_ProcessTD(EDBulkIn, TD_IN, TDBuffer, INQUIRY_LENGTH);
        if (rc == MS_FUNC_OK) {
            if (response) {
		for ( i = 0; i < INQUIRY_LENGTH; i++ )
			*response++ = *TDBuffer++;
#if 0
            	MemCpy (response, TDBuffer, INQUIRY_LENGTH);
	        	StrNullTrailingSpace (response->vendorID, SCSI_INQUIRY_VENDORCHARS);
	        	StrNullTrailingSpace (response->productID, SCSI_INQUIRY_PRODUCTCHARS);
	        	StrNullTrailingSpace (response->productRev, SCSI_INQUIRY_REVCHARS);
#endif
            }
            rc = Host_ProcessTD(EDBulkIn, TD_IN, TDBuffer, CSW_SIZE);
            if (rc == MS_FUNC_OK) {
                if (TDBuffer[12] != 0) {	// bCSWStatus byte
                    rc = ERR_MS_CMD_FAILED;
                }
            }
        }
    }
    return (rc);
}
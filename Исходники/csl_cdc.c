/** ============================================================================
 *   @n@b CDC_bulkInHandler
 *
 *   @b Description
 *   @n This function handles all the CDC ACM bulk IN data transactions
 *
 *   @b Arguments
 *   @verbatim
			pContext		 Pointer to the USBContext structure
            hCdcClass        Handle to the CDC Class Obj
     @endverbatim
 *
 *   <b> Return Value </b>  - Status of the processing (CSL_Status)
 *   @li    CSL_SOK                    (0)         Success                                    
 *   @li    CSL_ESYS_FAIL              (-1)        Generic failure
 *   @li    CSL_ESYS_BADHANDLE         (-5)        Handle passed to CSL was invalid
 *   @li    CSL_ESYS_INVPARAMS         (-6)        Invalid parameters       
 *
 *   <b> Pre Condition </b>
 *   @n  CDC module should be opened using CDC_Open/CDC_OpenFullspeed function
 *
 *   <b> Post Condition </b>
 *   @n  Returns request processing status
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
			CSL_CdcInitStructApp    cdcAppHandle;
			CSL_CdcClassStruct      cdcClassStruct;
			CSL_Status              status;

			// Assign values to all the members in cdcAppHandle struct
			cdcAppHandle.pCdcObj = &cdcClassStruct;
			.....
			.....
			status = CDC_Open(pAppClassHandle);
			....
			....
			
			in USB ISR:
			....
			....
			if (pContext->dwIntSourceL & (1<<CSL_CDC_BULK_IN_EP))
			{
				// Handle the CDC BULK IN
				///CDC_bulkInHandler(pContext, &CDC_AppHandle);
			}
			....
			....
     @endverbatim
 *  ============================================================================
 */
CSL_Status CDC_bulkInHandler(pUsbContext pContext, CSL_CdcInitStructApp *cdcAppHandle)
{
	CSL_Status status, txRxStatus;
	Uint16 bytesRem, txStartIdxSave, txEndIdxSave, i; 

	status = CSL_SOK;

	// Is the TX EP free?
	if (cdcAppHandle->txWorkBufIdx==0)
	{ 
		// is there anything need to send out
		txStartIdxSave = cdcAppHandle->txStartIdx;
		txEndIdxSave = cdcAppHandle->txEndIdx;
		if (txEndIdxSave==txStartIdxSave)
		{
			// nothing to transmit, then return
			return status;
		} else if (txEndIdxSave>txStartIdxSave)
		{
			// for no wrap around case
			// pack and copy the data from txBufferPtr to txWorkBufPtr
			for (i=0; i<(txEndIdxSave-txStartIdxSave); i++)
			{
				if (i%2)
					cdcAppHandle->txWorkBufPtr[i/2] = (cdcAppHandle->txBufferPtr[txStartIdxSave+i]<<8);
				else
					cdcAppHandle->txWorkBufPtr[i/2] = cdcAppHandle->txBufferPtr[txStartIdxSave+i]&0xFF;
			}
			// send whatever in the TX working buffer to host
			status = USB_postTransaction(pContext->hEpObjArray[3], txEndIdxSave-txStartIdxSave,
			                             cdcAppHandle->txWorkBufPtr, CSL_USB_IN_TRANSFER);
			if(status != CSL_SOK)
			{
				printf("USB TX Transaction failed\n");
			}

			/* Check the transaction status */
			txRxStatus = USB_isTransactionDone(pContext->hEpObjArray[3], &status);
			if(txRxStatus != CSL_USB_TRUE)
			{
				bytesRem = USB_bytesRemaining(pContext->hEpObjArray[3], &status);
				if(bytesRem)
				{
					printf("Bytes remaining: %d\n", bytesRem);
				}
			}
		
			// update the txStartIdx
			cdcAppHandle->txStartIdx = txEndIdxSave;
		} else if (txEndIdxSave<txStartIdxSave)
		{
			// for wrap around case
			// send the TX buffer (rxStartIdx - CSL_USB_CDC_DATA_BUF_SIZE) to host
			// pack and copy the data from txBufferPtr to txWorkBufPtr
			for (i=0; i<(CSL_USB_CDC_DATA_BUF_SIZE-txStartIdxSave); i++)
			{
				if (i%2)
					cdcAppHandle->txWorkBufPtr[i/2] = (cdcAppHandle->txBufferPtr[txStartIdxSave+i]<<8);
				else
					cdcAppHandle->txWorkBufPtr[i/2] = cdcAppHandle->txBufferPtr[txStartIdxSave+i]&0xFF;
			}
			// send whatever in the TX working buffer to host
			status = USB_postTransaction(pContext->hEpObjArray[3], CSL_USB_CDC_DATA_BUF_SIZE-txStartIdxSave,
			                             cdcAppHandle->txWorkBufPtr, CSL_USB_IN_TRANSFER);
			if(status != CSL_SOK)
			{
				printf("USB TX Transaction failed\n");
			}

			/* Check the transaction status */
			txRxStatus = USB_isTransactionDone(pContext->hEpObjArray[3], &status);
			if(txRxStatus != CSL_USB_TRUE)
			{
				bytesRem = USB_bytesRemaining(pContext->hEpObjArray[3], &status);
				if(bytesRem)
				{
					printf("Bytes remaining: %d\n", bytesRem);
				}
			}
		
			// update the txStartIdx
			cdcAppHandle->txStartIdx = 0;

			// send the TX buffer (0 - txEndIdx) to host
			// pack and copy the data from txBufferPtr to txWorkBufPtr
			for (i=0; i<txEndIdxSave; i++)
			{
				if (i%2)
					cdcAppHandle->txWorkBufPtr[i/2] = (cdcAppHandle->txBufferPtr[txStartIdxSave+i]<<8);
				else
					cdcAppHandle->txWorkBufPtr[i/2] = cdcAppHandle->txBufferPtr[txStartIdxSave+i]&0xFF;
			}
			// send whatever in the TX working buffer to host
			status = USB_postTransaction(pContext->hEpObjArray[3], txEndIdxSave,
			                             cdcAppHandle->txWorkBufPtr, CSL_USB_IN_TRANSFER);
			if(status != CSL_SOK)
			{
				printf("USB TX Transaction failed\n");
			}

			/* Check the transaction status */
			txRxStatus = USB_isTransactionDone(pContext->hEpObjArray[3], &status);
			if(txRxStatus != CSL_USB_TRUE)
			{
				bytesRem = USB_bytesRemaining(pContext->hEpObjArray[3], &status);
				if(bytesRem)
				{
					printf("Bytes remaining: %d\n", bytesRem);
				}
			}
		
			// update the txStartIdx
			cdcAppHandle->txStartIdx = txEndIdxSave;
		}
	}

	return status;
}
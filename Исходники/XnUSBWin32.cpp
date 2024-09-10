XN_C_API XnStatus xnUSBOpenEndPoint(XN_USB_DEV_HANDLE pDevHandle, XnUInt16 nEndPointID, XnUSBEndPointType nEPType, XnUSBDirectionType nDirType, XN_USB_EP_HANDLE* pEPHandlePtr)
{
	// Local variables
	XnBool bResult = TRUE;
	XnStatus nRetVal = XN_STATUS_OK;
	XnInt32 nRetBytes = 0;
	XnChar pConfigDescBuf[MAX_CONFIG_DESC_SIZE];
	XnChar* pBuf = NULL;
	PUSB_CONFIGURATION_DESCRIPTOR pUSBConfigDesc = NULL;
	PUSB_INTERFACE_DESCRIPTOR pUSBInterfaceDesc = NULL;
	PUSB_ENDPOINT_DESCRIPTOR pUSBEndPointDesc = NULL;
	XN_USB_EP_HANDLE pEPHandle = NULL;	
	XnChar cpPipeID[3];

	// Validate xnUSB
	XN_VALIDATE_USB_INIT();
	XN_VALIDATE_USB_PDEV_HANDLE(pDevHandle);

	// Validate the input/output pointers
	XN_VALIDATE_OUTPUT_PTR(pEPHandlePtr);

	// Allocate a new xnUSB EP handle
	XN_VALIDATE_ALIGNED_CALLOC(*pEPHandlePtr, xnUSBEPHandle, 1, XN_DEFAULT_MEM_ALIGN);
	pEPHandle = *pEPHandlePtr;

	// Read the config descriptor
	bResult = DeviceIoControl(pDevHandle->hUSBDevHandle, IOCTL_PSDRV_GET_CONFIG_DESCRIPTOR, pConfigDescBuf, sizeof(pConfigDescBuf), pConfigDescBuf, sizeof(pConfigDescBuf), (PULONG)&nRetBytes, NULL);
	if (bResult)
	{
		XnUInt32 nIFIdx = 0;
		UCHAR nEPIdx = 0;
		XnUInt32 nUBBEPType = 0;
		XnUInt32 nCurrIF = 0;

		pBuf = pConfigDescBuf;

		pUSBConfigDesc = (PUSB_CONFIGURATION_DESCRIPTOR)pBuf;

		pBuf += pUSBConfigDesc->bLength;

		// Scan all the interfaces
		do {
			pUSBInterfaceDesc = (PUSB_INTERFACE_DESCRIPTOR)pBuf;

			pBuf += pUSBInterfaceDesc->bLength;

			// Scan all the endpoints
			for (nEPIdx = 0; nEPIdx < pUSBInterfaceDesc->bNumEndpoints; nEPIdx++)
			{
				pUSBEndPointDesc = (PUSB_ENDPOINT_DESCRIPTOR)pBuf;

				// Is this the EP we're looking for?
				if ((pUSBEndPointDesc->bEndpointAddress == nEndPointID) && (pDevHandle->nAltInterface == nCurrIF))
				{
					// Get the EP type
					nUBBEPType = pUSBEndPointDesc->bmAttributes & USB_ENDPOINT_TYPE_MASK;

					// Verify that the EP type matches the requested EP
					if (nEPType == XN_USB_EP_BULK)
					{
						if (nUBBEPType != USB_ENDPOINT_TYPE_BULK)
						{
							XN_ALIGNED_FREE_AND_NULL(pEPHandle);
							return (XN_STATUS_USB_WRONG_ENDPOINT_TYPE);
						}
					}
					else if (nEPType == XN_USB_EP_INTERRUPT)
					{
						if (nUBBEPType != USB_ENDPOINT_TYPE_INTERRUPT)
						{
							XN_ALIGNED_FREE_AND_NULL(pEPHandle);
							return (XN_STATUS_USB_WRONG_ENDPOINT_TYPE);
						}
					}
					else if (nEPType == XN_USB_EP_ISOCHRONOUS)
					{
						if (nUBBEPType != USB_ENDPOINT_TYPE_ISOCHRONOUS)
						{
							XN_ALIGNED_FREE_AND_NULL(pEPHandle);
							return (XN_STATUS_USB_WRONG_ENDPOINT_TYPE);
						}
					}
					else
					{
						XN_ALIGNED_FREE_AND_NULL(pEPHandle);
						return (XN_STATUS_USB_UNKNOWN_ENDPOINT_TYPE);
					}

					// Verify that the EP direction matches the requested direction
					if (nDirType == XN_USB_DIRECTION_IN)
					{
						if (USB_ENDPOINT_DIRECTION_IN(pUSBEndPointDesc->bEndpointAddress) == FALSE)
						{
							XN_ALIGNED_FREE_AND_NULL(pEPHandle);
							return (XN_STATUS_USB_WRONG_ENDPOINT_DIRECTION);
						}
					}
					else if (nDirType == XN_USB_DIRECTION_OUT)
					{
						if (USB_ENDPOINT_DIRECTION_OUT(pUSBEndPointDesc->bEndpointAddress) == FALSE)
						{
							XN_ALIGNED_FREE_AND_NULL(pEPHandle);
							return (XN_STATUS_USB_WRONG_ENDPOINT_DIRECTION);
						}
					}
					else
					{
						XN_ALIGNED_FREE_AND_NULL(pEPHandle);
						return (XN_STATUS_USB_UNKNOWN_ENDPOINT_DIRECTION);
					}

					// Construct the pipe file name
					pEPHandle->cpPipeName[0] = 0;

					cpPipeID[0] = '0';
					cpPipeID[1] = '0' + nEPIdx;
					cpPipeID[2] = 0;
			
					StringCchCopy(pEPHandle->cpPipeName, MAX_DEVICE_STR_LENGTH, pDevHandle->cpDeviceName);
					StringCchCat(pEPHandle->cpPipeName, MAX_DEVICE_STR_LENGTH, PSDRV_PIPE_PREFIX);
					StringCchCat(pEPHandle->cpPipeName, MAX_DEVICE_STR_LENGTH, cpPipeID);

					// Open the regular pipe handle
					pEPHandle->hEPHandle = CreateFile(pEPHandle->cpPipeName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
					if (pEPHandle->hEPHandle == INVALID_HANDLE_VALUE)
					{
						XN_ALIGNED_FREE_AND_NULL(pEPHandle);
						return (XN_STATUS_USB_OPEN_ENDPOINT_FAILED);
					}

					// Init the overlapped I/O structs
					nRetVal = xnUSBInitOvlp(pEPHandle);
					if (nRetVal != XN_STATUS_OK)
					{
						XN_ALIGNED_FREE_AND_NULL(pEPHandle);
						return (XN_STATUS_USB_OPEN_ENDPOINT_FAILED);						
					}

					// Init the ThreadData variables
					xnOSMemSet(&pEPHandle->ThreadData, 0, sizeof(xnUSBReadThreadData));
					pEPHandle->ThreadData.bInUse = FALSE;

					// Init the default endpoint properties
					pEPHandle->nTimeOut = XN_USB_DEFAULT_EP_TIMEOUT;
					pEPHandle->nEPType = nEPType;
					pEPHandle->nEPDir = nDirType;
					pEPHandle->nEndPointID = nEndPointID;

					// Set the default endpoint timeout
					nRetVal = xnUSBSetPipeProperty(pEPHandle, PSUSBDRV_PIPE_PROPERTY_TIMEOUT, XN_USB_DEFAULT_EP_TIMEOUT);
					if (nRetVal != XN_STATUS_OK)
					{
						XN_ALIGNED_FREE_AND_NULL(pEPHandle);
						return (nRetVal);
					}

					if (nUBBEPType == USB_ENDPOINT_TYPE_ISOCHRONOUS)
					{
						// bits 11 and 12 mark the number of additional transactions, bits 0-10 mark the size
						XnUInt32 nAdditionalTransactions = pUSBEndPointDesc->wMaxPacketSize >> 11;
						XnUInt32 nPacketSize = pUSBEndPointDesc->wMaxPacketSize & 0x7FF;
						pEPHandle->nMaxPacketSize = (nAdditionalTransactions + 1) * (nPacketSize);
					}
					else
					{
						pEPHandle->nMaxPacketSize = pUSBEndPointDesc->wMaxPacketSize;
					}

					// Mark the endpoint as valid
					pEPHandle->bValid = TRUE;

					// The end... (Happy)
					return (XN_STATUS_OK);
				}

				pBuf += pUSBEndPointDesc->bLength;
			}
status_t
usb_disk_operation(device_lun *lun, uint8 operation, uint8 opLength,
	uint32 logicalBlockAddress, uint16 transferLength, void *data,
	size_t *dataLength, bool directionIn, err_act *_action)
{
	TRACE("operation: lun: %u; op: %u; oplen: %u; lba: %" B_PRIu32
		"; tlen: %u; data: %p; dlen: %p (%lu); in: %c\n",
		lun->logical_unit_number, operation, opLength, logicalBlockAddress,
		transferLength, data, dataLength, dataLength ? *dataLength : 0,
		directionIn ? 'y' : 'n');

	disk_device *device = lun->device;
	command_block_wrapper command;
	command.signature = CBW_SIGNATURE;
	command.tag = device->current_tag++;
	command.data_transfer_length = (dataLength != NULL ? *dataLength : 0);
	command.flags = (directionIn ? CBW_DATA_INPUT : CBW_DATA_OUTPUT);
	command.lun = lun->logical_unit_number;
	command.command_block_length
		= device->is_atapi ? ATAPI_COMMAND_LENGTH : opLength;
	memset(command.command_block, 0, sizeof(command.command_block));

	switch (opLength) {
		case 6:
		{
			scsi_command_6 *commandBlock
				= (scsi_command_6 *)command.command_block;
			commandBlock->operation = operation;
			commandBlock->lun = lun->logical_unit_number << 5;
			commandBlock->allocation_length = (uint8)transferLength;
			if (operation == SCSI_MODE_SENSE_6) {
				// we hijack the lba argument to transport the desired page
				commandBlock->reserved[1] = (uint8)logicalBlockAddress;
			}
			break;
		}

		case 10:
		{
			scsi_command_10 *commandBlock
				= (scsi_command_10 *)command.command_block;
			commandBlock->operation = operation;
			commandBlock->lun_flags = lun->logical_unit_number << 5;
			commandBlock->logical_block_address = htonl(logicalBlockAddress);
			commandBlock->transfer_length = htons(transferLength);
			break;
		}

		default:
			TRACE_ALWAYS("unsupported operation length %d\n", opLength);
			return B_BAD_VALUE;
	}

	status_t result = usb_disk_transfer_data(device, false, &command,
		sizeof(command_block_wrapper));
	if (result != B_OK)
		return result;

	if (device->status != B_OK ||
		device->actual_length != sizeof(command_block_wrapper)) {
		// sending the command block wrapper failed
		TRACE_ALWAYS("sending the command block wrapper failed: %s\n",
			strerror(device->status));
		usb_disk_reset_recovery(device);
		return B_ERROR;
	}

	size_t transferedData = 0;
	if (data != NULL && dataLength != NULL && *dataLength > 0) {
		// we have data to transfer in a data stage
		result = usb_disk_transfer_data(device, directionIn, data,
			*dataLength);
		if (result != B_OK)
			return result;

		transferedData = device->actual_length;
		if (device->status != B_OK || transferedData != *dataLength) {
			// sending or receiving of the data failed
			if (device->status == B_DEV_STALLED) {
				TRACE("stall while transfering data\n");
				gUSBModule->clear_feature(directionIn ? device->bulk_in
					: device->bulk_out, USB_FEATURE_ENDPOINT_HALT);
			} else {
				TRACE_ALWAYS("sending or receiving of the data failed: %s\n",
					strerror(device->status));
				usb_disk_reset_recovery(device);
				return B_ERROR;
			}
		}
	}

	command_status_wrapper status;
	result =  usb_disk_receive_csw(device, &status);
	if (result != B_OK) {
		// in case of a stall or error clear the stall and try again
		gUSBModule->clear_feature(device->bulk_in, USB_FEATURE_ENDPOINT_HALT);
		result = usb_disk_receive_csw(device, &status);
	}

	if (result != B_OK) {
		TRACE_ALWAYS("receiving the command status wrapper failed: %s\n",
			strerror(result));
		usb_disk_reset_recovery(device);
		return result;
	}

	if (status.signature != CSW_SIGNATURE || status.tag != command.tag) {
		// the command status wrapper is not valid
		TRACE_ALWAYS("command status wrapper is not valid: %#" B_PRIx32 "\n",
			status.signature);
		usb_disk_reset_recovery(device);
		return B_ERROR;
	}

	switch (status.status) {
		case CSW_STATUS_COMMAND_PASSED:
		case CSW_STATUS_COMMAND_FAILED:
		{
			// The residue from "status.data_residue" is not maintained
			// correctly by some devices, so calculate it instead.
			uint32 residue = command.data_transfer_length - transferedData;

			if (dataLength != NULL) {
				*dataLength -= residue;
				if (transferedData < *dataLength) {
					TRACE_ALWAYS("less data transfered than indicated: %"
						B_PRIuSIZE " vs. %" B_PRIuSIZE "\n", transferedData,
						*dataLength);
					*dataLength = transferedData;
				}
			}

			if (status.status == CSW_STATUS_COMMAND_PASSED) {
				// the operation is complete and has succeeded
				return B_OK;
			} else {
				if (operation == SCSI_REQUEST_SENSE_6)
					return B_ERROR;

				// the operation is complete but has failed at the SCSI level
				if (operation != SCSI_TEST_UNIT_READY_6) {
					TRACE_ALWAYS("operation %#" B_PRIx8
						" failed at the SCSI level\n", operation);
				}

				result = usb_disk_request_sense(lun, _action);
				return result == B_OK ? B_ERROR : result;
			}
		}

		case CSW_STATUS_PHASE_ERROR:
		{
			// a protocol or device error occured
			TRACE_ALWAYS("phase error in operation %#" B_PRIx8 "\n", operation);
			usb_disk_reset_recovery(device);
			return B_ERROR;
		}

		default:
		{
			// command status wrapper is not meaningful
			TRACE_ALWAYS("command status wrapper has invalid status\n");
			usb_disk_reset_recovery(device);
			return B_ERROR;
		}
	}
}
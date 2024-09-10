/**
  Changes the state of a network interface from "stopped" to "started".

  @param  This Protocol instance pointer.

  @retval EFI_SUCCESS           The network interface was started.
  @retval EFI_ALREADY_STARTED   The network interface is already in the started state.
  @retval EFI_INVALID_PARAMETER One or more of the parameters has an unsupported value.
  @retval EFI_DEVICE_ERROR      The command could not be sent to the network interface.
  @retval EFI_UNSUPPORTED       This function is not supported by the network interface.

**/
EFI_STATUS
EmuSnpStart (
  IN EMU_SNP_PROTOCOL  *This
  )
{
  EFI_STATUS         Status;
  EMU_SNP_PRIVATE    *Private;
  struct ifreq       BoundIf;
  struct bpf_program BpfProgram;
  struct bpf_insn    *FilterProgram;
	u_int							 Value;
	u_int  						 ReadBufferSize;
  UINT16             Temp16;
  UINT32             Temp32;

  Private = EMU_SNP_PRIVATE_DATA_FROM_THIS (This);

  switch (Private->Mode->State) {
    case EfiSimpleNetworkStopped:
      break;

    case EfiSimpleNetworkStarted:
    case EfiSimpleNetworkInitialized:
      return EFI_ALREADY_STARTED;
      break;

    default:
      return EFI_DEVICE_ERROR;
      break;
  }

  Status = EFI_SUCCESS;
  if (Private->BpfFd == 0) {
    Status = OpenBpfFileDescriptor (Private, &Private->BpfFd);
    if (EFI_ERROR (Status)) {
      goto DeviceErrorExit;
    }

    //
		// Get the read buffer size.
		//
		if (ioctl (Private->BpfFd, BIOCGBLEN, &ReadBufferSize) < 0) {
			goto DeviceErrorExit;
		}

		//
		// Default value from BIOCGBLEN is usually too small, so use a much larger size, if necessary.
		//
		if (ReadBufferSize < FixedPcdGet32 (PcdNetworkPacketFilterSize)) {
			ReadBufferSize = FixedPcdGet32 (PcdNetworkPacketFilterSize);
			if (ioctl (Private->BpfFd, BIOCSBLEN, &ReadBufferSize) < 0) {
				goto DeviceErrorExit;
			}
		}

		//
    // Associate our interface with this BPF file descriptor.
    //
    AsciiStrCpy (BoundIf.ifr_name, Private->InterfaceName);
    if (ioctl (Private->BpfFd, BIOCSETIF, &BoundIf) < 0) {
      goto DeviceErrorExit;
    }

    //
		// Enable immediate mode.
    //
    Value = 1;
    if (ioctl (Private->BpfFd, BIOCIMMEDIATE, &Value) < 0) {
      goto DeviceErrorExit;
    }

    //
    // Enable non-blocking I/O.
    //
    if (fcntl (Private->BpfFd, F_GETFL, 0) == -1) {
      goto DeviceErrorExit;
    }

    Value |= O_NONBLOCK;

    if (fcntl (Private->BpfFd, F_SETFL, Value) == -1) {
      goto DeviceErrorExit;
    }

    //
    // Disable "header complete" flag.  This means the supplied source MAC address is
    // what goes on the wire.
    //
    Value = 1;
    if (ioctl (Private->BpfFd, BIOCSHDRCMPLT, &Value) < 0) {
      goto DeviceErrorExit;
    }

    //
    // Allocate read buffer.
    //
		Private->ReadBufferSize = ReadBufferSize;
		Private->ReadBuffer = malloc (Private->ReadBufferSize);
    if (Private->ReadBuffer == NULL) {
      goto ErrorExit;
    }

    Private->CurrentReadPointer = Private->EndReadPointer = Private->ReadBuffer;

    //
		// Install our packet filter: successful reads should only produce broadcast or unicast
    // packets directed to our fake MAC address.
    //
    FilterProgram = malloc (sizeof (mFilterInstructionTemplate)) ;
    if ( FilterProgram == NULL ) {
      goto ErrorExit;
    }

    CopyMem (FilterProgram, &mFilterInstructionTemplate, sizeof (mFilterInstructionTemplate));

    //
    // Insert out fake MAC address into the filter.  The data has to be host endian.
    //
    CopyMem (&Temp32, &Private->Mode->CurrentAddress.Addr[0], sizeof (UINT32));
    FilterProgram[1].k = NTOHL (Temp32);
    CopyMem (&Temp16, &Private->Mode->CurrentAddress.Addr[4], sizeof (UINT16));
    FilterProgram[3].k = NTOHS (Temp16);

    BpfProgram.bf_len = sizeof (mFilterInstructionTemplate) / sizeof (struct bpf_insn);
    BpfProgram.bf_insns = FilterProgram;

    if (ioctl (Private->BpfFd, BIOCSETF, &BpfProgram) < 0) {
      goto DeviceErrorExit;
    }

    free (FilterProgram);

    //
    // Enable promiscuous mode.
    //
    if (ioctl (Private->BpfFd, BIOCPROMISC, 0) < 0) {
      goto DeviceErrorExit;
    }


    Private->Mode->State = EfiSimpleNetworkStarted;
  }

  return Status;

DeviceErrorExit:
  Status = EFI_DEVICE_ERROR;
ErrorExit:
  if (Private->ReadBuffer != NULL) {
    free (Private->ReadBuffer);
    Private->ReadBuffer = NULL;
  }
  return Status;
}
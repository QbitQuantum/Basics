VOID
NdisReadNetworkAddress(
	OUT PNDIS_STATUS				Status,
	OUT PVOID *						NetworkAddress,
	OUT PUINT						NetworkAddressLength,
	IN NDIS_HANDLE					ConfigurationHandle
	)
/*++

Routine Description:

	This routine is used to read the "NetworkAddress" parameter
	from the configuration database. It reads the value as a
	string separated by hyphens, then converts it to a binary
	array and stores the result.

Arguments:

	Status - Returns the status of the request.

	NetworkAddress - Returns a pointer to the address.

	NetworkAddressLength - Returns the length of the address.

	ConfigurationHandle - Handle returned by NdisOpenConfiguration. Points
	to the parameter subkey.

Return Value:

	None.

--*/
{
	NDIS_STRING						NetAddrStr = NDIS_STRING_CONST("NetworkAddress");
	PNDIS_CONFIGURATION_PARAMETER	ParameterValue;
	NTSTATUS						NtStatus;
	UCHAR							ConvertArray[3];
	PWSTR							CurrentReadLoc;
	PWSTR							AddressEnd;
	PUCHAR							CurrentWriteLoc;
	UINT							TotalBytesRead;
	ULONG							TempUlong;
	ULONG							AddressLength;

	ASSERT (KeGetCurrentIrql() < DISPATCH_LEVEL);

	do
	{
		//
		// First read the "NetworkAddress" from the registry
		//
		NdisReadConfiguration(Status, &ParameterValue, ConfigurationHandle, &NetAddrStr, NdisParameterString);

		if ((*Status != NDIS_STATUS_SUCCESS) ||
            (ParameterValue->ParameterType != NdisParameterString))
		{
			*Status = NDIS_STATUS_FAILURE;
			break;
		}

		//
		//	If there is not an address specified then exit now.
		//
		if (0 == ParameterValue->ParameterData.StringData.Length)
		{
			*Status = NDIS_STATUS_FAILURE;
			break;
		}

		//
		// Now convert the address to binary (we do this
		// in-place, since this allows us to use the memory
		// already allocated which is automatically freed
		// by NdisCloseConfiguration).
		//

		ConvertArray[2] = '\0';
		CurrentReadLoc = (PWSTR)ParameterValue->ParameterData.StringData.Buffer;
		CurrentWriteLoc = (PUCHAR)CurrentReadLoc;
		TotalBytesRead = ParameterValue->ParameterData.StringData.Length;
		AddressEnd = CurrentReadLoc + (TotalBytesRead / sizeof(WCHAR));
		AddressLength = 0;

		while ((CurrentReadLoc+2) <= AddressEnd)
		{
			//
			// Copy the current two-character value into ConvertArray
			//
			ConvertArray[0] = (UCHAR)(*(CurrentReadLoc++));
			ConvertArray[1] = (UCHAR)(*(CurrentReadLoc++));

			//
			// Convert it to a Ulong and update
			//
			NtStatus = RtlCharToInteger(ConvertArray, 16, &TempUlong);

			if (!NT_SUCCESS(NtStatus))
			{
				*Status = NDIS_STATUS_FAILURE;
				break;
			}

			*(CurrentWriteLoc++) = (UCHAR)TempUlong;
			++AddressLength;

			//
			// If the next character is a hyphen, skip it.
			//
			if (CurrentReadLoc < AddressEnd)
			{
				if (*CurrentReadLoc == (WCHAR)L'-')
				{
					++CurrentReadLoc;
				}
			}
		}

		if (NtStatus != NDIS_STATUS_SUCCESS)
			break;

		*Status = STATUS_SUCCESS;
		*NetworkAddress = ParameterValue->ParameterData.StringData.Buffer;
		*NetworkAddressLength = AddressLength;
		if (AddressLength == 0)
		{
			*Status = NDIS_STATUS_FAILURE;
		}
	} while (FALSE);
}
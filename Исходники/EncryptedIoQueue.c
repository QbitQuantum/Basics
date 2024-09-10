static VOID MainThreadProc (PVOID threadArg)
{
	EncryptedIoQueue *queue = (EncryptedIoQueue *) threadArg;
	PLIST_ENTRY listEntry;
	EncryptedIoQueueItem *item;

	LARGE_INTEGER fragmentOffset;
	ULONG dataRemaining;
	PUCHAR activeFragmentBuffer = queue->FragmentBufferA;
	PUCHAR dataBuffer;
	EncryptedIoRequest *request;
	uint64 intersectStart;
	uint32 intersectLength;
	ULONGLONG addResult;
	HRESULT hResult;

	if (IsEncryptionThreadPoolRunning())
		KeSetPriorityThread (KeGetCurrentThread(), LOW_REALTIME_PRIORITY);

	while (!queue->ThreadExitRequested)
	{
		if (!NT_SUCCESS (KeWaitForSingleObject (&queue->MainThreadQueueNotEmptyEvent, Executive, KernelMode, FALSE, NULL)))
			continue;

		while ((listEntry = ExInterlockedRemoveHeadList (&queue->MainThreadQueue, &queue->MainThreadQueueLock)))
		{
			PIRP irp = CONTAINING_RECORD (listEntry, IRP, Tail.Overlay.ListEntry);
			PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation (irp);
			
			if (queue->Suspended)
				KeWaitForSingleObject (&queue->QueueResumedEvent, Executive, KernelMode, FALSE, NULL);

			item = GetPoolBuffer (queue, sizeof (EncryptedIoQueueItem));
			if (!item)
			{
				TCCompleteDiskIrp (irp, STATUS_INSUFFICIENT_RESOURCES, 0);
				DecrementOutstandingIoCount (queue);
				IoReleaseRemoveLock (&queue->RemoveLock, irp);

				continue;
			}

			item->Queue = queue;
			item->OriginalIrp = irp;
			item->Status = STATUS_SUCCESS;

			IoSetCancelRoutine (irp, NULL);
			if (irp->Cancel)
			{
				CompleteOriginalIrp (item, STATUS_CANCELLED, 0);
				continue;
			}

			switch (irpSp->MajorFunction)
			{
			case IRP_MJ_READ:
				item->Write = FALSE;
				item->OriginalOffset = irpSp->Parameters.Read.ByteOffset;
				item->OriginalLength = irpSp->Parameters.Read.Length;
				break;

			case IRP_MJ_WRITE:
				item->Write = TRUE;
				item->OriginalOffset = irpSp->Parameters.Write.ByteOffset;
				item->OriginalLength = irpSp->Parameters.Write.Length;
				break;

			default:
				CompleteOriginalIrp (item, STATUS_INVALID_PARAMETER, 0);
				continue;
			}

#ifdef TC_TRACE_IO_QUEUE
			item->OriginalIrpOffset = item->OriginalOffset;
#endif

			// Handle misaligned read operations to work around a bug in Windows System Assessment Tool which does not follow FILE_FLAG_NO_BUFFERING requirements when benchmarking disk devices
			if (queue->IsFilterDevice
				&& !item->Write
				&& item->OriginalLength > 0
				&& (item->OriginalLength & (ENCRYPTION_DATA_UNIT_SIZE - 1)) == 0
				&& (item->OriginalOffset.QuadPart & (ENCRYPTION_DATA_UNIT_SIZE - 1)) != 0)
			{
				byte *buffer;
				ULONG alignedLength;
				LARGE_INTEGER alignedOffset;
				hResult = ULongAdd(item->OriginalLength, ENCRYPTION_DATA_UNIT_SIZE, &alignedLength);
				if (hResult != S_OK)
				{
					CompleteOriginalIrp (item, STATUS_INVALID_PARAMETER, 0);
					continue;
				}

				alignedOffset.QuadPart = item->OriginalOffset.QuadPart & ~((LONGLONG) ENCRYPTION_DATA_UNIT_SIZE - 1);

				buffer = TCalloc (alignedLength);
				if (!buffer)
				{
					CompleteOriginalIrp (item, STATUS_INSUFFICIENT_RESOURCES, 0);
					continue;
				}

				item->Status = TCReadDevice (queue->LowerDeviceObject, buffer, alignedOffset, alignedLength);

				if (NT_SUCCESS (item->Status))
				{
					UINT64_STRUCT dataUnit;

					dataBuffer = (PUCHAR) MmGetSystemAddressForMdlSafe (irp->MdlAddress, HighPagePriority);
					if (!dataBuffer)
					{
						TCfree (buffer);
						CompleteOriginalIrp (item, STATUS_INSUFFICIENT_RESOURCES, 0);
						continue;
					}

					if (queue->EncryptedAreaStart != -1 && queue->EncryptedAreaEnd != -1)
					{
						GetIntersection (alignedOffset.QuadPart, alignedLength, queue->EncryptedAreaStart, queue->EncryptedAreaEnd, &intersectStart, &intersectLength);
						if (intersectLength > 0)
						{
							dataUnit.Value = intersectStart / ENCRYPTION_DATA_UNIT_SIZE;
							DecryptDataUnits (buffer + (intersectStart - alignedOffset.QuadPart), &dataUnit, intersectLength / ENCRYPTION_DATA_UNIT_SIZE, queue->CryptoInfo);
						}
					}

					memcpy (dataBuffer, buffer + (item->OriginalOffset.LowPart & (ENCRYPTION_DATA_UNIT_SIZE - 1)), item->OriginalLength);
				}

				TCfree (buffer);
				CompleteOriginalIrp (item, item->Status, NT_SUCCESS (item->Status) ? item->OriginalLength : 0);
				continue;
			}

			// Validate offset and length
			if (item->OriginalLength == 0
				|| (item->OriginalLength & (ENCRYPTION_DATA_UNIT_SIZE - 1)) != 0
				|| (item->OriginalOffset.QuadPart & (ENCRYPTION_DATA_UNIT_SIZE - 1)) != 0
				|| (	!queue->IsFilterDevice && 
						(	(S_OK != ULongLongAdd(item->OriginalOffset.QuadPart, item->OriginalLength, &addResult))
							||	(addResult > (ULONGLONG) queue->VirtualDeviceLength)
						)
					)
				)
			{
				CompleteOriginalIrp (item, STATUS_INVALID_PARAMETER, 0);
				continue;
			}

#ifdef TC_TRACE_IO_QUEUE
			Dump ("Q  %I64d [%I64d] %c len=%d\n", item->OriginalOffset.QuadPart, GetElapsedTime (&queue->LastPerformanceCounter), item->Write ? 'W' : 'R', item->OriginalLength);
#endif

			if (!queue->IsFilterDevice)
			{
				// Adjust the offset for host file or device
				if (queue->CryptoInfo->hiddenVolume)
					hResult = ULongLongAdd(item->OriginalOffset.QuadPart, queue->CryptoInfo->hiddenVolumeOffset, &addResult);
				else
					hResult = ULongLongAdd(item->OriginalOffset.QuadPart, queue->CryptoInfo->volDataAreaOffset, &addResult); 

				if (hResult != S_OK)
				{
					CompleteOriginalIrp (item, STATUS_INVALID_PARAMETER, 0);
					continue;
				}
				else
					item->OriginalOffset.QuadPart = addResult;

				// Hidden volume protection
				if (item->Write && queue->CryptoInfo->bProtectHiddenVolume)
				{
					// If there has already been a write operation denied in order to protect the
					// hidden volume (since the volume mount time)
					if (queue->CryptoInfo->bHiddenVolProtectionAction)	
					{
						// Do not allow writing to this volume anymore. This is to fake a complete volume
						// or system failure (otherwise certain kinds of inconsistency within the file
						// system could indicate that this volume has used hidden volume protection).
						CompleteOriginalIrp (item, STATUS_INVALID_PARAMETER, 0);
						continue;
					}

					// Verify that no byte is going to be written to the hidden volume area
					if (RegionsOverlap ((unsigned __int64) item->OriginalOffset.QuadPart,
						(unsigned __int64) item->OriginalOffset.QuadPart + item->OriginalLength - 1,
						queue->CryptoInfo->hiddenVolumeOffset,
						(unsigned __int64) queue->CryptoInfo->hiddenVolumeOffset + queue->CryptoInfo->hiddenVolumeProtectedSize - 1))
					{
						Dump ("Hidden volume protection triggered: write %I64d-%I64d (protected %I64d-%I64d)\n", item->OriginalOffset.QuadPart, item->OriginalOffset.QuadPart + item->OriginalLength - 1, queue->CryptoInfo->hiddenVolumeOffset, queue->CryptoInfo->hiddenVolumeOffset + queue->CryptoInfo->hiddenVolumeProtectedSize - 1);
						queue->CryptoInfo->bHiddenVolProtectionAction = TRUE;

						// Deny this write operation to prevent the hidden volume from being overwritten
						CompleteOriginalIrp (item, STATUS_INVALID_PARAMETER, 0);
						continue;
					}
				}
			}
			else if (item->Write
				&& RegionsOverlap (item->OriginalOffset.QuadPart, item->OriginalOffset.QuadPart + item->OriginalLength - 1, TC_BOOT_VOLUME_HEADER_SECTOR_OFFSET, TC_BOOT_VOLUME_HEADER_SECTOR_OFFSET + TC_BOOT_ENCRYPTION_VOLUME_HEADER_SIZE - 1))
			{
				// Prevent inappropriately designed software from damaging important data that may be out of sync with the backup on the Rescue Disk (such as the end of the encrypted area).
				Dump ("Preventing write to the system encryption key data area\n");
				CompleteOriginalIrp (item, STATUS_MEDIA_WRITE_PROTECTED, 0);
				continue;
			}
			else if (item->Write && IsHiddenSystemRunning()
				&& (RegionsOverlap (item->OriginalOffset.QuadPart, item->OriginalOffset.QuadPart + item->OriginalLength - 1, TC_SECTOR_SIZE_BIOS, TC_BOOT_LOADER_AREA_SECTOR_COUNT * TC_SECTOR_SIZE_BIOS - 1)
				 || RegionsOverlap (item->OriginalOffset.QuadPart, item->OriginalOffset.QuadPart + item->OriginalLength - 1, GetBootDriveLength(), _I64_MAX)))
			{
				Dump ("Preventing write to boot loader or host protected area\n");
				CompleteOriginalIrp (item, STATUS_MEDIA_WRITE_PROTECTED, 0);
				continue;
			}

			dataBuffer = (PUCHAR) MmGetSystemAddressForMdlSafe (irp->MdlAddress, HighPagePriority);

			if (dataBuffer == NULL)
			{
				CompleteOriginalIrp (item, STATUS_INSUFFICIENT_RESOURCES, 0);
				continue;
			}

			// Divide data block to fragments to enable efficient overlapping of encryption and IO operations

			dataRemaining = item->OriginalLength;
			fragmentOffset = item->OriginalOffset;

			while (dataRemaining > 0)
			{
				BOOL isLastFragment = dataRemaining <= TC_ENC_IO_QUEUE_MAX_FRAGMENT_SIZE;
				
				ULONG dataFragmentLength = isLastFragment ? dataRemaining : TC_ENC_IO_QUEUE_MAX_FRAGMENT_SIZE;
				activeFragmentBuffer = (activeFragmentBuffer == queue->FragmentBufferA ? queue->FragmentBufferB : queue->FragmentBufferA);

				InterlockedIncrement (&queue->IoThreadPendingRequestCount);

				// Create IO request
				request = GetPoolBuffer (queue, sizeof (EncryptedIoRequest));
				if (!request)
				{
					CompleteOriginalIrp (item, STATUS_INSUFFICIENT_RESOURCES, 0);
					break;
				}
				request->Item = item;
				request->CompleteOriginalIrp = isLastFragment;
				request->Offset = fragmentOffset;
				request->Data = activeFragmentBuffer;
				request->OrigDataBufferFragment = dataBuffer;
				request->Length = dataFragmentLength;

				if (queue->IsFilterDevice)
				{
					if (queue->EncryptedAreaStart == -1 || queue->EncryptedAreaEnd == -1)
					{
						request->EncryptedLength = 0;
					}
					else
					{
						// Get intersection of data fragment with encrypted area
						GetIntersection (fragmentOffset.QuadPart, dataFragmentLength, queue->EncryptedAreaStart, queue->EncryptedAreaEnd, &intersectStart, &intersectLength);

						request->EncryptedOffset = intersectStart - fragmentOffset.QuadPart;
						request->EncryptedLength = intersectLength;
					}
				}
				else
				{
					request->EncryptedOffset = 0;
					request->EncryptedLength = dataFragmentLength;
				}

				AcquireFragmentBuffer (queue, activeFragmentBuffer);

				if (item->Write)
				{
					// Encrypt data
					memcpy (activeFragmentBuffer, dataBuffer, dataFragmentLength);

					if (request->EncryptedLength > 0)
					{
						UINT64_STRUCT dataUnit;
						ASSERT (request->EncryptedOffset + request->EncryptedLength <= request->Offset.QuadPart + request->Length);

						dataUnit.Value = (request->Offset.QuadPart + request->EncryptedOffset) / ENCRYPTION_DATA_UNIT_SIZE;

						if (queue->CryptoInfo->bPartitionInInactiveSysEncScope)
							dataUnit.Value += queue->CryptoInfo->FirstDataUnitNo.Value;
						else if (queue->RemapEncryptedArea)
							dataUnit.Value += queue->RemappedAreaDataUnitOffset;
								
						EncryptDataUnits (activeFragmentBuffer + request->EncryptedOffset, &dataUnit, request->EncryptedLength / ENCRYPTION_DATA_UNIT_SIZE, queue->CryptoInfo);
					}
				}

				// Queue IO request
				ExInterlockedInsertTailList (&queue->IoThreadQueue, &request->ListEntry, &queue->IoThreadQueueLock);
				KeSetEvent (&queue->IoThreadQueueNotEmptyEvent, IO_DISK_INCREMENT, FALSE);

				if (isLastFragment)
					break;

				dataRemaining -= TC_ENC_IO_QUEUE_MAX_FRAGMENT_SIZE;
				dataBuffer += TC_ENC_IO_QUEUE_MAX_FRAGMENT_SIZE;
				fragmentOffset.QuadPart += TC_ENC_IO_QUEUE_MAX_FRAGMENT_SIZE;
			}
		}
	}

	PsTerminateSystemThread (STATUS_SUCCESS);
}
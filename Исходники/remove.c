BOOLEAN
SpRemoveLogicalUnit(
    IN PDEVICE_OBJECT LogicalUnit,
    IN UCHAR RemoveType
    )

{
    PLOGICAL_UNIT_EXTENSION logicalUnitExtension = LogicalUnit->DeviceExtension;
    PCOMMON_EXTENSION commonExtension = LogicalUnit->DeviceExtension;
    PADAPTER_EXTENSION adapterExtension = logicalUnitExtension->AdapterExtension;

    ULONG isRemoved;
    ULONG oldDebugLevel;

    PAGED_CODE();

    if(commonExtension->IsRemoved != REMOVE_COMPLETE) {

        if(RemoveType == IRP_MN_REMOVE_DEVICE) {

            SpWaitForRemoveLock(LogicalUnit, UIntToPtr( 0xabcdabcd) );

            //
            // If the device was claimed we should release it now.
            //

            if(logicalUnitExtension->IsClaimed) {
                logicalUnitExtension->IsClaimed = FALSE;
                logicalUnitExtension->IsLegacyClaim = FALSE;
            }

        }

        DebugPrint((1, "SpRemoveLogicalUnit - %sremoving device %#p\n",
                    (RemoveType == IRP_MN_SURPRISE_REMOVAL) ? "surprise " : "",
                    LogicalUnit));

        //
        // If the lun isn't marked as missing yet or is marked as missing but 
        // PNP hasn't been informed yet then we cannot delete it.  Set it back 
        // to the NO_REMOVE state so that we'll be able to attempt a rescan.
        //
        // Likewise if the lun is invisible then just swallow the remove 
        // operation now that we've cleared any existing claims.
        //

        if(RemoveType == IRP_MN_REMOVE_DEVICE) {

            //
            // If the device is not missing or is missing but is still 
            // enumerated then don't finish destroying it.
            //

            if((logicalUnitExtension->IsMissing == TRUE) &&
               (logicalUnitExtension->IsEnumerated == FALSE)) {

                // do nothing here - fall through and destroy the device.

            } else {

                DebugPrint((1, "SpRemoveLogicalUnit - device is not missing "
                               "and will not be destroyed\n"));

                SpAcquireRemoveLock(LogicalUnit, UIntToPtr( 0xabcdabcd ));

                logicalUnitExtension->CommonExtension.IsRemoved = NO_REMOVE;

                return FALSE;
            }

        } else if((logicalUnitExtension->IsVisible == FALSE) && 
                  (logicalUnitExtension->IsMissing == FALSE)) {

            //
            // The surprise remove came because the device is no longer 
            // visible.  We don't want to destroy it.
            //

            return FALSE;
        }

        //
        // Mark the device as uninitialized so that we'll go back and
        // recreate all the necessary stuff if it gets restarted.
        //

        commonExtension->IsInitialized = FALSE;

        //
        // Delete the device map entry for this one (if any).
        //

        SpDeleteDeviceMapEntry(LogicalUnit);

        if(RemoveType == IRP_MN_REMOVE_DEVICE) {

            ASSERT(logicalUnitExtension->RequestTimeoutCounter == -1);
            ASSERT(logicalUnitExtension->ReadyLogicalUnit == NULL);
            ASSERT(logicalUnitExtension->PendingRequest == NULL);
            ASSERT(logicalUnitExtension->BusyRequest == NULL);
            ASSERT(logicalUnitExtension->QueueCount == 0);
    
            commonExtension->IsRemoved = REMOVE_COMPLETE;
            SpDeleteLogicalUnit(LogicalUnit);
        }
    }

    return TRUE;
}
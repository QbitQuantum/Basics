int checkDiscovery() {
    if (freespace_private_discoveryStatusChanged()) {
        int rc;
        int totalChanges = 0;

        // Wait for system to stabilize before scanning.
        if (CMP_WaitNoPendingInstallEvents(0) == WAIT_TIMEOUT) {
            DEBUG_PRINTF("Pending install events.  Wait for resolution.\n");
            freespace_private_requestDeviceRescan();
            return FREESPACE_ERROR_BUSY;
        }

        DEBUG_WPRINTF(L"Scanning devices\n");

        // Mark and sweep the device list.
        freespace_private_filterDevices(NULL, 0, NULL, filterInitialize);

        // Mark everything that still exists and add new devices
        rc = freespace_private_scanAndAddDevices();
        if (rc != FREESPACE_SUCCESS) {
            // Unexpected error.  Schedule a rescan.
            DEBUG_WPRINTF(L"Error %d while scanning devices.  Request a rescan.\n", rc);
            freespace_private_requestDeviceRescan();
            return rc;
        }

        // Handle all changes.
        totalChanges += checkDiscoveryRemoveDevices();
        totalChanges += checkDiscoveryPartiallyRemovedDevices();
        totalChanges += checkDiscoveryAddedDevices();

        /*
         * Continue to schedule a rescan until no changes are detected.
         * Although this should not be necessary, rescanning until a
         * stable state is reached should increase robustness.
         */
        if (totalChanges != 0) {
            DEBUG_WPRINTF(L"Detected %d changes.  Schedule rescan\n", totalChanges);
            freespace_private_requestDeviceRescan();
        }
    }

    return freespace_private_discoveryGetThreadStatus();
}
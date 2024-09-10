static void deviceInformationResponseHandler(const EmberEUI64 source,
                                             uint32_t transaction,
                                             uint8_t numberOfSubDevices,
                                             uint8_t startIndex,
                                             uint8_t deviceInformationRecordCount,
                                             uint8_t *deviceInformationRecordList)
{
  uint16_t deviceInformationRecordListLen = (deviceInformationRecordCount
                                           * ZLL_DEVICE_INFORMATION_RECORD_SIZE);
  uint16_t deviceInformationRecordListIndex = 0;
  uint8_t i;
  bool validResponse = (emberEventControlGetActive(emberAfPluginZllCommissioningTouchLinkEventControl)
                           && (network.securityAlgorithm.transactionId == transaction)
                           && MEMCOMPARE(network.eui64, source, EUI64_SIZE) == 0);

  emberAfZllCommissioningClusterFlush();
  emberAfZllCommissioningClusterPrint("RX: DeviceInformationResponse 0x%4x, 0x%x, 0x%x, 0x%x,",
                                      transaction,
                                      numberOfSubDevices,
                                      startIndex,
                                      deviceInformationRecordCount);
  emberAfZllCommissioningClusterFlush();
  for (i = 0; i < deviceInformationRecordCount; i++) {
    uint8_t *ieeeAddress;
    uint8_t endpointId;
    uint16_t profileId;
    uint16_t deviceId;
    uint8_t version;
    uint8_t groupIdCount;
    uint8_t sort;
    ieeeAddress = &deviceInformationRecordList[deviceInformationRecordListIndex];
    deviceInformationRecordListIndex += EUI64_SIZE;
    endpointId = emberAfGetInt8u(deviceInformationRecordList, deviceInformationRecordListIndex, deviceInformationRecordListLen);
    deviceInformationRecordListIndex++;
    profileId = emberAfGetInt16u(deviceInformationRecordList, deviceInformationRecordListIndex, deviceInformationRecordListLen);
    deviceInformationRecordListIndex += 2;
    deviceId = emberAfGetInt16u(deviceInformationRecordList, deviceInformationRecordListIndex, deviceInformationRecordListLen);
    deviceInformationRecordListIndex += 2;
    version = emberAfGetInt8u(deviceInformationRecordList, deviceInformationRecordListIndex, deviceInformationRecordListLen);
    deviceInformationRecordListIndex++;
    groupIdCount = emberAfGetInt8u(deviceInformationRecordList, deviceInformationRecordListIndex, deviceInformationRecordListLen);
    deviceInformationRecordListIndex++;
    sort = emberAfGetInt8u(deviceInformationRecordList, deviceInformationRecordListIndex, deviceInformationRecordListLen);
    deviceInformationRecordListIndex++;
    emberAfZllCommissioningClusterPrint(" [");
    emberAfZllCommissioningClusterDebugExec(emberAfPrintBigEndianEui64(ieeeAddress));
    emberAfZllCommissioningClusterPrint(" 0x%x 0x%2x 0x%2x 0x%x 0x%x 0x%x",
                                        endpointId,
                                        profileId,
                                        deviceId,
                                        version,
                                        groupIdCount,
                                        sort);
    emberAfZllCommissioningClusterFlush();

    if (validResponse
        && (subDeviceCount
            < EMBER_AF_PLUGIN_ZLL_COMMISSIONING_SUB_DEVICE_TABLE_SIZE)) {
      MEMMOVE(subDevices[subDeviceCount].ieeeAddress, ieeeAddress, EUI64_SIZE);
      subDevices[subDeviceCount].endpointId = endpointId;
      subDevices[subDeviceCount].profileId = profileId;
      subDevices[subDeviceCount].deviceId = deviceId;
      subDevices[subDeviceCount].version = version;
      subDevices[subDeviceCount].groupIdCount = groupIdCount;
      subDeviceCount++;
    } else {
      emberAfZllCommissioningClusterPrint(" (ignored)");
    }
    emberAfZllCommissioningClusterPrint("]");
    emberAfZllCommissioningClusterFlush();
  }
  emberAfZllCommissioningClusterPrintln("");

  if (validResponse
      && (subDeviceCount
          < EMBER_AF_PLUGIN_ZLL_COMMISSIONING_SUB_DEVICE_TABLE_SIZE)
      && subDeviceCount < numberOfSubDevices) {
    sendDeviceInformationRequest(startIndex + deviceInformationRecordCount);
  }
}
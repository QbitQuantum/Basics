/*
 * Handle the flash page replies
 */
void FirmwareTransferer::HandleMessage(uint8_t label,
                                       const uint8_t *data,
                                       unsigned int length) {
  if (label != FLASH_PAGE_LABEL || length != FLASH_STATUS_LENGTH)
    return;

  if (0 == memcmp(data, REPLY_SUCCESS, sizeof(FLASH_STATUS_LENGTH))) {
    if (!SendNextChunk() || m_sucessful)
      m_ss->Terminate();
  } else {
    OLA_FATAL << "Bad response from widget:" << string((const char*) data, 4);
    m_ss->Terminate();
  }
}
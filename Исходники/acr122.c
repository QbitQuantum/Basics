int
acr122_send (nfc_device *pnd, const uint8_t *pbtData, const size_t szData, int timeout)
{
  // FIXME: timeout is not handled
  (void) timeout;

  // Make sure the command does not overflow the send buffer
  if (szData > ACR122_COMMAND_LEN) {
    pnd->last_error = NFC_EINVARG;
    return pnd->last_error;
  }

  // Prepare and transmit the send buffer
  const size_t szTxBuf = szData + 6;
  uint8_t  abtTxBuf[ACR122_WRAP_LEN + ACR122_COMMAND_LEN] = { 0xFF, 0x00, 0x00, 0x00, szData + 1, 0xD4 };
  memcpy (abtTxBuf + 6, pbtData, szData);
  LOG_HEX ("TX", abtTxBuf, szTxBuf);

  DRIVER_DATA (pnd)->szRx = 0;

  DWORD dwRxLen = sizeof (DRIVER_DATA (pnd)->abtRx);

  if (DRIVER_DATA (pnd)->ioCard.dwProtocol == SCARD_PROTOCOL_UNDEFINED) {
    /*
     * In this communication mode, we directly have the response from the
     * PN532.  Save it in the driver data structure so that it can be retrieved
     * in ac122_receive().
     *
     * Some devices will never enter this state (e.g. Touchatag) but are still
     * supported through SCardTransmit calls (see bellow).
     *
     * This state is generaly reached when the ACR122 has no target in it's
     * field.
     */
    if (SCardControl (DRIVER_DATA (pnd)->hCard, IOCTL_CCID_ESCAPE_SCARD_CTL_CODE, abtTxBuf, szTxBuf, DRIVER_DATA (pnd)->abtRx, ACR122_RESPONSE_LEN, &dwRxLen) != SCARD_S_SUCCESS) {
      pnd->last_error = NFC_EIO;
      return pnd->last_error;
    }
  } else {
    /*
     * In T=0 mode, we receive an acknoledge from the MCU, in T=1 mode, we
     * receive the response from the PN532.
     */
    if (SCardTransmit (DRIVER_DATA (pnd)->hCard, &(DRIVER_DATA (pnd)->ioCard), abtTxBuf, szTxBuf, NULL, DRIVER_DATA (pnd)->abtRx, &dwRxLen) != SCARD_S_SUCCESS) {
      pnd->last_error = NFC_EIO;
      return pnd->last_error;
    }
  }

  if (DRIVER_DATA (pnd)->ioCard.dwProtocol == SCARD_PROTOCOL_T0) {
   /*
    * Check the MCU response
    */

    // Make sure we received the byte-count we expected
    if (dwRxLen != 2) {
      pnd->last_error = NFC_EIO;
      return pnd->last_error;
    }
    // Check if the operation was successful, so an answer is available
    if (DRIVER_DATA (pnd)->abtRx[0] == SCARD_OPERATION_ERROR) {
      pnd->last_error = NFC_EIO;
      return pnd->last_error;
    }
  } else {
    DRIVER_DATA (pnd)->szRx = dwRxLen;
  }

  return NFC_SUCCESS;
}
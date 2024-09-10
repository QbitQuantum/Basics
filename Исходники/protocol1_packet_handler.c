void rxPacket1(int port_num)
{
  uint8_t idx, s;
  int i;

  packetData[port_num].communication_result = COMM_TX_FAIL;

  uint8_t checksum = 0;
  uint8_t rx_length = 0;
  uint8_t wait_length = 6;    // minimum length ( HEADER0 HEADER1 ID LENGTH ERROR CHKSUM )

  while (True)
  {
    rx_length += readPort(port_num, &packetData[port_num].rx_packet[rx_length], wait_length - rx_length);
    if (rx_length >= wait_length)
    {
      idx = 0;

      // find packet header
      for (idx = 0; idx < (rx_length - 1); idx++)
      {
        if (packetData[port_num].rx_packet[idx] == 0xFF && packetData[port_num].rx_packet[idx + 1] == 0xFF)
          break;
      }

      if (idx == 0)   // found at the beginning of the packet
      {
        if (packetData[port_num].rx_packet[PKT_ID] > 0xFD ||                   // unavailable ID
            packetData[port_num].rx_packet[PKT_LENGTH] > RXPACKET_MAX_LEN ||   // unavailable Length
            packetData[port_num].rx_packet[PKT_ERROR] >= 0x64)                 // unavailable Error
        {
          // remove the first byte in the packet
          for (s = 0; s < rx_length - 1; s++)
          {
            packetData[port_num].rx_packet[s] = packetData[port_num].rx_packet[1 + s];
          }

          rx_length -= 1;
          continue;
        }

        // re-calculate the exact length of the rx packet
        wait_length = packetData[port_num].rx_packet[PKT_LENGTH] + PKT_LENGTH + 1;
        if (rx_length < wait_length)
        {
          // check timeout
          if (isPacketTimeout(port_num) == True)
          {
            if (rx_length == 0)
              packetData[port_num].communication_result = COMM_RX_TIMEOUT;
            else
              packetData[port_num].communication_result = COMM_RX_CORRUPT;
            break;
          }
          else
          {
            continue;
          }
        }

        // calculate checksum
        for (i = 2; i < wait_length - 1; i++)   // except header, checksum
        {
          checksum += packetData[port_num].rx_packet[i];
        }
        checksum = ~checksum;

        // verify checksum
        if (packetData[port_num].rx_packet[wait_length - 1] == checksum)
        {
          packetData[port_num].communication_result = COMM_SUCCESS;
        }
        else
        {
          packetData[port_num].communication_result = COMM_RX_CORRUPT;
        }
        break;
      }
      else
      {
        // remove unnecessary packets
        for (s = 0; s < rx_length - idx; s++)
        {
          packetData[port_num].rx_packet[s] = packetData[port_num].rx_packet[idx + s];
        }
        rx_length -= idx;
      }
    }
    else
    {
      // check timeout
      if (isPacketTimeout(port_num) == True)
      {
        if (rx_length == 0)
        {
          packetData[port_num].communication_result = COMM_RX_TIMEOUT;
        }
        else
        {
          packetData[port_num].communication_result = COMM_RX_CORRUPT;
        }
        break;
      }
    }
  }
  g_is_using[port_num] = False;
}
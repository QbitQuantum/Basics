void RxPacket1(int port_num)
{
    UINT8_T _idx, _s;
    int _i;

    packetData[port_num].communication_result_ = COMM_TX_FAIL;

    UINT8_T _checksum = 0;
    UINT8_T _rx_length = 0;
    UINT8_T _wait_length = 6;    // minimum length ( HEADER0 HEADER1 ID LENGTH ERROR CHKSUM )

    while (true)
    {
        _rx_length += ReadPort(port_num, &packetData[port_num].rxpacket_[_rx_length], _wait_length - _rx_length);
        if (_rx_length >= _wait_length)
        {
            _idx = 0;

            // find packet header
            for (_idx = 0; _idx < (_rx_length - 1); _idx++)
            {
                if (packetData[port_num].rxpacket_[_idx] == 0xFF && packetData[port_num].rxpacket_[_idx + 1] == 0xFF)
                    break;
            }

            if (_idx == 0)   // found at the beginning of the packet
            {
                if (packetData[port_num].rxpacket_[PKT_ID] > 0xFD ||                   // unavailable ID
                    packetData[port_num].rxpacket_[PKT_LENGTH] > RXPACKET_MAX_LEN ||   // unavailable Length
                    packetData[port_num].rxpacket_[PKT_ERROR] >= 0x64)                 // unavailable Error
                {
                    // remove the first byte in the packet
                    for (_s = 0; _s < _rx_length - 1; _s++)
                        packetData[port_num].rxpacket_[_s] = packetData[port_num].rxpacket_[1 + _s];

                    _rx_length -= 1;
                    continue;
                }

                // re-calculate the exact length of the rx packet
                _wait_length = packetData[port_num].rxpacket_[PKT_LENGTH] + PKT_LENGTH + 1;
                if (_rx_length < _wait_length)
                {
                    // check timeout
                    if (IsPacketTimeout(port_num) == true)
                    {
                        if (_rx_length == 0)
                            packetData[port_num].communication_result_ = COMM_RX_TIMEOUT;
                        else
                            packetData[port_num].communication_result_ = COMM_RX_CORRUPT;
                        break;
                    }
                    else
                        continue;
                }

                // calculate checksum
                for (_i = 2; _i < _wait_length - 1; _i++)   // except header, checksum
                    _checksum += packetData[port_num].rxpacket_[_i];
                _checksum = ~_checksum;

                // verify checksum
                if (packetData[port_num].rxpacket_[_wait_length - 1] == _checksum)
                    packetData[port_num].communication_result_ = COMM_SUCCESS;
                else
                    packetData[port_num].communication_result_ = COMM_RX_CORRUPT;
                break;
            }
            else
            {
                // remove unnecessary packets
                for (_s = 0; _s < _rx_length - _idx; _s++)
                    packetData[port_num].rxpacket_[_s] = packetData[port_num].rxpacket_[_idx + _s];
                _rx_length -= _idx;
            }
        }
        else
        {
            // check timeout
            if (IsPacketTimeout(port_num) == true)
            {
                if (_rx_length == 0)
                    packetData[port_num].communication_result_ = COMM_RX_TIMEOUT;
                else
                    packetData[port_num].communication_result_ = COMM_RX_CORRUPT;
                break;
            }
        }
    }
    is_using_[port_num] = false;
}
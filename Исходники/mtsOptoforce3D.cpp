void mtsOptoforce3D::Run(void)
{
    struct optopacket {
        unsigned char header[4];
        unsigned short count;
        unsigned short status;
        short fx;
        short fy;
        short fz;
        unsigned short checksum;
    };

    union PacketDataType {
        unsigned char bytes[16];
        optopacket packet;
    };

    PacketDataType buffer;
    ProcessQueuedCommands();

    if (connected) {
        bool found = false;
        unsigned short recvChecksum;
#if (CISST_OS == CISST_WINDOWS)
        // On Windows, serialPort.Read seems to always return the requested number
        // of characters, which is sizeof(buffer).
        // Thus, we have to check whether part of the expected packet has been combined
        // with another packet, such as the 7 byte response to the command sent to the sensor.
            int n = serialPort.Read((char *)&buffer, sizeof(buffer));

            while (!found) {
                for (int i = 0; i < n - 3; i++) {
                    if ((buffer.bytes[i] == 170) && (buffer.bytes[i + 1] == 7)
                        && (buffer.bytes[i + 2] == 8) && (buffer.bytes[i + 3] == 10)) {
                        if (i != 0) {                               // If pattern not found at beginning of buffer
                            memmove(buffer.bytes, buffer.bytes + i, n - i);    //    shift so that 170 is in buffer[0]
                            serialPort.Read(buffer.bytes + n - i, i);          //    fill the rest of the buffer
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {                                       // If pattern not yet found
                    memmove(buffer.bytes, buffer.bytes + n - 4, 4);               //    move last 4 characters to beginning of buffer
                    serialPort.Read(buffer.bytes + 4, sizeof(buffer.bytes) - 4);  //    get another 12 characters
                }
            }
            // Now, process the data
            RawSensor.X() = (double)static_cast<short>(_byteswap_ushort(buffer.packet.fx)) * scale.X();
            RawSensor.Y() = (double)static_cast<short>(_byteswap_ushort(buffer.packet.fy)) * scale.Y();
            RawSensor.Z() = (double)static_cast<short>(_byteswap_ushort(buffer.packet.fz)) * scale.Z();
            Count = _byteswap_ushort(buffer.packet.count);
            Status = _byteswap_ushort(buffer.packet.status);
            recvChecksum = _byteswap_ushort(buffer.packet.checksum);
#else
        // On Linux, serialPort.Read seems to return a complete packet, even if it is less than the
        // requested size.
        // Thus, we can discard packets that are not the correct size.
        while (!found) {
            if (serialPort.Read((char *)&buffer, sizeof(buffer)) == sizeof(buffer)) {
                // Check for expected 4 byte packet header
                found = ((buffer.bytes[0] == 170) && (buffer.bytes[1] == 7)
                    && (buffer.bytes[2] == 8) && (buffer.bytes[3] == 10));
            }
        }
        // Now, process the data
        RawSensor.X() = (double)static_cast<short>(bswap_16(buffer.packet.fx)) * scale.X();
        RawSensor.Y() = (double)static_cast<short>(bswap_16(buffer.packet.fy)) * scale.Y();
        RawSensor.Z() = (double)static_cast<short>(bswap_16(buffer.packet.fz)) * scale.Z();
        Count = bswap_16(buffer.packet.count);
        Status = bswap_16(buffer.packet.status);
        recvChecksum = bswap_16(buffer.packet.checksum);
#endif
        // Verify the checksum (last 2 bytes).
        unsigned short checksum = buffer.bytes[0];
        for (size_t i = 1; i < sizeof(buffer) - 2; i++)
            checksum += buffer.bytes[i];
        // (Status == 0) means no errors or overload warnings.
        // For now, we check ((Status&0xFC00) == 0), which ignores overload warnings.
        bool valid = (checksum == recvChecksum) && ((Status & 0xFC00) == 0);
        ForceTorque.SetValid(valid);

        if (valid) {
            if (calib_valid) {
                Force = RawSensor;
            }
            else if (matrix_a_valid) {
                // Obtain forces by applying the calibration matrix, which depends on sensor-specific calibration
                // values (A) and the assumed length to where the forces are applied (Length), which determines matrix_l (L).
                // The calibration matrix, matrix_cal, is equal to inv(A*L)

                Force = matrix_cal*RawSensor - bias;  // F = inv(A*L)*S - bias

                // Stablize the sensor readings
                ForceCurrent.Assign(Force);

                for (int i=0; i<3; i++) {
                    if(fabs(ForceCurrent.Element(i)) < 0.2)
                        ForceCurrent.Element(i) = 0.0;
            }
                
                Force.Assign(ForceCurrent);

                for (int i=0; i<3; i++)
                    Force.Element(i) = 0.5*ForceCurrent.Element(i) + 
                                        0.5*ForcePrevious.Element(i);
                ForcePrevious.Assign(Force);
            }
            else {
                Force = RawSensor - bias;
            }
            
            ForceTorque.SetForce(vctDouble6(Force.X(), Force.Y(), Force.Z(), 0.0, 0.0, 0.0));
        }
    }
    else {
        ForceTorque.SetValid(false);
        osaSleep(0.1);  // If not connected, wait
    }
}
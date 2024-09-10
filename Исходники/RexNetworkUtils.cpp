    Quaternion GetProcessedQuaternion(const uint8_t* bytes)
    {    
        uint16_t *rot = reinterpret_cast<uint16_t*>((uint16_t*)&bytes[0]);
        Quaternion rotation = UnpackQuaternionFromU16_4(rot);
        rotation.normalize();

        return OpenSimToOgreQuaternion(rotation);
    }
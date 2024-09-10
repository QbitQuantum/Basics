bool IOCtlSrc::ReadDVDInfo()
{
    DWORD unused;
    DVD_SESSION_ID session_id;

    BOOL ret = DeviceIoControl(m_device, IOCTL_DVD_START_SESSION, nullptr, 0,
                               &session_id, sizeof(session_id), &unused, nullptr);
    if (!ret)
        return false;

    // 4 bytes header + 18 bytes layer descriptor - Technically you only need
    // to read 17 bytes of the layer descriptor since bytes 17-2047 is for
    // media specific information. However, Windows requires you to read at
    // least 18 bytes of the layer descriptor or else the ioctl will fail. The
    // media specific information seems to be empty, so there's no point reading
    // any more than that.
    std::array<u8, 22> buffer;
    DVD_READ_STRUCTURE dvdrs{{0}, DvdPhysicalDescriptor, session_id, 0};

    ret = DeviceIoControl(m_device, IOCTL_DVD_READ_STRUCTURE, &dvdrs, sizeof(dvdrs),
                          buffer.data(), buffer.size(), &unused, nullptr);
    if (ret) {
        auto &layer = *reinterpret_cast<DVD_LAYER_DESCRIPTOR *>(
            reinterpret_cast<DVD_DESCRIPTOR_HEADER *>(buffer.data())->Data);

        u32 start_sector = _byteswap_ulong(layer.StartingDataSector);
        u32 end_sector = _byteswap_ulong(layer.EndDataSector);

        if (layer.NumberOfLayers == 0) {
            // Single layer
            m_media_type = 0;
            m_layer_break = 0;
            m_sectors = end_sector - start_sector + 1;
        } else if (layer.TrackPath == 0) {
            // Dual layer, Parallel Track Path
            dvdrs.LayerNumber = 1;
            ret = DeviceIoControl(m_device, IOCTL_DVD_READ_STRUCTURE, &dvdrs,
                                  sizeof(dvdrs), buffer.data(), buffer.size(), &unused, nullptr);
            if (ret) {
                u32 layer1_start_sector = _byteswap_ulong(layer.StartingDataSector);
                u32 layer1_end_sector = _byteswap_ulong(layer.EndDataSector);

                m_media_type = 1;
                m_layer_break = end_sector - start_sector;
                m_sectors = end_sector - start_sector + 1 + layer1_end_sector - layer1_start_sector + 1;
            }
        } else {
            // Dual layer, Opposite Track Path
            u32 end_sector_layer0 = _byteswap_ulong(layer.EndLayerZeroSector);
            m_media_type = 2;
            m_layer_break = end_sector_layer0 - start_sector;
            m_sectors = end_sector_layer0 - start_sector + 1 + end_sector - (~end_sector_layer0 & 0xFFFFFFU) + 1;
        }
    }

    DeviceIoControl(m_device, IOCTL_DVD_END_SESSION, &session_id,
                    sizeof(session_id), nullptr, 0, &unused, nullptr);

    return !!ret;
}
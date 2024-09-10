SoftSectoredDisk::SoftSectoredDisk(const char*     name,
                                   DiskImageFormat format): initialized_m(false)
{
    debugss(ssFloppyDisk, INFO, "Insert Disk: %s\n", name);

    if (format == dif_Unknown)
    {
        determineDiskFormat(name, format);
    }

    switch (format)
    {
        case dif_IMD:
            readIMD(name);
            break;

        case dif_TD0:
            readTD0(name);
            break;

        case dif_RAW:
            readRaw(name);
            break;

        case dif_8RAW:
            readRaw8(name);
            break;

        default:
            // Unknown format
            debugss(ssFloppyDisk, ERROR, "Unknown disk format: %d\n", format);

            break;
    }
}
static void PrvFillDeviceName(char* buffer, UInt16 length)
{
    UInt32 vendor = 0, device = 0;
    FtrGet(sysFtrCreator, sysFtrNumOEMCompanyID, &vendor);
    FtrGet(sysFtrCreator, sysFtrNumOEMDeviceID, &device);
    const char* vendorText = "Unknown";
    const char* deviceText = NULL;

    // TODO: update vendor/devices list (can't use array because of globals)
    switch (vendor)
    {
        case 'hspr':
            vendorText = "";
            switch (device) {
                case 0xb: deviceText = "Treo 180"; break;
                case 0xd: deviceText = "Treo 270"; break;
                case 0xe: deviceText = "Treo 300"; break;
                case 'H101': deviceText = "Treo 600"; break;
                case 'H201': deviceText = "Treo 600 Simulator"; break;
                case 'H102': deviceText = "Treo 650"; break;
                case 'H202': deviceText = "Treo 650 Simulator"; break;
            }
            break;

        case 'sony':
            vendorText = "Sony";
            switch (device) {
                case 'mdna': deviceText = "PEG-T615C"; break;
                case 'prmr': deviceText = "PEG-UX50"; break;
                case 'atom': deviceText = "PEG-TH55"; break;
                case 'mdrd': deviceText = "PEG-NX80V"; break;
                case 'tldo': deviceText = "PEG-NX73V"; break;
                case 'vrna': deviceText = "PEG-TG50"; break;
                case 'crdb': deviceText = "PEG-NX60 or NX70V"; break;
                case 'mcnd': deviceText = "PEG-SJ33"; break;
                case 'glps': deviceText = "PEG-SJ22"; break;
                case 'goku': deviceText = "PEG-TJ35"; break;
                case 'luke': deviceText = "PEG-TJ37"; break;
                case 'ystn': deviceText = "PEG-N610C"; break;
            }
            break;

        case 'palm':
        case 'Palm':
            vendorText = "";
            switch (device) {
                case 'hbbs': deviceText = "Palm m130"; break;
                case 'ecty': deviceText = "Palm m505"; break;
                case 'lith': deviceText = "Palm m515"; break;
                case 'Zpth': deviceText = "Zire 71"; break;
                case 'MT64': deviceText = "Tungsten C"; break;
                case 'atc1': deviceText = "Tungsten W"; break;
                case 'Cct1': deviceText = "Tungsten E"; break;
                case 'Frg1': deviceText = "Tungsten T"; break;
                case 'Frg2': deviceText = "Tungsten T2"; break;
                case 'Arz1': deviceText = "Tungsten T3"; break;
                case 'Zir4': deviceText = "Tungsten E2"; break;
                case 'TnT5': deviceText = "Tungsten T5"; break;
                case 'Cubs': deviceText = "Zire"; break;
                case 'Zi21': deviceText = "Zire 21"; break;
                case 'Zi22': deviceText = "Zire 31"; break;
                case 'Zi72': deviceText = "Zire 72"; break;
                case 'TunX': deviceText = "LifeDrive"; break;
            }
            break;

        case 'psys':
            vendorText = "Palm OS Simulator";
            break;
    }
    StrNCat(buffer, vendorText, length);
    if (NULL != deviceText)
    {
        if (0 != StrLen(vendorText))
            StrNCat(buffer, " ", length);
        StrNCat(buffer, deviceText, length);
    }
}
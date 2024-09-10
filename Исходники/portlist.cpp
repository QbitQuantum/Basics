// Return a list of all serial ports
wxArrayString serial_port_list()
{
    wxArrayString list;
#if defined(LINUX)
    // This is ugly guessing, but Linux doesn't seem to provide anything else.
    // If there really is an API to discover serial devices on Linux, please
    // email [email protected] with the info.  Please?
    // The really BAD aspect is all ports get DTR raised briefly, because linux
    // has no way to open the port without raising DTR, and there isn't any way
    // to tell if the device file really represents hardware without opening it.
    // maybe sysfs or udev provides a useful API??
    DIR *dir;
    struct dirent *f;
    struct stat st;
    unsigned int i, len[NUM_DEVNAMES];
    char s[512];
    int fd, bits;
    termios mytios;

    dir = opendir("/dev/");
    if (dir == NULL) return list;
    for (i=0; i<NUM_DEVNAMES; i++) len[i] = strlen(devnames[i]);
    // Read all the filenames from the /dev directory...
    while ((f = readdir(dir)) != NULL) {
        // ignore everything that doesn't begin with "tty"
        if (strncmp(f->d_name, "tty", 3)) continue;
        // ignore anything that's not a known serial device name
        for (i=0; i<NUM_DEVNAMES; i++) {
            if (!strncmp(f->d_name + 3, devnames[i], len[i])) break;
        }
        if (i >= NUM_DEVNAMES) continue;
        snprintf(s, sizeof(s), "/dev/%s", f->d_name);
        // check if it's a character type device (almost certainly is)
        if (stat(s, &st) != 0 || !(st.st_mode & S_IFCHR)) continue;
        // now see if we can open the file - if the device file is
        // populating /dev but doesn't actually represent a loaded
        // driver, this is where we will detect it.
        fd = open(s, O_RDONLY | O_NOCTTY | O_NONBLOCK);
        if (fd < 0) {
            // if permission denied, give benefit of the doubt
            // (otherwise the port will be invisible to the user
            // and we won't have a to alert them to the permssion
            // problem)
            if (errno == EACCES) list.Add(s);
            // any other error, assume it's not a real device
            continue;
        }
        // does it respond to termios requests? (probably will since
        // the name began with tty).  Some devices where a single
        // driver exports multiple names will open but this is where
        // we can really tell if they work with real hardare.
        if (tcgetattr(fd, &mytios) != 0) {
            close(fd);
            continue;
        }
        // does it respond to reading the control signals?  If it's
        // some sort of non-serial terminal (eg, pseudo terminals)
        // this is where we will detect it's not really a serial port
        if (ioctl(fd, TIOCMGET, &bits) < 0) {
            close(fd);
            continue;
        }
        // it passed all the tests, it's a serial port, or some sort
        // of "terminal" that looks exactly like a real serial port!
        close(fd);
        // unfortunately, Linux always raises DTR when open is called.
        // not nice!  Every serial port is going to get DTR raised
        // and then lowered.  I wish there were a way to prevent this,
        // but it seems impossible.
        list.Add(s);
    }
    closedir(dir);
#elif defined(MACOSX)
    // adapted from SerialPortSample.c, by Apple
    // http://developer.apple.com/samplecode/SerialPortSample/listing2.html
    // and also testserial.c, by Keyspan
    // http://www.keyspan.com/downloads-files/developer/macosx/KesypanTestSerial.c
    // www.rxtx.org, src/SerialImp.c seems to be based on Keyspan's testserial.c
    // neither keyspan nor rxtx properly release memory allocated.
    // more documentation at:
    // http://developer.apple.com/documentation/DeviceDrivers/Conceptual/WorkingWSerial/WWSerial_SerialDevs/chapter_2_section_6.html
    mach_port_t masterPort;
    CFMutableDictionaryRef classesToMatch;
    io_iterator_t serialPortIterator;
    if (IOMasterPort(NULL, &masterPort) != KERN_SUCCESS) return list;
    // a usb-serial adaptor is usually considered a "modem",
    // especially when it implements the CDC class spec
    classesToMatch = IOServiceMatching(kIOSerialBSDServiceValue);
    if (!classesToMatch) return list;
    CFDictionarySetValue(classesToMatch, CFSTR(kIOSerialBSDTypeKey),
                         CFSTR(kIOSerialBSDModemType));
    if (IOServiceGetMatchingServices(masterPort, classesToMatch,
                                     &serialPortIterator) != KERN_SUCCESS) return list;
    macos_ports(&serialPortIterator, list);
    IOObjectRelease(serialPortIterator);
    // but it might be considered a "rs232 port", so repeat this
    // search for rs232 ports
    classesToMatch = IOServiceMatching(kIOSerialBSDServiceValue);
    if (!classesToMatch) return list;
    CFDictionarySetValue(classesToMatch, CFSTR(kIOSerialBSDTypeKey),
                         CFSTR(kIOSerialBSDRS232Type));
    if (IOServiceGetMatchingServices(masterPort, classesToMatch,
                                     &serialPortIterator) != KERN_SUCCESS) return list;
    macos_ports(&serialPortIterator, list);
    IOObjectRelease(serialPortIterator);
#elif defined(WINDOWS)
    // http://msdn.microsoft.com/en-us/library/aa365461(VS.85).aspx
    // page with 7 ways - not all of them work!
    // http://www.naughter.com/enumser.html
    // may be possible to just query the windows registary
    // http://it.gps678.com/2/ca9c8631868fdd65.html
    // search in HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
    // Vista has some special new way, vista-only
    // http://msdn2.microsoft.com/en-us/library/aa814070(VS.85).aspx
    char *buffer, *p;
    //DWORD size = QUERYDOSDEVICE_BUFFER_SIZE;
    DWORD ret;

    buffer = (char *)malloc(QUERYDOSDEVICE_BUFFER_SIZE);
    if (buffer == NULL) return list;
    memset(buffer, 0, QUERYDOSDEVICE_BUFFER_SIZE);
    ret = QueryDosDeviceA(NULL, buffer, QUERYDOSDEVICE_BUFFER_SIZE);
    if (ret) {
        printf("Detect Serial using QueryDosDeviceA: ");
        for (p = buffer; *p; p += strlen(p) + 1) {
            printf(":  %s", p);
            if (strncmp(p, "COM", 3)) continue;
            list.Add(wxString(p) + ":");
        }
    } else {
        char buf[1024];
        buf[0] = 0;
        //win32_err(buf);
        printf("QueryDosDeviceA failed, error \"%s\"\n", buf);
        printf("Detect Serial using brute force GetDefaultCommConfig probing: ");
        for (int i=1; i<=32; i++) {
            printf("try  %s", buf);
            COMMCONFIG cfg;
            DWORD len;
            snprintf(buf, sizeof(buf), "COM%d", i);
            if (GetDefaultCommConfigA(buf, &cfg, &len)) {
                wxString name;
                name.Printf("COM%d:", i);
                list.Add(name);
                printf(":  %s", buf);
            }
        }
    }
    free(buffer);
#endif
    list.Sort();
    return list;
}
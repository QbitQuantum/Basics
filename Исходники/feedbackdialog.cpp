void FeedbackDialog::GenerateSpecs()
{
    // Gather some information about the system and embed it into the report
    QDesktopWidget* screen = QApplication::desktop();
    QString os_version = "Operating system: ";
    QString qt_version = QString("Qt version: ") + QT_VERSION_STR + QString("\n");
    QString total_ram = "Total RAM: ";
    QString number_of_cores = "Number of cores: ";
    QString compiler_bits = "Compiler architecture: ";
    QString compiler_version = "Compiler version: ";
    QString kernel_line = "Kernel: ";
    QString screen_size = "Size of the screen(s): " +
        QString::number(screen->width()) + "x" + QString::number(screen->height()) + "\n";
    QString number_of_screens = "Number of screens: " + QString::number(screen->screenCount()) + "\n";
    QString processor_name = "Processor: ";

    // platform specific code
#ifdef Q_OS_MACX
    number_of_cores += QString::number(sysconf(_SC_NPROCESSORS_ONLN)) + "\n";

    uint64_t memsize;
    size_t len = sizeof(memsize);
    static int mib_s[2] = { CTL_HW, HW_MEMSIZE };
    if (sysctl (mib_s, 2, &memsize, &len, NULL, 0) == 0)
        total_ram += QString::number(memsize/1024/1024) + " MB\n";
    else
        total_ram += "Error getting total RAM information\n";

    int mib[] = {CTL_KERN, KERN_OSRELEASE};
    sysctl(mib, sizeof mib / sizeof(int), NULL, &len, NULL, 0);

    char *kernelVersion = (char *)malloc(sizeof(char)*len);
    sysctl(mib, sizeof mib / sizeof(int), kernelVersion, &len, NULL, 0);

    QString kernelVersionStr = QString(kernelVersion);
    free(kernelVersion);
    int major_version = kernelVersionStr.split(".").first().toUInt() - 4;
    int minor_version = kernelVersionStr.split(".").at(1).toUInt();
    os_version += QString("Mac OS X 10.%1.%2").arg(major_version).arg(minor_version) + " ";

    switch(major_version)
    {
        case 4:  os_version += "\"Tiger\"\n"; break;
        case 5:  os_version += "\"Leopard\"\n"; break;
        case 6:  os_version += "\"Snow Leopard\"\n"; break;
        case 7:  os_version += "\"Lion\"\n"; break;
        case 8:  os_version += "\"Mountain Lion\"\n"; break;
        default: os_version += "\"Unknown version\"\n"; break;
    }
#endif
#ifdef Q_OS_WIN
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    number_of_cores += QString::number(sysinfo.dwNumberOfProcessors) + "\n";
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    total_ram += QString::number(status.ullTotalPhys/1024/1024) + " MB\n";

    switch(QSysInfo::windowsVersion())
    {
        case QSysInfo::WV_NT: os_version += "Windows NT\n"; break;
        case QSysInfo::WV_2000: os_version += "Windows 2000\n"; break;
        case QSysInfo::WV_XP: os_version += "Windows XP\n"; break;
        case QSysInfo::WV_2003: os_version += "Windows Server 2003\n"; break;
        case QSysInfo::WV_VISTA: os_version += "Windows Vista\n"; break;
        case QSysInfo::WV_WINDOWS7: os_version += "Windows 7\n"; break;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
        case QSysInfo::WV_WINDOWS8: os_version += "Windows 8\n"; break;
#endif
        default: os_version += "Windows (Unknown version)\n"; break;
    }
    kernel_line += "Windows kernel\n";
#endif
#ifdef Q_OS_LINUX
    number_of_cores += QString::number(sysconf(_SC_NPROCESSORS_ONLN)) + "\n";
    quint32 pages = sysconf(_SC_PHYS_PAGES);
    quint32 page_size = sysconf(_SC_PAGE_SIZE);
    quint32 total = pages * page_size / 1024 / 1024;
    total_ram += QString::number(total) + " MB\n";
    os_version += "GNU/Linux or BSD\n";
#endif

    // uname -a
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    QProcess *process = new QProcess();
    QStringList arguments = QStringList("-a");
    process->start("uname", arguments);
    if (process->waitForFinished())
        kernel_line += QString(process->readAll());
    delete process;
#endif

#if (defined(Q_OS_WIN) && defined(__i386__)) || defined(__x86_64__)
    // cpu info
    quint32 registers[4];
    quint32 i;

    i = 0x80000002;
    asm volatile
      ("cpuid" : "=a" (registers[0]), "=b" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
       : "a" (i), "c" (0));
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[0]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[1]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[2]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[3]), 4);
    i = 0x80000003;
    asm volatile
      ("cpuid" : "=a" (registers[0]), "=b" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
       : "a" (i), "c" (0));
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[0]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[1]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[2]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[3]), 4);
    i = 0x80000004;
    asm volatile
      ("cpuid" : "=a" (registers[0]), "=b" (registers[1]), "=c" (registers[2]), "=d" (registers[3])
       : "a" (i), "c" (0));
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[0]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[1]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[2]), 4);
    processor_name += QByteArray(reinterpret_cast<char*>(&registers[3]), 4);
    processor_name += "\n";
#else
    processor_name += "Unknown";
#endif

    // compiler
#ifdef __GNUC__
    compiler_version += "GCC " + QString(__VERSION__) + "\n";
#else
    compiler_version += "Unknown\n";
#endif

    if(sizeof(void*) == 4)
        compiler_bits += "i386\n";
    else if(sizeof(void*) == 8)
        compiler_bits += "x86_64\n";

    // concat system info
    specs = qt_version
        + os_version
        + total_ram
        + screen_size
        + number_of_screens
        + processor_name
        + number_of_cores
        + compiler_version
        + compiler_bits
        + kernel_line;
}
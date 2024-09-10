void display_computer_info(os_info_t const * const oi, system_info_t const * const si)
{
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);

    printf("------ System Information ------\n");
    printf("Computer: %s\n", oi->computer_name);
    printf("OS: %s (%s)\n", oi->product_name, si->cpu_arch);
    printf("Build: %s\n", oi->build);

    printf("Manufacturer: %s\n", si->manufacturer);
    printf("Pruduct: %s\n", si->product_name);
    printf("BIOS: %s (%s)\n", si->bios_version, si->bios_date);
    printf("CPU: %s (%d CPUs)\n", si->cpu_desc, si->cpu_num);

    printf("Memory: %ldMB RAM\n", (long)get_mb_from_byte(si->memory));
    printf("Pagefile: %ldMB\n", (long)get_mb_from_byte(si->pagefile));
    printf("\n");
}
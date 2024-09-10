static INT find_joystick_devices(void)
{
    INT i;

    if (joystick_devices_count != -1) return joystick_devices_count;

    joystick_devices_count = 0;
    for (i = 0; i < MAX_JOYSTICKS; i++)
    {
        int fd;
        struct JoyDev joydev, *new_joydevs;
        BYTE axes_map[ABS_MAX + 1];

        snprintf(joydev.device, sizeof(joydev.device), "%s%d", JOYDEV_NEW, i);
        if ((fd = open(joydev.device, O_RDONLY)) < 0)
        {
            snprintf(joydev.device, sizeof(joydev.device), "%s%d", JOYDEV_OLD, i);
            if ((fd = open(joydev.device, O_RDONLY)) < 0) continue;
        }

        strcpy(joydev.name, "Wine Joystick");
#if defined(JSIOCGNAME)
        if (ioctl(fd, JSIOCGNAME(sizeof(joydev.name) - sizeof(JOYDEVDRIVER)), joydev.name) < 0)
            WARN("ioctl(%s,JSIOCGNAME) failed: %s\n", joydev.device, strerror(errno));
#endif

        /* Append driver name */
        strcat(joydev.name, JOYDEVDRIVER);

        if (device_disabled_registry(joydev.name)) {
            close(fd);
            continue;
        }

#ifdef JSIOCGAXES
        if (ioctl(fd, JSIOCGAXES, &joydev.axis_count) < 0)
        {
            WARN("ioctl(%s,JSIOCGAXES) failed: %s, defauting to 2\n", joydev.device, strerror(errno));
            joydev.axis_count = 2;
        }
#endif
#ifdef JSIOCGBUTTONS
        if (ioctl(fd, JSIOCGBUTTONS, &joydev.button_count) < 0)
        {
            WARN("ioctl(%s,JSIOCGBUTTONS) failed: %s, defauting to 2\n", joydev.device, strerror(errno));
            joydev.button_count = 2;
        }
#endif

        if (ioctl(fd, JSIOCGAXMAP, axes_map) < 0)
        {
            WARN("ioctl(%s,JSIOCGNAME) failed: %s\n", joydev.device, strerror(errno));
            joydev.dev_axes_map = NULL;
        }
        else
            if ((joydev.dev_axes_map = HeapAlloc(GetProcessHeap(), 0, joydev.axis_count * sizeof(int))))
            {
                INT j;

                /* Remap to DI numbers */
                for (j = 0; j < joydev.axis_count; j++)
                    if (axes_map[j] < 8)
                        /* Axis match 1-to-1 */
                        joydev.dev_axes_map[j] = j;
                    else if (axes_map[j] == 16 ||
                             axes_map[j] == 17)
                        /* POV axis */
                        joydev.dev_axes_map[j] = 8;
                    else
                        joydev.dev_axes_map[j] = -1;
            }

        close(fd);

        if (!joystick_devices_count)
            new_joydevs = HeapAlloc(GetProcessHeap(), 0, sizeof(struct JoyDev));
        else
            new_joydevs = HeapReAlloc(GetProcessHeap(), 0, joystick_devices,
                                      (joystick_devices_count + 1) * sizeof(struct JoyDev));
        if (!new_joydevs) continue;

        TRACE("Found a joystick on %s: %s\n  with %d axes and %d buttons\n", joydev.device,
              joydev.name, joydev.axis_count, joydev.button_count);

        joystick_devices = new_joydevs;
        joystick_devices[joystick_devices_count++] = joydev;
    }

    return joystick_devices_count;
}
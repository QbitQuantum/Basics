static void
dp_set_variables(Display * dpy, XDevice * dev, int argc, char *argv[],
                 int first_cmd)
{
    int i;
    double val;
    struct Parameter *par;
    Atom prop, type, float_type;
    int format;
    unsigned char *data;
    unsigned long nitems, bytes_after;

    union flong *f;
    long *n;
    char *b;

    float_type = XInternAtom(dpy, XATOM_FLOAT, True);
    if (!float_type)
        fprintf(stderr, "Float properties not available.\n");

    for (i = first_cmd; i < argc; i++) {
        val = parse_cmd(argv[i], &par);
        if (!par)
            continue;

        prop = XInternAtom(dpy, par->prop_name, True);
        if (!prop) {
            fprintf(stderr, "Property for '%s' not available. Skipping.\n",
                    par->name);
            continue;

        }

        XGetDeviceProperty(dpy, dev, prop, 0, 1000, False, AnyPropertyType,
                           &type, &format, &nitems, &bytes_after, &data);

        if (type == None) {
            fprintf(stderr, "Property for '%s' not available. Skipping.\n",
                    par->name);
            continue;
        }

        switch (par->prop_format) {
        case 8:
            if (format != par->prop_format || type != XA_INTEGER) {
                fprintf(stderr, "   %-23s = format mismatch (%d)\n",
                        par->name, format);
                break;
            }
            b = (char *) data;
            b[par->prop_offset] = rint(val);
            break;
        case 32:
            if (format != par->prop_format ||
                (type != XA_INTEGER && type != XA_CARDINAL)) {
                fprintf(stderr, "   %-23s = format mismatch (%d)\n",
                        par->name, format);
                break;
            }
            n = (long *) data;
            n[par->prop_offset] = rint(val);
            break;
        case 0:                /* float */
            if (!float_type)
                continue;
            if (format != 32 || type != float_type) {
                fprintf(stderr, "   %-23s = format mismatch (%d)\n",
                        par->name, format);
                break;
            }
            f = (union flong *) data;
            f[par->prop_offset].f = val;
            break;
        }

        XChangeDeviceProperty(dpy, dev, prop, type, format,
                              PropModeReplace, data, nitems);
        XFlush(dpy);
    }
}
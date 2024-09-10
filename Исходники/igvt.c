/**
 * @brief Set the foreground VM
 *
 * @param domid The domain ID of the port to put in the foreground
 * @return 0 on success
 */
int igvt_set_foreground_vm(unsigned int domid)
{
    FILE *fd;
    char path[128];
    struct stat st;
    int retval = 0;
    int n, r = -1;
    int status;

    if (domid != 0) {
        snprintf(path, sizeof(path), VGT_KERNEL_PATH "/vm%d", domid);

        if (stat(path, &st) != 0) {
	    igvt_printf(IGVT_WARNING, "%s::VM %d at %s doesn't exist\n",
			__func__, domid, path);

            return -EINVAL;
        }
    }

    /* Check to see if the fg vm needs to change */
    fd = fopen(VGT_KERNEL_PATH "/control/foreground_vm", "r");

    if (!fd) {
	igvt_printf(IGVT_WARNING, "::%s Foreground VM file " 
		    VGT_KERNEL_PATH
		    "/control/foreground_vm can't be open for read\n",
		    __func__);

        return -ENODEV;
    }

    n = fscanf(fd, "%d", &r);

    fclose(fd);

    if (n == 1 && r == domid) {
	/* No change required. */
        return 0;
    }

    /* We need to change the fg vm. */
    fd = fopen(VGT_KERNEL_PATH "/control/foreground_vm", "w");

    if (!fd) {
	igvt_printf(IGVT_WARNING, "::%s Foreground VM file "
		    VGT_KERNEL_PATH
		    "/control/foreground_vm can't be open for write\n",
		    __func__);

        return -ENODEV;
    }

    status = fprintf(fd, "%d", domid);

    if (status <= 0) {
	igvt_printf(IGVT_WARNING, "%s::fprintf returned %d, error: %s\n",
		    __func__, status, strerror(errno));
    }

    status = fclose(fd);

    if (status < 0) {
	igvt_printf(IGVT_WARNING, "%s::fclose returned %d, error: %s\n",
		    __func__, status, strerror(errno));
    }

    /* check that it was actually set. */
    fd = fopen(VGT_KERNEL_PATH "/control/foreground_vm", "r");

    if (!fd) {
	igvt_printf(IGVT_WARNING, "%s::Foreground VM file "
		    VGT_KERNEL_PATH 
		    "/control/foreground_vm can't be open for re-read\n",
		    __func__);

        return -ENODEV;
    }

    n = fscanf(fd, "%d", &r);

    if (n != 1 || r != domid) {
        igvt_printf(IGVT_WARNING,
		    "%s:: set DomID %d does not match "
		    "returned DomID: %d nRead: %d\n",
	             __func__, domid, r, n);

        retval = -EAGAIN;
    }

    fclose(fd);

    return retval;
}
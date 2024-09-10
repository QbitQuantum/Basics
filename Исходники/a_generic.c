int32_t
_m_get_media_info(rmedia_handle_t *handle, void *ip)
{
	smmedium_prop_t *medinfo = ip;
	struct dk_minfo media_info;
	struct dk_geom	dkgeom;
	int32_t ret_val;
	enum dkio_state state = DKIO_NONE;

	if (handle == NULL) {
		DPRINTF("Null Handle\n");
		errno = EINVAL;
		return (-1);
	}
	if (handle->sm_signature != (int32_t)LIBSMEDIA_SIGNATURE) {
		DPRINTF2(
		    "Signature expected=0x%x, found=0x%x\n",
		    LIBSMEDIA_SIGNATURE, handle->sm_signature);
		errno = EINVAL;
		return (-1);
	}
	if (handle->sm_fd < 0) {
		DPRINTF("Invalid file handle.\n");
		errno = EINVAL;
		return (-1);
	}
	if (ioctl(handle->sm_fd, DKIOCSTATE, &state) < 0) {
		PERROR("DKIOCSTATE failed");
		return (-1);
	}
	if (state != DKIO_INSERTED) {
		DPRINTF("No media.\n");
		medinfo->sm_media_type = SM_NOT_PRESENT;
		medinfo->sm_version = SMMEDIA_PROP_V_1;
		return (0);
	}

	(void) memset((void *) medinfo, 0, sizeof (smmedium_prop_t));

	ret_val = ioctl(handle->sm_fd, DKIOCGMEDIAINFO, &media_info);
	if (ret_val < 0) {
		DPRINTF("DKIOCGMEDIAINFO ioctl failed");
		return (ret_val);
	}

	medinfo->sm_media_type = media_info.dki_media_type;
	medinfo->sm_blocksize = media_info.dki_lbsize;
	medinfo->sm_capacity = media_info.dki_capacity;

	/* Is it a removable magnetic disk? */
	if (medinfo->sm_media_type == DK_FIXED_DISK) {
		int32_t removable = 0;

		ret_val = ioctl(handle->sm_fd, DKIOCREMOVABLE, &removable);
		if (ret_val < 0) {
			DPRINTF("DKIOCREMOVABLE ioctl failed");
			return (ret_val);
		}
		if (removable) {
			medinfo->sm_media_type = SM_PCMCIA_ATA;
		}
	}
	ret_val = ioctl(handle->sm_fd, DKIOCGGEOM, &dkgeom);
	if (ret_val < 0) {
#ifdef sparc
		DPRINTF("DKIOCGGEOM ioctl failed");
		return (ret_val);
#else /* !sparc */
		/*
		 * Try getting Physical geometry on x86.
		 */
		ret_val = ioctl(handle->sm_fd, DKIOCG_PHYGEOM, &dkgeom);
		if (ret_val < 0) {
			DPRINTF("DKIOCG_PHYGEOM ioctl failed");
			return (ret_val);
		}
#endif /* sparc */
	}

	medinfo->sm_pcyl = dkgeom.dkg_pcyl;
	medinfo->sm_nhead = dkgeom.dkg_nhead;
	medinfo->sm_nsect = dkgeom.dkg_nsect;

	return (0);
}
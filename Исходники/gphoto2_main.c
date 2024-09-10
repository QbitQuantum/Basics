static TW_UINT16
GPHOTO2_OpenDS( pTW_IDENTITY pOrigin, pTW_IDENTITY self) {
    int ret, m, p, count, i;
    CameraAbilities a;
    GPPortInfo info;
    const char	*model, *port;

    if (GPHOTO2_dsmentry == NULL)
    {
        static const WCHAR twain32W[] = {'t','w','a','i','n','_','3','2',0};
        HMODULE moddsm = GetModuleHandleW(twain32W);

        if (moddsm)
            GPHOTO2_dsmentry = (void*)GetProcAddress(moddsm, "DSM_Entry");

        if (!GPHOTO2_dsmentry)
        {
            ERR("can't find DSM entry point\n");
            return TWRC_FAILURE;
        }
    }

    if (TWRC_SUCCESS != gphoto2_auto_detect())
	return TWRC_FAILURE;

    if (lstrcmpA(self->ProductFamily,"GPhoto2 Camera")) {
	FIXME("identity passed is not a gphoto camera, but %s!?!\n", self->ProductFamily);
	return TWRC_FAILURE;
    }
    count = gp_list_count (detected_cameras);
    if (!count) {
	ERR("No camera found by autodetection. Returning failure.\n");
	return TWRC_FAILURE;
    }

    if (!lstrcmpA (self->ProductName, "GPhoto2 Camera")) {
	TRACE("Potential undetected camera. Just using the first autodetected one.\n");
	i = 0;
    } else {
	for (i=0;i<count;i++) {
	    const char *cname, *pname;
	    TW_STR32	name;

	    gp_list_get_name  (detected_cameras, i, &cname);
	    gp_list_get_value (detected_cameras, i, &pname);
	    if (!lstrcmpA(self->ProductName,cname))
		break;
	    snprintf(name, sizeof(name), "%s", cname);
	    if (!lstrcmpA(self->ProductName,name))
		break;
	    snprintf(name, sizeof(name), "%s@%s", cname, pname);
	    if (!lstrcmpA(self->ProductName,name))
		break;
        }
        if (i == count) {
	    TRACE("Camera %s not found in autodetected list. Using first entry.\n", self->ProductName);
	    i=0;
        }
    }
    gp_list_get_name  (detected_cameras, i, &model);
    gp_list_get_value  (detected_cameras, i, &port);
    TRACE("model %s, port %s\n", model, port);
    ret = gp_camera_new (&activeDS.camera);
    if (ret < GP_OK) {
	ERR("gp_camera_new: %d\n", ret);
	return TWRC_FAILURE;
    }
    m = gp_abilities_list_lookup_model (abilities_list, model);
    if (m < GP_OK) {
	FIXME("Model %s not found, %d!\n", model, m);
	return TWRC_FAILURE;
    }
    ret = gp_abilities_list_get_abilities (abilities_list, m, &a);
    if (ret < GP_OK) {
	FIXME("gp_camera_list_get_abilities failed? %d\n", ret);
	return TWRC_FAILURE;
    }
    ret = gp_camera_set_abilities (activeDS.camera, a);
    if (ret < GP_OK) {
	FIXME("gp_camera_set_abilities failed? %d\n", ret);
	return TWRC_FAILURE;
    }

    p = gp_port_info_list_lookup_path (port_list, port);
    if (p < GP_OK) {
	FIXME("port %s not in portlist?\n", port);
	return TWRC_FAILURE;
    }
    ret = gp_port_info_list_get_info (port_list, p, &info);
    if (ret < GP_OK) {
	FIXME("could not get portinfo for port %s?\n", port);
	return TWRC_FAILURE;
    }
    ret = gp_camera_set_port_info (activeDS.camera, info);
    if (ret < GP_OK) {
	FIXME("could not set portinfo for port %s to camera?\n", port);
	return TWRC_FAILURE;
    }
    list_init( &(activeDS.files) );
    activeDS.currentState = 4;
    activeDS.twCC 		= TWRC_SUCCESS;
    activeDS.pixelflavor	= TWPF_CHOCOLATE;
    activeDS.pixeltype		= TWPT_RGB;
    activeDS.capXferMech	= TWSX_MEMORY;
    activeDS.identity.Id = self->Id;
    activeDS.appIdentity = *pOrigin;
    TRACE("OK!\n");
    return TWRC_SUCCESS;
}
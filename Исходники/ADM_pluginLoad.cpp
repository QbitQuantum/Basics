/**
 * 	\fn tryLoadingVideoFilterPlugin
 *  \brief try to load the plugin given as argument..
 */
static uint8_t tryLoadingVideoFilterPlugin(const char *file)
{
	ADM_vf_plugin *plugin = new ADM_vf_plugin(file);
    admVideoFilterInfo          *info=NULL;

	if (!plugin->isAvailable())
	{
		printf("[ADM_vf_plugin] Unable to load %s\n", ADM_GetFileName(file));
		goto Err_ad;
	}

	// Check API version
	if (plugin->getApiVersion() != VF_API_VERSION)
	{
		printf("[ADM_vf_plugin] File %s has API version too old (%d vs %d)\n",
			ADM_GetFileName(file), plugin->getApiVersion(), VF_API_VERSION);
		goto Err_ad;
	}
    if(!(plugin->supportedUI() & UI_GetCurrentUI()))
    {  // FIXME
        ADM_info("==> wrong UI\n");
        goto Err_ad;

    }
	// Get infos
	uint32_t major, minor, patch;

	plugin->getFilterVersion(&major, &minor, &patch);
	plugin->nameOfLibrary = ADM_strdup(ADM_GetFileName(file));

    info=&(plugin->info);


    info->internalName=plugin->getInternalName();
    info->desc=plugin->getDesc();
    info->displayName=plugin->getDisplayName();
    info->category=plugin->getCategory();

	printf("[ADM_vf_plugin] Plugin loaded version %d.%d.%d, name %s/%s\n",
		major, minor, patch, info->internalName, info->displayName);
    if(info->category>=VF_MAX)
    {
        ADM_error("This filter has an unknown caregory!\n");
        goto Err_ad;

    }else
    {
        plugin->tag=ADM_videoFilterPluginsList[info->category].size()+info->category*100;
        ADM_videoFilterPluginsList[info->category].append(plugin);
    }

	return 1;

Err_ad:
	delete plugin;
	return 0;
}
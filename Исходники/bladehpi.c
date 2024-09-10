static int
get_bladehpi_hostlist(struct pluginDevice *dev)
{
	struct blade_info *	bi;
	SaErrorT		ohrc;
	SaHpiEntryIdT		ohnextid;
	SaHpiRptEntryT		ohRPT;
	SaHpiDomainInfoT 	ohdi;
	SaHpiUint32T		ohupdate;

	if (Debug) {
		LOG(PIL_DEBUG, "%s: called, dev->device=%s"
		,	__FUNCTION__,	dev->device);
	}

	if (dev->device == NULL || *dev->device == 0) {
		LOG(PIL_CRIT, "Unconfigured stonith object in %s"
		,	__FUNCTION__);
		return S_BADCONFIG;
	}

	ohrc = saHpiDomainInfoGet(dev->ohsession, &ohdi);
	if (ohrc != SA_OK) {
		LOG(PIL_CRIT, "Unable to get domain info in %s (%d)"
		,	__FUNCTION__, ohrc);
		return S_BADCONFIG;
	}
	
try_again:
	ohupdate = ohdi.RptUpdateCount;
	dev->ohdevid = dev->ohsensid = dev->ohsensnum = 0;
	ohnextid = SAHPI_FIRST_ENTRY;
	do {
		char blname[SAHPI_MAX_TEXT_BUFFER_LENGTH];
		int  blnum;

		ohrc = saHpiRptEntryGet(dev->ohsession, ohnextid
				       , &ohnextid, &ohRPT);
		if (ohrc != SA_OK) {
			LOG(PIL_CRIT, "Unable to get RPT entry in %s (%d)"
			,	__FUNCTION__, ohrc);
			free_bladehpi_hostlist(dev);
			return S_BADCONFIG;
		}

		switch (get_resource_type(dev->device, &ohRPT)) {
		case OHRES_BLADECENT:
			dev->ohdevid = ohRPT.ResourceId;

			if (Debug) {
				LOG(PIL_DEBUG, "BladeCenter '%s' has id %d"
				,	(char*)ohRPT.ResourceTag.Data
				,	dev->ohdevid);
			}
			break;

		case OHRES_MGMTMOD:
			if (ohRPT.ResourceCapabilities&SAHPI_CAPABILITY_SENSOR){
 				dev->ohsensnum = get_sensor_num(dev->ohsession
							, ohRPT.ResourceId);

				if (dev->ohsensnum) {
					dev->ohsensid = ohRPT.ResourceId;

					if (Debug) {
						LOG(PIL_DEBUG
						, "MgmtModule '%s' has id %d "
						"with sensor #%d"
						, (char*)ohRPT.ResourceTag.Data
						, dev->ohsensid
						, dev->ohsensnum);
					}
				}
			} 
			break;

		case OHRES_BLADE:
			if ((bi = (struct blade_info *)
				MALLOC(sizeof(struct blade_info))) == NULL) {
			        LOG(PIL_CRIT, "Out of memory in %s"
				,	__FUNCTION__);
				free_bladehpi_hostlist(dev);
			        return S_OOPS;
			}

			/*
			 * New format consists of "Blade N - name" while older
			 * format consists only of "name"; we only need to
			 * stash name because ResourceID is the important info
			 */
			if (sscanf((char*)ohRPT.ResourceTag.Data, "Blade %d - %s"
					, &blnum, blname) == 2) {
				bi->name = STRDUP(blname);
			} else {
				bi->name = STRDUP((char*)ohRPT.ResourceTag.Data);
			}
			if (bi->name == NULL) {
				LOG(PIL_CRIT, "Out of memory for strdup in %s"
				,	__FUNCTION__);
				free_bladehpi_hostlist(dev);
			        return S_OOPS;
			}

			bi->resourceId = ohRPT.ResourceId;
			bi->resourceCaps = ohRPT.ResourceCapabilities;
			dev->hostlist = g_list_append(dev->hostlist, bi);

			if (Debug) {
				LOG(PIL_DEBUG, "Blade '%s' has id %d, caps %x"
				, bi->name, bi->resourceId, bi->resourceCaps);
			}
			break;
		}
	} while (ohrc == SA_OK && ohnextid != SAHPI_LAST_ENTRY);

	ohrc = saHpiDomainInfoGet(dev->ohsession, &ohdi);
	if (ohrc != SA_OK) {
		LOG(PIL_CRIT, "Unable to get domain info in %s (%d)"
		,	__FUNCTION__, ohrc);
		free_bladehpi_hostlist(dev);
		return S_BADCONFIG;
	}

	if (ohupdate != ohdi.RptUpdateCount) {
		free_bladehpi_hostlist(dev);
		if(Debug){
			LOG(PIL_DEBUG, "Looping through entries again,"
				" count changed from %d to %d"
			,	ohupdate, ohdi.RptUpdateCount);
		}
		goto try_again;
	}

	dev->ohrptcnt = ohupdate;

	return S_OK;
}
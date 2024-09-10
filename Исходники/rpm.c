/* Extract the file */
static size_t RPMCopy(install_info *info, const char *path, const char *dest, const char *current_option_name, 
		      xmlNodePtr node,
		      int (*update)(install_info *info, const char *path, size_t progress, size_t size, const char *current))
{
    FD_t fdi;
    Header hd;
    size_t size;
    int_32 type, c;
    int rc, isSource;
    void *p;
	const char *reloc = xmlGetProp(node, "relocate");
	const char *autorm = xmlGetProp(node, "autoremove");
	const char *depsoff = xmlGetProp(node, "nodeps");
	int relocate = (reloc && !strcasecmp(reloc, "true"));
	int autoremove = (autorm && !strcasecmp(autorm, "true"));
	int nodeps = (depsoff && !strcasecmp(depsoff, "true"));

    fdi = fdOpen(path, O_RDONLY, 0644);
    rc = rpmReadPackageHeader(fdi, &hd, &isSource, NULL, NULL);
    if ( rc ) {
		log_warning(_("RPM error: %s"), rpmErrorString());
        return 0;
    }

    size = 0;
    if ( rpm_access && ! force_manual ) { /* We can call RPM directly */
        char cmd[300];
        FILE *fp;
        float percent = 0.0;
		double bytes_copied = 0.0;
		double previous_bytes = 0.0;
        char *name = "", *version = "", *release = "";
		char *options = (char *) malloc(PATH_MAX);
		options[0] = '\0';

        headerGetEntry(hd, RPMTAG_SIZE, &type, &p, &c);
        if(type==RPM_INT32_TYPE){
			size = *(int_32*) p;
        }
        headerGetEntry(hd, RPMTAG_RELEASE, &type, &p, &c);
        if(type==RPM_STRING_TYPE){
			release = (char *) p;
        }
        headerGetEntry(hd, RPMTAG_NAME, &type, &p, &c);
        if(type==RPM_STRING_TYPE){
			name = (char*)p;
        }
        headerGetEntry(hd, RPMTAG_VERSION, &type, &p, &c);
        if(type==RPM_STRING_TYPE){
			version = (char*)p;
        }
        fdClose(fdi);

		if (relocate) { /* force relocating RPM to install directory */
			sprintf(options, " --relocate /=%s --badreloc ", dest);
		}

		if (nodeps) {
			strcat(options, " --nodeps ");
		}

		snprintf(cmd,sizeof(cmd),"rpm -U --percent --root %s %s %s", rpm_root,
				 options, path);

		fp = popen(cmd, "r");
		while ( percent < 100.0 ) {
			if(!fp || feof(fp)){
				pclose(fp);
				free(options);
				log_warning(_("Unable to install RPM file: '%s'"), path);
				return 0;
			}
			fscanf(fp,"%s", cmd);
			if(strcmp(cmd,"%%")){
				pclose(fp);
				free(options);
				log_warning(_("Unable to install RPM file: '%s'"), path);
				return 0;
			}
			fscanf(fp,"%f", &percent);
			/* calculate the bytes installed in this pass of the loop */
			bytes_copied = (percent/100.0)*size - previous_bytes;
			previous_bytes += bytes_copied;
			info->installed_bytes += bytes_copied;
			if ( ! update(info, path, (percent/100.0)*size, size, current_option_name) )
				break;
		}
		pclose(fp);
		free (options);
		/* Log the RPM installation */
		add_rpm_entry(info, current_option, name, version, atoi(release), autoremove);
    } else { /* Manually install the RPM file */
        gzFile gzdi = NULL;
		BZFILE *bzdi = NULL;
		FILE *fd = NULL;
		unsigned char magic[2];
        stream *cpio;
    
        if(headerIsEntry(hd, RPMTAG_PREIN)){      
			headerGetEntry(hd, RPMTAG_PREIN, &type, &p, &c);
			if(type==RPM_STRING_TYPE)
				run_script(info, (char*)p, 1, 1);
        }

		/* Identify the type of compression for the archive */
		if ( fdRead(fdi, magic, 2) < 2 ) {
			return 0;
		}
		lseek(fdFileno(fdi), -2L, SEEK_CUR); 
		if ( magic[0]==037 && magic[1]==0213 ) {
			gzdi = gzdopen(fdFileno(fdi), "r");    /* XXX gzdi == fdi */
		} else if ( magic[0]=='B' && magic[1]=='Z' ) {
			bzdi = BZDOPEN(fdFileno(fdi), "r");
		} else { /* Assume not compressed */
			fd = fdopen(fdFileno(fdi), "r");
		}
		
        cpio = file_fdopen(info, path, fd, gzdi, bzdi, "r");

        /* if relocate="true", copy the files into dest instead of rpm_root */
		if (relocate) {
			size = copy_cpio_stream(info, cpio, dest, current_option_name, node, update);
		} else {
			size = copy_cpio_stream(info, cpio, rpm_root, current_option_name, node, update);
		}

        if(headerIsEntry(hd, RPMTAG_POSTIN)){      
			headerGetEntry(hd, RPMTAG_POSTIN, &type, &p, &c);
			if(type==RPM_STRING_TYPE)
				run_script(info, (char*)p, 1, 1);
        }

        /* Append the uninstall scripts to the uninstall */
        if(headerIsEntry(hd, RPMTAG_PREUN)){      
			headerGetEntry(hd, RPMTAG_PREUN, &type, &p, &c);
			if(type==RPM_STRING_TYPE)
				add_script_entry(info, current_option, (char*)p, 0);
        }
        if(headerIsEntry(hd, RPMTAG_POSTUN)){      
			headerGetEntry(hd, RPMTAG_POSTUN, &type, &p, &c);
			if(type==RPM_STRING_TYPE)
				add_script_entry(info, current_option, (char*)p, 1);
        }
        fdClose(fdi);
    }
    return size;
}
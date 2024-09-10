int rhizome_direct_form_received(rhizome_http_request *r)
{
  const char *submitBareFileURI=confValueGet("rhizome.api.addfile.uri", NULL);

  /* Process completed form based on the set of fields seen */
  if (!strcmp(r->path,"/rhizome/import")) {
    switch(r->fields_seen) {
    case RD_MIME_STATE_MANIFESTHEADERS | RD_MIME_STATE_DATAHEADERS: {
	/* Got a bundle to import */
	DEBUGF("Call bundle import for rhizomedata.%d.{data,file}",
	       r->alarm.poll.fd);
	strbuf manifest_path = strbuf_alloca(50);
	strbuf payload_path = strbuf_alloca(50);
	strbuf_sprintf(manifest_path, "rhizomedirect.%d.manifest", r->alarm.poll.fd);
	strbuf_sprintf(payload_path, "rhizomedirect.%d.data", r->alarm.poll.fd);
	int ret = rhizome_bundle_import_files(strbuf_str(manifest_path), strbuf_str(payload_path), 1); // ttl = 1
	
	DEBUGF("Import returned %d",ret);
	
	rhizome_direct_clear_temporary_files(r);
	/* report back to caller.
	  200 = ok, which is probably appropriate for when we already had the bundle.
	  201 = content created, which is probably appropriate for when we successfully
	  import a bundle (or if we already have it).
	  403 = forbidden, which might be appropriate if we refuse to accept it, e.g.,
	  the import fails due to malformed data etc.
	  (should probably also indicate if we have a newer version if possible)
	*/
	switch (ret) {
	case 0:
	  return rhizome_server_simple_http_response(r, 201, "Bundle succesfully imported.");
	case 2:
	  return rhizome_server_simple_http_response(r, 200, "Bundle already imported.");
	}
	return rhizome_server_simple_http_response(r, 500, "Server error: Rhizome import command failed.");
      }
      break;     
    default:
      /* Clean up after ourselves */
      rhizome_direct_clear_temporary_files(r);	     
    }
  } else if (!strcmp(r->path,"/rhizome/enquiry")) {
    int fd=-1;
    char file[1024];
    switch(r->fields_seen) {
    case RD_MIME_STATE_DATAHEADERS:
      /* Read data buffer in, pass to rhizome direct for comparison with local
	 rhizome database, and send back responses. */
      snprintf(file,1024,"rhizomedirect.%d.%s",r->alarm.poll.fd,"data");
      fd=open(file,O_RDONLY);
      if (fd == -1) {
	WHYF_perror("open(%s, O_RDONLY)", alloca_str_toprint(file));
	/* Clean up after ourselves */
	rhizome_direct_clear_temporary_files(r);	     
	return rhizome_server_simple_http_response(r,500,"Couldn't read a file");
      }
      struct stat stat;
      if (fstat(fd, &stat) == -1) {
	WHYF_perror("stat(%d)", fd);
	/* Clean up after ourselves */
	close(fd);
	rhizome_direct_clear_temporary_files(r);	     
	return rhizome_server_simple_http_response(r,500,"Couldn't stat a file");
      }
      unsigned char *addr = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
      if (addr==MAP_FAILED) {
	WHYF_perror("mmap(NULL, %lld, PROT_READ, MAP_SHARED, %d, 0)", (long long) stat.st_size, fd);
	/* Clean up after ourselves */
	close(fd);
	rhizome_direct_clear_temporary_files(r);	     
	return rhizome_server_simple_http_response(r,500,"Couldn't mmap() a file");
      }
      /* Ask for a fill response.  Regardless of the size of the set of BARs passed
	 to us, we will allow up to 64KB of response. */
      rhizome_direct_bundle_cursor 
	*c=rhizome_direct_get_fill_response(addr,stat.st_size,65536);
      munmap(addr,stat.st_size);
      close(fd);

      if (c)
	{
	  /* TODO: Write out_buffer as the body of the response.
	     We should be able to do this using the async framework fairly easily.
	  */
	  
	  int bytes=c->buffer_offset_bytes+c->buffer_used;
	  r->buffer=malloc(bytes+1024);
	  r->buffer_size=bytes+1024;
	  r->buffer_offset=0;
	  assert(r->buffer);

	  /* Write HTTP response header */
	  struct http_response hr;
	  hr.result_code=200;
	  hr.content_type="binary/octet-stream";
	  hr.content_length=bytes;
	  hr.body=NULL;
	  r->request_type=0;
	  rhizome_server_set_response(r,&hr);
	  assert(r->buffer_offset<1024);

	  /* Now append body and send it back. */
	  bcopy(c->buffer,&r->buffer[r->buffer_length],bytes);
	  r->buffer_length+=bytes;
	  r->buffer_offset=0;

	  /* Clean up cursor after sending response */
	  rhizome_direct_bundle_iterator_free(&c);
	  /* Clean up after ourselves */
	  rhizome_direct_clear_temporary_files(r);	     

	  return 0;
	}
      else
	{
	  return rhizome_server_simple_http_response(r,500,"Could not get response to enquiry");
	}

      /* Clean up after ourselves */
      rhizome_direct_clear_temporary_files(r);	     
      break;
    default:
      /* Clean up after ourselves */
      rhizome_direct_clear_temporary_files(r);	     

      return rhizome_server_simple_http_response(r, 404, "/rhizome/enquiry requires 'data' field");
    }
  }  
  /* Allow servald to be configured to accept files without manifests via HTTP
     from localhost, so that rhizome bundles can be created programatically.
     There are probably still some security loop-holes here, which is part of
     why we leave it disabled by default, but it will be sufficient for testing
     possible uses, including integration with OpenDataKit.
  */
  else if (submitBareFileURI&&(!strcmp(r->path,submitBareFileURI))) {
    if (strcmp(inet_ntoa(r->requestor.sin_addr),
	       confValueGet("rhizome.api.addfile.allowedaddress","127.0.0.1")))
      {	
	DEBUGF("rhizome.api.addfile request received from %s, but is only allowed from %s",
	       inet_ntoa(r->requestor.sin_addr),
	       confValueGet("rhizome.api.addfile.allowedaddress", "127.0.0.1"));

	rhizome_direct_clear_temporary_files(r);	     
	return rhizome_server_simple_http_response(r,404,"Not available from here.");
      }

    switch(r->fields_seen) {
    case RD_MIME_STATE_DATAHEADERS:
      /* We have been given a file without a manifest, we should only
	 accept if it we are configured to do so, and the connection is from
	 localhost.  Otherwise people could cause your servald to create
	 arbitrary bundles, which would be bad.
      */
      /* A bundle to import */
      DEBUGF("Call bundle import sans-manifest for rhizomedata.%d.{data,file}",
	     r->alarm.poll.fd);
      
      char filepath[1024];
      snprintf(filepath,1024,"rhizomedirect.%d.data",r->alarm.poll.fd);

      const char *manifestTemplate
	=confValueGet("rhizome.api.addfile.manifesttemplate", NULL);
      
      if (manifestTemplate&&access(manifestTemplate, R_OK) != 0)
	{
	  rhizome_direct_clear_temporary_files(r);	     
	  return rhizome_server_simple_http_response(r,500,"rhizome.api.addfile.manifesttemplate points to a file I could not read.");
	}

      rhizome_manifest *m = rhizome_new_manifest();
      if (!m)
	{
	  rhizome_server_simple_http_response(r,500,"No free manifest slots. Try again later.");
	  rhizome_direct_clear_temporary_files(r);	     
	  return WHY("Manifest struct could not be allocated -- not added to rhizome");
	}

      if (manifestTemplate)
	if (rhizome_read_manifest_file(m, manifestTemplate, 0) == -1) {
	  rhizome_manifest_free(m);
	  rhizome_direct_clear_temporary_files(r);	     
	  return rhizome_server_simple_http_response(r,500,"rhizome.api.addfile.manifesttemplate can't be read as a manifest.");
	}

      /* Fill in a few missing manifest fields, to make it easier to use when adding new files:
	 - the default service is FILE
	 - use the current time for "date"
	 - if service is file, then use the payload file's basename for "name"
      */
      const char *service = rhizome_manifest_get(m, "service", NULL, 0);
      if (service == NULL) {
	rhizome_manifest_set(m, "service", (service = RHIZOME_SERVICE_FILE));
	if (debug & DEBUG_RHIZOME) DEBUGF("missing 'service', set default service=%s", service);
      } else {
	if (debug & DEBUG_RHIZOME) DEBUGF("manifest contains service=%s", service);
      }
      if (rhizome_manifest_get(m, "date", NULL, 0) == NULL) {
	rhizome_manifest_set_ll(m, "date", (long long) gettime_ms());
	if (debug & DEBUG_RHIZOME) DEBUGF("missing 'date', set default date=%s", rhizome_manifest_get(m, "date", NULL, 0));
      }

      const char *name = rhizome_manifest_get(m, "name", NULL, 0);
      if (name == NULL) {
	name=r->data_file_name;
	rhizome_manifest_set(m, "name", r->data_file_name);
	if (debug & DEBUG_RHIZOME) DEBUGF("missing 'name', set name=\"%s\" from HTTP post field filename specification", name);
      } else {
	if (debug & DEBUG_RHIZOME) DEBUGF("manifest contains name=\"%s\"", name);
      }

      const char *senderhex
	= rhizome_manifest_get(m, "sender", NULL, 0);
      if (!senderhex) senderhex=confValueGet("rhizome.api.addfile.author",NULL);
      unsigned char authorSid[SID_SIZE];
      if (senderhex) fromhexstr(authorSid,senderhex,SID_SIZE);
      const char *bskhex
	=confValueGet("rhizome.api.addfile.bundlesecretkey", NULL);   

      /* Bind an ID to the manifest, and also bind the file.  Then finalise the 
	 manifest. But if the manifest already contains an ID, don't override it. */
      if (rhizome_manifest_get(m, "id", NULL, 0) == NULL) {
	if (rhizome_manifest_bind_id(m, senderhex ? authorSid : NULL)) {
	  rhizome_manifest_free(m);
	  m = NULL;
	  rhizome_direct_clear_temporary_files(r);
	  return rhizome_server_simple_http_response(r,500,"Could not bind manifest to an ID");
	}	
      } else if (bskhex) {
	/* Allow user to specify a bundle secret key so that the same bundle can
	   be updated, rather than creating a new bundle each time. */
	unsigned char bsk[RHIZOME_BUNDLE_KEY_BYTES];
	fromhexstr(bsk,bskhex,RHIZOME_BUNDLE_KEY_BYTES);
	memcpy(m->cryptoSignSecret, bsk, RHIZOME_BUNDLE_KEY_BYTES);
	if (rhizome_verify_bundle_privatekey(m) == -1) {
	  rhizome_manifest_free(m);
	  m = NULL;
	  rhizome_direct_clear_temporary_files(r);
	  return rhizome_server_simple_http_response(r,500,"rhizome.api.addfile.bundlesecretkey did not verify.  Using the right key for the right bundle?");
	}
      } else {
	/* Bundle ID specified, but without a BSK or sender SID specified.
	   Therefore we cannot work out the bundle key, and cannot update the
	   bundle. */
	rhizome_manifest_free(m);
	m = NULL;
	rhizome_direct_clear_temporary_files(r);
	return rhizome_server_simple_http_response(r,500,"rhizome.api.addfile.bundlesecretkey not set, and manifest template contains no sender, but template contains a hard-wired bundle ID.  You must specify at least one, or not supply id= in the manifest template.");
	
      }
      
      int encryptP = 0; // TODO Determine here whether payload is to be encrypted.
      if (rhizome_manifest_bind_file(m, filepath, encryptP)) {
	rhizome_manifest_free(m);
	rhizome_direct_clear_temporary_files(r);
	return rhizome_server_simple_http_response(r,500,"Could not bind manifest to file");
      }      
      if (rhizome_manifest_finalise(m)) {
	rhizome_manifest_free(m);
	rhizome_direct_clear_temporary_files(r);
	return rhizome_server_simple_http_response(r,500,
						   "Could not finalise manifest");
      }
      if (rhizome_add_manifest(m,255 /* TTL */)) {
	rhizome_manifest_free(m);
	rhizome_direct_clear_temporary_files(r);
	return rhizome_server_simple_http_response(r,500,
						   "Add manifest operation failed");
      }
            
      DEBUGF("Import sans-manifest appeared to succeed");
      
      /* Respond with the manifest that was added. */
      rhizome_server_simple_http_response(r, 200, (char *)m->manifestdata);

      /* clean up after ourselves */
      rhizome_manifest_free(m);
      rhizome_direct_clear_temporary_files(r);

      return 0;
      break;
    default:
      /* Clean up after ourselves */
      rhizome_direct_clear_temporary_files(r);	     
      
      return rhizome_server_simple_http_response(r, 400, "Rhizome create bundle from file API requires 'data' field");     
    }
  }  

  /* Clean up after ourselves */
  rhizome_direct_clear_temporary_files(r);	     
  /* Report error */
  return rhizome_server_simple_http_response(r, 500, "Something went wrong.  Probably a missing data or manifest part, or invalid combination of URI and data/manifest provision.");

}
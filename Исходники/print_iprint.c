static int iprint_queue_get(const char *sharename,
			    enum printing_types printing_type,
			    char *lpq_command,
			    print_queue_struct **q, 
			    print_status_struct *status)
{
	fstring		printername;
	http_t		*http = NULL;		/* HTTP connection to server */
	ipp_t		*request = NULL,	/* IPP Request */
			*response = NULL;	/* IPP Response */
	ipp_attribute_t	*attr = NULL;		/* Current attribute */
	cups_lang_t	*language = NULL;	/* Default language */
	char		uri[HTTP_MAX_URI]; /* printer-uri attribute */
	char		serviceUri[HTTP_MAX_URI]; /* service-uri attribute */
	char		httpPath[HTTP_MAX_URI];	/* path portion of the uri */
	int		jobUseUnixTime = 0;	/* Whether job times should
                                                 * be assumed to be Unix time */
	int		qcount = 0,		/* Number of active queue entries */
			qalloc = 0;		/* Number of queue entries allocated */
	print_queue_struct *queue = NULL,	/* Queue entries */
			*temp;		/* Temporary pointer for queue */
	const char	*user_name,	/* job-originating-user-name attribute */
			*job_name;	/* job-name attribute */
	int		job_id;		/* job-id attribute */
	int		job_k_octets;	/* job-k-octets attribute */
	time_t		job_time;	/* time-at-creation attribute */
	time_t		printer_up_time = 0;	/* printer's uptime */
	ipp_jstate_t	job_status;	/* job-status attribute */
	int		job_priority;	/* job-priority attribute */
	static const char *jattrs[] =	/* Requested job attributes */
			{
			  "job-id",
			  "job-k-octets",
			  "job-name",
			  "job-originating-user-name",
			  "job-priority",
			  "job-state",
			  "time-at-creation",
			};
	static const char *pattrs[] =	/* Requested printer attributes */
			{
			  "printer-state",
			  "printer-state-message",
			  "printer-current-time",
			  "printer-up-time"
			};

	*q = NULL;

	/* HACK ALERT!!!  The porblem with support the 'printer name' 
	   option is that we key the tdb off the sharename.  So we will 
	   overload the lpq_command string to pass in the printername 
	   (which is basically what we do for non-cups printers ... using 
	   the lpq_command to get the queue listing). */

	fstrcpy( printername, lpq_command );

	DEBUG(5,("iprint_queue_get(%s, %p, %p)\n", printername, q, status));

       /*
	* Make sure we don't ask for passwords...
	*/

	cupsSetPasswordCB(iprint_passwd_cb);

       /*
	* Try to connect to the server...
	*/

	if ((http = httpConnect(iprint_server(), ippPort())) == NULL) {
		DEBUG(0,("Unable to connect to iPrint server %s - %s\n", 
			 iprint_server(), strerror(errno)));
		goto out;
	}

       /*
	* Generate the printer URI and the service URI that goes with it...
	*/

	slprintf(uri, sizeof(uri) - 1, "ipp://%s/ipp/%s", iprint_server(), printername);
	slprintf(serviceUri, sizeof(serviceUri) - 1, "ipp://%s/ipp/", iprint_server());

       /*
	* For Linux iPrint servers from OES SP1 on, the iPrint server
	* uses Unix time for job start times unless it detects the iPrint
	* client in an http User-Agent header.  (This was done to accomodate
	* CUPS broken behavior.  According to RFC 2911, section 4.3.14, job
	* start times are supposed to be relative to how long the printer has
	* been up.)  Since libcups doesn't allow us to set that header before
	* the request is sent, this ugly hack allows us to detect the server
	* version and decide how to interpret the job time.
	*/
	if (iprint_get_server_version(http, serviceUri) >=
	    NOVELL_SERVER_VERSION_OES_SP1)
		jobUseUnixTime = 1;

	request = ippNew();

	request->request.op.operation_id = IPP_GET_PRINTER_ATTRIBUTES;
	request->request.op.request_id   = 2;

	language = cupsLangDefault();

	ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_CHARSET,
	             "attributes-charset", NULL, "utf-8");

	ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE,
	             "attributes-natural-language", NULL, language->language);

	ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI,
	             "printer-uri", NULL, uri);

	ippAddStrings(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD,
	              "requested-attributes",
	              (sizeof(pattrs) / sizeof(pattrs[0])),
	              NULL, pattrs);

       /*
	* Do the request and get back a response...
	*/

	slprintf(httpPath, sizeof(httpPath) - 1, "/ipp/%s", printername);

	if ((response = cupsDoRequest(http, request, httpPath)) == NULL) {
		DEBUG(0,("Unable to get printer status for %s - %s\n", printername,
			 ippErrorString(cupsLastError())));
		*q = queue;
		goto out;
	}

	if (response->request.status.status_code >= IPP_OK_CONFLICT) {
		DEBUG(0,("Unable to get printer status for %s - %s\n", printername,
			 ippErrorString(response->request.status.status_code)));
		*q = queue;
		goto out;
	}

       /*
	* Get the current printer status and convert it to the SAMBA values.
	*/

	if ((attr = ippFindAttribute(response, "printer-state", IPP_TAG_ENUM)) != NULL) {
		if (attr->values[0].integer == IPP_PRINTER_STOPPED)
			status->status = LPSTAT_STOPPED;
		else
			status->status = LPSTAT_OK;
	}

	if ((attr = ippFindAttribute(response, "printer-state-message",
	                             IPP_TAG_TEXT)) != NULL)
		fstrcpy(status->message, attr->values[0].string.text);

	if ((attr = ippFindAttribute(response, "printer-up-time",
	                             IPP_TAG_INTEGER)) != NULL)
		printer_up_time = attr->values[0].integer;

	ippDelete(response);
	response = NULL;

       /*
	* Build an IPP_GET_JOBS request, which requires the following
	* attributes:
	*
	*    attributes-charset
	*    attributes-natural-language
	*    requested-attributes
	*    printer-uri
	*/

	request = ippNew();

	request->request.op.operation_id = IPP_GET_JOBS;
	request->request.op.request_id   = 3;

	ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_CHARSET,
	             "attributes-charset", NULL, "utf-8");

	ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_LANGUAGE,
	             "attributes-natural-language", NULL, language->language);

	ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI,
	             "printer-uri", NULL, uri);

	ippAddStrings(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD,
	              "requested-attributes",
	              (sizeof(jattrs) / sizeof(jattrs[0])),
	              NULL, jattrs);

       /*
	* Do the request and get back a response...
	*/

	slprintf(httpPath, sizeof(httpPath) - 1, "/ipp/%s", printername);

	if ((response = cupsDoRequest(http, request, httpPath)) == NULL) {
		DEBUG(0,("Unable to get jobs for %s - %s\n", uri,
			 ippErrorString(cupsLastError())));
		goto out;
	}

	if (response->request.status.status_code >= IPP_OK_CONFLICT) {
		DEBUG(0,("Unable to get jobs for %s - %s\n", uri,
			 ippErrorString(response->request.status.status_code)));
		goto out;
	}

       /*
	* Process the jobs...
	*/

	qcount = 0;
	qalloc = 0;
	queue  = NULL;

	for (attr = response->attrs; attr != NULL; attr = attr->next) {
	       /*
		* Skip leading attributes until we hit a job...
		*/

		while (attr != NULL && attr->group_tag != IPP_TAG_JOB)
			attr = attr->next;

		if (attr == NULL)
			break;

	       /*
		* Allocate memory as needed...
		*/
		if (qcount >= qalloc) {
			qalloc += 16;

			queue = SMB_REALLOC_ARRAY(queue, print_queue_struct, qalloc);

			if (queue == NULL) {
				DEBUG(0,("iprint_queue_get: Not enough memory!"));
				qcount = 0;
				goto out;
			}
		}

		temp = queue + qcount;
		memset(temp, 0, sizeof(print_queue_struct));

	       /*
		* Pull the needed attributes from this job...
		*/

		job_id       = 0;
		job_priority = 50;
		job_status   = IPP_JOB_PENDING;
		job_time     = 0;
		job_k_octets = 0;
		user_name    = NULL;
		job_name     = NULL;

		while (attr != NULL && attr->group_tag == IPP_TAG_JOB) {
			if (attr->name == NULL) {
				attr = attr->next;
				break;
			}

			if (strcmp(attr->name, "job-id") == 0 &&
			    attr->value_tag == IPP_TAG_INTEGER)
				job_id = attr->values[0].integer;

			if (strcmp(attr->name, "job-k-octets") == 0 &&
			    attr->value_tag == IPP_TAG_INTEGER)
				job_k_octets = attr->values[0].integer;

			if (strcmp(attr->name, "job-priority") == 0 &&
			    attr->value_tag == IPP_TAG_INTEGER)
				job_priority = attr->values[0].integer;

			if (strcmp(attr->name, "job-state") == 0 &&
			    attr->value_tag == IPP_TAG_ENUM)
				job_status = (ipp_jstate_t)(attr->values[0].integer);

			if (strcmp(attr->name, "time-at-creation") == 0 &&
			    attr->value_tag == IPP_TAG_INTEGER)
			{
			       /*
				* If jobs times are in Unix time, the accuracy of the job
				* start time depends upon the iPrint server's time being
				* set correctly.  Otherwise, the accuracy depends upon
				* the Samba server's time being set correctly
				*/

				if (jobUseUnixTime)
					job_time = attr->values[0].integer; 
				else
					job_time = time(NULL) - printer_up_time + attr->values[0].integer;
			}

			if (strcmp(attr->name, "job-name") == 0 &&
			    (attr->value_tag == IPP_TAG_NAMELANG ||
			     attr->value_tag == IPP_TAG_NAME))
				job_name = attr->values[0].string.text;

			if (strcmp(attr->name, "job-originating-user-name") == 0 &&
			    (attr->value_tag == IPP_TAG_NAMELANG ||
			     attr->value_tag == IPP_TAG_NAME))
				user_name = attr->values[0].string.text;

			attr = attr->next;
		}

	       /*
		* See if we have everything needed...
		*/

		if (user_name == NULL || job_name == NULL || job_id == 0) {
			if (attr == NULL)
				break;
			else
				continue;
		}

		temp->job      = job_id;
		temp->size     = job_k_octets * 1024;
		temp->status   = job_status == IPP_JOB_PENDING ? LPQ_QUEUED :
		                 job_status == IPP_JOB_STOPPED ? LPQ_PAUSED :
                                 job_status == IPP_JOB_HELD ? LPQ_PAUSED :
                                 LPQ_PRINTING;
		temp->priority = job_priority;
		temp->time     = job_time;
		strncpy(temp->fs_user, user_name, sizeof(temp->fs_user) - 1);
		strncpy(temp->fs_file, job_name, sizeof(temp->fs_file) - 1);

		qcount ++;

		if (attr == NULL)
			break;
	}

       /*
	* Return the job queue...
	*/

	*q = queue;

 out:
	if (response)
		ippDelete(response);

	if (language)
		cupsLangFree(language);

	if (http)
		httpClose(http);

	return qcount;
}
int cgiMain() {

  static char      title[256]        = "";
  static char   subtitle[256]        = "";
         char      sorting[16]       = "desc";
         time_t    now               = time(NULL);
         time_t    start             = time(NULL);
         time_t    expiration        = time(NULL);
         double    available_secs    = 0;
         double    remaining_secs    = 0;
  struct dirent    **certstore_files = NULL;
         int       pagenumber        = 1;
         int       certcounter       = 0;
         int       tempcounter       = 0;
         int       pagecounter       = 0;
         int       dispcounter       = 0;
         int       dispmaxlines      = 0;
         int       certvalidity      = 0;
         div_t     disp_calc;
         div_t     oddline_calc;
         double    percent           = 0;

         cert                        = X509_new();
         certsubject                 = X509_NAME_new();
	 char      **form_data       = NULL;  /* string array for query data */

  /* get the current time */
  now = time(NULL);

/* ------------------------------------------------------------------------- *
 * If we are called without arguments, we display the cert search criteria   *
 * ------------------------------------------------------------------------- */
  if (cgiFormEntries(&form_data) != cgiFormSuccess)
    int_error("Error: Could not retrieve CGI form data.");
  if(form_data[0] == NULL) {

    start_tm = *gmtime(&now);

    snprintf(title, sizeof(title), "Search existing Certificates");
    pagehead(title);
    fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"get\">");
    fprintf(cgiOut, "<table>");

    /* Search for Subject String */
    fprintf(cgiOut, "<tr><th colspan=\"5\">Search by Name</th></tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th class=\"cnt\" rowspan=\"2\">\n");
    fprintf(cgiOut, "<input type=\"radio\" value=\"dn\" name=\"search\" />");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "Distinguished Name Field:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    fprintf(cgiOut, "<select name=\"field\">");
    fprintf(cgiOut, "<option value=\"countryName\">Country</option>");
    fprintf(cgiOut, "<option value=\"stateOrProvinceName\">State</option>");
    fprintf(cgiOut, "<option value=\"localityName\">Location</option>");
    fprintf(cgiOut, "<option value=\"organizationName\">Organisation</option>");
    fprintf(cgiOut, "<option value=\"organizationalUnitName\">Department</option>");
    fprintf(cgiOut, "<option value=\"emailAddress\">E-Mail Addr</option>");
    fprintf(cgiOut, "<option selected=\"selected\" value=\"commonName\">Common Name</option>");
    fprintf(cgiOut, "<option value=\"surname\">Surname</option>");
    fprintf(cgiOut, "<option value=\"givenName\">Given Name</option>");
    fprintf(cgiOut, "</select>");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "Search String<br />[20 chars max]:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    fprintf(cgiOut, "<input type=\"text\" size=\"15\" name=\"dnvalue\" value=\"changeme.com\" />");
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<td class=\"desc\" colspan=\"4\">\n");
    fprintf(cgiOut, "Search for certificates that have the given string in the selected DN field. ");
    fprintf(cgiOut, "The search is case sensitive, so results for country=us can be different from country=US and country=Us.");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "</tr>\n");

    /* Search for Expiration Date */
    fprintf(cgiOut, "<tr><th colspan=\"5\">Search by Expiration Date</th></tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th class=\"cnt\" rowspan=\"2\">\n");
    fprintf(cgiOut, "<input type=\"radio\" value=\"exp\" name=\"search\" checked=\"checked\" />");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "Expiration Date is<br />between Start Date:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    strftime(membio_buf, sizeof(membio_buf), "%d.%m.%Y", &start_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"9\" name=\"exp_startdate\" value=\"%s\" /> ", membio_buf);
    strftime(membio_buf, sizeof(membio_buf), "%H:%M", &start_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"3\" name=\"exp_starttime\" value=\"%s\" />", membio_buf);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "and End Date<br />[default 90 days]:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    /* set second time 3 months (90 days) into the future: 86400s/d*90d=7776000s */
    expiration = now + 7776000;
    expiration_tm = *gmtime(&expiration);
    strftime(membio_buf, sizeof(membio_buf), "%d.%m.%Y", &expiration_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"9\" name=\"exp_enddate\" value=\"%s\" /> ", membio_buf);
    strftime(membio_buf, sizeof(membio_buf), "%H:%M", &expiration_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"3\" name=\"exp_endtime\" value=\"%s\" />", membio_buf);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<td class=\"desc\" colspan=\"4\">\n");
    fprintf(cgiOut, "Search for certificates that expire(d) between the selected start and end date. ");
    fprintf(cgiOut, "By default, the search is pre-set to find certificates that expire in the next 3 months.");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "</tr>\n");

    /* Search for Enabled Date */
    fprintf(cgiOut, "<tr><th colspan=\"5\">Search by Creation Date</th></tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th class=\"cnt\" rowspan=\"2\">\n");
    fprintf(cgiOut, "<input type=\"radio\" value=\"ena\" name=\"search\" />");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "Enabled Date is<br />between Start Date:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    /* set second time 3 months (90 days) into the past: 86400s/d*90d=7776000s */
    expiration = now - 7776000;
    expiration_tm = *gmtime(&expiration);
    strftime(membio_buf, sizeof(membio_buf), "%d.%m.%Y", &expiration_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"9\" name=\"ena_startdate\" value=\"%s\" /> ", membio_buf);
    strftime(membio_buf, sizeof(membio_buf), "%H:%M", &expiration_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"3\" name=\"ena_starttime\" value=\"%s\" />", membio_buf);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "and End Date<br />[default now]:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    strftime(membio_buf, sizeof(membio_buf), "%d.%m.%Y", &start_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"9\" name=\"ena_enddate\" value=\"%s\" /> ", membio_buf);
    strftime(membio_buf, sizeof(membio_buf), "%H:%M", &start_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"3\" name=\"ena_endtime\" value=\"%s\" />", membio_buf);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<td class=\"desc\" colspan=\"4\">\n");
    fprintf(cgiOut, "Search for certificates that become valid between the selected start and end date. ");
    fprintf(cgiOut, "By default, the search is pre-set to show certificates created in the past 3 months.");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "</tr>\n");

    /* Search for Revocation Date */
    fprintf(cgiOut, "<tr><th colspan=\"5\">Search by Revocation Date</th></tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th class=\"cnt\" rowspan=\"2\">\n");
    fprintf(cgiOut, "<input type=\"radio\" value=\"rev\" name=\"search\" />");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "Revocation Date is<br />between Start Date:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    /* set second time 3 months (90 days) into the past: 86400s/d*90d=7776000s */
    expiration = now - 7776000;
    expiration_tm = *gmtime(&expiration);
    strftime(membio_buf, sizeof(membio_buf), "%d.%m.%Y", &expiration_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"9\" name=\"rev_startdate\" value=\"%s\" /> ", membio_buf);
    strftime(membio_buf, sizeof(membio_buf), "%H:%M", &expiration_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"3\" name=\"rev_starttime\" value=\"%s\"/>", membio_buf);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "and End Date<br />[now]:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    strftime(membio_buf, sizeof(membio_buf), "%d.%m.%Y", &start_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"9\" name=\"rev_enddate\" value=\"%s\" /> ", membio_buf);
    strftime(membio_buf, sizeof(membio_buf), "%H:%M", &start_tm);
    fprintf(cgiOut, "<input type=\"text\" size=\"3\" name=\"rev_endtime\" value=\"%s\" />", membio_buf);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<td class=\"desc\" colspan=\"4\">\n");
    fprintf(cgiOut, "Search for certificates that have been revoked between the selected start and end date. ");
    fprintf(cgiOut, " By default, the search is pre-set to show certificates revoked in the past 3 months.");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "</tr>\n");

    /* Search for Serial Number */
    fprintf(cgiOut, "<tr><th colspan=\"5\">Search by Serial Number</th></tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th class=\"cnt\" rowspan=\"2\">\n");
    fprintf(cgiOut, "<input type=\"radio\" value=\"ser\" name=\"search\" />");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "Serial Number is<br />between Start Serial:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    fprintf(cgiOut, "<input type=\"text\" size=\"14\" name=\"startserial\" ");
    fprintf(cgiOut, "value=\"%s\" style=\"text-align:right;\" />", startserstr);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "<td class=\"type\">\n");
    fprintf(cgiOut, "and End Serial<br />[max 10e11]:");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "<td class=\"center\">\n");
    fprintf(cgiOut, "<input type=\"text\" size=\"14\" name=\"endserial\" ");
    fprintf(cgiOut, "value=\"%s\" style=\"text-align:right;\" />", endserstr);
    fprintf(cgiOut, "</td>");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<td class=\"desc\" colspan=\"4\">\n");
    fprintf(cgiOut, "Search for certificates whose serial number is between the given ");
    fprintf(cgiOut, "start and end serial number in decimal format. To find a particular certificate, set start and end serial to be equal.");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "</tr>\n");

    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th colspan=\"5\">");
    fprintf(cgiOut, "<input type=\"submit\" value=\"Search Certificates\" />");
    fprintf(cgiOut, "</th>");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "</table>\n");
    fprintf(cgiOut, "</form>\n");
    pagefoot();

  }
  else {
  
  /* ------------------------------------------------------------------- *
   * check if we got the CGI form data                                   *
   * --------------------------------------------------------------------*/
    if ( cgiFormString("search", search, sizeof(search))
                                                     != cgiFormSuccess )
      int_error("Error retrieving CGI form search type.");
    else {
      if (strcmp(search, "dn") == 0) {
        if ( cgiFormString("field", field, sizeof(field))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form DN search field information.");

        if ( cgiFormString("dnvalue", dnvalue, sizeof(dnvalue))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form DN search dnvalue information.");
        snprintf(title, sizeof(title), "Search Certs by Subject");
        snprintf(subtitle, sizeof(subtitle), "Certificates with DN %s=%s", field, dnvalue);
      }
      else if (strcmp(search, "exp") == 0) {
        if ( cgiFormString("exp_startdate", exp_startdate, sizeof(exp_startdate))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form expiration start date.");

        if ( cgiFormString("exp_starttime", exp_starttime, sizeof(exp_starttime))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form expiration start time.");

        if ( cgiFormString("exp_enddate", exp_enddate, sizeof(exp_enddate))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form expiration end date.");

        if ( cgiFormString("exp_endtime", exp_endtime, sizeof(exp_endtime))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form expiration end time.");

        strncat(exp_startstr, exp_startdate, sizeof(exp_startstr)-1);
        strncat(exp_startstr, " ", 1); /* add a space between date and time */
        strncat(exp_startstr, exp_starttime, sizeof(exp_startstr)-strlen(exp_startstr)-1);
        strncat(exp_endstr, exp_enddate, sizeof(exp_endstr)-1);
        strncat(exp_endstr, " ", 1); /* add a space between date and time */
        strncat(exp_endstr, exp_endtime, sizeof(exp_endstr)-strlen(exp_endstr)-1);
        snprintf(title, sizeof(title), "Search Certs by Expiration");
        snprintf(subtitle, sizeof(subtitle), "Certificates with expiration between %s and %s", exp_startstr, exp_endstr);
      }
      else if (strcmp(search, "ena") == 0) {
        if ( cgiFormString("ena_startdate", ena_startdate, sizeof(ena_startdate))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable start date.");

        if ( cgiFormString("ena_starttime", ena_starttime, sizeof(ena_starttime))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable start time.");

        if ( cgiFormString("ena_enddate", ena_enddate, sizeof(ena_enddate))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable end date.");

        if ( cgiFormString("ena_endtime", ena_endtime, sizeof(ena_endtime))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable end time.");

        strncat(ena_startstr, ena_startdate, sizeof(ena_startstr)-1);
        strncat(ena_startstr, " ", 1); /* add a space between date and time */
        strncat(ena_startstr, ena_starttime, sizeof(ena_startstr)-strlen(ena_startstr)-1);
        strncat(ena_endstr, ena_enddate, sizeof(ena_endstr)-1);
        strncat(ena_endstr, " ", 1); /* add a space between date and time */
        strncat(ena_endstr, ena_endtime, sizeof(ena_endstr)-strlen(ena_endstr)-1);
        snprintf(title, sizeof(title), "Search Certs by Start Date");
        snprintf(subtitle, sizeof(subtitle), "Certificates with start date between %s and %s", ena_startstr, ena_endstr);
      }
      else if (strcmp(search, "rev") == 0) {
        if ( cgiFormString("rev_startdate", rev_startdate, sizeof(rev_startdate))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable start date.");

        if ( cgiFormString("rev_starttime", rev_starttime, sizeof(rev_starttime))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable start time.");

        if ( cgiFormString("rev_enddate", rev_enddate, sizeof(rev_enddate))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable end date.");

        if ( cgiFormString("rev_endtime", rev_endtime, sizeof(rev_endtime))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form enable end time.");

        strncat(rev_startstr, rev_startdate, sizeof(rev_startstr)-1);
        strncat(rev_startstr, " ", 1); /* add a space between date and time */
        strncat(rev_startstr, rev_starttime, sizeof(rev_startstr)-strlen(rev_startstr)-1);
        strncat(rev_endstr, rev_enddate, sizeof(rev_endstr)-1);
        strncat(rev_endstr, " ", 1); /* add a space between date and time */
        strncat(rev_endstr, rev_endtime, sizeof(rev_endstr)-strlen(rev_endstr)-1);
        snprintf(title, sizeof(title), "Search Revoked Certificates");
        snprintf(subtitle, sizeof(subtitle), "Certificates revoked between %s and %s", rev_startstr, rev_endstr);
      }
      else if (strcmp(search, "ser") == 0) {
        if ( cgiFormString("startserial", startserstr, sizeof(startserstr))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form start serial value.");

        if ( cgiFormString("endserial", endserstr, sizeof(endserstr))
                                                     != cgiFormSuccess )
        int_error("Error retrieving CGI form end serial value.");
        snprintf(title, sizeof(title), "Search Certs by Serial Number");
        snprintf(subtitle, sizeof(subtitle), "Certificates with serial number between %s and %s", startserstr, endserstr);
      }
      else int_error("Error CGI form retrieving a valid search type.");
    }

/* -------------------------------------------------------------------------- *
 * We got CGI arguments, first we get a list of .pem files from the cert dir  *
 * ---------------------------------------------------------------------------*/
  certcounter = scandir(CACERTSTORE, &certstore_files, file_select, hexsort);
  // It can happen that our search does not return any certs. This is not an error.
  //if(certcounter<=0) int_error("Error: No certificate files found.");

/* -------------------------------------------------------------------------- *
 * calculate how many pages we get with MAXCERTDISPLAY                         *
 * ---------------------------------------------------------------------------*/

  if(certcounter<=MAXCERTDISPLAY) pagecounter = 1;
  else {
    disp_calc = div(certcounter, MAXCERTDISPLAY);
    /* if the count of certs divided by MAXCERTDISPLAY has no remainder */
    if(disp_calc.rem == 0) pagecounter = disp_calc.quot;
    /* with a remainder, we must prepare an extra page for the rest */
    else pagecounter = disp_calc.quot +1;
  }

/* -------------------------------------------------------------------------- *
 * Check if we have been subsequently called with a pagenumber & sort request *
 * ---------------------------------------------------------------------------*/

  if(cgiFormInteger("page", &pagenumber, 1) == cgiFormSuccess)
    if(pagenumber > pagecounter || pagenumber <=0)
      int_error("Error: Page does not exist.");

  if(cgiFormString("sort", sorting, sizeof(sorting)) != cgiFormSuccess)
      strncpy(sorting, "desc", sizeof(sorting));

/* -------------------------------------------------------------------------- *
 * now we know how many certs we have in total and we can build the page(s).  *
 * For every MAXCERTDISPLAY certs we start a new page and cycle through by    *
 * calling ourself with the requested certs in range.                         *
 * ---------------------------------------------------------------------------*/

  if(strcmp(sorting, "asc") == 0) {

    if(certcounter <= MAXCERTDISPLAY) {
       dispmaxlines = certcounter;
       tempcounter = 0;
    }
    else
      if(pagenumber == pagecounter &&
             ( pagecounter * MAXCERTDISPLAY) - certcounter != 0) {

        tempcounter = (pagecounter * MAXCERTDISPLAY) - MAXCERTDISPLAY;
        dispmaxlines = certcounter - ((pagecounter-1) * MAXCERTDISPLAY);
      }
      else {

        tempcounter = (pagenumber * MAXCERTDISPLAY) - MAXCERTDISPLAY;
        dispmaxlines = MAXCERTDISPLAY;
      }
  }

  if(strcmp(sorting, "desc") == 0) {

    if(certcounter <= MAXCERTDISPLAY) {
       dispmaxlines = certcounter;
       tempcounter = certcounter;
    }
    else
      if(pagenumber == pagecounter &&
             ( pagecounter * MAXCERTDISPLAY) - certcounter != 0) {

        tempcounter = certcounter - ((pagecounter-1) * MAXCERTDISPLAY);
        dispmaxlines = certcounter - ((pagecounter-1) * MAXCERTDISPLAY);
      }
      else {

       tempcounter = certcounter - (pagenumber*MAXCERTDISPLAY) + MAXCERTDISPLAY;
       dispmaxlines = MAXCERTDISPLAY;
      }
  }

/* -------------------------------------------------------------------------- *
 * start the html output                                                      *
 * ---------------------------------------------------------------------------*/

  pagehead(title);

  //debugging only:
  //printf("Number of certs: %d\n", certcounter);
  //printf("Num tempcounter: %d\n", tempcounter);
  //printf("Number of pages: %d\n", pagecounter);
  //printf("Div Quotient: %d\n", disp_calc.quot);
  //printf("Div Remainder: %d\n", disp_calc.rem);
  //fprintf(cgiOut, "</BODY></HTML>\n");
  //exit(0);

/* -------------------------------------------------------------------------- *
 * start the form output                                                      *
 * ---------------------------------------------------------------------------*/

   fprintf(cgiOut, "<h3>%s</h3>\n", subtitle);
   fprintf(cgiOut, "<p></p>\n");
   fprintf(cgiOut, "<table>\n");
   fprintf(cgiOut, "<tr>\n");
   fprintf(cgiOut, "<th width=\"20\">");
   fprintf(cgiOut, "#");
   fprintf(cgiOut, "</th>\n");
   fprintf(cgiOut, "<th width=\"495\">");
   fprintf(cgiOut, "Certificate Subject Information");
   fprintf(cgiOut, "</th>\n");
   fprintf(cgiOut, "<th width=\"60\" colspan=\"2\">");
   fprintf(cgiOut, "Expires");
   fprintf(cgiOut, "</th>\n");
   fprintf(cgiOut, "<th width=\"65\">");
   fprintf(cgiOut, "Action");
   fprintf(cgiOut, "</th>\n");
   fprintf(cgiOut, "</tr>\n");

  /* if our search did not return any certs, we display a note instead */
  if(certcounter<=0) {
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<td class=\"even\" colspan=\"5\">");
    fprintf(cgiOut, "Could not find any certificates for the given search criteria.");
    fprintf(cgiOut, "</td>\n");
    fprintf(cgiOut, "</tr>\n");
  }

  for(dispcounter=0; dispcounter < dispmaxlines; dispcounter++) {

    /* zero certificate values and flags */
    certvalidity = 0;
    percent = 0;
    available_secs = 0;
    remaining_secs = 0;
    cert = X509_new();
    certsubject = X509_NAME_new();

    if(strcmp(sorting, "desc") == 0) tempcounter--;

    snprintf(certfilestr, sizeof(certfilestr), "%s/%s",
                           CACERTSTORE, certstore_files[tempcounter]->d_name);

    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th rowspan=\"2\">");
    fprintf(cgiOut, "%d", tempcounter+1);
    fprintf(cgiOut, "</th>\n");

    oddline_calc = div(tempcounter+1, 2);
    if(oddline_calc.rem)
      fprintf(cgiOut, "<td rowspan=\"2\" class=\"odd\">");
    else
      fprintf(cgiOut, "<td rowspan=\"2\" class=\"even\">");

    if ( (certfile = fopen(certfilestr, "r")) != NULL) {
      PEM_read_X509(certfile, &cert, NULL, NULL);

      /* ---------------------------------------------------------- *
       * Display the subject data. Use the UTF-8 flag to show       *
       * Japanese Kanji. This also needs the separator flag to work *
       * ---------------------------------------------------------- */
      certsubject = X509_get_subject_name(cert);
      X509_NAME_print_ex_fp(cgiOut, certsubject, 0,
         ASN1_STRFLGS_UTF8_CONVERT|XN_FLAG_SEP_CPLUS_SPC);

      /* store certificate start date for later eval */
      start_date = X509_get_notBefore(cert);

      /* store certificate expiration date for later eval */
      expiration_date = X509_get_notAfter(cert);

      /* check the start and end dates in the cert */
      if (X509_cmp_current_time (X509_get_notBefore (cert)) >= 0)
        /* flag the certificate as not valid yet */
        certvalidity = 0;
      else
      if (X509_cmp_current_time (X509_get_notAfter (cert)) <= 0)
        /* flag the certificate as expired */
        certvalidity = 0;
      else 
        /* flag the certificate is still valid */
        certvalidity = 1;

      fclose(certfile);
    }
    else 
       fprintf(cgiOut, "Error: Can't open certificate file %s for reading.",
                                                                 certfilestr);
    fprintf(cgiOut, "</td>\n");

    if(certvalidity == 0) {

      /* expiration bar display column */
      fprintf(cgiOut, "<th rowspan=\"2\">\n");
      fprintf(cgiOut, "<table class=\"led\">\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "</table>\n");
      fprintf(cgiOut, "</th>\n");

      /* remaining days before expiration column */
      fprintf(cgiOut, "<th class=\"exnok\" rowspan=\"2\">");
      fprintf(cgiOut, "Inval.<br />/Expd");
      fprintf(cgiOut, "</th>\n");
    }

    if(certvalidity == 1) {

      /* ------ START get the certificate lifetime in seconds ------ */
      /* copy the start date into a string */
      membio = BIO_new(BIO_s_mem());
      ASN1_TIME_print(membio, start_date);
      BIO_gets(membio, membio_buf, sizeof(membio_buf));
      BIO_free(membio);

      /* parse the start date string into a time struct */
      memset (&start_tm, '\0', sizeof(start_tm));
      strptime(membio_buf, "%h %d %T %Y %z", &start_tm);
      start = mktime(&start_tm);

      /* ------ START get the certificate remaining time in seconds ------ */
      /* copy the expiration date into a string */
      membio = BIO_new(BIO_s_mem());
      ASN1_TIME_print(membio, expiration_date);
      BIO_gets(membio, membio_buf, sizeof(membio_buf));
      BIO_free(membio);
  
      /* parse the expiration date string into a time struct */
      memset (&expiration_tm, '\0', sizeof(expiration_tm));
      strptime(membio_buf, "%h %d %T %Y %z", &expiration_tm);
  
      /* get the current time */
      expiration = mktime(&expiration_tm);
  
      /* get the time difference between expiration time and current time */
      remaining_secs = difftime(expiration, now);
      /* ------ END get the certificate remaining time in seconds ------ */

      /* get the time difference between start and expiration time */
      available_secs = difftime(expiration, start);
      /* ------ END get the certificate lifetime in seconds ------ */
  
      /* ------ START calculate percentage of lifetime left ------ */
      /* remaining_secs *100                                       */
      /* ------------------- = X, rounded down with floor()        */
      /* available_secs                                            */
      percent = floor((remaining_secs*100)/available_secs);
      /* ------ END calculate percentage of lifetime left   ------ */
  
      /* expiration bar display column */
      fprintf(cgiOut, "<th rowspan=\"2\">");
      fprintf(cgiOut, "<table class=\"led\">\n");
      if (percent >= 90) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#00FF00></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 80) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#00FF33></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 70) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#99FF33></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 60) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#FFFF00></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 50) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#FFCC00></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 40) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#FF9900></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 30) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#FF6600></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 20) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#FF3300></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      if (percent >= 10) fprintf(cgiOut, "  <tr><td class=\"led\" bgcolor=#FF0000></td></tr>\n");
      else fprintf(cgiOut, "  <tr><td class=\"led-off\"></td></tr>\n");
      fprintf(cgiOut, "</table>\n");
      fprintf(cgiOut, "</th>");
  
      /* remaining days before expiration column */
      //fprintf(cgiOut, membio_buf);
      if (percent < 10) fprintf(cgiOut, "<th class=\"exnok\" rowspan=\"2\">\n");
      else fprintf(cgiOut, "<th class=\"exok\" rowspan=\"2\">\n");
      if(floor(remaining_secs/63072000) > 0) fprintf(cgiOut, "%.f<br />years", remaining_secs/31536000);
      else if(floor(remaining_secs/86400) > 0 ) fprintf(cgiOut, "%.f<br />days", remaining_secs/86400);
      else if(floor(remaining_secs/3600) > 0 ) fprintf(cgiOut, "%.f<br />hours", remaining_secs/3600);
      else if(floor(remaining_secs/60) > 0 ) fprintf(cgiOut, "%.f<br />mins", remaining_secs/60);
      else fprintf(cgiOut, "%.f<br />secs", remaining_secs);
      fprintf(cgiOut, "</th>\n");
    }

    /* action column */
    fprintf(cgiOut, "<th>");
    fprintf(cgiOut, "<form action=\"getcert.cgi\" method=\"post\">\n");
    fprintf(cgiOut, "<input type=\"hidden\" name=\"cfilename\" ");
    fprintf(cgiOut, "value=\"%s\" />\n", certstore_files[tempcounter]->d_name);
    fprintf(cgiOut, "<input type=\"hidden\" name=\"format\" value=\"pem\" />\n");
    fprintf(cgiOut, "<input class=\"getcert\" type=\"submit\" value=\"Detail\" />\n");
    fprintf(cgiOut, "</form>\n");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "</tr>\n");
    fprintf(cgiOut, "<tr>\n");
    fprintf(cgiOut, "<th>");
    fprintf(cgiOut, "<form action=\"getcert.cgi\" method=\"post\">\n");
    fprintf(cgiOut, "<input type=\"hidden\" name=\"cfilename\" ");
    fprintf(cgiOut, "value=\"%s\" />\n", certstore_files[tempcounter]->d_name);
    fprintf(cgiOut, "<input type=\"hidden\" name=\"format\" value=\"text\" />\n");
    fprintf(cgiOut, "<input class=\"getcert\" type=\"submit\" value=\"Renew\" />\n");
    fprintf(cgiOut, "</form>");
    fprintf(cgiOut, "</th>\n");
    fprintf(cgiOut, "</tr>\n");

    if(strcmp(sorting, "asc") == 0) tempcounter++;
  }


  fprintf(cgiOut, "<tr>\n");
  fprintf(cgiOut, "<th colspan=\"5\">");
  fprintf(cgiOut, "Total # of certs: %d | ", certcounter);
  fprintf(cgiOut, "Page %d of %d", pagenumber, pagecounter);
  fprintf(cgiOut, "</th>");
  fprintf(cgiOut, "</tr>");
  fprintf(cgiOut, "</table>\n");

  fprintf(cgiOut, "<p></p>\n");

  fprintf(cgiOut, "<table>\n");

  fprintf(cgiOut, "<tr>\n");
  fprintf(cgiOut, "<th>");
  fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"post\">");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"sort\" ");
  fprintf(cgiOut, "value=\"desc\" />\n");
  resubmit();
  fprintf(cgiOut, "<input type=\"submit\" name=\"sort\"");
  fprintf(cgiOut, " value=\"Latest Certs first\" />");
  fprintf(cgiOut, "</form>");
  fprintf(cgiOut, "</th>\n");

  fprintf(cgiOut, "<th>");
  fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"post\">");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"sort\" ");
  fprintf(cgiOut, "value=\"asc\">\n");
  resubmit();
  fprintf(cgiOut, "<input type=\"submit\" name=\"sort\"");
  fprintf(cgiOut, " value=\"Oldest Certs first\">");
  fprintf(cgiOut, "</form>");
  fprintf(cgiOut, "</th>\n");

  // filler 1
  fprintf(cgiOut, "<th width=\"15\">");
  fprintf(cgiOut, "&nbsp;");
  fprintf(cgiOut, "</th>\n");

  // goto page 1
  fprintf(cgiOut, "<th width=\"5\">");
  fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"post\">");
  resubmit();
  fprintf(cgiOut, "<input type=\"submit\" value=\"&lt;&lt;\" />");
  fprintf(cgiOut, "</form>");
  fprintf(cgiOut, "</th>\n");

  // goto page before
  fprintf(cgiOut, "<th width=\"5\">");
  fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"post\">");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"certcounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", certcounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"pagecounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", pagecounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"page\" ");
  fprintf(cgiOut, "value=\"");
  tempcounter = 0;
  if(pagenumber > 1) tempcounter = pagenumber - 1;
  else tempcounter = 1;
  fprintf(cgiOut, "%d", tempcounter);
  fprintf(cgiOut, "\" />\n");
  resubmit();
  fprintf(cgiOut, "<input type=\"submit\" value=\"&lt; 1\">");
  fprintf(cgiOut, "</form>");
  fprintf(cgiOut, "</th>\n");

  // goto page after
  fprintf(cgiOut, "<th width=\"5\">");
  fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"post\">");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"certcounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", certcounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"pagecounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", pagecounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"page\" ");
  fprintf(cgiOut, "value=\"");
  tempcounter = 0;
  if(pagecounter > pagenumber) tempcounter = pagenumber + 1;
  else tempcounter = pagecounter;
  fprintf(cgiOut, "%d", tempcounter);
  fprintf(cgiOut, "\" />\n");
  resubmit();
  fprintf(cgiOut, "<input type=\"submit\" value=\"1 &gt;\" />");
  fprintf(cgiOut, "</form>");
  fprintf(cgiOut, "</th>\n");

  // goto last page
  fprintf(cgiOut, "<th width=\"5\">");
  fprintf(cgiOut, "<form action=\"certsearch.cgi\" method=\"post\">");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"certcounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", certcounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"pagecounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", pagecounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"page\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", pagecounter);
  fprintf(cgiOut, "\" />\n");
  resubmit();
  fprintf(cgiOut, "<input type=\"submit\" value=\"&gt;&gt;\" />");
  fprintf(cgiOut, "</form>");
  fprintf(cgiOut, "</th>\n");

  // goto page number
  fprintf(cgiOut, "<th width=\"120\">\n");
  fprintf(cgiOut, "<form class=\"setpage\" action=\"certsearch.cgi\" method=\"post\">\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"certcounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", certcounter);
  fprintf(cgiOut, "\" />\n");
  fprintf(cgiOut, "<input type=\"hidden\" name=\"pagecounter\" ");
  fprintf(cgiOut, "value=\"");
  fprintf(cgiOut, "%d", pagecounter);
  fprintf(cgiOut, "\" />\n");
  resubmit();
  fprintf(cgiOut, "<input class=\"goto\" type=\"submit\" value=\"Goto\" />\n");
  fprintf(cgiOut, "&nbsp; &nbsp;");
  fprintf(cgiOut, "<input class=\"page\" type=\"text\" name=\"page\" ");
  fprintf(cgiOut, "value=\"%d\" />\n", pagecounter);
  fprintf(cgiOut, "</form>\n");
  fprintf(cgiOut, "</th>\n");

  fprintf(cgiOut, "</tr>\n");
  fprintf(cgiOut, "</table>\n");

/* ---------------------------------------------------------------------------*
 * end the html output                                                        *
 * ---------------------------------------------------------------------------*/

  pagefoot();
}
  return(0);
}
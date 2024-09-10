/*=== populate_collections_ctr_list =====================================
  Populates poplists associated with Remittance Center text field on miscinfo
  window.
  ===========================================================================*/
int populate_collections_ctr_list()
{
   int  ret_code;
   int  db_value;
   char description[POPLIST_DESCR_LEN];

   num_collections_ctr_codes = 0;

   dbcmd (dbproc1, "select sc.service_center_id, sc_name ") ;
   dbcmd (dbproc1, "from SERVICE_CENTERS sc, SERVICE_CENTER_TYPES sct ");
   dbcmd (dbproc1, "where sc.service_center_id = sct.service_center_id ") ;
   dbfcmd(dbproc1, "and service_center_type = %d", SC_FRONT);

   br_dbsqlexec(dbproc1);
   if (Sybase_error)
   {
      dbcancel(dbproc1);
      return(FAILURE);
   }

   while ((ret_code = dbresults(dbproc1)) != NO_MORE_RESULTS)
   {
      if (ret_code == FAIL)
      {
         dbcancel(dbproc1);
         return(FAILURE);
      }
      else
      {
         dbbind(dbproc1, 1, INTBIND, 0, &db_value);
         dbbind(dbproc1, 2, NTBSTRINGBIND, 0, description);
         while (dbnextrow(dbproc1) != NO_MORE_ROWS)
         {
            num_collections_ctr_codes++;

            /* Increase memory for list structure */
            collections_ctr_list =
               (DB_POPLIST_TYPE *) realloc (collections_ctr_list,
                num_collections_ctr_codes * sizeof (DB_POPLIST_TYPE));
	    if (collections_ctr_list == NULL) 
	      {
		printf("realloc of collections_ctr_list FAILED %d\n",
			num_collections_ctr_codes);
		exit(1) ;
	      }

            /* Increase memory for XmString structure */
            collections_ctr_strings =
               (XmString *) realloc (collections_ctr_strings,
               num_collections_ctr_codes * sizeof (XmString));
	    if (collections_ctr_strings == NULL) 
	      {
		printf("realloc of serv_ctcollections_ctr_strings FAILED %d\n",
			num_collections_ctr_codes);
		exit(1) ;
	    }

            /* Fill in list structre */
            collections_ctr_list[num_collections_ctr_codes-1].db_code =
               db_value;
            strcpy
               (collections_ctr_list[num_collections_ctr_codes-1].description,
               description);

            /* Fill in XmString structure */
            collections_ctr_strings[num_collections_ctr_codes-1] =
	      XmStringCreateSimple(description);

	    collections_ctr_default = 0 ;
         } /* end while dbnextrow */
      } /* end else */
   } /* end while dbresuls */

   return(SUCCESS);

} /* end populate_collections_ctr_list */
int   mdsdcl_set_command(		/* Return: status		*/
    struct _mdsdcl_ctrl  *ctrl		/* <m> the control structure	*/
   )
   {
    int   sts;
    void  *newTable;
    static DYNAMIC_DESCRIPTOR(dsc_table);

		/*------------------------------------------------------
		 * Get tablename and find its address in shared library ...
		 *-----------------------------------------------------*/
    sts = cli_get_value("TABLE",&dsc_table);
    if (sts & 1)
       {
        int i;
        for (i=0;i<dsc_table.dscW_length;i++)
          dsc_table.dscA_pointer[i] = _tolower(dsc_table.dscA_pointer[i]);
        if (!strstr(dsc_table.dscA_pointer,"_commands"))
          str_concat(&dsc_table,&dsc_table,"_commands",0);
        sts = LibFindImageSymbol(&dsc_table,&dsc_table,&newTable);
        if (~sts & 1)
            return(MdsMsg(sts,"Failed to open table %s",
                dsc_table.dscA_pointer));

		/*------------------------------------------------------
		 *... add newTable address to "tbladr[]" list
		 *-----------------------------------------------------*/
        for (i=0 ; i<ctrl->tables ; i++)
            if (newTable == ctrl->tbladr[i])  break;
        if (i == ctrl->tables)
           {
            if (ctrl->tables >= MAX_TABLES)
               {
                fprintf(stderr,"set_command: *WARN* Max_tables exceeded\n");
                return(0);
               }
            ctrl->tbladr[ctrl->tables++] = newTable;
           }
       }

		/*------------------------------------------------------
		 * Check for other qualifiers ...
		 *-----------------------------------------------------*/
    if (cli_present("HELPLIB") & 1)
        cli_get_value("HELPLIB",&ctrl->helplib);

    if (cli_present("PROMPT") & 1)
        cli_get_value("PROMPT",&ctrl->prompt);

    if (cli_present("DEF_FILE") & 1)
        cli_get_value("DEF_FILE",&ctrl->def_file);

    return(1);
   }
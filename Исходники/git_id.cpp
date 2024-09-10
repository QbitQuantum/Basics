bool convert_sql_updates()
{
    if(new_sql_updates.empty()) return true;

    printf("+ converting sql updates\n");

    // rename the sql update files and add the required update statement
    for(std::set<std::string>::iterator itr = new_sql_updates.begin(); itr != new_sql_updates.end(); ++itr)
    {
        sql_update_info info;
        if(!get_sql_update_info(itr->c_str(), info)) return false;
        if(info.db_idx == NUM_DATABASES) return false;

        // generating the new name should work for updates with or without a rev
        char src_file[MAX_PATH], new_name[MAX_PATH], dst_file[MAX_PATH];
        snprintf(src_file, MAX_PATH, "%s%s/%s", path_prefix, sql_update_dir, itr->c_str());
        snprintf(new_name, MAX_PATH, "%d_%0*d_%s%s%s", rev, 2, info.nr, info.db, info.has_table ? "_" : "", info.table);
        snprintf(dst_file, MAX_PATH, "%s%s/%s.sql", path_prefix, sql_update_dir, new_name);

        FILE * fin = fopen( src_file, "r" );
        if(!fin) return false;
        FILE * fout = fopen( dst_file, "w" );
        if(!fout) { fclose(fin); return false; }

        // add the update requirements
        fprintf(fout, "ALTER TABLE %s CHANGE COLUMN required_%s required_%s bit;\n\n",
            db_version_table[info.db_idx], last_sql_update[info.db_idx], new_name);

        // skip the first one or two lines from the input
        // if it already contains update requirements
        if(fgets(buffer, MAX_BUF, fin))
        {
            char dummy[MAX_BUF];
            if(sscanf(buffer, "ALTER TABLE %s CHANGE COLUMN required_%s required_%s bit", dummy, dummy, dummy) == 3)
            {
                if(fgets(buffer, MAX_BUF, fin) && buffer[0] != '\n')
                    fputs(buffer, fout);
            }
            else
                fputs(buffer, fout);
        }

        // copy the rest of the file
        char c;
        while( (c = getc(fin)) != EOF )
            putc(c, fout);

        fclose(fin);
        fclose(fout);

        // rename the file in git
        snprintf(cmd, MAX_CMD, "git add %s", dst_file);
        system_switch_index(cmd);
        snprintf(cmd, MAX_CMD, "git rm --quiet %s", src_file);
        system_switch_index(cmd);

        // update the last sql update for the current database
        strncpy(last_sql_update[info.db_idx], new_name, MAX_PATH);
    }

    return true;
}
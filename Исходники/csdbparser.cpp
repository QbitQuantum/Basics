csdbparser::enResult csdbparser::get_next_symbol(symdata_pack* pack)
{
    CSDBP_GENERAL_CHK();
    enResult res;
    bool endOfSymbData;
    bool foundSomething;
    int ch;

//if (m_state != stSYMB_SETUP_DONE) return resUNKNOWN_ERR;

    pack->clear();
    if (m_debug) printf("=====> get_next_symbol\n");
    do
    {
        res = single_line_symbol(endOfSymbData, foundSomething);
        if (res != resOK) return res;
        if (endOfSymbData)
        {
            pack->valid = false;
            if (m_debug) printf("End of symbols data!\n");
            return resOK;
        }
    }
    while (foundSomething);
    pack->valid = true;
    pack->filename = m_current_srcfile;
    if (m_debug) printf("=====> Back from get_next_symbol\n");

    ch = fgetc(m_fp);
    if (ch == 0x0A)
    {
        pack->line_num = -1; // empty line
        return resOK; //EOL
    }
    else ungetc(ch, m_fp);

    if (fscanf(m_fp, "%ld", &(pack->line_num)) != 1)
    {
        return resUNKNOWN_ERR;
    }
    ch = fgetc(m_fp); // the space after the line number
    if (fgets(m_buf, m_bufsize, m_fp) == NULL)
    {
        return resFILE_ACCESS_ERR;
    }
    pack->line_text = chomp(m_buf);
    if (m_debug)
    {
        printf("fn = %s, lineno=%ld, firstline=%s\n",
               pack->filename.c_str(), pack->line_num, pack->line_text.c_str());
    }

    int loopcheck = 0; // prevent infinite loop
    sym_data sd;
    while (loopcheck++ < 65500)
    {
        // symbol line
        ch = fgetc(m_fp);
        if ((ch == 0x0A)&&(loopcheck > 1))
        {
            break; //EOL
        }
        else if ((ch >= 0x30)&&(ch <= 0x39)&&(loopcheck > 1))
        {
            ungetc(ch, m_fp);
            break; // symbol shouldn't start with line numbers
        }
        else
        {
            ungetc(ch, m_fp);
            res = symbolread(&sd, pack);
            if (res != resOK) return res;
            pack->line_text += sd.symbname;
            if (sd.valid)
            {
                pack->symbols.push_back(sd);
            }
        }
        // no-symbol line
        ch = fgetc(m_fp);
        if ((ch == 0x0A)&&(loopcheck > 1))
        {
            ;
        }
        else
        {
            ungetc(ch, m_fp);
            if (fgets(m_buf, m_bufsize, m_fp) == NULL)
            {
                return resFILE_ACCESS_ERR;
            }
            pack->line_text += chomp(m_buf);
        }
    }
    return resOK;
}
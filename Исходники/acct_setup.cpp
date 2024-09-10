int PROJECT_INIT::init() {
    char    buf[256];
    MIOFILE mf;
    FILE*   p;

    clear();
    p = fopen(PROJECT_INIT_FILENAME, "r");
    if (p) {
        mf.init_file(p);
        while(mf.fgets(buf, sizeof(buf))) {
            if (match_tag(buf, "</project_init>")) break;
            else if (parse_str(buf, "<name>", name, 256)) continue;
            else if (parse_str(buf, "<team_name>", team_name, 256)) continue;
            else if (parse_str(buf, "<url>", url, 256)) {
                canonicalize_master_url(url);
                continue;
            } else if (parse_str(buf, "<account_key>", account_key, 256)) {
                continue;
            }
        }
        fclose(p);
        msg_printf(0, MSG_INFO, "Found project_init.xml for %s", url);
    }
    return 0;
}
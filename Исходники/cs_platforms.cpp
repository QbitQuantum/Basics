// write XML list of supported platforms
//
void CLIENT_STATE::write_platforms(PROJECT* p, MIOFILE& mf) {

    mf.printf(
        "    <platform_name>%s</platform_name>\n",
        p->anonymous_platform ? "anonymous" : get_primary_platform()
    );

    for (unsigned int i=1; i<platforms.size(); i++) {
        PLATFORM& platform = platforms[i];
        mf.printf(
            "    <alt_platform>\n"
            "        <name>%s</name>\n"
            "    </alt_platform>\n",
            platform.name.c_str()
        );
    }
}
/*
 * Given a filename return a filesystem URL. Relative paths are prefixed with
 * the datafile directory path.
 */
gchar *
data_file_url(const gchar *filename)
{
    gchar *file_path;
    gchar *uri;

    /* Absolute path? */
#ifdef G_OS_WIN32
    if((strlen(filename) > 2) && (filename[1] == ':')) {
      file_path = g_strdup(filename);
#else
    if((strlen(filename) > 1) && (filename[0] == '/')) {
      file_path = g_strdup(filename);
#endif
    } else if(running_in_build_directory()) {
        file_path = g_strdup_printf("%s/doc/%s", get_datafile_dir(), filename);
    } else {
        file_path = g_strdup_printf("%s/%s", get_datafile_dir(), filename);
    }

    /* XXX - check, if the file is really existing, otherwise display a simple_dialog about the problem */

    /* convert filename to uri */
    uri = g_filename_to_uri(file_path, NULL, NULL);
    g_free(file_path);
    return uri;
}

const char *
topic_online_url(topic_action_e action)
{
    switch(action) {
    case(ONLINEPAGE_HOME):
        return "http://www.wireshark.org";
        break;
    case(ONLINEPAGE_WIKI):
        return "http://wiki.wireshark.org";
        break;
    case(ONLINEPAGE_DOWNLOAD):
        return "http://www.wireshark.org/download.html";
        break;
    case(ONLINEPAGE_USERGUIDE):
        return "http://www.wireshark.org/docs/wsug_html_chunked/";
        break;
    case(ONLINEPAGE_FAQ):
        return "http://www.wireshark.org/faq.html";
        break;
    case(ONLINEPAGE_ASK):
        return "http://ask.wireshark.org";
        break;
    case(ONLINEPAGE_SAMPLE_FILES):
        return "http://wiki.wireshark.org/SampleCaptures";
        break;
    case(ONLINEPAGE_CAPTURE_SETUP):
        return "http://wiki.wireshark.org/CaptureSetup";
        break;
    case(ONLINEPAGE_NETWORK_MEDIA):
        return "http://wiki.wireshark.org/CaptureSetup/NetworkMedia";
        break;
    case(ONLINEPAGE_SAMPLE_CAPTURES):
        return "http://wiki.wireshark.org/SampleCaptures";
        break;
    case(ONLINEPAGE_SECURITY):
        return "http://wiki.wireshark.org/Security";
        break;
    case(ONLINEPAGE_CHIMNEY):
        return "http://wiki.wireshark.org/CaptureSetup/Offloading#chimney";
        break;
    default:
        return NULL;
    }
}

/*
 * Open the help dialog and show a specific HTML help page.
 */
gchar *
user_guide_url(const gchar *page) {
    GString *url = g_string_new("");
    gchar *ug_url = NULL;

    /*
     * Try to open local .chm file. This is not the most intuitive way to
     * go about this but it fits in with the rest of the _url functions.
     */
#ifdef HHC_DIR
    HWND hw;

    g_string_printf(url, "%s\\user-guide.chm::/wsug_chm/%s>Wireshark Help",
        get_datafile_dir(), page);

    hw = HtmlHelpW(NULL,
        utf_8to16(url->str),
        HH_DISPLAY_TOPIC, 0);

    /* if the .chm file could be opened, stop here */
    if(hw != NULL) {
        g_string_free(url, TRUE /* free_segment */);
        return NULL;
    }
#endif /* HHC_DIR */

#ifdef DOC_DIR
    if (g_file_test(DOC_DIR "/guides/wsug_html_chunked", G_FILE_TEST_IS_DIR)) {
        /* try to open the HTML page from wireshark.org instead */
        g_string_printf(url, "file://" DOC_DIR "/guides/wsug_html_chunked/%s", page);
    } else {
#endif /* ifdef DOC_DIR */
       /* try to open the HTML page from wireshark.org instead */
        g_string_printf(url, "http://www.wireshark.org/docs/wsug_html_chunked/%s", page);
#ifdef DOC_DIR
    }
#endif /* ifdef DOC_DIR */


    ug_url = url->str;
    g_string_free(url, FALSE);
    return ug_url;
}
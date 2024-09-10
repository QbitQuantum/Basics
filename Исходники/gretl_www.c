static void urlinfo_set_url (urlinfo *u, const char *url)
{
    u->url[0] = '\0';
    strncat(u->url, url, URLLEN - 1);
}
Encoding *ParseEncodingNameFromList(GGadget *listfield) {
    const unichar_t *name = _GGadgetGetTitle(listfield);
    int32 len;
    GTextInfo **ti = GGadgetGetList(listfield,&len);
    int i;
    Encoding *enc = NULL;

    for ( i=0; i<len; ++i ) if ( ti[i]->text!=NULL ) {
            if ( u_strcmp(name,ti[i]->text)==0 ) {
                enc = FindOrMakeEncoding(ti[i]->userdata);
                break;
            }
        }

    if ( enc == NULL ) {
        char *temp = u2utf8_copy(name);
        enc = FindOrMakeEncoding(temp);
        free(temp);
    }
    if ( enc==NULL )
        ff_post_error(_("Bad Encoding"),_("Bad Encoding"));
    return( enc );
}
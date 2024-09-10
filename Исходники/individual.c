void gges_mapping_append_symbol(struct gges_mapping *mapping, char *token)
{
    int tlen;

    if (mapping) {
        tlen = strlen(token);
        /* first, check to see if the string buffer needs
         * extending, and realloc as required */
        if ((mapping->l + tlen + 1) > mapping->sz) {
            while (mapping->sz < (mapping->l + tlen + 1)) mapping->sz += BUFFER_INC;

            mapping->buffer = REALLOC(mapping->buffer, mapping->sz, sizeof(char));
        }

        /* then, push terminal symbol into stream */
        strcat(mapping->buffer, token);
        mapping->l += tlen;
    } else {
        fprintf(stdout, "%s", token);
    }
}
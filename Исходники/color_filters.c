/* XXX - Would it make more sense to use GStrings here instead of reallocing
   our buffers? */
static gboolean
read_filters_file(FILE *f, gpointer user_data)
{
#define INIT_BUF_SIZE 128
    gchar    *name             = NULL;
    gchar    *filter_exp       = NULL;
    guint32   name_len         = INIT_BUF_SIZE;
    guint32   filter_exp_len   = INIT_BUF_SIZE;
    guint32   i                = 0;
    gint32    c;
    guint16   fg_r, fg_g, fg_b, bg_r, bg_g, bg_b;
    gboolean  disabled         = FALSE;
    gboolean  skip_end_of_line = FALSE;

    name = (gchar *)g_malloc(name_len + 1);
    filter_exp = (gchar *)g_malloc(filter_exp_len + 1);

    while (1) {

        if (skip_end_of_line) {
            do {
                c = getc(f);
            } while (c != EOF && c != '\n');
            if (c == EOF)
                break;
            disabled = FALSE;
            skip_end_of_line = FALSE;
        }

        while ((c = getc(f)) != EOF && isspace(c)) {
            if (c == '\n') {
                continue;
            }
        }

        if (c == EOF)
            break;

        if (c == '!') {
            disabled = TRUE;
            continue;
        }

        /* skip # comments and invalid lines */
        if (c != '@') {
            skip_end_of_line = TRUE;
            continue;
        }

        /* we get the @ delimiter.
         * Format is:
         * @name@filter expression@[background r,g,b][foreground r,g,b]
         */

        /* retrieve name */
        i = 0;
        while (1) {
            c = getc(f);
            if (c == EOF || c == '@')
                break;
            if (i >= name_len) {
                /* buffer isn't long enough; double its length.*/
                name_len *= 2;
                name = (gchar *)g_realloc(name, name_len + 1);
            }
            name[i++] = c;
        }
        name[i] = '\0';

        if (c == EOF) {
            break;
        } else if (i == 0) {
            skip_end_of_line = TRUE;
            continue;
        }

        /* retrieve filter expression */
        i = 0;
        while (1) {
            c = getc(f);
            if (c == EOF || c == '@')
                break;
            if (i >= filter_exp_len) {
                /* buffer isn't long enough; double its length.*/
                filter_exp_len *= 2;
                filter_exp = (gchar *)g_realloc(filter_exp, filter_exp_len + 1);
            }
            filter_exp[i++] = c;
        }
        filter_exp[i] = '\0';

        if (c == EOF) {
            break;
        } else if (i == 0) {
            skip_end_of_line = TRUE;
            continue;
        }

        /* retrieve background and foreground colors */
        if (fscanf(f,"[%hu,%hu,%hu][%hu,%hu,%hu]",
                   &bg_r, &bg_g, &bg_b, &fg_r, &fg_g, &fg_b) == 6) {

            /* we got a complete color filter */

            color_t bg_color, fg_color;
            color_filter_t *colorf;
            dfilter_t *temp_dfilter;

            if (!dfilter_compile(filter_exp, &temp_dfilter)) {
                g_warning("Could not compile \"%s\" in colorfilters file.\n%s",
                          name, dfilter_error_msg);
                prefs.unknown_colorfilters = TRUE;

                skip_end_of_line = TRUE;
                continue;
            }

            if (!initialize_color(&fg_color, fg_r, fg_g, fg_b)) {
                /* oops */
                simple_dialog(ESD_TYPE_ERROR, ESD_BTN_OK,
                              "Could not allocate foreground color "
                              "specified in input file for %s.", name);
                dfilter_free(temp_dfilter);
                skip_end_of_line = TRUE;
                continue;
            }
            if (!initialize_color(&bg_color, bg_r, bg_g, bg_b)) {
                /* oops */
                simple_dialog(ESD_TYPE_ERROR, ESD_BTN_OK,
                              "Could not allocate background color "
                              "specified in input file for %s.", name);
                dfilter_free(temp_dfilter);
                skip_end_of_line = TRUE;
                continue;
            }

            colorf = color_filter_new(name, filter_exp, &bg_color,
                                      &fg_color, disabled);
            if(user_data == &color_filter_list) {
                GSList **cfl = (GSList **)user_data;

                /* internal call */
                colorf->c_colorfilter = temp_dfilter;
                *cfl = g_slist_append(*cfl, colorf);
            } else {
                /* external call */
                /* just editing, don't need the compiled filter */
                dfilter_free(temp_dfilter);
                color_filter_add_cb (colorf, user_data);
            }
        }    /* if sscanf */

        skip_end_of_line = TRUE;
    }

    g_free(name);
    g_free(filter_exp);
    return TRUE;
}
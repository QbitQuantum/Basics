void insert(int intarget)
{
    size_t
	nmemb;
    PATTERN_
        *p;
    char
	**p2;

    str2pattern ();

    nmemb = n_patterns;
    p = lfind (buffer2, patterns, &nmemb, sizeof (PATTERN_), lfindpat);
    if (! p) {
	if (n_patterns == max_patterns) {
	    max_patterns += 32;
	    patterns = (PATTERN_ *) s_realloc (patterns, max_patterns * sizeof (PATTERN_));
	}
	patterns [n_patterns].s = s_strdup (buffer2);
	patterns [n_patterns].n_forms = 0;
	patterns [n_patterns].max_forms = 0;
	patterns [n_patterns].i = 0;
	patterns [n_patterns].o = 0;
	patterns [n_patterns].used = 0;
	patterns [n_patterns].rejected = 0;
	patterns [n_patterns].forms = NULL;
	p = &(patterns [n_patterns]);
	n_patterns++;
    }

    if (intarget)
	p->i++;
    else
	p->o++;

    if (p->i + p->o >= minvar)
	p->used = 1;

    p2 = NULL;
    if (p->n_forms > 0) {
	nmemb = p->n_forms;
	p2 = lfind (buffer, p->forms, &nmemb, sizeof (char *), searchcmp);
    }
    if (! p2) {
	if (p->n_forms == p->max_forms) {
	    p->max_forms += 32;
	    p->forms = (char **) s_realloc (p->forms, p->max_forms * sizeof (char *));
	}
	p->forms[p->n_forms] = s_strdup (buffer);
	p->n_forms++;
    }

}
static void print_icu_transliterators(const struct config_t *p_config)
{
    UErrorCode status;
    UEnumeration *en = utrans_openIDs(&status);
    int32_t count = uenum_count(en, &status);
    const char *name;
    int32_t length;

    if (p_config->xmloutput)
        fprintf(p_config->outfile, "<transliterators count=\"%d\">\n",  count);
    else
        fprintf(p_config->outfile, "Available ICU transliterators: %d\n", count);

    while ((name = uenum_next(en, &length, &status)))
    {
        if (p_config->xmloutput)
            fprintf(p_config->outfile, "<transliterator id=\"%s\"/>\n", name);
        else
            fprintf(p_config->outfile, "%s\n", name);
    }
    uenum_close(en);
    if (p_config->xmloutput)
        fprintf(p_config->outfile, "</transliterators>\n");
    else
    {
        fprintf(p_config->outfile, "\n\nUnicode Set Patterns:\n"
                "   Pattern         Description\n"
                "   Ranges          [a-z] 	The lower case letters a through z\n"
                "   Named Chars     [abc123] The six characters a,b,c,1,2 and 3\n"
                "   String          [abc{def}] chars a, b and c, and string 'def'\n"
                "   Categories      [\\p{Letter}] Perl General Category 'Letter'.\n"
                "   Categories      [:Letter:] Posix General Category 'Letter'.\n"
                "\n"
                "   Combination     Example\n"
                "   Union           [[:Greek:] [:letter:]]\n"
                "   Intersection    [[:Greek:] & [:letter:]]\n"
                "   Set Complement  [[:Greek:] - [:letter:]]\n"
                "   Complement      [^[:Greek:] [:letter:]]\n"
                "\n"
             "see: http://icu.sourceforge.net/userguide/unicodeSet.html\n"
                "\n"
                "Examples:\n"
                "   [:Punctuation:] Any-Remove\n"
                "   [:Cased-Letter:] Any-Upper\n"
                "   [:Control:] Any-Remove\n"
                "   [:Decimal_Number:] Any-Remove\n"
                "   [:Final_Punctuation:] Any-Remove\n"
                "   [:Georgian:] Any-Upper\n"
                "   [:Katakana:] Any-Remove\n"
                "   [:Arabic:] Any-Remove\n"
                "   [:Punctuation:] Remove\n"
                "   [[:Punctuation:]-[.,]] Remove\n"
                "   [:Line_Separator:] Any-Remove\n"
                "   [:Math_Symbol:] Any-Remove\n"
                "   Lower; [:^Letter:] Remove (word tokenization)\n"
                "   [:^Number:] Remove (numeric tokenization)\n"
                "   [:^Katagana:] Remove (remove everything except Katagana)\n"
                "   Lower;[[:WhiteSpace:][:Punctuation:]] Remove (word tokenization)\n"
                "   NFD; [:Nonspacing Mark:] Remove; NFC   (removes accents from characters)\n"
                "   [A-Za-z]; Lower(); Latin-Katakana; Katakana-Hiragana (transforms latin and katagana to hiragana)\n"
                "   [[:separator:][:start punctuation:][:initial punctuation:]] Remove \n"
                "\n"
                "see http://userguide.icu-project.org/transforms/general\n"
                "    http://www.unicode.org/reports/tr44/\n"
            );


        fprintf(p_config->outfile, "\n\n");

    }
}
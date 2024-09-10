bool
DictConv::convertDictUsingLexicon(const char *ofile, const char *ifile)
{
    static char buf[4096];
    static char word_buf[2048];
    static TWCHAR wbuf[1024];
    unsigned id;
    unsigned real_id = 99;

    FILE *ifp = fopen(ifile, "r");
    if (!ifp)
        return false;
    FILE *ofp = fopen(ofile, "w");
    if (!ofp) {
        fclose(ifp);
        return false;
    }

    printf("Iterate the lines...\n");
    fflush(stdout);
    while (fgets(buf, sizeof(buf), ifp) != NULL) {
        if (parseLine(buf, word_buf, id)) {
            if (word_buf[0] != L'<' && word_buf[0] != 0) {
                fprintf(ofp, "%s %d ", word_buf, ++real_id);
                MBSTOWCS(wbuf, word_buf, 1024);
                int i = 0, sz = WCSLEN(wbuf);
                bool unknown = false;
                for (; i < sz; i++) {
                    if (i != 0) {
                        fprintf(ofp, "'");
                    }
                    wstring key(&wbuf[i], size_t(1));
                    CLexicon::iterator it = m_Lexicon.find(key);
                    if (it != m_Lexicon.end()) {
                        fprintf(ofp, "%s", m_Lexicon[key].c_str());
                    } else {
                        unknown = true;
                        fprintf(ofp, "XXX");
                    }
                }
                if (unknown)
                    --real_id;
                fprintf(ofp, "\n");
            } else {
                fprintf(ofp, "%s\n", buf);
            }
        }
    }
    fclose(ifp);
    fclose(ofp);

    return true;
}
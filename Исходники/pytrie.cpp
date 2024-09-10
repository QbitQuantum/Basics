void
CPinyinTrie::print(const TNode* pRoot, std::string& prefix, FILE *fp) const
{
    static char buf[1024];
    if (pRoot->m_nWordId > 0) {
        fprintf(fp, "%s", prefix.c_str());
        if (pRoot->m_csLevel)
            fprintf(fp, "(GBK+)");
        unsigned int sz = pRoot->m_nWordId;
        const TWordIdInfo *pwids = pRoot->getWordIdPtr();
        for (unsigned int i = 0; i < sz; ++i) {
            unsigned int id = pwids[i].m_id;
            const TWCHAR *pw = operator[](id);
            int len = WCSLEN(pw);
            if (len != lengthAt(id)) {
                printf(" (lengthAt %d error) ", id);
            }
            WCSTOMBS(buf, pw, 1024);
            fprintf(fp, " %s", buf);
            if (pwids[i].m_bSeen == 0)
                fprintf(fp, "[x]");
            else
                fprintf(fp, "[o]");

            fprintf(fp, "(%d)", pwids[i].m_cost);
        }
        fprintf(fp, "\n");
    }
    unsigned int sz = pRoot->m_nTransfer;
    const TTransUnit* ptrans = pRoot->getTrans();
    for (unsigned int i = 0; i < sz; ++i) {
        unsigned s = ptrans[i].m_Syllable;
        const TNode *pch = transfer(pRoot, s);
        const char *str = CPinyinData::decodeSyllable(s);
        if (!str) break;
        prefix = prefix + str + '\'';
        print(pch, prefix, fp);
        prefix.resize(prefix.size() - strlen(str) - 1);
    }
}
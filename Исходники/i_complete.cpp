static int _LNK_CONV CmpStr(const void *p1, const void *p2) {
#else
static int CmpStr(const void *p1, const void *p2) {
#endif // defined(__IBMCPP__)
    return strcoll(*(const char **)p1, *(const char **)p2);
}

/**
 * Create Sorted list of possible word extensions
 */
ExComplete::ExComplete(EBuffer *B): ExView() {
    Buffer = B;
    Orig = Buffer->CP;
    WordBegin = NULL;
    WordFixed = WordPos = WordsLast = 0;
    Words = new char *[MAXCOMPLETEWORDS + 2];
    if (Words != NULL)
        RefreshComplete();
}

ExComplete::~ExComplete() {
//    fprintf(stderr, "W %p %p %p %d\n", Words, WordContinue, WordBegin, WordsLast);

    if (WordBegin != NULL)
        delete[] WordBegin;

    if (Words != NULL) {
        for (int i = 0; i < WordsLast; i++)
            delete[] Words[i];
        delete[] Words;
    }
}

void ExComplete::Activate(int gotfocus) {
    ExView::Activate(gotfocus);
}
void MESSAGE_DESCS::write(int seqno, MIOFILE& fout, bool translatable) {
    int i, j;
    unsigned int k;
    MESSAGE_DESC* mdp;
    char buf[1024];

    // messages are stored in descreasing seqno,
    // i.e. newer ones are at the head of the vector.
    // compute j = index of first message to return
    //
    j = (int)msgs.size()-1;
    for (k=0; k<msgs.size(); k++) {
        mdp = msgs[k];
        if (mdp->seqno <= seqno) {
            j = k-1;
            break;
        }
    }

    fout.printf("<msgs>\n");
    for (i=j; i>=0; i--) {
        mdp = msgs[i];
        strcpy(buf, mdp->message.c_str());
        if (!translatable) {
            strip_translation(buf);
        }
        fout.printf(
            "<msg>\n"
            " <project>%s</project>\n"
            " <pri>%d</pri>\n"
            " <seqno>%d</seqno>\n"
            " <body>\n%s\n</body>\n"
            " <time>%d</time>\n",
            mdp->project_name,
            mdp->priority,
            mdp->seqno,
            buf,
            mdp->timestamp
        );
        fout.printf("</msg>\n");
    }
    fout.printf("</msgs>\n");
}
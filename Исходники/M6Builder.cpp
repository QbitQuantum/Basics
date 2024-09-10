void M6Processor::ProcessDocument()
{
    try
    {
        unique_ptr<M6Lexicon> tsLexicon(new M6Lexicon);
        vector<M6InputDocument*> docs;

        for (;;)
        {
            string text, filename;
            tie(text, filename) = mDocQueue.Get();

            if (text.empty() or docs.size() == 100)
            {
                // remap tokens
                vector<uint32> remapped(tsLexicon->Count() + 1, 0);

                {
                    M6Lexicon::M6SharedLock sharedLock(mLexicon);

                    for (uint32 t = 1; t < tsLexicon->Count(); ++t)
                    {
                        const char* w;
                        size_t l;
                        tsLexicon->GetString(t, w, l);
                        remapped[t] = mLexicon.Lookup(w, l);
                    }
                }

                {
                    M6Lexicon::M6UniqueLock uniqueLock(mLexicon);

                    for (uint32 t = 1; t < tsLexicon->Count(); ++t)
                    {
                        if (remapped[t] != 0)
                            continue;

                        const char* w;
                        size_t l;
                        tsLexicon->GetString(t, w, l);
                        remapped[t] = mLexicon.Store(w, l);
                    }
                }

                for (M6InputDocument* doc : docs)
                {
                    doc->RemapTokens(&remapped[0]);
                    mDatabank.Store(doc);
                }

                docs.clear();
                tsLexicon.reset(new M6Lexicon);
            }

            if (text.empty())
                break;

            M6InputDocument* doc = new M6InputDocument(mDatabank, text);

            mParser->ParseDocument(doc, filename, mDbHeader);
            if (mWriteFasta)
            {
                string fasta;
                mParser->ToFasta(text, mConfig->get_attribute("id"),
                    doc->GetAttribute("id"), doc->GetAttribute("title"), fasta);
                if (not fasta.empty())
                    doc->SetFasta(fasta);
            }

            doc->Tokenize(*tsLexicon, 0);
            doc->Compress();
            docs.push_back(doc);
        }

        assert(docs.empty());

        mDocQueue.Put(kSentinel);
    }
    catch (exception&)
    {
        Error(current_exception());
    }
}
void BracketedSentenceWidget::updateText()
{
  alpinocorpus::CorpusInfo corpusInfo =
    alpinocorpus::predefinedCorpusOrFallback(d_corpusReader->type());

    if (!d_entry.isEmpty() && d_corpusReader)
    {
        std::vector<alpinocorpus::LexItem> items = d_corpusReader->sentence(
            d_entry.toUtf8().constData(), d_query.toUtf8().constData(),
            corpusInfo.tokenAttribute(), MISSING_ATTRIBUTE, corpusInfo);

        clear();

        // Reset colors.
        setTextColor(Qt::black);
        setTextBackgroundColor(Qt::white);

        bool adoptSpace = false;
        size_t prevDepth = 0;
        for (std::vector<alpinocorpus::LexItem>::const_iterator iter = items.begin();
            iter != items.end(); ++iter)
        {
            size_t depth = iter->matches.size();

            if (depth != prevDepth) {
                if (depth == 0)
                {
                    setTextColor(Qt::black);
                    setTextBackgroundColor(Qt::white);
                }
                else
                {
                    setTextColor(Qt::white);
                    d_highlightColor.setAlpha(std::min(85 + 42 * depth,
                        static_cast<size_t>(255)));
                    setTextBackgroundColor(d_highlightColor);
                }

                prevDepth = depth;
            }

            if (adoptSpace) {
                insertPlainText(" ");
                adoptSpace = false;
            }

            insertPlainText(QString::fromUtf8(iter->word.c_str()));

            std::vector<alpinocorpus::LexItem>::const_iterator next = iter + 1;
            if (next != items.end()) {
                if (next->matches.size() < depth)
                    adoptSpace = true;
                else
                    insertPlainText(" ");
            }
        }
    }
}
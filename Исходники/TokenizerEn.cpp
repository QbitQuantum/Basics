void TokenizerEn::splitLine(const wstring& i_sentence, vector<wstring>& o_content, vector<size_t>& o_positions) const
{
    // find last non-punctuator
    int lastLetter = (int)i_sentence.length()-1;
    for(; lastLetter >= 0; --lastLetter)
    {
        if(!isSpace(i_sentence[lastLetter]) && !isPunct(i_sentence[lastLetter]))
        {
            break;
        }
    }

    o_content.clear();
    o_positions.clear();
    size_t wordBegin = i_sentence.length();
    for(size_t pos = 0; pos <= i_sentence.length(); pos++)
    {
        if(pos == i_sentence.length()
            || isSpace(i_sentence[pos]) )
        {
            if(wordBegin < pos)
            {
                wstring word = i_sentence.substr(wordBegin, pos - wordBegin);
                vector<wstring> newContent;
                vector<size_t> newPos;
                splitSpecialSymbols(word, newContent, newPos, (pos > lastLetter) );
                o_content.insert(o_content.end(), newContent.begin(), newContent.end());
                for(auto pos_iter = newPos.begin(); pos_iter != newPos.end(); ++pos_iter)
                {
                    (*pos_iter)+=wordBegin;
                }
                o_positions.insert(o_positions.end(), newPos.begin(), newPos.end());
                wordBegin = i_sentence.length();
            }
        } else if(wordBegin > pos) {
            wordBegin = pos;
        }
    }
}
word_frequency_t getWeightedFrequency(wstring const &text)
{
    word_frequency_t freq;
    for(int i = 0; i < text.length() - WORD_MAXIMUM; i++) {
        wstring candidate = L"";
        for(int j = WORD_MINIMUM; j <= WORD_MAXIMUM; j++) {
            assert(i + j <= text.length() && "access violation");
            candidate.push_back(text[i + j - 1]);
            auto it = freq.find(candidate);
            if(it != freq.end())
                it->second += 1.0;
            else
                freq[candidate] = 1.0;
        }
    }
    for(auto &it : freq) {
        int len = it.first.length();
        it.second = it.second * len * len - 0.3;
    }
    return freq;
}
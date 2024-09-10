// inspired from <Programming Pearls> -- Handwaving
void reverseWords2(string &s) {
    if (s.length() == 0) return;

    string result = "";
    if (s[s.length()-1] == ' ') {
        int last = s.find_last_not_of(' ') + 1;
        s.erase(last, s.length() - last);
    }

    int first = s.find_first_not_of(' ', 0);
    while (first != string::npos) {
        int wend = s.find(' ', first);  // word end
        if (wend == string::npos) wend = s.length();

        string word = s.substr(first, wend - first);
        reverse(word.begin(), word.end());
        result += word;

        first = s.find_first_not_of(' ', wend); // next word
        if (first == string::npos) break;

        result += ' ';
    }
    reverse(result.begin(), result.end());
    s.swap(result);
}
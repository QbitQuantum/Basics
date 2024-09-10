/**
    Load a dictionary, allowing for subsequent calls to FindWords
    path should lead to a text file with one word per line
    Call FreeDictionary() when finished to free allocated space

    Populates dictionary and alphabet_iter
*/
void LoadDictionary(const char* path)
{
    if (dictionary_loaded)
    {
        cout << "Overwriting existing dictionary" << endl;
        FreeDictionary();
    }

    // Open the file specified by path
    ifstream dict_file(path);
    if (!dict_file.is_open())
    {
        cout << "Failed to access dictionary at path: " << path << endl;
        return;
    }

    // Add all words to our dictionary and sort 
    string temp;
    while (getline(dict_file, temp))
    {
        transform(temp.begin(), temp.end(), temp.begin(), tolower);
        dictionary.push_back(temp);
    }
    sort(dictionary.begin(), dictionary.end());

    // Store iterator for each character for faster searching
    for (char cur_index_char = 'a'; cur_index_char <= 'z' + 1; cur_index_char++)
    {
        temp = cur_index_char;
        alphabet_iter[cur_index_char - 'a'] = lower_bound(dictionary.begin(), dictionary.end(), temp);
    }

    dictionary_loaded = true;
    dict_file.close();
}
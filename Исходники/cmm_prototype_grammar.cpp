// Parse string text to words
// Seperator by punctuation, space
StringArray parse_words(const simple::string& text)
{
    const unsigned char *p = (const unsigned char *) text.c_str();
    StringArray arr(text.length() / 4);
    
    size_t i = 0;
    while (i < text.length())
    {
        // Skip all spaces
        while (p[i] && isspace(p[i]))
            i++;

        if (!p[i])
            // End of parse
            break;

        // Lead by _ or alphabet
        size_t b = i;
        if (isalpha(p[i]) || p[i] == '_')
        {
            while (p[i] && (isalnum(p[i]) || p[i] == '_'))
                i++;
            arr.push_back(simple::string((const char *)p + b, i - b));
            continue;
        }

        // Lead by number, looking number.number
        if (isdigit(p[i]))
        {
            bool has_dot = false;
            while (isdigit(p[i]) || (p[i] == '.' && !has_dot))
            {
                if (p[i] == '.')
                    has_dot = true;
                i++;
            }
            arr.push_back(simple::string((const char *)p + b, i - b));
            continue;
        }

        // Lead by .
        if (p[i] == '.')
        {
            if (p[i + 1] == '.' && p[i + 2] == '.')
            {
                // Got ...
                arr.push_back("...");
                i += 3;
                continue;
            }

            if (p[i + 1] == '.')
            {
                // Got ..
                arr.push_back("..");
                i += 2;
                continue;
            }

            if (isdigit(p[i]))
            {
                // Got .number
                while (isdigit(p[i]))
                    i++;
                arr.push_back(simple::string((const char *)p + b, i - b));
                continue;
            }

            // Got .
            arr.push_back(".");
            i++;
            continue;
        }

        // Got single char
        arr.push_back(simple::string((const char *)p + i, 1));
        i++;
    }
    return arr;
}
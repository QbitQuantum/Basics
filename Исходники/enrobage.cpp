/**
 * Copy or remove license header. Architecture files can contain a header specifying
 * the license. If this header contains an exception tag (for example "FAUST COMPILER EXCEPTION")
 * it is an indication for the compiler to remove the license header from the resulting code. 
 * A header is the first non blank line that begins a comment.
 */
void streamCopyLicense(istream& src, ostream& dst, const string& exceptiontag)
{
    string          s;
    vector<string>	H;

    // skip blank lines
    while (getline(src,s) && isBlank(s)) dst << s << endl;

    // first non blank should start a comment
    if (s.find("/*")==string::npos) { dst << s << endl; return; }

    // copy the header into H
    bool remove = false;
    H.push_back(s);

    while (getline(src,s) && s.find("*/") == string::npos) {
        H.push_back(s);
        if (s.find(exceptiontag) != string::npos) remove=true;
    }

    // copy the header unless explicitely granted to remove it
    if (!remove) {
        // copy the header
        for (unsigned int i=0; i<H.size(); i++) {
            dst << H[i] << endl;
        }
        dst << s << endl;
    }
}
/****************************************************************************
PARAMETERS:
str        - text of #if statement

RETURNS:
true or false depending on how it evaluated

REMARKS:
TODO: rewrite this whole thing using regular expressions when they are done.

SEE ALSO:
wxIfElseVariable
****************************************************************************/
bool ParseIfStatementValue(
    wxString &str)
{
    // Find out if the tag has parenthesis
    // recursive to parse the text within the parenthesis,
    // replacing the text with 1 or 0, (hardcoded true or false)
    int b;
    while ((b = str.Find('(')) != -1) {
        int e;
        // Find the matching parenthesis
        int nextbeg, nextend;
        int parencount = 1, min = b+1;
        do {
            nextbeg = str.find('(', min);
            nextend = str.find(')', min);
            if (nextbeg < nextend && nextbeg != wxString::npos) {
                parencount++;
                min = nextbeg+1;
                }
            else {
                parencount--;
                min = nextend+1;
                }

            if (nextend == wxString::npos) {
#ifdef CHECKED		
                wxMessageBox("wxHTML #if\\else error: Unmatched parenthesis in #if expression.","Error",wxICON_ERROR);
#endif
                return true;
                }
            // once parencount reaches 0 again we have found our matchin )
            } while (parencount > 0);

        e = nextend;

        // Extract the expression from the parenthesis block and recurse
        // to solve it.
        wxString tag;
        tag = str.Mid(b+1, e-b-1);
        bool val = ParseIfStatementValue(tag);
        // Add extra spaces just in case of NOT(VAL)
        if (val) str = str.Mid(0, b) + " 1" + str.Mid(e+1);
        else str = str.Mid(0, b) + " 0" + str.Mid(e+1);
        }

    // Remove spaces from left and right
    str.Trim(false);
    str.Trim(true);

    // Convert text method of operators "AND" and "OR" to c style
    // this makes only one special case necessary for each later on
    str.Replace(" AND ", "&&");
    str.Replace(" OR ", "||");
    str.Replace(" EQUALS ", "==");

    // Check for equals statements
    // == statements are special because they are evaluated as a single block
    int equ;
    equ = str.find("==");
    while (equ != wxString::npos) {
        int begin, end;
        int begin2, end2; // ends of words
        begin = equ-1;
        end = equ+2;

        // remove spaces, find extents
        while (end < str.Length() && str.GetChar(end) == ' ')
            end++;
        while (begin >= 0 && str.GetChar(begin) == ' ')
            begin--;
        end2 = end;
        begin2 = begin;
        if (str.GetChar(end2) == '\'' || str.GetChar(end2) == '\"') {
            end2++;
            while (end2 < str.Length() && str.GetChar(end2) != '\'' && str.GetChar(end2) != '\"' )
                end2++;
            end2++;
            }
        else {
            while (end2 < str.Length() && IsLetter(str.GetChar(end2)))
                end2++;
            }
        while (begin >= 0 && IsLetter(str.GetChar(begin)))
            begin--;

        if (begin < 0) begin = 0;
        else begin++;
        if (end2 >= str.Length()) end2 = str.Length();

        wxString tmpeq = GetEquals(str.Mid(begin, begin2-begin+1), str.Mid(end, end2-end));
        str = str.Mid(0, begin) + wxString(" ") + tmpeq + wxString(" ") +
            str.Mid(end2);
        equ = str.find("==");

        // Remove spaces from left and right
        str.Trim(false);
        str.Trim(true);
        }

    // We use ReverseFind so that the whole left expression gets evaluated agains
    // the right single item, creating a left -> right evaluation
    // Search for || operators, recurse to solve (so we don't have to handle special cases here)
    int and, or;
    and = ReverseFind(str, "&&");
    or = ReverseFind(str, "||");
    if ( (and != -1) || (or != -1) ) {
        wxString tag1, tag2;
        // handle the rightmost first to force left->right evaluation
        if ( (and > or) ) {
            return (
                ParseIfStatementValue(tag2 = str.Mid(and+2)) &&
                ParseIfStatementValue(tag1 = str.Mid(0, and)) );
            }
        else {
            return (
                ParseIfStatementValue(tag2 = str.Mid(or+2)) ||
                ParseIfStatementValue(tag1 = str.Mid(0, or)) );
            }
        }

    // By the time we get to this place in the function we are guarenteed to have a single
    // variable operation, perhaps with a NOT or ! operator
    bool notval = false;

    // search for a NOT or ! operator
    if (str.Mid(0, 1) == "!") {
        str.Remove(0, 1);
        str.Trim(false); // trim spaces from left
        notval = true;
        }
    else if (str.Mid(0,4).CmpNoCase("NOT ") == 0) {
        str.Remove(0, 4);
        str.Trim(false); // trim any extra spaces from left
        notval = true;
        }

    // now all we have left is the name of the class or a hardcoded 0 or 1
    if (str == "") {
#ifdef CHECKED		
        wxMessageBox("wxHTML #if\\else error: Empty expression in #if\\#elif statement.","Error",wxICON_ERROR);
#endif
        return true;
        }

    // check for hardcoded 0 and 1 cases, (these are used by parenthesis catcher)
    // this just decomplicates the recursion algorithm
    if (str == "0") return notval;
    if (str == "1") return !notval;

    // Grab the value from the variable class identified by cname
    bool value = wxIfElseVariable::GetValue(str);
    if (notval) value = !value;
    return value;

}
// ========================================================================
// METHOD ::fromcsv
// ----------------
// Converts a string containing CSV format data to a two-dimensional array
// of values.
// ========================================================================
bool value::fromcsv (const string &csvData, bool withHeaders,
                     const string &key)
{
    value headerNames;
    int rowc, colc;
    bool withKey;
    int keyPos;
    int numColumns, numRows;
    value rowSplit;
    value columnSplit;
    string row;

    if (key.strlen()) withKey = true;
    else withKey = false;
    keyPos = 0;

    clear();

    rowSplit = strutil::splitlines (csvData);
    rowc = 0;
    numRows = rowSplit.count();
    numColumns = 0;

    if (! numRows) return false;

    if (withHeaders)
    {
        row = rowSplit[0].sval();
        columnSplit = strutil::splitcsv (row);
        numColumns = columnSplit.count();
        if (! numColumns) return false;

        for (colc=0; colc<numColumns; ++colc)
        {
            headerNames.newval() = columnSplit[colc].sval();
            if (headerNames[-1].sval() == key)
            {
                keyPos = colc;
            }
        }
        ++rowc;
    }
    for (; rowc<numRows; ++rowc)
    {
        row = rowSplit[rowc].sval();

        if (row.strlen())
        {
            columnSplit = strutil::splitquoted (row, ',');

            if (withKey)
            {
                (*this)[columnSplit[keyPos].sval()].type ("row");
            }
            else
            {
                newval("row");
            }
            for (colc=0; colc<numColumns; ++colc)
            {
                if (withHeaders)
                {
                    (*this)[-1][headerNames[colc].sval()] =
                        columnSplit[colc];
                }
                else
                {
                    (*this)[-1].newval() = columnSplit[colc];
                }
            }
        }
    }
    return true;
}
void RemoteDataSourceServer::doCmdRow(bool raw, MemoryBuffer & in, MemoryBuffer & out)
{
    Owned<IFvDataSource> ds = readDataSource(in);
    if (!ds)
    {
        out.append(false);
        return;
    }

    __int64 requestedRow;
    in.read(requestedRow);

    unsigned startPos = out.length();
    unsigned numRows = 0;
    out.append(true);                       // ok
    out.append(requestedRow);       // start 

    unsigned numRowsPos = out.length();
    out.append(numRows);                // total number of rows;
    loop
    {
        unsigned lengthPos = out.length();
        out.append((unsigned)0);                // size of this row.
        unsigned startRow = out.length();
        if (raw)
        {
            if (!ds->getRawRow(out, requestedRow+numRows))
                break;
        }
        else
        {
            if (!ds->getRow(out, requestedRow+numRows))
                break;
        }
        if ((numRows != 0) && (out.length() > REMOTE_DATA_SIZE))
            break;
        unsigned endRow = out.length();
        out.rewrite(lengthPos);
        out.append(endRow-startRow);
        out.rewrite(endRow);
        numRows++;
    }

    if (numRows == 0)
    {
        out.rewrite(startPos);
        out.append(false);
        return;
    }

    unsigned totalLength = out.length();
    out.rewrite(numRowsPos);
    out.append(numRows);
    out.rewrite(totalLength);
}
bool PagedWorkUnitDataSource::loadBlock(__int64 startRow, offset_t startOffset)
{
    MemoryBuffer temp;
    MemoryBuffer2IDataVal xxx(temp); 
    RowBlock * rows;
    if (returnedMeta->isFixedSize())
    {
        unsigned fixedSize = returnedMeta->fixedSize();
        unsigned readSize = (WU_BLOCK_SIZE / fixedSize) * fixedSize;
        wuResult->getResultRaw(xxx, startOffset, readSize, NULL, NULL);
        if (temp.length() == 0)
            return false;
        rows = new FixedRowBlock(temp, startRow, startOffset, fixedSize);
    }
    else
    {
        wuResult->getResultRaw(xxx, startOffset, WU_BLOCK_SIZE, NULL, NULL);
        if (temp.length() == 0)
            return false;
        rows = new VariableRowBlock(temp, startRow, startOffset, returnedRecordSize, startOffset + temp.length() == totalSize);
    }
    cache.addRowsOwn(rows);
    return true;
}
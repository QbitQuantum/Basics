 void addResult(rowcount_t resultCount, MemoryBuffer &resultData, bool complete)
 {
     Owned<IWorkUnit> wu = &container.queryJob().queryWorkUnit().lock();
     Owned<IWUResult> result = updateWorkUnitResult(wu, resultName, resultSeq);
     if (appendOutput)
         result->addResultRaw(resultData.length(), resultData.toByteArray(), ResultFormatRaw);
     else
         result->setResultRaw(resultData.length(), resultData.toByteArray(), ResultFormatRaw);
     result->setResultRowCount(resultCount);
     result->setResultTotalRowCount(resultCount);
     resultData.clear();
     if (complete)
         result->setResultStatus(ResultStatusCalculated);
     appendOutput = true;
 }
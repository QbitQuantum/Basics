void BestPositionFindTask::run() {
    U2SequenceObject dnaSeq("sequence", sequenceRef);
    QByteArray sequence = dnaSeq.getWholeSequenceData(stateInfo);
    CHECK_OP(stateInfo, );

    if(sequence.isEmpty()) {
        return;
    }
    if(!inputMsa->getAlphabet()->isCaseSensitive()) {
        sequence = sequence.toUpper();
    }
    const int aliLen = inputMsa->getLength();
    const int nSeq = inputMsa->getNumRows();

    int similarity = 0;

    if(referenceRowId >= 0) {
        const MultipleSequenceAlignmentRow row = inputMsa->getMsaRow(referenceRowId);
        int iterationsNum = aliLen - sequence.length() + 1;
        for (int p = 0; p < iterationsNum; p++ ) {
            stateInfo.setProgress(100 * p / iterationsNum);
            char c = row->charAt(p);
            int selLength = 0;
            int patternSimilarity = MSAUtils::getPatternSimilarityIgnoreGaps(row, p, sequence, selLength);
            if (U2Msa::GAP_CHAR != c && patternSimilarity > similarity) {
                similarity = patternSimilarity;
                bestPosition = p;
            }
        }
    } else {
        int processedRows = 0;
        foreach(const MultipleSequenceAlignmentRow &row, inputMsa->getMsaRows()) {
            stateInfo.setProgress(100 * processedRows / nSeq);
            for (int p = 0; p < ( aliLen - sequence.length() + 1 ); p++ ) {
                char c = row->charAt(p);
                int selLength = 0;
                int patternSimilarity = MSAUtils::getPatternSimilarityIgnoreGaps(row, p, sequence, selLength);
                if (U2Msa::GAP_CHAR != c && patternSimilarity > similarity) {
                    similarity = patternSimilarity;
                    bestPosition = p;
                }
            }
            processedRows++;
        }
    }
}
static TDStrResult GetFinalDocumentImportances(
    const TVector<TVector<double>>& rawImportances,
    EDocumentStrengthType docImpMethod,
    int topSize,
    EImportanceValuesSign importanceValuesSign
) {
    const ui32 trainDocCount = rawImportances.size();
    Y_ASSERT(rawImportances.size() != 0);
    const ui32 testDocCount = rawImportances[0].size();
    TVector<TVector<double>> preprocessedImportances;
    if (docImpMethod == EDocumentStrengthType::Average) {
        preprocessedImportances = TVector<TVector<double>>(1, TVector<double>(trainDocCount));
        for (ui32 trainDocId = 0; trainDocId < trainDocCount; ++trainDocId) {
            for (ui32 testDocId = 0; testDocId < testDocCount; ++testDocId) {
                preprocessedImportances[0][trainDocId] += rawImportances[trainDocId][testDocId];
            }
        }
        for (ui32 trainDocId = 0; trainDocId < trainDocCount; ++trainDocId) {
            preprocessedImportances[0][trainDocId] /= testDocCount;
        }

    } else {
        Y_ASSERT(docImpMethod == EDocumentStrengthType::PerObject || docImpMethod == EDocumentStrengthType::Raw);
        preprocessedImportances = TVector<TVector<double>>(testDocCount, TVector<double>(trainDocCount));
        for (ui32 trainDocId = 0; trainDocId < trainDocCount; ++trainDocId) {
            for (ui32 testDocId = 0; testDocId < testDocCount; ++testDocId) {
                preprocessedImportances[testDocId][trainDocId] = rawImportances[trainDocId][testDocId];
            }
        }
    }

    TDStrResult result(preprocessedImportances.size());
    for (ui32 testDocId = 0; testDocId < preprocessedImportances.size(); ++testDocId) {
        TVector<double>& preprocessedImportancesRef = preprocessedImportances[testDocId];

        const ui32 docCount = preprocessedImportancesRef.size();
        TVector<ui32> indices(docCount);
        std::iota(indices.begin(), indices.end(), 0);
        if (docImpMethod != EDocumentStrengthType::Raw) {
            Sort(indices.begin(), indices.end(), [&](ui32 first, ui32 second) {
                return Abs(preprocessedImportancesRef[first]) > Abs(preprocessedImportancesRef[second]);
            });
        }

        std::function<bool(double)> predicate;
        if (importanceValuesSign == EImportanceValuesSign::Positive) {
            predicate = [](double v){return v > 0;};
        } else if (importanceValuesSign == EImportanceValuesSign::Negative) {
            predicate = [](double v){return v < 0;};
        } else {
            Y_ASSERT(importanceValuesSign == EImportanceValuesSign::All);
            predicate = [](double){return true;};
        }

        int currentSize = 0;
        for (ui32 i = 0; i < docCount; ++i) {
            if (currentSize == topSize) {
                break;
            }
            if (predicate(preprocessedImportancesRef[indices[i]])) {
                result.Scores[testDocId].push_back(preprocessedImportancesRef[indices[i]]);
                result.Indices[testDocId].push_back(indices[i]);
            }
            ++currentSize;
        }
    }
    return result;
}
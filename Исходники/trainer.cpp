    void Trainer::Save(const std::wstring& modelFilePath, const std::vector<DictionaryValue>& learnerState, const Dictionary& externalState, const Dictionary& distributedState)
    {
        std::wstring tempModelFile = modelFilePath + L".tmp";
        Dictionary state;
        state[versionPropertyName] = trainerCheckpointVersion;
        state[learnersPropertyName] = learnerState;
        state[externalStatePropertyName] = externalState;
        state[distributedStatePropertyName] = distributedState;

        m_combinedTrainingFunction->Save(tempModelFile);
        std::wstring trainerStateCheckpointFilePath = GetTrainerStateCheckpointFilePath(modelFilePath);
        std::wstring tempCheckpointFile = trainerStateCheckpointFilePath + L".tmp";

        state.Save(tempCheckpointFile);

        // The return value is ignored here.
        _wunlink(modelFilePath.c_str());
        _wunlink(trainerStateCheckpointFilePath.c_str());

        renameOrDie(tempModelFile, modelFilePath);
        renameOrDie(tempCheckpointFile, trainerStateCheckpointFilePath);
    }
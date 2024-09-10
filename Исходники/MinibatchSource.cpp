    /*virtual*/ const std::unordered_map<StreamInformation, MinibatchData>&
    CompositeMinibatchSource::GetNextMinibatch(size_t minibatchSizeInSequences,
                                               size_t minibatchSizeInSamples,
                                               size_t numberOfWorkers,
                                               size_t workerRank,
                                               const DeviceDescriptor& device /*= DeviceDescriptor::UseDefaultDevice()*/) /*override*/
    {
        auto profGetMinibatch = Microsoft::MSR::CNTK::ScopeProfile(Microsoft::MSR::CNTK::profilerEvtMainGetMinibatch);

        m_minibatchData.clear();

        if (!m_epochEndReached)
        {
            if (minibatchSizeInSequences != 0)
                LogicError("GetNextMinibatch: Specifying minibatch size in #sequences is currently unsupported");

            if (minibatchSizeInSamples == 0)
                InvalidArgument("GetNextMinibatch: Requested minibatch size must be > 0.");

            if (m_prevMinibatchSize == 0)
            {
                EpochConfiguration epochConfig;
                epochConfig.m_numberOfWorkers = numberOfWorkers;
                epochConfig.m_workerRank = workerRank;
                epochConfig.m_minibatchSizeInSamples = minibatchSizeInSamples;
                epochConfig.m_truncationSize = m_truncationLength;
                epochConfig.m_allowMinibatchesToCrossSweepBoundaries = true;

                if (m_maxNumSamplesToRead == MinibatchSource::FullDataSweep)
                {
                    epochConfig.m_totalEpochSizeInSamples = Microsoft::MSR::CNTK::requestDataSize;
                }
                else if (m_maxNumSamplesToRead == MinibatchSource::InfinitelyRepeat)
                {
                    // Setting big value, but not the max in order to avoid bit overflow.
                    epochConfig.m_totalEpochSizeInSamples = std::numeric_limits<size_t>::max() / 2;
                }
                else 
                {
                    epochConfig.m_totalEpochSizeInSamples = m_maxNumSamplesToRead;
                }

                epochConfig.m_totalEpochSizeInSweeps = m_maxNumSweepsToRead;

                epochConfig.m_epochIndex = 0;

                m_matrices.clear();

                std::unordered_set<InputStreamDescription> inputs;
                for (const auto& s : m_streamInfos)
                {
                    auto inputStreamDescription = GetInputStreamDescription(s, device);
                    inputs.insert(inputStreamDescription);

                    if (s.m_elementType == DataType::Float)
                    {
                        auto iter = std::find_if(m_compositeDataReaderStreamDescs.begin(), m_compositeDataReaderStreamDescs.end(), [s](StreamDescriptionPtr& streamInfo) {
                            return streamInfo->m_id == s.m_id;
                        });
                        assert(iter != m_compositeDataReaderStreamDescs.end());

                        m_matrices.AddInput(
                            s.m_name,
                            std::make_shared<Matrix<float>>(0, 0, inputStreamDescription.GetDeviceId(), inputStreamDescription.GetMatrixType(), inputStreamDescription.GetMatrixFormat()),
                            std::make_shared<MBLayout>(),
                            *(*iter)->m_sampleLayout);
                    }
                    else
                        LogicError("GetNextMinibatch: Input of type other than DataType::Float is currently unsupported by the CNTK built-in composite MinibatchSource!");
                }

                m_shim->StartEpoch(epochConfig, inputs);

                m_prevMinibatchSize = minibatchSizeInSamples;
                m_workerRank = workerRank;
                m_numWorkers = numberOfWorkers;
            }

            if (minibatchSizeInSamples != m_prevMinibatchSize || m_workerRank != workerRank || m_numWorkers != numberOfWorkers || m_restorePosition != 0)
            {
                std::map<std::wstring, int> inputDescriptions;
                for (const auto& s : m_streamInfos)
                    inputDescriptions[s.m_name] = AsCNTKImplDeviceId(device);

                ReaderConfiguration newConfig;
                newConfig.m_numberOfWorkers = numberOfWorkers;
                newConfig.m_workerRank = workerRank;
                newConfig.m_minibatchSizeInSamples = minibatchSizeInSamples;
                newConfig.m_truncationSize = m_truncationLength;
                newConfig.m_allowMinibatchesToCrossSweepBoundaries = true;

                if (m_restorePosition != 0)
                {
                    m_shim->SetCurrentSamplePosition(m_restorePosition);
                    m_restorePosition = 0;
                }

                m_shim->SetConfiguration(newConfig, inputDescriptions);

                m_prevMinibatchSize = minibatchSizeInSamples;
                m_workerRank = workerRank;
                m_numWorkers = numberOfWorkers;
            }

            auto hasData = m_shim->GetMinibatch(m_matrices);
            m_epochEndReached = m_shim->IsEndOfEpoch();

            if (m_epochEndReached && !hasData)
                return m_minibatchData;

            bool hasReachedSweepEnd = m_shim->IsEndOfSweep();

            for (const auto& s: m_streamInfos)
            {
                auto input = m_matrices.GetInput(s.m_name);
                auto& currentStreamInfo = s;

                ValuePtr minibatchValuePtr;
                if (!hasData)
                {
                    m_minibatchData[currentStreamInfo] = { nullptr, 0, 0 };
                    continue;
                }

                if (s.m_elementType == DataType::Float)
                {
                    auto matrix = dynamic_pointer_cast<Matrix<float>>(input.matrix);
                    if (!matrix)
                        LogicError("GetNextMinibatch: Invalid matrix type.");

                    minibatchValuePtr = MakeSharedObject<PackedValue>(s.m_sampleLayout, Axis::DefaultInputVariableDynamicAxes(), matrix, input.pMBLayout, /*readOnly =*/ false);

                    size_t numSamples = input.pMBLayout->GetActualNumSamples();
                    size_t numSequences = input.pMBLayout->GetNumSequences();

                    m_minibatchData[currentStreamInfo] = { minibatchValuePtr, numSequences, numSamples, hasReachedSweepEnd };
                }
                else
                    LogicError("GetNextMinibatch: Input of type other than DataType::Float is currently unsupported by the CNTK built-in composite MinibatchSource!");
            }
        }

        return m_minibatchData;
    }
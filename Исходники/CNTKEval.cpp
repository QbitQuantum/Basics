void CNTKEvalExtended<ElemType>::ForwardPassT(const std::vector<ValueBuffer<ElemType, ValueContainer> >& inputs, std::vector<ValueBuffer<ElemType, ValueContainer> >& outputs, bool resetRNN)
{
    if (!m_started)
        RuntimeError("ForwardPass() called before StartForwardEvaluation()");

    if (inputs.size() != (size_t)std::distance(m_inputMatrices.begin(), m_inputMatrices.end()))
        RuntimeError("Expected %d inputs, but got %d.", (int)std::distance(m_inputMatrices.begin(), m_inputMatrices.end()), (int)inputs.size());

    if (outputs.size() != m_outputNodes.size())
        RuntimeError("Expected %d outputs, but got %d.", (int)m_outputNodes.size(), (int)outputs.size());

    size_t i = 0;
    for (auto& inputNode : m_inputNodes)
    {
        // const cast: The matrix class takes this over without copying and could theoretically change the contents,
        // though it doesn't in this case.
        auto& buffer = const_cast<ValueBuffer<ElemType, ValueContainer>&>(inputs[i]);
        auto matrix = dynamic_pointer_cast<Matrix<ElemType>>(inputNode->ValuePtr());
        auto type = matrix->GetMatrixType();
        size_t numRows = inputNode->GetSampleLayout().GetNumElements();

        if (buffer.m_buffer.data() == nullptr)
            RuntimeError("Input %ls: Buffer is not allocated.", m_inputNodes[i]->GetName().c_str());
        if (type == MatrixType::DENSE)
        {
            if (buffer.m_buffer.size() % numRows != 0)
                RuntimeError("Input %ls: Expected input data to be a multiple of %" PRIu64 ", but it is %" PRIu64 ".", 
                             m_inputNodes[i]->GetName().c_str(), numRows, buffer.m_buffer.size());
            if (buffer.m_buffer.size() == 0)
                RuntimeError("Input %ls: Expected at least one element.", m_inputNodes[i]->GetName().c_str());
        }
        else if (type == MatrixType::SPARSE)
        {
            if (buffer.m_colIndices.data() == nullptr)
                RuntimeError("Input %ls: Due to sparse input format, expected colIndices array, but was nullptr.", m_inputNodes[i]->GetName().c_str());
            if (buffer.m_indices.data() == nullptr)
                RuntimeError("Input %ls: Due to sparse input format, expected Indices array, but was nullptr.", m_inputNodes[i]->GetName().c_str());
            if (buffer.m_colIndices.size() < 2)
                RuntimeError("Input %ls: Expected at least one element (2 entries in colIndices array).", m_inputNodes[i]->GetName().c_str());
            if (buffer.m_colIndices[0] != 0)
                RuntimeError("Input %ls: First element of column indices must be 0", m_inputNodes[i]->GetName().c_str());
            if (buffer.m_colIndices[buffer.m_colIndices.size() - 1] != buffer.m_indices.size())
                RuntimeError("Input %ls: Last element of column indices must be equal to the size of indices (%ld), but was %d", 
                             m_inputNodes[i]->GetName().c_str(), buffer.m_indices.size(), 
                             buffer.m_colIndices[buffer.m_colIndices.size() - 1]);
        }

        int numCols = type == MatrixType::DENSE ? buffer.m_buffer.size() / numRows : buffer.m_colIndices.size() - 1;
        if (numCols < 1)
            RuntimeError("Input: the number of column must be greater than or equal to 1.");
        inputNode->GetMBLayout()->Init(1, numCols);
        
        // SentinelValueIndicatingUnspecifedSequenceBeginIdx is used to specify the lower bound of look-back step of recurrent nodes
        inputNode->GetMBLayout()->AddSequence(0, 0, resetRNN ? 0 : SentinelValueIndicatingUnspecifedSequenceBeginIdx, numCols);

        if (type == MatrixType::DENSE)
            matrix->SetValue(numRows, numCols, matrix->GetDeviceId(), buffer.m_buffer.data(), matrixFlagNormal);
        else if (type == MatrixType::SPARSE)
        {
            // In the sparse case the m_data layout is identical to CUDA's CSC layout
            // (see http://docs.nvidia.com/cuda/cusparse/#compressed-sparse-column-format-csc).
            matrix->SetMatrixFromCSCFormat(buffer.m_colIndices.data(), buffer.m_indices.data(), buffer.m_buffer.data(),
                                           buffer.m_buffer.size(), numRows, numCols);
        }

        ++i;
    }

    ComputationNetwork::BumpEvalTimeStamp(m_inputNodes);
    this->m_net->ForwardProp(m_outputNodes);

    for (size_t i2 = 0; i2 < m_outputNodes.size(); ++i2)
    {
        auto node = m_outputNodes[i2];
        
        shared_ptr<Matrix<ElemType>> outputMatrix = dynamic_pointer_cast<Matrix<ElemType>>(node->ValuePtr());
        auto pMBLayout = node->GetMBLayout();
        if (!pMBLayout)
        {
            pMBLayout = make_shared<MBLayout>();
            pMBLayout->InitAsFrameMode(1); // treat this as if we have one single sample
        }

        const auto& seq = pMBLayout->GetAllSequences();
        if (seq.size() != 1)
            RuntimeError("Only 1 output sequence supported by this API");

        ValueContainer<ElemType>& vec = outputs[i2].m_buffer;

        size_t numElements = outputMatrix->GetNumElements();

        if (vec.capacity() < numElements)
        {
            // Bad luck - we can't reallocate memory of an external object at this point.
            RuntimeError("Not enough space in output buffer for output '%ls'.", node->GetName().c_str());
        }

        vec.resize(numElements);
        ElemType* data = const_cast<ElemType*>(vec.data());
        outputMatrix->CopyToArray(data, numElements);
    }
}
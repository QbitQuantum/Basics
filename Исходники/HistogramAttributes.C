void
HistogramAttributes::SetOutputType(HistogramAttributes::OutputType outputType_)
{
    outputType = outputType_;
    Select(ID_outputType, (void *)&outputType);
}
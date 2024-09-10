//==============================================================================
void AnalysisModel::removeAnalysis(ValueTree analysisTree)
{
    ValueTree mainTree = analysisTree.getParent();
    
    mainTree.removeChild(analysisTree, nullptr);
}
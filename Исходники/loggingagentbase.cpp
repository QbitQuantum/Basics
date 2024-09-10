void CLogContentFilter::filterAndAddLogContentBranch(StringArray& branchNamesInFilter, unsigned idx,
    StringArray& branchNamesInLogContent, IPropertyTree* originalLogContentBranch, IPropertyTree* updateLogRequestTree, bool& logContentEmpty)
{
    Owned<IPropertyTreeIterator> contentItr = originalLogContentBranch->getElements(branchNamesInFilter.item(idx));
    ForEach(*contentItr)
    {
        IPropertyTree& contentToLogBranch = contentItr->query();
        if (idx == branchNamesInFilter.length() - 1)
        {
            addLogContentBranch(branchNamesInLogContent, &contentToLogBranch, updateLogRequestTree);
            logContentEmpty = false;
        }
        else
        {
            branchNamesInLogContent.append(contentToLogBranch.queryName());
            filterAndAddLogContentBranch(branchNamesInFilter, idx+1, branchNamesInLogContent, &contentToLogBranch,
                updateLogRequestTree, logContentEmpty);
            branchNamesInLogContent.remove(branchNamesInLogContent.length() - 1);
        }
    }
}
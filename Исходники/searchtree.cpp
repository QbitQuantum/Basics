inline unsigned int SearchTreeNode::GetDeepestMatchingPosition(BasicSearchTree* tree, const wxString& s,unsigned int StringStartDepth)
{
    if (StringStartDepth >= GetDepth())
        return GetDepth();

    if (StringStartDepth + s.length() <= GetLabelStartDepth())
        return StringStartDepth + s.length();
    // StringStartDepth + s.length() = string's depth. It must be greater
    //   than the label's start depth, otherwise there's an error.
    // Example: If StringStartDepth = 0, s.length() = 1, then string's depth = 1.
    // If the parent node's depth = 1, it means the comparison should belong
    // to the parent node's edge (the first character in the  tree), not this one.

    unsigned int startpos = GetLabelStartDepth() - StringStartDepth;
    // startpos determines the starting position of the string, to compare with
    // the label.
    // if StringStartDepth = 0, and the Label's Start Depth = 0
    // (it means we're comparing an edge that goes from the root node to
    // the currentnode). So we should start comparison at string's position 0-0 = 0.


    // Now let's compare the strings and find the first difference.
    const wxString& the_label = GetActualLabel(tree);
    size_t i,i_limit;
    i_limit = s.length() - startpos;
    if (i_limit > m_LabelLen)
        i_limit = m_LabelLen;

    for (i = 0; i < i_limit; i++)
    {
        if (the_label[m_LabelStart+i]!=s[startpos+i])
            break;
    }

    return GetLabelStartDepth() + i;
}
CBaseNode *CMayaNode::GetChild(int childId)
{
    MStatus status;
    MFnDagNode dagNode (m_dagPath, &status);
    if (status != MS::kSuccess)
        return 0;

    MObject objChild = dagNode.child (childId, &status);
    if (status != MS::kSuccess)
        return 0;

    MFnDagNode	childDagNode (objChild, &status);
    if (status != MS::kSuccess)
        return 0;

    MDagPath childPath;
    if (childDagNode.getPath (childPath) != MS::kSuccess)
        return 0;

    CMayaNode *pNode = new CMayaNode;
    if (!pNode->Create (childPath))
    {
        delete pNode;
        return 0;
    }

    return pNode;
}
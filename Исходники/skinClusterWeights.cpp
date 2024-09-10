bool skinClusterWeights::isSkinClusterIncluded(MObject &node)
{
    MStatus   status;
    unsigned int i;

    if (skinClusterArray.length() == 0) return true;

    for (i = 0; i < skinClusterArray.length(); i++) {
 	if (skinClusterArray[i] == node) return true;
    }

    return false;
}
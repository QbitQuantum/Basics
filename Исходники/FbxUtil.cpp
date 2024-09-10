void decompose(FbxNode* fbxNode, float time, Vector3* scale, Quaternion* rotation, Vector3* translation)
{
    FbxAMatrix fbxMatrix;
    Matrix matrix;
    FbxTime kTime;
    kTime.SetMilliSeconds((FbxLongLong)time);
    fbxMatrix = fbxNode->EvaluateLocalTransform(kTime);
    copyMatrix(fbxMatrix, matrix);
    matrix.decompose(scale, rotation, translation);
}
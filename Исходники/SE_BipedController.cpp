SE_Vector3f SE_BipedController::convert(int vertexIndex,int frameindex,const char * objname, const SE_Vector3f& v)
{
    SE_Vector4f input;
    input.set(v,1);
    SE_Vector4f result(0,0,0,0);

    SE_SkeletonUnit *su = findSU(objname);

    //bipedIndex.size is number that how many bips effact this vertext.
    int bipNumPerVertex = su->objVertexBlendInfo[vertexIndex]->bipedIndex.size();  

    //how many bips will take effact to one vertex
    for(int i = 0; i < bipNumPerVertex; ++i)
    {
        int bipIndex = su->objVertexBlendInfo[vertexIndex]->bipedIndex[i];//bipIndex is start from 1, not 0.

        int bipindexfromcache = su->bipCache[bipIndex-1]->bipIndexOnBipAnimation;

        SE_Biped *bip = oneBipAnimation[bipindexfromcache];// find bip from all bips

        if(bip->animationInfo.size() == 0)
        {
            continue;
        }

#ifdef _FORDEBUG
        SE_Matrix4f bindpos = bip->bind_pose;
        SE_Matrix4f inversOfbp = bindpos.inverse();

        SE_Quat worldR = bip->animationInfo[frameindex]->rotateQ;
        SE_Vector3f worldT = bip->animationInfo[frameindex]->translate;
        SE_Vector3f worldS = bip->animationInfo[frameindex]->scale;

        SE_Matrix4f transform;
        transform.identity();
        //not use scale
        transform.set(worldR.toMatrix3f(),SE_Vector3f(1,1,1),worldT);//myTransform relate parent        

        SE_Matrix4f parentBoneToWorld;
        parentBoneToWorld.identity();

        if(bip->parent)
        {
            parentBoneToWorld = *(bip->parent->boneToWorldPerFrame[frameindex]);
        }
        else
        {
            //this bip is ROOT,the transform is world relative;
        }        

        SE_Matrix4f m = parentBoneToWorld.mul(transform).mul(inversOfbp);

        SE_Matrix4f m = mAfterTransformMatrixToWorld[bipindexfromcache].mul(mBindposeMatrixInverse[bipindexfromcache]);
#else
        SE_Matrix4f m = AllFrameFinalTransformMatrix[frameindex][bipindexfromcache];
#endif

        result = result + m.map(input) * su->objVertexBlendInfo[vertexIndex]->weight[i];
    }
    return result.xyz();
}
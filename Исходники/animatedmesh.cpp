void copyAiAnimation(const aiScene *scene, const aiMesh *sourceMesh, const unsigned int &animationIndex,
    std::map<std::string, unsigned int> &boneNameToIndex,
    std::map<std::string, const aiNode *> &nodeNameToPointer,
    std::map<std::string, aiMatrix4x4> &nodeNameToMatrix,
    Skeleton &skeleton)
{
    const aiAnimation *sourceAnimation = scene->mAnimations[animationIndex];
    const std::string animationName = std::string(sourceAnimation->mName.data);
    skeleton.animations.insert(std::pair<std::string, Animation>(animationName, Animation()));
    Animation *animation = &skeleton.animations[animationName];
    const size_t nrFrames = getAiNrAnimationFrames(sourceAnimation);
    
    animation->name = animationName;
    animation->frames.assign(nrFrames*skeleton.bones.size(), KeyFrame());
    
    if (sourceAnimation->mNumChannels != skeleton.bones.size())
    {
        std::cerr << "Warning: animation '" << animation->name << "' has an invalid number of channels (" << sourceAnimation->mNumChannels << " for " << skeleton.bones.size() << " bones)!" << std::endl;
    }
    
    //Store inverse of global transformation.
    aiMatrix4x4 inverseGlobalTransformation = scene->mRootNode->mTransformation;
    
    inverseGlobalTransformation.Inverse();
    
    //Process all frames.
    KeyFrame *frames = &animation->frames[0];
    
    for (size_t frame = 0; frame < nrFrames; ++frame)
    {
        //For this frame, first reset all transformations to their originals.
        for (std::map<std::string, aiMatrix4x4>::iterator i = nodeNameToMatrix.begin(); i != nodeNameToMatrix.end(); ++i)
        {
            assert(nodeNameToPointer[i->first]);
            i->second = nodeNameToPointer[i->first]->mTransformation;
        }
        
        //Then, retrieve all transformations that are stored in the animation data for the corresponding nodes.
        for (size_t i = 0; i < sourceAnimation->mNumChannels; ++i)
        {
            const aiNodeAnim *nodeAnim = sourceAnimation->mChannels[i];
            
            //Get data for this frame.
            aiVector3D scale(1.0f, 1.0f, 1.0f);
            aiQuaternion rotate(1.0f, 0.0f, 0.0f, 0.0f);
            aiVector3D translate(0.0f, 0.0f, 0.0f);
            
            if (frame < nodeAnim->mNumScalingKeys) scale = nodeAnim->mScalingKeys[frame].mValue;
            else if (nodeAnim->mNumScalingKeys > 0) scale = nodeAnim->mScalingKeys[nodeAnim->mNumScalingKeys - 1].mValue;
            if (frame < nodeAnim->mNumRotationKeys) rotate = nodeAnim->mRotationKeys[frame].mValue;
            else if (nodeAnim->mNumRotationKeys > 0) rotate = nodeAnim->mRotationKeys[nodeAnim->mNumRotationKeys - 1].mValue;
            if (frame < nodeAnim->mNumPositionKeys) translate = nodeAnim->mPositionKeys[frame].mValue;
            else if (nodeAnim->mNumPositionKeys > 0) translate = nodeAnim->mPositionKeys[nodeAnim->mNumPositionKeys - 1].mValue;
            
            //Create transformation matrix.
            if (nodeNameToMatrix.find(nodeAnim->mNodeName.data) == nodeNameToMatrix.end())
            {
                std::cerr << "Warning: animation data for node '" << nodeAnim->mNodeName.data << "' is not available!" << std::endl;
                throw std::exception();
            }
            
            aiMatrix4x4 scaleMatrix;
            aiMatrix4x4 rotationMatrix = aiMatrix4x4(rotate.GetMatrix());
            aiMatrix4x4 translationMatrix;
            
            aiMatrix4x4::Scaling(scale, scaleMatrix);
            aiMatrix4x4::Translation(translate, translationMatrix);
            
            nodeNameToMatrix[nodeAnim->mNodeName.data] = translationMatrix*rotationMatrix*scaleMatrix;
        }
        
        //Recursively update these transformations.
        updateAiNodeMatrices(scene->mRootNode, aiMatrix4x4(), nodeNameToMatrix);

        //Assign the updated transformations to the corresponding bones.
        for (std::map<std::string, aiMatrix4x4>::const_iterator i = nodeNameToMatrix.begin(); i != nodeNameToMatrix.end(); ++i)
        {
            std::map<std::string, unsigned int>::const_iterator boneIterator = boneNameToIndex.find(i->first);
            
            if (boneIterator != boneNameToIndex.end())
            {
                const unsigned int boneIndex = boneIterator->second;
                //const aiMatrix4x4 finalTransformation = inverseGlobalTransformation*i->second*sourceMesh->mBones[boneIndex]->mOffsetMatrix;
                const aiMatrix4x4 finalTransformation = i->second*sourceMesh->mBones[boneIndex]->mOffsetMatrix;
                
                aiVector3D scale(1.0f, 1.0f, 1.0f);
                aiQuaternion rotate(1.0f, 0.0f, 0.0f, 0.0f);
                aiVector3D translate(0.0f, 0.0f, 0.0f);
                
                finalTransformation.Decompose(scale, rotate, translate);
                
                frames[boneIndex] = KeyFrame(vec3(scale.x, scale.y, scale.z),
                                             frame,
                                             quatconj(vec4(rotate.x, rotate.y, rotate.z, rotate.w)),
                                             vec4(translate.x, translate.y, translate.z, 0.0f));
            }
        }
        
        //Advance to next frame.
        frames += skeleton.bones.size();
    }
    
#ifndef NDEBUG
    std::cerr << "Added animation '" << animation->name << "' with " << nrFrames << " frames, resulting in " << animation->frames.size() << " keyframes." << std::endl;
#endif
}
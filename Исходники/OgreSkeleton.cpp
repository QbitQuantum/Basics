    void Skeleton::_mergeSkeletonAnimations(const Skeleton* src,
        const BoneHandleMap& boneHandleMap,
        const StringVector& animations)
    {
        ushort handle;

        ushort numSrcBones = src->getNumBones();
        ushort numDstBones = this->getNumBones();

        if (boneHandleMap.size() != numSrcBones)
        {
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "Number of bones in the bone handle map must equal to "
                "number of bones in the source skeleton.",
                "Skeleton::_mergeSkeletonAnimations");
        }

        bool existsMissingBone = false;

        // Check source skeleton structures compatible with ourself (that means
        // identically bones with identical handles, and with same hierarchy, but
        // not necessary to have same number of bones and bone names).
        for (handle = 0; handle < numSrcBones; ++handle)
        {
            const Bone* srcBone = src->getBone(handle);
            ushort dstHandle = boneHandleMap[handle];

            // Does it exists in target skeleton?
            if (dstHandle < numDstBones)
            {
                Bone* destBone = this->getBone(dstHandle);

                // Check both bones have identical parent, or both are root bone.
                const Bone* srcParent = static_cast<Bone*>(srcBone->getParent());
                Bone* destParent = static_cast<Bone*>(destBone->getParent());
                if ((srcParent || destParent) &&
                    (!srcParent || !destParent ||
                     boneHandleMap[srcParent->getHandle()] != destParent->getHandle()))
                {
                    OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                        "Source skeleton incompatible with this skeleton: "
                        "difference hierarchy between bone '" + srcBone->getName() +
                        "' and '" + destBone->getName() + "'.",
                        "Skeleton::_mergeSkeletonAnimations");
                }
            }
            else
            {
                existsMissingBone = true;
            }
        }

        // Clone bones if need
        if (existsMissingBone)
        {
            // Create missing bones
            for (handle = 0; handle < numSrcBones; ++handle)
            {
                const Bone* srcBone = src->getBone(handle);
                ushort dstHandle = boneHandleMap[handle];

                // The bone is missing in target skeleton?
                if (dstHandle >= numDstBones)
                {
                    Bone* dstBone = this->createBone(srcBone->getName(), dstHandle);
                    // Sets initial transform
                    dstBone->setPosition(srcBone->getInitialPosition());
                    dstBone->setOrientation(srcBone->getInitialOrientation());
                    dstBone->setScale(srcBone->getInitialScale());
                    dstBone->setInitialState();
                }
            }

            // Link new bones to parent
            for (handle = 0; handle < numSrcBones; ++handle)
            {
                const Bone* srcBone = src->getBone(handle);
                ushort dstHandle = boneHandleMap[handle];

                // Is new bone?
                if (dstHandle >= numDstBones)
                {
                    const Bone* srcParent = static_cast<Bone*>(srcBone->getParent());
                    if (srcParent)
                    {
                        Bone* destParent = this->getBone(boneHandleMap[srcParent->getHandle()]);
                        Bone* dstBone = this->getBone(dstHandle);
                        destParent->addChild(dstBone);
                    }
                }
            }

            // Derive root bones in case it was changed
            this->deriveRootBone();

            // Reset binding pose for new bones
            this->reset(true);
            this->setBindingPose();
        }

        //
        // We need to adapt animations from source to target skeleton, but since source
        // and target skeleton bones bind transform might difference, so we need to alter
        // keyframes in source to suit to target skeleton.
        //
        // For any given animation time, formula:
        //
        //      LocalTransform = BindTransform * KeyFrame;
        //      DerivedTransform = ParentDerivedTransform * LocalTransform
        //
        // And all derived transforms should be keep identically after adapt to
        // target skeleton, Then:
        //
        //      DestDerivedTransform == SrcDerivedTransform
        //      DestParentDerivedTransform == SrcParentDerivedTransform
        // ==>
        //      DestLocalTransform = SrcLocalTransform
        // ==>
        //      DestBindTransform * DestKeyFrame = SrcBindTransform * SrcKeyFrame
        // ==>
        //      DestKeyFrame = inverse(DestBindTransform) * SrcBindTransform * SrcKeyFrame
        //
        // We define (inverse(DestBindTransform) * SrcBindTransform) as 'delta-transform' here.
        //

        // Calculate delta-transforms for all source bones.
        vector<DeltaTransform>::type deltaTransforms(numSrcBones);
        for (handle = 0; handle < numSrcBones; ++handle)
        {
            const Bone* srcBone = src->getBone(handle);
            DeltaTransform& deltaTransform = deltaTransforms[handle];
            ushort dstHandle = boneHandleMap[handle];

            if (dstHandle < numDstBones)
            {
                // Common bone, calculate delta-transform

                Bone* dstBone = this->getBone(dstHandle);

                deltaTransform.translate = srcBone->getInitialPosition() - dstBone->getInitialPosition();
                deltaTransform.rotate = dstBone->getInitialOrientation().Inverse() * srcBone->getInitialOrientation();
                deltaTransform.scale = srcBone->getInitialScale() / dstBone->getInitialScale();

                // Check whether or not delta-transform is identity
                const Real tolerance = 1e-3f;
                Vector3 axis;
                Radian angle;
                deltaTransform.rotate.ToAngleAxis(angle, axis);
                deltaTransform.isIdentity =
                    deltaTransform.translate.positionEquals(Vector3::ZERO, tolerance) &&
                    deltaTransform.scale.positionEquals(Vector3::UNIT_SCALE, tolerance) &&
                    Math::RealEqual(angle.valueRadians(), 0.0f, tolerance);
            }
            else
            {
                // New bone, the delta-transform is identity

                deltaTransform.translate = Vector3::ZERO;
                deltaTransform.rotate = Quaternion::IDENTITY;
                deltaTransform.scale = Vector3::UNIT_SCALE;
                deltaTransform.isIdentity = true;
            }
        }

        // Now copy animations

        ushort numAnimations;
        if (animations.empty())
            numAnimations = src->getNumAnimations();
        else
            numAnimations = static_cast<ushort>(animations.size());
        for (ushort i = 0; i < numAnimations; ++i)
        {
            const Animation* srcAnimation;
            if (animations.empty())
            {
                // Get animation of source skeleton by the given index
                srcAnimation = src->getAnimation(i);
            }
            else
            {
                // Get animation of source skeleton by the given name
                const LinkedSkeletonAnimationSource* linker;
                srcAnimation = src->_getAnimationImpl(animations[i], &linker);
                if (!srcAnimation || linker)
                {
                    OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND,
                        "No animation entry found named " + animations[i],
                        "Skeleton::_mergeSkeletonAnimations");
                }
            }

            // Create target animation
            Animation* dstAnimation = this->createAnimation(srcAnimation->getName(), srcAnimation->getLength());

            // Copy interpolation modes
            dstAnimation->setInterpolationMode(srcAnimation->getInterpolationMode());
            dstAnimation->setRotationInterpolationMode(srcAnimation->getRotationInterpolationMode());

            // Copy track for each bone
            for (handle = 0; handle < numSrcBones; ++handle)
            {
                const DeltaTransform& deltaTransform = deltaTransforms[handle];
                ushort dstHandle = boneHandleMap[handle];

                if (srcAnimation->hasNodeTrack(handle))
                {
                    // Clone track from source animation

                    const NodeAnimationTrack* srcTrack = srcAnimation->getNodeTrack(handle);
                    NodeAnimationTrack* dstTrack = dstAnimation->createNodeTrack(dstHandle, this->getBone(dstHandle));
                    dstTrack->setUseShortestRotationPath(srcTrack->getUseShortestRotationPath());

                    ushort numKeyFrames = srcTrack->getNumKeyFrames();
                    for (ushort k = 0; k < numKeyFrames; ++k)
                    {
                        const TransformKeyFrame* srcKeyFrame = srcTrack->getNodeKeyFrame(k);
                        TransformKeyFrame* dstKeyFrame = dstTrack->createNodeKeyFrame(srcKeyFrame->getTime());

                        // Adjust keyframes to match target binding pose
                        if (deltaTransform.isIdentity)
                        {
                            dstKeyFrame->setTranslate(srcKeyFrame->getTranslate());
                            dstKeyFrame->setRotation(srcKeyFrame->getRotation());
                            dstKeyFrame->setScale(srcKeyFrame->getScale());
                        }
                        else
                        {
                            dstKeyFrame->setTranslate(deltaTransform.translate + srcKeyFrame->getTranslate());
                            dstKeyFrame->setRotation(deltaTransform.rotate * srcKeyFrame->getRotation());
                            dstKeyFrame->setScale(deltaTransform.scale * srcKeyFrame->getScale());
                        }
                    }
                }
                else if (!deltaTransform.isIdentity)
                {
                    // Create 'static' track for this bone

                    NodeAnimationTrack* dstTrack = dstAnimation->createNodeTrack(dstHandle, this->getBone(dstHandle));
                    TransformKeyFrame* dstKeyFrame;

                    dstKeyFrame = dstTrack->createNodeKeyFrame(0);
                    dstKeyFrame->setTranslate(deltaTransform.translate);
                    dstKeyFrame->setRotation(deltaTransform.rotate);
                    dstKeyFrame->setScale(deltaTransform.scale);

                    dstKeyFrame = dstTrack->createNodeKeyFrame(dstAnimation->getLength());
                    dstKeyFrame->setTranslate(deltaTransform.translate);
                    dstKeyFrame->setRotation(deltaTransform.rotate);
                    dstKeyFrame->setScale(deltaTransform.scale);
                }
            }
        }
    }
bool BodyItemImpl::store(Archive& archive)
{
    archive.setDoubleFormat("% .6f");

    archive.writeRelocatablePath("modelFile", self->filePath());
    archive.write("currentBaseLink", (currentBaseLink ? currentBaseLink->name() : ""), DOUBLE_QUOTED);

    /// \todo Improve the following for current / initial position representations
    write(archive, "rootPosition", body->rootLink()->p());
    write(archive, "rootAttitude", Matrix3(body->rootLink()->R()));
    Listing* qs = archive.createFlowStyleListing("jointPositions");
    int n = body->numJoints();
    for(int i=0; i < n; ++i){
        qs->append(body->joint(i)->q(), 10, n);
    }

    //! \todo replace the following code with the ValueTree serialization function of BodyState
    SE3 initialRootPosition;
    if(initialState.getRootLinkPosition(initialRootPosition)){
        write(archive, "initialRootPosition", initialRootPosition.translation());
        write(archive, "initialRootAttitude", Matrix3(initialRootPosition.rotation()));
    }
    BodyState::Data& initialJointPositions = initialState.data(BodyState::JOINT_POSITIONS);
    if(!initialJointPositions.empty()){
        qs = archive.createFlowStyleListing("initialJointPositions");
        for(int i=0; i < initialJointPositions.size(); ++i){
            qs->append(initialJointPositions[i], 10, n);
        }
    }

    write(archive, "zmp", zmp);

    if(isOriginalModelStatic != body->isStaticModel()){
        archive.write("staticModel", body->isStaticModel());
    }

    archive.write("selfCollisionDetection", isSelfCollisionDetectionEnabled);
    archive.write("isEditable", isEditable);

    return true;
}
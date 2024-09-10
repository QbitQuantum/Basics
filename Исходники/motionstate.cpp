void MotionState::getWorldTransform(btTransform& worldTrans) const {
    const Matrix4 transformation = object().transformationMatrix();
    worldTrans.setOrigin(btVector3(transformation.translation()));
    worldTrans.setBasis(btMatrix3x3(transformation.rotationScaling()));
}
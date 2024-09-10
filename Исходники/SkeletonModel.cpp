void SkeletonModel::renderJointConstraints(gpu::Batch& batch, int jointIndex) {
    if (jointIndex == -1 || jointIndex >= _rig->getJointStateCount()) {
        return;
    }
    const FBXGeometry& geometry = _geometry->getFBXGeometry();
    const float BASE_DIRECTION_SIZE = 0.3f;
    float directionSize = BASE_DIRECTION_SIZE * extractUniformScale(_scale);
    // FIXME: THe line width of 3.0f is not supported anymore, we ll need a workaround

    do {
        const FBXJoint& joint = geometry.joints.at(jointIndex);
        const JointState& jointState = _rig->getJointState(jointIndex);
        glm::vec3 position = _rotation * jointState.getPosition() + _translation;
        glm::quat parentRotation = (joint.parentIndex == -1) ?
            _rotation :
            _rotation * _rig->getJointState(joint.parentIndex).getRotation();
        float fanScale = directionSize * 0.75f;
        
        Transform transform = Transform();
        transform.setTranslation(position);
        transform.setRotation(parentRotation);
        transform.setScale(fanScale);
        batch.setModelTransform(transform);
        
        const int AXIS_COUNT = 3;

        auto geometryCache = DependencyManager::get<GeometryCache>();

        for (int i = 0; i < AXIS_COUNT; i++) {
            if (joint.rotationMin[i] <= -PI + EPSILON && joint.rotationMax[i] >= PI - EPSILON) {
                continue; // unconstrained
            }
            glm::vec3 axis;
            axis[i] = 1.0f;
            
            glm::vec3 otherAxis;
            if (i == 0) {
                otherAxis.y = 1.0f;
            } else {
                otherAxis.x = 1.0f;
            }
            glm::vec4 color(otherAxis.r, otherAxis.g, otherAxis.b, 0.75f);

            QVector<glm::vec3> points;
            points << glm::vec3(0.0f, 0.0f, 0.0f);
            const int FAN_SEGMENTS = 16;
            for (int j = 0; j < FAN_SEGMENTS; j++) {
                glm::vec3 rotated = glm::angleAxis(glm::mix(joint.rotationMin[i], joint.rotationMax[i],
                    (float)j / (FAN_SEGMENTS - 1)), axis) * otherAxis;
                points << rotated;
            }
            // TODO: this is really inefficient constantly recreating these vertices buffers. It would be
            // better if the skeleton model cached these buffers for each of the joints they are rendering
            geometryCache->updateVertices(_triangleFanID, points, color);
            geometryCache->renderVertices(batch, gpu::TRIANGLE_FAN, _triangleFanID);
            
        }
        
        renderOrientationDirections(batch, jointIndex, position, _rotation * jointState.getRotation(), directionSize);
        jointIndex = joint.parentIndex;
        
    } while (jointIndex != -1 && geometry.joints.at(jointIndex).isFree);
}
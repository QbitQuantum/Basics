void X3DConverter::startShape(const std::array<float, 12>& matrix) {

    // Finding axis/angle from matrix using Eigen for its bullet proof implementation.
    Eigen::Transform<float, 3, Eigen::Affine> t;
    t.setIdentity();
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            t(i, j) = matrix[i+j*3];
        }
    }

    Eigen::Matrix3f rotationMatrix;
	Eigen::Matrix3f scaleMatrix;
    t.computeRotationScaling(&rotationMatrix, &scaleMatrix);
	Eigen::Quaternionf q;
	Eigen::AngleAxisf aa;
	q = rotationMatrix;
    aa = q;

	Eigen::Vector3f scale = scaleMatrix.diagonal();
	Eigen::Vector3f translation = t.translation();

    startNode(ID::Transform);
    m_writers.back()->setSFVec3f(ID::translation, translation.x(), translation.y() , translation.z());
    m_writers.back()->setSFRotation(ID::rotation, aa.axis().x(), aa.axis().y(), aa.axis().z(), aa.angle());
    m_writers.back()->setSFVec3f(ID::scale, scale.x(), scale.y(), scale.z());
    startNode(ID::Shape);
    startNode(ID::Appearance);
    startNode(ID::Material);
    m_writers.back()->setSFColor<vector<float> >(ID::diffuseColor, RVMColorHelper::color(m_materials.back()));
    endNode(ID::Material); // Material
    endNode(ID::Appearance); // Appearance

}
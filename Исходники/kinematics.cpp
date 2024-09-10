InverseKinematicsReportPtr
KinematicSolver::inverse(const btTransform& pose) {
	return inverse(pose,defaultIKOptions_);
}
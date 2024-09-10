	SMC_higher_order(/*systems::ExecutionManager* em*/bool status,
			const Eigen::Matrix4d coeff, const Eigen::Vector4d delta,
			const Eigen::Matrix4d A, const Eigen::Matrix4d B, const float P,
			const float Q,
			const std::string& sysName = "Slidingmode_Controller") :
			System(sysName), referencejpInput(this), referencejvInput(this), referencejaInput(
					this), feedbackjpInput(this), feedbackjvInput(this), M(
					this), C(this),

			controlOutput(this, &controlOutputValue), STATUS(status), Coeff(
					coeff), Delta(delta), A(A), B(B), P(P), Q(Q) {
		inv_B = B.inverse();
	}
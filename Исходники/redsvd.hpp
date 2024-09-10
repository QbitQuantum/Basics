		void compute(const MatrixType& A, const Index rank)
		{
			if(A.cols() == 0 || A.rows() == 0)
				return;

			Index r = (rank < A.cols()) ? rank : A.cols();

			r = (r < A.rows()) ? r : A.rows();

			// Gaussian Random Matrix for A^T
			DenseMatrix O(A.rows(), r);
			sample_gaussian(O);

			// Compute Sample Matrix of A^T
			DenseMatrix Y = A.transpose() * O;

			// Orthonormalize Y
			gram_schmidt(Y);

			// Range(B) = Range(A^T)
			DenseMatrix B = A * Y;

			// Gaussian Random Matrix
			DenseMatrix P(B.cols(), r);
			sample_gaussian(P);

			// Compute Sample Matrix of B
			DenseMatrix Z = B * P;

			// Orthonormalize Z
			gram_schmidt(Z);

			// Range(C) = Range(B)
			DenseMatrix C = Z.transpose() * B;

			Eigen::JacobiSVD<DenseMatrix> svdOfC(C, Eigen::ComputeThinU | Eigen::ComputeThinV);

			// C = USV^T
			// A = Z * U * S * V^T * Y^T()
			m_matrixU = Z * svdOfC.matrixU();
			m_vectorS = svdOfC.singularValues();
			m_matrixV = Y * svdOfC.matrixV();
		}
void pca_small(MatrixXd &B, int method, MatrixXd& U, VectorXd &d, bool verbose)
{
   if(method == METHOD_SVD)
   {
      verbose && std::cout << timestamp() << " SVD begin" << std::endl;
      JacobiSVD<MatrixXd> svd(B, ComputeThinU | ComputeThinV);
      U = svd.matrixU();
      MatrixXd V = svd.matrixV();
      d = svd.singularValues().array().pow(2);
      verbose && std::cout << timestamp() << " SVD done" << std::endl;
   }
   else if(method == METHOD_EIGEN)
   {
      verbose && std::cout << timestamp() << " Eigen-decomposition begin" << std::endl;
      MatrixXd BBT = B * B.transpose();
      verbose && std::cout << timestamp() << " dim(BBT): " << dim(BBT) << std::endl;
      SelfAdjointEigenSolver<MatrixXd> eig(BBT);

      // The eigenvalues come out sorted in *increasing* order,
      // but we need decreasing order
      VectorXd eval = eig.eigenvalues();
      MatrixXd evec = eig.eigenvectors();
      d.resize(eval.size());
      U.resize(BBT.rows(), BBT.rows());

      unsigned int k = 0, s = d.size();
      for(unsigned int i = d.size() - 1 ; i != -1 ; --i)
      {
	 // we get eigenvalues, which are the squared singular values
	 d(k) = eval(i);
	 U.col(k) = evec.col(i);
	 k++;
      }
   }
}
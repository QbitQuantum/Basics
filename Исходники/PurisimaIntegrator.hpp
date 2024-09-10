 /*! Returns off-diagonal elements of the matrix representation of the double layer operator by collocation
  *  \param[in] elements list of finite elements
  *  \param[in] kernD    function for the evaluation of the off-diagonal of D
  */
 Eigen::MatrixXd offDiagonalD(const std::vector<Element> & elements,
         const integrator::KernelD & kernD) const
 {
     size_t mat_size = elements.size();
     Eigen::MatrixXd D = Eigen::MatrixXd::Zero(mat_size, mat_size);
     for (size_t i = 0; i < mat_size; ++i) {
         Eigen::Vector3d source = elements[i].center();
         for (size_t j = 0; j < mat_size; ++j) {
             // Fill off-diagonal
             Eigen::Vector3d probe = elements[j].center();
             Eigen::Vector3d probeNormal = elements[j].normal();
             probeNormal.normalize();
             if (i != j) D(i, j) = kernD(probeNormal, source, probe);
         }
     }
     return D;
 }
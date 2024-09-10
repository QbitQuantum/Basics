Image smooth_detector(const Image& source, Interpolation level, int r) {
  Image output(source.rows(), source.columns(), 1, numeric_limits<float>::max());
  const MatrixXf reg_matrix = ComputeRegMatrix(level, r);
  const LDLT<MatrixXf> solver = (reg_matrix.transpose() * reg_matrix).ldlt();
  for (int pr = 0; pr <= source.rows() - r; ++pr) {
    for (int pc = 0; pc <= source.columns() - r; ++pc) {
      VectorXf dist = VectorXf::Zero(r * r);
      for (int ch = 0; ch < source.channels(); ++ch) {
        EigenImage y = ExtractPatch(source, r, pr, pc, ch);
        VectorXf reg_surf = solver.solve(reg_matrix.transpose() * y.asvector());
        dist += (reg_matrix * reg_surf - y.asvector()).cwiseAbs2();
      }
      dist = dist.cwiseSqrt();
      for (int row = pr; row < min(output.rows(), pr + r); ++row) {
        for (int col = pc; col < min(output.columns(), pc + r); ++col) {
          output.val(col, row) = min(output.val(col, row), dist((row - pr) * r + col - pc));
        }
      }
    }
  }
  return output;
}
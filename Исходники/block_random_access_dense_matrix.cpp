BlockRandomAccessDenseMatrix::BlockRandomAccessDenseMatrix(
    const vector<int>& blocks) {
  const int num_blocks = blocks.size();
  block_layout_.resize(num_blocks, 0);
  num_rows_ = 0;
  for (int i = 0; i < num_blocks; ++i) {
    block_layout_[i] = num_rows_;
    num_rows_ += blocks[i];
  }

  values_.reset(new double[num_rows_ * num_rows_]);

  cell_infos_.reset(new CellInfo[num_blocks * num_blocks]);
  for (int i = 0; i < num_blocks * num_blocks; ++i) {
    cell_infos_[i].values = values_.get();
  }

  SetZero();
}
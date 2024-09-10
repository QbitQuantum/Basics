  /**
   * 将两个稀疏矩阵模板按竖直方向连接成为一个新的模板
   * 要求这两个矩阵具有相同的列数。
   *
   * @param sp0 上边的模板
   * @param sp1 下边的模板
   * @param sp 得到的新模板
   */
  void vCatSparsityPattern(const SparsityPattern& sp0,
			   const SparsityPattern& sp1,
			   SparsityPattern& sp)
  {
    u_int m0 = sp0.n_rows();
    u_int n0 = sp0.n_cols();

    /**
     * 检查这个两个模板是否都已经压缩过了。
     * 
     */
    Assert(sp0.is_compressed(), ExcNotCompressed());
    Assert(sp1.is_compressed(), ExcNotCompressed());

    /**
     * 检查这两个模板是否具有相同的列数。
     * 
     */
    Assert (n0 == sp1.n_cols(), ExcDimensionDontMatch(m0, sp1.n_cols()));
  
    u_int i, j, m1 = sp1.n_rows();
    std::vector<u_int> row_length(m0 + m1, 0);
    for (i = 0;i < m0;i ++)
      row_length[i] = sp0.row_length(i);
    for (i = 0;i < m1;i ++)
      row_length[i + m0] = sp1.row_length(i);
    sp.reinit(m0 + m1, n0, row_length);
    const std::size_t * p_rowstart0 = sp0.get_rowstart_indices();
    const u_int * p_column0 = sp0.get_column_numbers();
    const std::size_t * p_rowstart1 = sp1.get_rowstart_indices();
    const u_int * p_column1 = sp1.get_column_numbers();
    for (i = 0;i < m0;i ++)
      for (j = p_rowstart0[i];j < p_rowstart0[i + 1];j ++)
	sp.add(i, p_column0[j]);
    for (i = 0;i < m1;i ++)
      for (j = p_rowstart1[i];j < p_rowstart1[i + 1];j ++)
	sp.add(m0 + i, p_column1[j]);
    sp.compress();
  };
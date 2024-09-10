 void swap(rmq_support_sparse_table& rm) {
     std::swap(m_k, rm.m_k);
     m_table.swap(rm.m_table);
 }
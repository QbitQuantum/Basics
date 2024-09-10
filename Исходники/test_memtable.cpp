TEST(TestMemTable, total_empty)
{
  MemTable mt;
  PageArena<char> allocer;
  ObScanParam scan_param;
  ObUpsMutator ups_mutator;
  ObMutator &mutator = ups_mutator.get_mutator();
  ObMutator result;
  MemTableTransDescriptor td;
  MemTableIterator iter;
  ObRowCompaction rc;
  ObCellInfo *ci = NULL;

  mt.init();

  read_scan_param("test_cases/test_mt_empty_set.scan.ini", "MT_EMPTY_SET_SCAN", allocer, scan_param);
  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.scan(td, *(scan_param.get_range()), false, iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  iter.reset();
  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.get(td, 1000, ObString(17, 17, const_cast<char*>("pre_1001|suf_0000")), iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_SUCCESS, rc.next_cell());
  EXPECT_EQ(OB_SUCCESS, rc.get_cell(&ci));
  EXPECT_EQ(true, ObActionFlag::OP_ROW_DOES_NOT_EXIST == ci->value_.get_ext());
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  mt.clear();
  mutator.reset();
  iter.reset();
  read_cell_infos("test_cases/test_mt_empty1_set.ci.ini", "MT_EMPTY1_SET_CI", allocer, mutator, result);
  mt.start_transaction(WRITE_TRANSACTION, td);
  mt.start_mutation(td);
  EXPECT_EQ(OB_SUCCESS, mt.set(td, ups_mutator, false));
  mt.end_mutation(td, false);
  mt.end_transaction(td, false);

  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.scan(td, *(scan_param.get_range()), false, iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  iter.reset();
  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.get(td, 1000, ObString(17, 17, const_cast<char*>("pre_1001|suf_0000")), iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_SUCCESS, rc.next_cell());
  EXPECT_EQ(OB_SUCCESS, rc.get_cell(&ci));
  EXPECT_EQ(true, ObActionFlag::OP_ROW_DOES_NOT_EXIST == ci->value_.get_ext());
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  mt.clear();
  mutator.reset();
  iter.reset();
  read_cell_infos("test_cases/test_mt_empty2_set.ci.ini", "MT_EMPTY2_SET_CI", allocer, mutator, result);
  mt.start_transaction(WRITE_TRANSACTION, td);
  mt.start_mutation(td);
  EXPECT_EQ(OB_SUCCESS, mt.set(td, ups_mutator, false));
  mt.end_mutation(td, false);
  mt.end_transaction(td, false);

  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.scan(td, *(scan_param.get_range()), false, iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  iter.reset();
  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.get(td, 1000, ObString(17, 17, const_cast<char*>("pre_1001|suf_0000")), iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_SUCCESS, rc.next_cell());
  EXPECT_EQ(OB_SUCCESS, rc.get_cell(&ci));
  EXPECT_EQ(true, ObActionFlag::OP_ROW_DOES_NOT_EXIST == ci->value_.get_ext());
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  ////////////////////////////////////////////////////////////////////////////////////////////////////

  mt.clear();
  mutator.reset();
  iter.reset();
  read_cell_infos("test_cases/test_mt_empty3_set.ci.ini", "MT_EMPTY3_SET_CI", allocer, mutator, result);
  mt.start_transaction(WRITE_TRANSACTION, td);
  mt.start_mutation(td);
  EXPECT_EQ(OB_SUCCESS, mt.set(td, ups_mutator, false));
  mt.end_mutation(td, false);
  mt.end_transaction(td, false);

  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.scan(td, *(scan_param.get_range()), false, iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  iter.reset();
  mt.start_transaction(READ_TRANSACTION, td);
  EXPECT_EQ(OB_SUCCESS, mt.get(td, 1000, ObString(17, 17, const_cast<char*>("pre_1001|suf_0000")), iter));
  rc.set_iterator(&iter);
  EXPECT_EQ(OB_SUCCESS, rc.next_cell());
  EXPECT_EQ(OB_SUCCESS, rc.get_cell(&ci));
  EXPECT_EQ(true, ObActionFlag::OP_ROW_DOES_NOT_EXIST == ci->value_.get_ext());
  EXPECT_EQ(OB_ITER_END, rc.next_cell());
  mt.end_transaction(td);

  mt.destroy();
}
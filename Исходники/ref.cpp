void call_ref()
{
  VectorXcf ca  = VectorXcf::Random(10);
  VectorXf a    = VectorXf::Random(10);
  RowVectorXf b = RowVectorXf::Random(10);
  MatrixXf A    = MatrixXf::Random(10,10);
  RowVector3f c = RowVector3f::Random();
  const VectorXf& ac(a);
  VectorBlock<VectorXf> ab(a,0,3);
  const VectorBlock<VectorXf> abc(a,0,3);
  

  VERIFY_EVALUATION_COUNT( call_ref_1(a,a), 0);
  VERIFY_EVALUATION_COUNT( call_ref_1(b,b.transpose()), 0);
//   call_ref_1(ac,a<c);           // does not compile because ac is const
  VERIFY_EVALUATION_COUNT( call_ref_1(ab,ab), 0);
  VERIFY_EVALUATION_COUNT( call_ref_1(a.head(4),a.head(4)), 0);
  VERIFY_EVALUATION_COUNT( call_ref_1(abc,abc), 0);
  VERIFY_EVALUATION_COUNT( call_ref_1(A.col(3),A.col(3)), 0);
//   call_ref_1(A.row(3),A.row(3));    // does not compile because innerstride!=1
  VERIFY_EVALUATION_COUNT( call_ref_3(A.row(3),A.row(3).transpose()), 0);
  VERIFY_EVALUATION_COUNT( call_ref_4(A.row(3),A.row(3).transpose()), 0);
//   call_ref_1(a+a, a+a);          // does not compile for obvious reason

  MatrixXf tmp = A*A.col(1);
  VERIFY_EVALUATION_COUNT( call_ref_2(A*A.col(1), tmp), 1);     // evaluated into a temp
  VERIFY_EVALUATION_COUNT( call_ref_2(ac.head(5),ac.head(5)), 0);
  VERIFY_EVALUATION_COUNT( call_ref_2(ac,ac), 0);
  VERIFY_EVALUATION_COUNT( call_ref_2(a,a), 0);
  VERIFY_EVALUATION_COUNT( call_ref_2(ab,ab), 0);
  VERIFY_EVALUATION_COUNT( call_ref_2(a.head(4),a.head(4)), 0);
  tmp = a+a;
  VERIFY_EVALUATION_COUNT( call_ref_2(a+a,tmp), 1);            // evaluated into a temp
  VERIFY_EVALUATION_COUNT( call_ref_2(ca.imag(),ca.imag()), 1);      // evaluated into a temp

  VERIFY_EVALUATION_COUNT( call_ref_4(ac.head(5),ac.head(5)), 0);
  tmp = a+a;
  VERIFY_EVALUATION_COUNT( call_ref_4(a+a,tmp), 1);           // evaluated into a temp
  VERIFY_EVALUATION_COUNT( call_ref_4(ca.imag(),ca.imag()), 0);

  VERIFY_EVALUATION_COUNT( call_ref_5(a,a), 0);
  VERIFY_EVALUATION_COUNT( call_ref_5(a.head(3),a.head(3)), 0);
  VERIFY_EVALUATION_COUNT( call_ref_5(A,A), 0);
//   call_ref_5(A.transpose(),A.transpose());   // does not compile because storage order does not match
  VERIFY_EVALUATION_COUNT( call_ref_5(A.block(1,1,2,2),A.block(1,1,2,2)), 0);
  VERIFY_EVALUATION_COUNT( call_ref_5(b,b), 0);             // storage order do not match, but this is a degenerate case that should work
  VERIFY_EVALUATION_COUNT( call_ref_5(a.row(3),a.row(3)), 0);

  VERIFY_EVALUATION_COUNT( call_ref_6(a,a), 0);
  VERIFY_EVALUATION_COUNT( call_ref_6(a.head(3),a.head(3)), 0);
  VERIFY_EVALUATION_COUNT( call_ref_6(A.row(3),A.row(3)), 1);           // evaluated into a temp thouth it could be avoided by viewing it as a 1xn matrix
  tmp = A+A;
  VERIFY_EVALUATION_COUNT( call_ref_6(A+A,tmp), 1);                // evaluated into a temp
  VERIFY_EVALUATION_COUNT( call_ref_6(A,A), 0);
  VERIFY_EVALUATION_COUNT( call_ref_6(A.transpose(),A.transpose()), 1);      // evaluated into a temp because the storage orders do not match
  VERIFY_EVALUATION_COUNT( call_ref_6(A.block(1,1,2,2),A.block(1,1,2,2)), 0);
  
  VERIFY_EVALUATION_COUNT( call_ref_7(c,c), 0);
}
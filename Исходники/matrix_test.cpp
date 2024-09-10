void MatrixTest::test_dot_vector(void)
{
   message += "test_dot_vector\n";

   Matrix<double> a;
   Vector<double> b;

   Vector<double> c;

   // Test

   a.set(2, 2, 0.0);
   b.set(2, 0.0);

   c = a.dot(b);

   assert_true(c == 0.0, LOG);

   // Test

   a.set(2, 2, 1.0);
   b.set(2, 1.0);

   c = a.dot(b);

   assert_true(c == 2.0, LOG);

   // Test

   a.set(2, 5);
   a.randomize_normal();

   b.set(5);
   b.randomize_normal();

   c = a.dot(b);

   assert_true((c - dot(a, b)).calculate_absolute_value() < 1.0e-3, LOG);

   // Test

   a.set(2, 2);
   a(0,0) = 1.0;
   a(0,1) = 2.0;
   a(1,0) = 3.0;
   a(1,1) = 4.0;

   b.set(2);
   b[0] = -1.0;
   b[1] =  1.0;

   c = a.dot(b);

   assert_true(c == 1.0, LOG);
}
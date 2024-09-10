  TEST(Integer, OpenPow)
  {
    Integer base(10);
    Integer exp(100);
    EXPECT_EQ(exp, base.Pow(Integer(10), Integer(101)));
    EXPECT_EQ(Integer(0), base.Pow(Integer(10), Integer(100)));

    for(int i=0; i<10; i++) {
      Integer p = Integer::GetRandomInteger(1024, true);
      Integer a = Integer::GetRandomInteger(0, p);
      Integer b = Integer::GetRandomInteger(0, p);
      Integer e1 = Integer::GetRandomInteger(0, p);
      Integer e2 = Integer::GetRandomInteger(0, p);


      EXPECT_EQ(p.PowCascade(a, e1, b, e2), 
          (a.Pow(e1, p) * b.Pow(e2, p))%p);

      EXPECT_EQ(Integer(1), a.Pow(0, p));
      EXPECT_EQ(a, a.Pow(1, p));
    }
  }
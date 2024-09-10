TEST_F(UnitsFixture,BTUUnit_ArithmeticOperators)
{
  LOG(Debug,"BTUUnit_ArithmeticOperators");

  // /=
  BTUUnit P1(BTUExpnt(1));
  BTUUnit t1(BTUExpnt(0,0,1));
  P1 /= t1;
  EXPECT_EQ("Btu/h",P1.standardString(false));
  EXPECT_EQ(1,P1.baseUnitExponent("Btu"));
  EXPECT_EQ(-1,P1.baseUnitExponent("h"));
  EXPECT_EQ(0,P1.baseUnitExponent("ft"));
  EXPECT_EQ(0,P1.baseUnitExponent("m"));

  // *
  Unit E1 = P1 * t1;
  EXPECT_TRUE(E1.system() == UnitSystem::BTU);
  EXPECT_EQ("Btu",E1.standardString(false));
  EXPECT_EQ("",E1.prettyString());

  // /
  Unit u = P1/E1;
  u /= t1;
  EXPECT_TRUE(u.system() == UnitSystem::BTU);
  EXPECT_EQ("1/h^2",u.standardString(false));
  EXPECT_EQ(-2,u.baseUnitExponent("h"));
  EXPECT_EQ(0,u.baseUnitExponent("Btu"));

  // pow
  u.pow(-1,2);
  EXPECT_EQ("h",u.standardString(false));
  EXPECT_EQ(1,u.baseUnitExponent("h"));

}
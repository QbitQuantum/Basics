/* ****************************************************************************
*
* atoF - 
*/
TEST(string, atoF)
{
  std::string  e;
  double       d;

  d = atoF("", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("empty string", e);
  
  d = atoF(" ", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("invalid characters in string to convert", e);

  d = atoF("34", &e);
  EXPECT_EQ(34, d);
  EXPECT_EQ("", e);

  d = atoF("-34.0", &e);
  EXPECT_EQ(-34.0, d);
  EXPECT_EQ("", e);

  d = atoF("+34.1", &e);
  EXPECT_EQ(34.1, d);
  EXPECT_EQ("", e);

  d = atoF(".34", &e);
  EXPECT_EQ(.34, d);
  EXPECT_EQ("", e);

  d = atoF("--4", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("non-digit after unary minus/plus", e);

  d = atoF("+-4", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("non-digit after unary minus/plus", e);

  d = atoF("-.4", &e);
  EXPECT_EQ(-0.4, d);
  EXPECT_EQ("", e);

  d = atoF(".34.0", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("more than one dot", e);

  d = atoF("34.", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("last character in a double cannot be a dot", e);

  d = atoF("x34", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("invalid characters in string to convert", e);

  d = atoF("--224", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("non-digit after unary minus/plus", e);

  d = atoF("-.224", &e);
  EXPECT_EQ(-0.224, d);
  EXPECT_EQ("", e);

  d = atoF("2-24", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("invalid characters in string to convert", e);

  d = atoF("224-", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("invalid characters in string to convert", e);

  d = atoF("224.-", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("invalid characters in string to convert", e);

  d = atoF("224.", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("last character in a double cannot be a dot", e);

  d = atoF("2.2.4", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("more than one dot", e);

  d = atoF("2 24", &e);
  EXPECT_EQ(0.0, d);
  EXPECT_EQ("invalid characters in string to convert", e);
}
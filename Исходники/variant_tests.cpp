TEST_F(VariantTests, testSetters)
{
  OpenAB::Variant variant;
  ASSERT_TRUE(variant.invalid());

  //set bool variable
  variant.set(true);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::BOOL, variant.getType());
  ASSERT_EQ(true, variant.getBool());

  //set char variable
  variant.set('a');
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::CHAR, variant.getType());
  ASSERT_EQ('a', variant.getChar());

  //set string variable
  variant.set("hello");
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::STRING, variant.getType());
  ASSERT_EQ("hello", variant.getString());

  variant.set(std::string("hello"));
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::STRING, variant.getType());
  ASSERT_EQ("hello", variant.getString());

  //set secure string variable
  variant.set(OpenAB::SecureString("hello"));
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::SECURE_STRING, variant.getType());
  ASSERT_EQ("hello", std::string(variant.getSecureString().str()));

  //set pointer variable
  variant.set((void*)0xBAAD);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::POINTER, variant.getType());
  ASSERT_EQ((void*)0xBAAD, variant.getPointer());

  //set float variable
  variant.set(123.45f);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::DOUBLE, variant.getType());
  ASSERT_EQ(123.45f, variant.getDouble());

  //set double variable
  variant.set(123.45);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::DOUBLE, variant.getType());
  ASSERT_EQ(123.45, variant.getDouble());

  //set int variables
  variant.set((u_int8_t)123);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::INTEGER, variant.getType());
  ASSERT_EQ(123, variant.getInt());

  variant.set((u_int16_t)123);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::INTEGER, variant.getType());
  ASSERT_EQ(123, variant.getInt());

  variant.set((u_int32_t)123);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::INTEGER, variant.getType());
  ASSERT_EQ(123, variant.getInt());

  variant.set((int8_t)123);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::INTEGER, variant.getType());
  ASSERT_EQ(123, variant.getInt());

  variant.set((int16_t)123);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::INTEGER, variant.getType());
  ASSERT_EQ(123, variant.getInt());

  variant.set((int32_t)123);
  ASSERT_FALSE(variant.invalid());
  ASSERT_EQ(OpenAB::Variant::INTEGER, variant.getType());
  ASSERT_EQ(123, variant.getInt());
}
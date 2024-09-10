TEST_F(SerializationTest, FloatingTypesTest) {
  HasManyFloats hmf;
  hmf.a = nextafter(10000.0f, 10000.1f);
  hmf.b = nextafter(20000.0, 20000.1);
  hmf.c = nextafter(30000.0L, 30000.1L);

  std::stringstream ss;
  leap::Serialize(ss, hmf);
  auto deserialized = leap::Deserialize<HasManyFloats>(ss);
  ASSERT_EQ(hmf.a, deserialized->a) << "Float datatype not properly round-trip serialized";
  ASSERT_EQ(hmf.b, deserialized->b) << "Double datatype not properly round-trip serialized";
  ASSERT_EQ(hmf.c, deserialized->c) << "Long double datatype not properly round-trip serialized";
}
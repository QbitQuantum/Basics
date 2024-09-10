 uint32_t listen() {
     ASSERT_TRUE(orb.Listen(0));
     return orb.GetListenPort();
 }
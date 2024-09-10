TEST_F(RgbScreenServerTest, testSetPixelViaBinaryStreams) {
   uint8_t command = RemoteRgbScreenProtocol::SET_PIXEL;
   uint8_t x = 7;
   uint8_t y = 6;
   Color color(60,70,80);

   Com::BinaryOutputPackage out(mInBuffer);

   out << command << x << y << color;

   EXPECT_CALL(mScreen,setPixel(x,y,color));

   mRgbScreenServer.handleRequest(mIn,mOutMock);
}
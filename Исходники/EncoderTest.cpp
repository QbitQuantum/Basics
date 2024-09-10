/**
 * Test that memory is not leaked/corrupted during error paths.
 */
void
EncoderTest::testEncodeInvalidParameters()
{
  // Sub-test 1
  {
    int32_t width=176;
    int32_t height=360; // invalid dimensions for H263 codec
    RefPointer<Codec> codec = Codec::findEncodingCodec(Codec::CODEC_ID_H263);
    RefPointer<Encoder> encoder = Encoder::make(codec.value());

    RefPointer<MediaPicture> picture = MediaPicture::make(width*2,height*2,
        PixelFormat::PIX_FMT_YUV420P);

    // set the encoder properties we need
    encoder->setWidth(picture->getWidth());
    encoder->setHeight(picture->getHeight());
    encoder->setPixelFormat(picture->getFormat());
    encoder->setProperty("b", (int64_t)400000); // bitrate
    encoder->setProperty("g", (int64_t) 10); // gop

    RefPointer<Rational> tb = Rational::make(1,25);
    encoder->setTimeBase(tb.value());

    // open the encoder
    try {
      // Temporarily turn down logging
      LoggerStack stack;
      stack.setGlobalLevel(Logger::LEVEL_ERROR, false);

      encoder->open(0, 0);
      TS_FAIL("should never get here");
    } catch (std::exception & e) {
      // ignore exception
    }
  }

  // Sub-test 2
  {
    int32_t width=176;
    int32_t height=144;

    RefPointer<Codec> codec = Codec::findEncodingCodec(Codec::CODEC_ID_H264);
    RefPointer<Encoder> encoder = Encoder::make(codec.value());
    RefPointer<MediaPicture> picture = MediaPicture::make(width*2,height*2,
        PixelFormat::PIX_FMT_YUV420P);

    // set the encoder properties we need
    encoder->setWidth(picture->getWidth());
    encoder->setHeight(picture->getHeight());
    encoder->setPixelFormat(picture->getFormat());
    encoder->setProperty("b", (int64_t)400000); // bitrate
    encoder->setProperty("g", (int64_t) 10); // gop
    encoder->setProperty("bf", (int64_t)1); // max b frames

    RefPointer<Rational> tb = Rational::make(1,25);
    encoder->setTimeBase(tb.value());

    // Do not open the encoder

    // create an output muxer
    RefPointer<Muxer> muxer = Muxer::make("EncoderTest_encodeVideo.mov", 0, 0);

    // add a stream for the encoded packets
    try {
      // Temporarily turn down logging
      LoggerStack stack;
      stack.setGlobalLevel(Logger::LEVEL_ERROR, false);

      RefPointer<MuxerStream> stream = muxer->addNewStream(encoder.value());
      TS_FAIL("should never get here");
    } catch (std::exception & e) {
      // success
    }
  }
}
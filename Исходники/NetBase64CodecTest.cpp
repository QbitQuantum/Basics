   void testUtl2Utl()
      {
         UtlString encoded;
         UtlString decoded;

         char msg[2048];

         for (unsigned int test = 0; test < (sizeof(tests)/sizeof(TestData)); test++)
         {
            UtlString input(tests[test].inputData, tests[test].inputSize);
            
            encoded.remove(0);
            NetBase64Codec::encode(input, encoded);
            
            sprintf(msg,
                    "\n  test case %d encoding"
                    "\n     expected size %d data '%s'"
                    "\n     actual   size %d data '%s'",
                    test,
                    strlen(tests[test].output), tests[test].output,
                    encoded.length(), encoded.data()
                    );
            CPPUNIT_ASSERT_MESSAGE(msg,
                                   (   (encoded.length() == strlen(tests[test].output))
                                    && (encoded.compareTo(tests[test].output) == 0)
                                    ));

            decoded.remove(0);
            bool decodedOk;
            decodedOk = NetBase64Codec::decode(encoded, decoded);

            sprintf(msg,
                    "\n  test case %d decoding %s"
                    "\n     expected size %d data '%s'"
                    "\n     actual   size %d data '%s'",
                    test, decodedOk ? "ok" : "failed",
                    tests[test].inputSize, tests[test].inputData,
                    decoded.length(), decoded.data()
                    );
            CPPUNIT_ASSERT_MESSAGE(msg,
                                   (   decodedOk
                                    && (decoded.length() == tests[test].inputSize)
                                    && (memcmp(tests[test].inputData,
                                               decoded.data(),
                                               tests[test].inputSize
                                               )
                                        == 0)
                                    ));
         }
      }
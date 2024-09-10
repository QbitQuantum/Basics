void BinaryReaderWriterTest::write(BinaryWriter& writer)
{
	writer << true;
	writer << false;
	writer << 'a';
	writer << (short) -100;
	writer << (unsigned short) 50000;
	writer << -123456;
	writer << (unsigned) 123456;
	writer << (long) -1234567890;
	writer << (unsigned long) 1234567890;
	
#if defined(POCO_HAVE_INT64)
	writer << (Int64) -1234567890;
	writer << (UInt64) 1234567890;
#endif

	writer << (float) 1.5;
	writer << (double) -1.5;
	
	writer << "foo";
	writer << "";
	
	writer << std::string("bar");
	writer << std::string();
	
	writer.write7BitEncoded((UInt32) 100);
	writer.write7BitEncoded((UInt32) 1000);
	writer.write7BitEncoded((UInt32) 10000);
	writer.write7BitEncoded((UInt32) 100000);
	writer.write7BitEncoded((UInt32) 1000000);

#if defined(POCO_HAVE_INT64)
	writer.write7BitEncoded((UInt64) 100);
	writer.write7BitEncoded((UInt64) 1000);
	writer.write7BitEncoded((UInt64) 10000);
	writer.write7BitEncoded((UInt64) 100000);
	writer.write7BitEncoded((UInt64) 1000000);
#endif

	writer.writeRaw("RAW");
}
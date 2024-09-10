bool
test_compression (CORBA::ULong nelements,
              Compression::CompressionManager_ptr cm)
{
  bool succeed = false;

  CORBA::OctetSeq mytest;
  mytest.length (nelements);
  for (CORBA::ULong j = 0; j != nelements; ++j)
    {
      mytest[j] = 'a';
    }

  Compression::Compressor_var compressor = cm->get_compressor (
    ::Compression::COMPRESSORID_BZIP2, 6);

  CORBA::OctetSeq myout;
  myout.length ((CORBA::ULong)(mytest.length() * 1.1));

  compressor->compress (mytest, myout);

  CORBA::OctetSeq decompress;
  decompress.length (nelements);

  compressor->decompress (myout, decompress);

  if (decompress != mytest)
    {
      ACE_ERROR ((LM_ERROR, "Error, decompress not working\n"));
    }
  else
    {
      succeed = true;
      ACE_DEBUG ((LM_DEBUG, "Compression worked with bzip2, original "
                            "size %d, compressed size %d\n",
                            mytest.length(), myout.length ()));
    }
  return succeed;
}
static int  test_compressor(const ::Compression::Compressor_var &compressor)
{
    if (::CORBA::is_nil(compressor.in())) {
        ACE_ERROR_RETURN((LM_ERROR,
            ACE_TEXT("ERROR: nil Compressor.\n")),-1);
    }

    ::CORBA::ULong  in_len = static_cast< CORBA::ULong>(sizeof(test_array));
    ::CORBA::Octet* in_buf = reinterpret_cast< CORBA::Octet*>(test_array);

    ::Compression::Buffer in_data(in_len, in_len, in_buf, false);

    ::Compression::Buffer comp_out;

    comp_out.length(static_cast< ::CORBA::ULong>(in_len * 1.1));

    {
      HRTimer _hrt(ACE_TEXT("Compress Time - "));
      compressor->compress(in_data, comp_out);
    }

    ACE_HEX_DUMP((  LM_INFO,
                    reinterpret_cast<const char*>(comp_out.get_buffer()),
                    comp_out.length(),
                    ACE_TEXT("Compressed Buffer")
                    ));

    ::Compression::Buffer decomp_out; decomp_out.length(1024);

    {
        HRTimer _hrt(ACE_TEXT("DeCompress Time - "));
        compressor->decompress(comp_out, decomp_out);
    }

    // Make sure we got back the original OK.
    if (ACE_OS::memcmp( in_data.get_buffer(), decomp_out.get_buffer(), in_data.length()))
    {
        ACE_ERROR_RETURN((LM_ERROR,
            ACE_TEXT("ERROR: Did not Compress/Decompress correctly.\n")),-1);
    }

    ACE_ERROR_RETURN((LM_INFO, ACE_TEXT("\n********* END TEST ************\n")), 0);
}
/**
 * Attempt to compress and decompress.
 */
void
TestDecompress(CuTest * tc)
{
    char input[] =
        {
 "This is a test input string.  I like to test inputThis is a test input string.  I like to test input."
};
    uLongf input_len = (uLongf) strlen(input);

    uLongf compressed_len = 2000;
    void *compressed = malloc(compressed_len);

    uLongf decompressed_len = 2000;
    void *decompressed = malloc(decompressed_len);


  /**
   * Attempt the compression.
   */
    int ret =
        compress2(compressed, &compressed_len, (void *)input, input_len,
                  Z_BEST_SPEED);

  /**
   * Assert it 1.  Worked.
   */
    CuAssertTrue(tc, ret == Z_OK);

  /**
   * The output size is smaller than the input size.
   */
    CuAssertTrue(tc, compressed_len < input_len);


  /**
   * OK now we decompress.
   */
    ret =
        uncompress(decompressed, &decompressed_len, (void *)compressed,
                   compressed_len);

  /**
   * Assert: 1. it worked.
   */
    CuAssertTrue(tc, ret == Z_OK);

  /**
   * 2. Output is longer than the input.
   */
    CuAssertTrue(tc, compressed_len < decompressed_len);

  /**
   * 3. Ouptut is equal to original starting point.
   */
    CuAssertTrue(tc, decompressed_len == input_len);
    CuAssertTrue(tc, (strcmp(decompressed, input) == 0));

    free(compressed);
    free(decompressed);
}
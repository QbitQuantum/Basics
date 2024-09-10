void TestNdsUnicode61Tokenizer_japanese()
{
    // "出身の物理化学者、電気化学者。"
    static const char TEST_INPUT[] =
    {
        // U+51FA CJK UNIFIED IDEOGRAPH-51FA 出
        C(0xe5), C(0x87), C(0xba),
        // U+8EAB CJK UNIFIED IDEOGRAPH-8EAB 身
        C(0xe8), C(0xba), C(0xab),
        // U+306E HIRAGANA LETTER NO の
        C(0xe3), C(0x81), C(0xae),
        // U+7269 CJK UNIFIED IDEOGRAPH-7269 物
        C(0xe7), C(0x89), C(0xa9),
        // U+7406 CJK UNIFIED IDEOGRAPH-7406 理
        C(0xe7), C(0x90), C(0x86),
        // U+5316 CJK UNIFIED IDEOGRAPH-5316 化
        C(0xe5), C(0x8c), C(0x96),
        // U+5B66 CJK UNIFIED IDEOGRAPH-5B66 学
        C(0xe5), C(0xad), C(0xa6),
        // U+8005 CJK UNIFIED IDEOGRAPH-8005 者
        C(0xe8), C(0x80), C(0x85),
        // U+3001 IDEOGRAPHIC COMMA 、
        C(0xe3), C(0x80), C(0x81),
        // U+96FB CJK UNIFIED IDEOGRAPH-96FB 電
        C(0xe9), C(0x9b), C(0xbb),
        // U+6C17 CJK UNIFIED IDEOGRAPH-6C17 気
        C(0xe6), C(0xb0), C(0x97),
        // U+5316 CJK UNIFIED IDEOGRAPH-5316 化
        C(0xe5), C(0x8c), C(0x96),
        // U+5B66 CJK UNIFIED IDEOGRAPH-5B66 学
        C(0xe5), C(0xad), C(0xa6),
        // U+8005 CJK UNIFIED IDEOGRAPH-8005 者
        C(0xe8), C(0x80), C(0x85),
        // U+3002 IDEOGRAPHIC FULL STOP 。
        C(0xe3), C(0x80), C(0x82),
    };

    /*
     * A bit of a hack to keep tests simple: This assumes each of the
     * characters in this test takes SINGLE_CJK_CHAR_BYTES bytes.
     */
    static const size_t SINGLE_CJK_CHAR_BYTES = 3;

    static const char OUTPUT_TOKEN_00[] =
    {
            // U+51FA CJK UNIFIED IDEOGRAPH-51FA 出
            C(0xe5), C(0x87), C(0xba),
            // U+8EAB CJK UNIFIED IDEOGRAPH-8EAB 身
            C(0xe8), C(0xba), C(0xab),
    };
    static const char OUTPUT_TOKEN_01[] =
    {
            // U+8EAB CJK UNIFIED IDEOGRAPH-8EAB 身
            C(0xe8), C(0xba), C(0xab),
            // U+306E HIRAGANA LETTER NO の
            C(0xe3), C(0x81), C(0xae),
    };
    static const char OUTPUT_TOKEN_02[] =
    {
            // U+306E HIRAGANA LETTER NO の
            C(0xe3), C(0x81), C(0xae),
            // U+7269 CJK UNIFIED IDEOGRAPH-7269 物
            C(0xe7), C(0x89), C(0xa9),
    };
    static const char OUTPUT_TOKEN_03[] =
    {
            // U+7269 CJK UNIFIED IDEOGRAPH-7269 物
            C(0xe7), C(0x89), C(0xa9),
            // U+7406 CJK UNIFIED IDEOGRAPH-7406 理
            C(0xe7), C(0x90), C(0x86),
    };
    static const char OUTPUT_TOKEN_04[] =
    {
            // U+7406 CJK UNIFIED IDEOGRAPH-7406 理
            C(0xe7), C(0x90), C(0x86),
            // U+5316 CJK UNIFIED IDEOGRAPH-5316 化
            C(0xe5), C(0x8c), C(0x96),
    };
    static const char OUTPUT_TOKEN_05[] =
    {
            // U+5316 CJK UNIFIED IDEOGRAPH-5316 化
            C(0xe5), C(0x8c), C(0x96),
            // U+5B66 CJK UNIFIED IDEOGRAPH-5B66 学
            C(0xe5), C(0xad), C(0xa6),
    };
    static const char OUTPUT_TOKEN_06[] =
    {
            // U+5B66 CJK UNIFIED IDEOGRAPH-5B66 学
            C(0xe5), C(0xad), C(0xa6),
            // U+8005 CJK UNIFIED IDEOGRAPH-8005 者
            C(0xe8), C(0x80), C(0x85),
    };
    static const char OUTPUT_TOKEN_07[] =
    {
            // U+96FB CJK UNIFIED IDEOGRAPH-96FB 電
            C(0xe9), C(0x9b), C(0xbb),
            // U+6C17 CJK UNIFIED IDEOGRAPH-6C17 気
            C(0xe6), C(0xb0), C(0x97),
    };
    static const char OUTPUT_TOKEN_08[] =
    {
            // U+6C17 CJK UNIFIED IDEOGRAPH-6C17 気
            C(0xe6), C(0xb0), C(0x97),
            // U+5316 CJK UNIFIED IDEOGRAPH-5316 化
            C(0xe5), C(0x8c), C(0x96),
    };
    static const char OUTPUT_TOKEN_09[] =
    {
            // U+5316 CJK UNIFIED IDEOGRAPH-5316 化
            C(0xe5), C(0x8c), C(0x96),
            // U+5B66 CJK UNIFIED IDEOGRAPH-5B66 学
            C(0xe5), C(0xad), C(0xa6),
    };
    static const char OUTPUT_TOKEN_10[] =
    {
            // U+5B66 CJK UNIFIED IDEOGRAPH-5B66 学
            C(0xe5), C(0xad), C(0xa6),
            // U+8005 CJK UNIFIED IDEOGRAPH-8005 者
            C(0xe8), C(0x80), C(0x85),
    };

    static const Token OUTPUT_TOKENS[] =
    {
            {
                    OUTPUT_TOKEN_00,
                    ARRAY_SIZE(OUTPUT_TOKEN_00),
                    0*3,
                    0*3 + SINGLE_CJK_CHAR_BYTES // don't include last character
            },
            {
                    OUTPUT_TOKEN_01,
                    ARRAY_SIZE(OUTPUT_TOKEN_01),
                    1*3, // all the CJK test characters are 3 bytes long
                    1*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_02,
                    ARRAY_SIZE(OUTPUT_TOKEN_02),
                    2*3,
                    2*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_03,
                    ARRAY_SIZE(OUTPUT_TOKEN_03),
                    3*3,
                    3*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_04,
                    ARRAY_SIZE(OUTPUT_TOKEN_04),
                    4*3,
                    4*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_05,
                    ARRAY_SIZE(OUTPUT_TOKEN_05),
                    5*3,
                    5*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_06,
                    ARRAY_SIZE(OUTPUT_TOKEN_06),
                    6*3,
                    6*3 + ARRAY_SIZE(OUTPUT_TOKEN_06) // last before a separator -> include both chars
            },
            {
                    OUTPUT_TOKEN_07,
                    ARRAY_SIZE(OUTPUT_TOKEN_07),
                    9*3, // there it a comma between token 7 and 8 (comma + last pair -> 2 more chars)
                    9*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_08,
                    ARRAY_SIZE(OUTPUT_TOKEN_08),
                    10*3,
                    10*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_09,
                    ARRAY_SIZE(OUTPUT_TOKEN_09),
                    11*3,
                    11*3 + SINGLE_CJK_CHAR_BYTES
            },
            {
                    OUTPUT_TOKEN_10,
                    ARRAY_SIZE(OUTPUT_TOKEN_10),
                    12*3,
                    12*3 + ARRAY_SIZE(OUTPUT_TOKEN_10) // last before a separator -> include both chars
            },
    };

    NdsUnicode61Tokenizer tokenizer;
    EXPECT_EQ(true, tokenizer.open(0, NULL));
    NdsUnicode61Tokenizer::cursor* cur = tokenizer.getCursor(TEST_INPUT, ARRAY_SIZE(TEST_INPUT));
    EXPECT_EQ(true, cur != NULL);

    TestReturnedTokens(*cur, OUTPUT_TOKENS, ARRAY_SIZE(OUTPUT_TOKENS));

    delete cur;
    EXPECT_EQ(true, tokenizer.close());
}
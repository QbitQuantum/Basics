int main(int argc, char* argv[])
{
    int               test = argc > 1 ? atoi(argv[1]) : 0;
    int           verbose1 = argc > 2;
    int           verbose2 = argc > 3;
    int           verbose3 = argc > 4;
    int allocatorVerbosity = argc > 5;  // always the last

    bslma::TestAllocator defaultAllocator("default", allocatorVerbosity);
    bslma::Default::setDefaultAllocator(&defaultAllocator);

    bslma::TestAllocator globalAllocator("global", allocatorVerbosity);
    bslma::Default::setGlobalAllocator(&globalAllocator);

    cout << "TEST " << __FILE__ << " CASE " << test << endl;;

    bslma::TestAllocator  ta(allocatorVerbosity);
    bslma::TestAllocator *pa = &ta;

    typedef BDEC::DecimalConvertUtil Util;

    cout.precision(35);

    switch (test) { case 0:
    case 2: {
        // --------------------------------------------------------------------
        // TESTING Usage Examples
        // Concerns: Usage Examples build and work
        // Testing: Usage examples

        if (verbose1) bsl::cout << "\nTesting Usage Examples"
                                << "\n======================" << bsl::endl;

        if (verbose2) bsl::cout << "\nSending decimals as octets "
                                   "using network format" << bsl::endl;
        // Suppose you have two communicating entities (programs) that talk to
        // each other using a binary (as opposed to text) protocol.  In such
        // protocol it is important to establish a so-called network format,
        // and convert to and from that format in the protocol layer.  The
        // sender (suppose that it is an IBM server that has just finished an
        // expensive calculation involving millions of numbers and needs to
        // send the result to its client) will need to convert the data to
        // network format before sending:
        //..
        { // "server"
            unsigned char   msgbuffer[256];
            BDEC::Decimal64 number(BDLDFP_DECIMAL_DD(1.234567890123456e-42));
            unsigned char   expected[] = {
                              0x25, 0x55, 0x34, 0xb9, 0xc1, 0xe2, 0x8e, 0x56 };

            unsigned char *next = msgbuffer;
            next = bdldfp::DecimalConvertUtil::decimalToNetwork(next, number);

            ASSERT(memcmp(msgbuffer, expected, sizeof(number)) == 0);
        }
        //..
        // The receiver/client shall then restore the number from network
        // format:
        //..
        { // "client"
            unsigned char   msgbuffer[] ={
                              0x25, 0x55, 0x34, 0xb9, 0xc1, 0xe2, 0x8e, 0x56 };
            BDEC::Decimal64 number;
            BDEC::Decimal64 expected(BDLDFP_DECIMAL_DD(1.234567890123456e-42));

            unsigned char *next = msgbuffer;
            next = bdldfp::DecimalConvertUtil::decimalFromNetwork(&number, next);

            ASSERT(number == expected);
        }
        //..

        if (verbose2) bsl::cout << "\nStoring/sending decimals in binary"
                                    " floating-point" << bsl::endl;
        // Suppose you have two communicating entities (programs) that talk to
        // each other using a legacy protocol that employs binary
        // floating-point formats to send/receive numbers.  So your application
        // layer will have to store the decimal into a binary FP variable,
        // ensure that it can be restored (in other words that it has "fit"
        // into the binary type) when sending, and restore the decimal number
        // (from the binary type) when receiving:
        //..
        {
            const BDEC::Decimal64 number(
                                       BDLDFP_DECIMAL_DD(1.23456789012345e-42));

            double dbl = Util::decimalToDouble(number);

            if (Util::decimal64FromDouble(dbl) != number) {
                // Do what is appropriate for the application
            }
            //..
            // The receiver would then restore the number using the appropriate
            // 'decimal64FromDouble' function:
            //..
            BDEC::Decimal64 restored = Util::decimal64FromDouble(dbl);

            ASSERT(number == restored);
        }
        //..
    } break;

    case 1: {
        // --------------------------------------------------------------------
        // TESTING Breathing test
        // Concerns: Forwarding to the right routines
        // Plan: Try all operations see if basics work
        // Testing: all functions
        // --------------------------------------------------------------------

        if (verbose1) bsl::cout << "\nBreathing Test"
                                << "\n==============" << bsl::endl;

        if (verbose2) bsl::cout << "C++ Decimal FP to Binary FP" << bsl::endl;

        for (int i = 0; i < DEC2BIN_DATA_COUNT; ++i) {
            const DecBinTestCase& tc = DEC2BIN_DATA[i];

            BDEC::Decimal32  d32 (tc.d32());
            BDEC::Decimal64  d64 (tc.d64());
            BDEC::Decimal128 d128(tc.d128());
#define D2B_ASSERT(nn, fn, mn)                                                \
    LOOP3_ASSERT(tc.d_line, d##nn, Util::decimal##nn##To##fn(d##nn),          \
                            Util::decimal##nn##To##fn(d##nn) == tc.d_##mn);   \
    LOOP3_ASSERT(tc.d_line, d##nn, Util::decimalTo##fn(d##nn),                \
                            Util::decimalTo##fn(d##nn) == tc.d_##mn)
            if (tc.doD32()) {
                D2B_ASSERT(32, LongDouble, ld);
                D2B_ASSERT(32, Double, d);
                D2B_ASSERT(32, Float, f);

                D2B_ASSERT(64, LongDouble, ld);
                D2B_ASSERT(64, Double, d);
                D2B_ASSERT(64, Float, f);

                D2B_ASSERT(128, LongDouble, ld);
                D2B_ASSERT(128, Double, d);
                D2B_ASSERT(128, Float, f);
            }
#undef D2B_ASSERT
        }

        if (verbose2) bsl::cout << "Network format conversions" << bsl::endl;

        { // 32
            unsigned char n_d32[] = { 0x26, 0x54, 0xD2, 0xE7 };
            BDEC::Decimal32 h_d32(1234567);
            unsigned char buffer[sizeof(BDEC::Decimal32)];
            BDEC::Decimal32 d32;

            Util::decimalToNetwork(buffer, h_d32);
            ASSERT(0 == memcmp(n_d32, buffer, sizeof(n_d32)));

            Util::decimalFromNetwork(&d32, buffer);
            ASSERT(d32 == h_d32);
        }

        { // 64
            unsigned char n_d64[] = { 0x26, 0x39, 0x34, 0xB9,
                                      0xC1, 0xE2, 0x8E, 0x56 };
            BDEC::Decimal64 h_d64(1234567890123456ull);
            unsigned char buffer[sizeof(BDEC::Decimal64)];
            BDEC::Decimal64 d64;

            Util::decimalToNetwork(buffer, h_d64);
            ASSERT(0 == memcmp(n_d64, buffer, sizeof(n_d64)));

            Util::decimalFromNetwork(&d64, buffer);
            ASSERT(d64 == h_d64);
        }

        { // 128
            unsigned char n_d128[] = { 0x26, 0x08, 0x13, 0x4B,
                                       0x9C, 0x1E, 0x28, 0xE5,
                                       0x6F, 0x3C, 0x12, 0x71,
                                       0x77, 0x82, 0x35, 0x34,};
            BDEC::Decimal128 h_d128(
                        BDLDFP_DECIMAL_DL(1234567890123456789012345678901234.));
            unsigned char buffer[sizeof(BDEC::Decimal128)];
            BDEC::Decimal128 d128;

            Util::decimalToNetwork(buffer, h_d128);
            ASSERT(0 == memcmp(n_d128, buffer, sizeof(n_d128)));

            Util::decimalFromNetwork(&d128, buffer);
            ASSERT(d128 == h_d128);
        }

        if (verbose2) bsl::cout << "Decimal-binary-decimal trip" << bsl::endl;

        // No guarantees if these aren't binary:

        if (std::numeric_limits<long double>::radix == 2 &&
            std::numeric_limits<     double>::radix == 2 &&
            std::numeric_limits<      float>::radix == 2)
        {
            if (verbose3) bsl::cout << "Decimal32" << bsl::endl;
            {
                BDEC::Decimal32 original;

                long double bin_ld;  // Carrier binaries
                double      bin_d;
                float       bin_f;

                BDEC::Decimal32  restored;

                // Testing 0.0

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing -0.0

                original = -original;

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 1.0

                original = BDLDFP_DECIMAL_DF(1.);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.1

                original = BDLDFP_DECIMAL_DF(0.1);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.2

                original = BDLDFP_DECIMAL_DF(0.2);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.3

                original = BDLDFP_DECIMAL_DF(0.3);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.123456

                original = BDLDFP_DECIMAL_DF(0.123456);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.1234567 -- float cannot do that

                original = BDLDFP_DECIMAL_DF(0.1234567);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                // Testing Dec32-max

                original = std::numeric_limits<BDEC::Decimal32>::max();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                // Testing Dec32-min -- float cannot do that

                original = std::numeric_limits<BDEC::Decimal32>::min();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                // Testing Dec32-denorm_min -- float cannot do that

                original = std::numeric_limits<BDEC::Decimal32>::denorm_min();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                // Testing NaN

                original = std::numeric_limits<BDEC::Decimal32>::quiet_NaN();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(restored != restored);

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(restored != restored);

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(restored != restored);

                // Testing +INF

                original = std::numeric_limits<BDEC::Decimal32>::infinity();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing -INF

                original = -original;

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal32FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal32FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));
            }

            if (verbose3) bsl::cout << "Decimal64" << bsl::endl;
            {
                BDEC::Decimal64 original;

                long double bin_ld;  // Carrier binaries
                double      bin_d;
                float       bin_f;

                BDEC::Decimal64  restored;

                // Testing 0.0

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing -0.0

                original = -original;

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 1.0

                original = BDLDFP_DECIMAL_DD(1.);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.1

                original = BDLDFP_DECIMAL_DD(0.1);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.2

                original = BDLDFP_DECIMAL_DD(0.2);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.3

                original = BDLDFP_DECIMAL_DD(0.3);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.123456 - the last that shall fit a float

                original = BDLDFP_DECIMAL_DD(0.123456);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.123456789012345 - the last that shall fit a double

                original = BDLDFP_DECIMAL_DD(0.123456789012345);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                if (sizeof(double) < sizeof(long double)) {
                    // Testing 0.1234567890123456 -- Need 128 bits in binary

                    original = BDLDFP_DECIMAL_DD(0.1234567890123456);

                    bin_ld  = Util::decimalToLongDouble(original);

                    restored = Util::decimal64FromLongDouble(bin_ld);
                    ASSERT(strictEqual(original, restored));

                    // Testing Dec64-max  -- won't fit in a double or float

                    original = std::numeric_limits<BDEC::Decimal64>::max();

                    bin_ld  = Util::decimalToLongDouble(original);

                    restored = Util::decimal64FromLongDouble(bin_ld);
                    ASSERT(strictEqual(original, restored));

                    // Testing Dec64-min -- double, float cannot do that

                    original = std::numeric_limits<BDEC::Decimal64>::min();

                    bin_ld  = Util::decimalToLongDouble(original);

                    restored = Util::decimal64FromLongDouble(bin_ld);
                    ASSERT(strictEqual(original, restored));

                    // Testing Dec64-denorm_min -- float/double cannot do that

                    original =
                            std::numeric_limits<BDEC::Decimal64>::denorm_min();

                    bin_ld  = Util::decimalToLongDouble(original);

                    restored = Util::decimal64FromLongDouble(bin_ld);
                    ASSERT(strictEqual(original, restored));
                }

                // Testing NaN

                original = std::numeric_limits<BDEC::Decimal64>::quiet_NaN();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(restored != restored);

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(restored != restored);

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(restored != restored);

                // Testing +INF

                original = std::numeric_limits<BDEC::Decimal64>::infinity();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing -INF

                original = -original;

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal64FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal64FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));
            }

            if (verbose3) bsl::cout << "Decimal128" << bsl::endl;
            {
                BDEC::Decimal128 original;

                long double bin_ld;  // Carrier binaries
                double      bin_d;
                float       bin_f;

                BDEC::Decimal128  restored;

                // Testing 0.0

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing -0.0

                original = -original;

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 1.0

                original = BDLDFP_DECIMAL_DL(1.);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.1

                original = BDLDFP_DECIMAL_DL(0.1);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.2

                original = BDLDFP_DECIMAL_DL(0.2);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.3

                original = BDLDFP_DECIMAL_DL(0.3);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.123456 - the last that shall fit a float

                original = BDLDFP_DECIMAL_DL(0.123456);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing 0.123456789012345 - the last that shall fit a double

                original = BDLDFP_DECIMAL_DL(0.123456789012345);

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                if (sizeof(double) < sizeof(long double)) {
                    // Testing 0.1234567890123456 -- Need 128 bits in binary

                    original = BDLDFP_DECIMAL_DL(0.1234567890123456);

                    bin_ld  = Util::decimalToLongDouble(original);

                    restored = Util::decimal128FromLongDouble(bin_ld);
                    ASSERT(strictEqual(original, restored));

                    // Testing Dec128-max  -- won't fit into anything

                    // Testing Dec128-min  -- won't fit into anything

                    // Testing Dec128-denorm_min -- won't fit into anything
                }

                // Testing NaN

                original = std::numeric_limits<BDEC::Decimal128>::quiet_NaN();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(restored != restored);

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(restored != restored);

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(restored != restored);

                // Testing +INF

                original = std::numeric_limits<BDEC::Decimal128>::infinity();

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));

                // Testing -INF

                original = -original;

                bin_ld  = Util::decimalToLongDouble(original);
                bin_d   = Util::decimalToDouble(original);
                bin_f   = Util::decimalToFloat(original);

                restored = Util::decimal128FromLongDouble(bin_ld);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromDouble(bin_d);
                ASSERT(strictEqual(original, restored));

                restored = Util::decimal128FromFloat(bin_f);
                ASSERT(strictEqual(original, restored));
            }
        }
        else {
            if (verbose2) bsl::cout << "Skipped, no binary FP" << bsl::endl;
        }

    } break;


    default: {
        cerr << "WARNING: CASE '" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    // CONCERN: No memory came from the global or default allocator.

    LOOP2_ASSERT(test, globalAllocator.numBlocksTotal(),
                 0 == globalAllocator.numBlocksTotal());
    LOOP2_ASSERT(test, defaultAllocator.numBlocksTotal(),
                 0 == defaultAllocator.numBlocksTotal());

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
    }

    return testStatus;
}
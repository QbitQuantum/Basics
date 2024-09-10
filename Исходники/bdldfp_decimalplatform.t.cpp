int main(int argc, char* argv[])
{
    int               test = argc > 1 ? atoi(argv[1]) : 0;
    int           verbose1 = argc > 2;
    int           verbose2 = argc > 3;
    int           verbose3 = argc > 4;

    cout << "TEST " << __FILE__ << " CASE " << test << endl;;

    switch (test) { case 0:
    case 4: {
        // --------------------------------------------------------------------
        // TESTING macros define a configuration according to component
        // contract
        //
        // Concerns:
        //: 1 Pairs of macros that promise mutally exclusive values (1 and 0)
        //:   actually have mutually exclusive values
        //:
        //: 2 All promised macros are present.
        //:
        //: 3 Any macros which are optional are present as a full group.
        //:
        //: 4 Any macros which evaluate to an expression produce the correct
        //:   expression.  (These are the NaN variants)
        //:
        //:   1 Any NaN expression should compare inequal to itself.
        //:
        //:   2 Any NaN expressions which are intended for different types
        //:     should actually have distinct types at compile time.
        //:
        //:   3 Any NaN expressions which are intended for the same type should
        //:     have the same compile-time type.
        //:
        //:   4 Any two NaN expressions for the same type with different
        //:     semantics should have a different bit pattern (representation),
        //:     thus implying different runtime semantics.
        //:
        //:   5 [Untestable at this time] Any NaN expressions evaluates to a
        //:     value with the intended semantics (i.e.: signalling vs.
        //:     quiet).
        //
        // Plan:
        //: 1 Assert on unexpected combinations C1-2
        //:
        //: 2 (Optionally compiled) Enumerate all pairings of optional NaN
        //:   expression variants for correct type and no identical bit
        //:   patterns between different expressions. C3, C4.1-4.4
        // --------------------------------------------------------------------
        if (verbose1) bsl::cout << "\nTesting for Valid Configuration"
                                << "\n==============================="
                                << bsl::endl;
        ASSERT(BDLDFP_DECIMALPLATFORM_C99_TR +
               BDLDFP_DECIMALPLATFORM_DECNUMBER == 1);

        ASSERT(BDLDFP_DECIMALPLATFORM_HARDWARE +
               BDLDFP_DECIMALPLATFORM_SOFTWARE == 1);

        ASSERT(BDLDFP_DECIMALPLATFORM_BIG_ENDIAN +
               BDLDFP_DECIMALPLATFORM_LITTLE_ENDIAN == 1);

        ASSERT(BDLDFP_DECIMALPLATFORM_DPD +
               BDLDFP_DECIMALPLATFORM_BININT == 1);

        #ifndef BDLDFP_DECIMALPLATFORM_SNPRINTF_BUFFER_SIZE
            ASSERT(!"BDLDFP_DECIMALPLATFORM_SNPRINTF_BUFFER_SIZE"
                    " is not defined!");
        #endif

        // NaN macros must exist, and be valid NaN objects, by not comparing
        // equal:

        #if BDLDFP_DECIMALPLATFORM_C99_TR
            #ifndef BDLDFP_DECIMALPLATFORM_C99_QNAN32
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_QNAN32 is not defined!");
            #else
                ASSERT(BDLDFP_DECIMALPLATFORM_C99_QNAN32
                                         != BDLDFP_DECIMALPLATFORM_C99_QNAN32);
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_QNAN64
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_QNAN64 is not defined!");
            #else
                ASSERT(BDLDFP_DECIMALPLATFORM_C99_QNAN64
                                         != BDLDFP_DECIMALPLATFORM_C99_QNAN64);
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_QNAN128
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_QNAN128 is not defined!");
            #else
                ASSERT(BDLDFP_DECIMALPLATFORM_C99_QNAN128
                                        != BDLDFP_DECIMALPLATFORM_C99_QNAN128);
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_SNAN32
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_SNAN32 is not defined!");
            #else
                ASSERT(BDLDFP_DECIMALPLATFORM_C99_SNAN32
                                         != BDLDFP_DECIMALPLATFORM_C99_SNAN32);
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_SNAN64
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_SNAN64 is not defined!");
            #else
                ASSERT(BDLDFP_DECIMALPLATFORM_C99_SNAN64
                                         != BDLDFP_DECIMALPLATFORM_C99_SNAN64);
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_SNAN128
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_SNAN128 is not defined!");
            #else
                ASSERT(BDLDFP_DECIMALPLATFORM_C99_SNAN128
                                        != BDLDFP_DECIMALPLATFORM_C99_SNAN128);
            #endif

            #if defined(BDLDFP_DECIMALPLATFORM_C99_QNAN32) \
             && defined(BDLDFP_DECIMALPLATFORM_C99_SNAN32) \
             && defined(BDLDFP_DECIMALPLATFORM_C99_QNAN64) \
             && defined(BDLDFP_DECIMALPLATFORM_C99_SNAN64) \
             && defined(BDLDFP_DECIMALPLATFORM_C99_QNAN128) \
             && defined(BDLDFP_DECIMALPLATFORM_C99_SNAN128)

                // qNaN32 must be different from all other larger variants
                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99QNAN64));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99SNAN64));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99QNAN128));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99SNAN128));


                // sNaN32 must be different from all other larger variants
                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99SNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99QNAN64));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99SNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99SNAN64));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99SNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99QNAN128));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99SNAN32,
                                      BDLDFP_DECIMALPLATFORM_C99SNAN128));

                // qNaN64 must be different from all other larger variants

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN64,
                                      BDLDFP_DECIMALPLATFORM_C99QNAN128));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN64,
                                      BDLDFP_DECIMALPLATFORM_C99SNAN128));

                // sNaN64 must be different from all other larger variants

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN64,
                                      BDLDFP_DECIMALPLATFORM_C99QNAN128));

                ASSERT(differentTypes(BDLDFP_DECIMALPLATFORM_C99QNAN64,
                                      BDLDFP_DECIMALPLATFORM_C99SNAN128));


                // sNaN and qNaN expressions should be different bit patterns:

                ASSERT(differentBits(BDLDFP_DECIMALPLATFORM_C99_SNAN32,
                                     BDLDFP_DECIMALPLATFORM_C99_QNAN32));

                ASSERT(differentBits(BDLDFP_DECIMALPLATFORM_C99_SNAN64,
                                     BDLDFP_DECIMALPLATFORM_C99_QNAN64));

                ASSERT(differentBits(BDLDFP_DECIMALPLATFORM_C99_SNAN128,
                                     BDLDFP_DECIMALPLATFORM_C99_QNAN128));

            #endif
        #endif
    } break;

    case 3: {
        // --------------------------------------------------------------------
        // TESTING 'differentBits' testing support function.
        //
        // Concerns:
        //: 1 Identical expressions (yielding identical bit patterns) should
        //:   compare the same.
        //:
        //: 2 Differing expressions (yielding different bit patterns) should
        //:   compare differently.
        //
        // Plan:
        //: 1 'int', 'float', and 'bool' expressions will be tested.  (The
        //:   function is an adaptible template.)
        //:
        //: 2 Boolean conjunction will be used as the expression operator for
        //:   'bool'.
        //:
        //: 3 Addition will be used as the expression operator for 'int' and
        //:   'float'.
        //:
        //: 4 Types will only be tested against themselves.  (No other forms
        //:   should compile.)
        //:
        //: 5 All permutations of 1 and 2 variable-combining expressions will
        //:   be tested for correctness, among all 3 permutations of types.
        //:
        //: 6 Two representative values will be tested for each above case (two
        //:   different expressions).  All permutations of these values will be
        //:   tested.
        // --------------------------------------------------------------------

        // int, int:
        ASSERT(!differentBits( 1,  1));
        ASSERT( differentBits( 1, 42));
        ASSERT( differentBits(42,  1));
        ASSERT(!differentBits(42, 42));

        ASSERT( differentBits( 1, 1 +  1));
        ASSERT( differentBits( 1, 1 + 42));
        ASSERT( differentBits(42, 1 +  1));
        ASSERT( differentBits(42, 1 + 42));

        ASSERT(!differentBits( 2, 1 +  1));
        ASSERT(!differentBits(43, 1 + 42));

        ASSERT( differentBits(1 +  1,  1));
        ASSERT( differentBits(1 +  1, 42));
        ASSERT( differentBits(1 + 42,  1));
        ASSERT( differentBits(1 + 42, 42));

        ASSERT(!differentBits(1 +  1,  2));
        ASSERT(!differentBits(1 + 42, 43));

        ASSERT(!differentBits(1 +  1, 1 +  1));
        ASSERT( differentBits(1 +  1, 1 + 42));
        ASSERT( differentBits(1 + 42, 1 +  1));
        ASSERT(!differentBits(1 + 42, 1 + 42));
    } break;

    case 2: {
        // --------------------------------------------------------------------
        // TESTING 'differentTypes' testing support function.
        //
        // Concerns:
        //: 1 Same types should compare same.
        //:
        //: 2 Different types should compare different.
        //:
        //: 3 Convertible/compatible types should compare different.
        //:
        //: 4 Different types on lhs and rhs should compare different, in both
        //:   permutations.
        //:
        //: 5 Complicated expressions should have correct type evaluation.
        //
        // Plan:
        //: 1 'int's, 'float's, and 'bool's will be tested as three distinct
        //:   types.
        //:
        //: 2 Boolean conjunction will be used as the expression operator for
        //:   'bool's.
        //:
        //: 3 Addition will be used as the expression operator for 'int's and
        //:   'float's.
        //:
        //: 4 All permutation pairings of the three types will be tested for
        //:   correctness with the contract:
        //:   o int,   int
        //:   o int,   bool
        //:   o int,   float
        //:   o bool,  int
        //:   o bool,  bool
        //:   o bool,  float
        //:   o float, int
        //:   o float, bool
        //:   o float, float
        //:
        //: 5 All permutations of 1 and 2 variable-combining expressions will
        //:   be tested for correctness, among all 9 permutations of types.
        //:
        //: 6 Two representative values will be tested for each above case (two
        //:   different expressions).  All permutations of these values will be
        //:   tested.
        // --------------------------------------------------------------------

        // int, int:
        ASSERT(!differentTypes( 1,  1));
        ASSERT(!differentTypes( 1, 42));
        ASSERT(!differentTypes(42,  1));
        ASSERT(!differentTypes(42, 42));

        ASSERT(!differentTypes( 1, 1 +  1));
        ASSERT(!differentTypes( 1, 1 + 42));
        ASSERT(!differentTypes(42, 1 +  1));
        ASSERT(!differentTypes(42, 1 + 42));

        ASSERT(!differentTypes(1 +  1,  1));
        ASSERT(!differentTypes(1 +  1, 42));
        ASSERT(!differentTypes(1 + 42,  1));
        ASSERT(!differentTypes(1 + 42, 42));

        ASSERT(!differentTypes(1 +  1, 1 +  1));
        ASSERT(!differentTypes(1 +  1, 1 + 42));
        ASSERT(!differentTypes(1 + 42, 1 +  1));
        ASSERT(!differentTypes(1 + 42, 1 + 42));

        // int, bool:
        ASSERT( differentTypes( 1,  true));
        ASSERT( differentTypes( 1, false));
        ASSERT( differentTypes(42,  true));
        ASSERT( differentTypes(42, false));

        ASSERT( differentTypes( 1, true &&  true));
        ASSERT( differentTypes( 1, true && false));
        ASSERT( differentTypes(42, true &&  true));
        ASSERT( differentTypes(42, true && false));

        ASSERT( differentTypes(1 +  1,  true));
        ASSERT( differentTypes(1 +  1, false));
        ASSERT( differentTypes(1 + 42,  true));
        ASSERT( differentTypes(1 + 42, false));

        ASSERT( differentTypes(1 +  1, true &&  true));
        ASSERT( differentTypes(1 +  1, true && false));
        ASSERT( differentTypes(1 + 42, true &&  true));
        ASSERT( differentTypes(1 + 42, true && false));

        // int, float:
        ASSERT( differentTypes( 1,  1.0f));
        ASSERT( differentTypes( 1, 42.0f));
        ASSERT( differentTypes(42,  1.0f));
        ASSERT( differentTypes(42, 42.0f));

        ASSERT( differentTypes( 1, 1.0f +  1.0f));
        ASSERT( differentTypes( 1, 1.0f + 42.0f));
        ASSERT( differentTypes(42, 1.0f +  1.0f));
        ASSERT( differentTypes(42, 1.0f + 42.0f));

        ASSERT( differentTypes(1 +  1,  1.0f));
        ASSERT( differentTypes(1 +  1, 42.0f));
        ASSERT( differentTypes(1 + 42,  1.0f));
        ASSERT( differentTypes(1 + 42, 42.0f));

        ASSERT( differentTypes(1 +  1, 1.0f +  1.0f));
        ASSERT( differentTypes(1 +  1, 1.0f + 42.0f));
        ASSERT( differentTypes(1 + 42, 1.0f +  1.0f));
        ASSERT( differentTypes(1 + 42, 1.0f + 42.0f));

        // bool, int
        ASSERT( differentTypes( true,  1));
        ASSERT( differentTypes( true, 42));
        ASSERT( differentTypes(false,  1));
        ASSERT( differentTypes(false, 42));

        ASSERT( differentTypes( true, 1 +  1));
        ASSERT( differentTypes( true, 1 + 42));
        ASSERT( differentTypes(false, 1 +  1));
        ASSERT( differentTypes(false, 1 + 42));

        ASSERT( differentTypes( true && false,  1));
        ASSERT( differentTypes( true && false, 42));
        ASSERT( differentTypes(false &&  true,  1));
        ASSERT( differentTypes(false &&  true, 42));

        ASSERT( differentTypes( true && false, 1 +  1));
        ASSERT( differentTypes( true && false, 1 + 42));
        ASSERT( differentTypes(false &&  true, 1 +  1));
        ASSERT( differentTypes(false &&  true, 1 + 42));

        // bool, bool
        ASSERT(!differentTypes( true,  true));
        ASSERT(!differentTypes( true, false));
        ASSERT(!differentTypes(false,  true));
        ASSERT(!differentTypes(false, false));

        ASSERT(!differentTypes( true,  true && false));
        ASSERT(!differentTypes( true, false &&  true));
        ASSERT(!differentTypes(false,  true && false));
        ASSERT(!differentTypes(false, false &&  true));

        ASSERT(!differentTypes( true && false,  true));
        ASSERT(!differentTypes( true && false, false));
        ASSERT(!differentTypes(false &&  true,  true));
        ASSERT(!differentTypes(false &&  true, false));

        ASSERT(!differentTypes( true && false,  true && false));
        ASSERT(!differentTypes( true && false, false &&  true));
        ASSERT(!differentTypes(false &&  true,  true && false));
        ASSERT(!differentTypes(false &&  true, false &&  true));

        // bool, float
        ASSERT( differentTypes( true,  1.0f));
        ASSERT( differentTypes( true, 42.0f));
        ASSERT( differentTypes(false,  1.0f));
        ASSERT( differentTypes(false, 42.0f));

        ASSERT( differentTypes( true, 1.0f +  1.0f));
        ASSERT( differentTypes( true, 1.0f + 42.0f));
        ASSERT( differentTypes(false, 1.0f +  1.0f));
        ASSERT( differentTypes(false, 1.0f + 42.0f));

        ASSERT( differentTypes( true && false,  1.0f));
        ASSERT( differentTypes( true && false, 42.0f));
        ASSERT( differentTypes(false &&  true,  1.0f));
        ASSERT( differentTypes(false &&  true, 42.0f));

        ASSERT( differentTypes( true && false, 1.0f +  1.0f));
        ASSERT( differentTypes( true && false, 1.0f + 42.0f));
        ASSERT( differentTypes(false &&  true, 1.0f +  1.0f));
        ASSERT( differentTypes(false &&  true, 1.0f + 42.0f));

        // float, int
        ASSERT( differentTypes( 1.0f,  1));
        ASSERT( differentTypes( 1.0f, 42));
        ASSERT( differentTypes(42.0f,  1));
        ASSERT( differentTypes(42.0f, 42));

        ASSERT( differentTypes( 1.0f, 1 &&  1));
        ASSERT( differentTypes( 1.0f, 1 && 42));
        ASSERT( differentTypes(42.0f, 1 &&  1));
        ASSERT( differentTypes(42.0f, 1 && 42));

        ASSERT( differentTypes(1.0f +  1.0f,  1));
        ASSERT( differentTypes(1.0f +  1.0f, 42));
        ASSERT( differentTypes(1.0f + 42.0f,  1));
        ASSERT( differentTypes(1.0f + 42.0f, 42));

        ASSERT( differentTypes(1.0f +  1.0f, 1 &&  1));
        ASSERT( differentTypes(1.0f +  1.0f, 1 && 42));
        ASSERT( differentTypes(1.0f + 42.0f, 1 &&  1));
        ASSERT( differentTypes(1.0f + 42.0f, 1 && 42));

        // float, bool
        ASSERT( differentTypes( 1.0f,  true));
        ASSERT( differentTypes( 1.0f, false));
        ASSERT( differentTypes(42.0f,  true));
        ASSERT( differentTypes(42.0f, false));

        ASSERT( differentTypes( 1.0f,  true && false));
        ASSERT( differentTypes( 1.0f, false &&  true));
        ASSERT( differentTypes(42.0f,  true && false));
        ASSERT( differentTypes(42.0f, false &&  true));

        ASSERT( differentTypes(1.0f +  1.0f,  true));
        ASSERT( differentTypes(1.0f +  1.0f, false));
        ASSERT( differentTypes(1.0f + 42.0f,  true));
        ASSERT( differentTypes(1.0f + 42.0f, false));

        ASSERT( differentTypes(1.0f +  1.0f,  true && false));
        ASSERT( differentTypes(1.0f +  1.0f, false &&  true));
        ASSERT( differentTypes(1.0f + 42.0f,  true && false));
        ASSERT( differentTypes(1.0f + 42.0f, false &&  true));

        // float, float
        ASSERT(!differentTypes( 1.0f,  1.0f));
        ASSERT(!differentTypes( 1.0f, 42.0f));
        ASSERT(!differentTypes(42.0f,  1.0f));
        ASSERT(!differentTypes(42.0f, 42.0f));

        ASSERT(!differentTypes( 1.0f, 1.0f +  1.0f));
        ASSERT(!differentTypes( 1.0f, 1.0f + 42.0f));
        ASSERT(!differentTypes(42.0f, 1.0f +  1.0f));
        ASSERT(!differentTypes(42.0f, 1.0f + 42.0f));

        ASSERT(!differentTypes(1.0f +  1.0f,  1.0f));
        ASSERT(!differentTypes(1.0f +  1.0f, 42.0f));
        ASSERT(!differentTypes(1.0f + 42.0f,  1.0f));
        ASSERT(!differentTypes(1.0f + 42.0f, 42.0f));

        ASSERT(!differentTypes(1.0f +  1.0f, 1.0f +  1.0f));
        ASSERT(!differentTypes(1.0f +  1.0f, 1.0f + 42.0f));
        ASSERT(!differentTypes(1.0f + 42.0f, 1.0f +  1.0f));
        ASSERT(!differentTypes(1.0f + 42.0f, 1.0f + 42.0f));
    } break;

    case 1: {
        // --------------------------------------------------------------------
        // TESTING macros define an expected/sane configuration
        // Concerns: No configs we did not think of.
        // Plan: Assert on unexpected combinations
        // Testing:
        // --------------------------------------------------------------------
        if (verbose1) bsl::cout << "\nTesting Sane Configuration is Reported"
                                << "\n======================================"
                                << bsl::endl;
        ASSERT(BDLDFP_DECIMALPLATFORM_C99_TR +
               BDLDFP_DECIMALPLATFORM_DECNUMBER == 1);

        ASSERT(BDLDFP_DECIMALPLATFORM_HARDWARE +
               BDLDFP_DECIMALPLATFORM_SOFTWARE == 1);

        #ifndef BDLDFP_DECIMALPLATFORM_SNPRINTF_BUFFER_SIZE
            ASSERT(!"BDLDFP_DECIMALPLATFORM_SNPRINTF_BUFFER_SIZE"
                    " is not defined!");
        #endif

        #if BDLDFP_DECIMALPLATFORM_C99_TR
            #ifndef BDLDFP_DECIMALPLATFORM_C99_QNAN32
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_QNAN32 is not defined!");
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_QNAN64
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_QNAN64 is not defined!");
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_QNAN128
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_QNAN128 is not defined!");
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_SNAN32
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_SNAN32 is not defined!");
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_SNAN64
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_SNAN64 is not defined!");
            #endif
            #ifndef BDLDFP_DECIMALPLATFORM_C99_SNAN128
                ASSERT(!"BDLDFP_DECIMALPLATFORM_C99_SNAN128 is not defined!");
            #endif
        #endif
    } break;

    default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
    }

    return testStatus;
}
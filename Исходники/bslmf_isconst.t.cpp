int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    int veryVerbose = argc > 3;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:
      case 2: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //
        // Concerns:
        //: 1 The usage example provided in the component header file compiles,
        //:   links, and runs as shown.
        //
        // Plan:
        //: 1 Incorporate usage example from header into test driver, remove
        //:   leading comment characters, and replace 'assert' with 'ASSERT'.
        //:   (C-1)
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) printf("\nUSAGE EXAMPLE\n"
                            "\n=============\n");

///Usage
///-----
// In this section we show intended use of this component.
//
///Example 1: Verify 'Const' Types
///- - - - - - - - - - - - - - - -
// Suppose that we want to assert whether a particular type is a
// 'const'-qualified.
//
// First, we create two 'typedef's -- a 'const'-qualified type and a
// unqualified type:
//..
        typedef int        MyType;
        typedef const int  MyConstType;
//..
// Now, we instantiate the 'bsl::is_const' template for each of the
// 'typedef's and assert the 'value' static data member of each instantiation:
//..
        ASSERT(false == bsl::is_const<MyType>::value);
        ASSERT(true == bsl::is_const<MyConstType>::value);
//..

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // 'bsl::is_const::value'
        //   Ensure that the static data member 'value' of 'bsl::is_const'
        //   instantiations having various (template parameter) 'TYPES' has the
        //   correct value.
        //
        // Concerns:
        //: 1 'is_const::value' is 'false' when 'TYPE' is a (possibly
        //:   'volatile'-qualified) type.
        //:
        //: 2 'is_const::value' is 'true' when 'TYPE' is a 'const'-qualified or
        //:    cv-qualified type.
        //
        // Plan:
        //   Verify that 'bsl::is_const::value' has the correct value for
        //   each (template parameter) 'TYPE' in the concerns.
        //
        // Testing:
        //   bsl::is_const::value
        // --------------------------------------------------------------------

        if (verbose) printf("\nbsl::is_const::value\n"
                            "\n====================\n");

        // C-1
        ASSERT(false == is_const<int>::value);
        ASSERT(false == is_const<int volatile>::value);

        ASSERT(false == is_const<TestType>::value);
        ASSERT(false == is_const<TestType volatile>::value);

        // C-2
        ASSERT(true == is_const<int const>::value);
        ASSERT(true == is_const<int const volatile>::value);

        ASSERT(true == is_const<TestType const>::value);
        ASSERT(true == is_const<TestType const volatile>::value);
      } break;
      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
    }

    return testStatus;
}
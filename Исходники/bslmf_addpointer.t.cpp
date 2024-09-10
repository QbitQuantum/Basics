int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    int veryVerbose = argc > 3;

    (void) verbose;
    (void) veryVerbose;

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
///Example 1: Transform Type to Pointer Type to that Type
/// - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Suppose that we want to transform a type to a pointer type to that type.
//
// First, we create two 'typedef's -- a pointer type ('MyPtrType')
// and the type pointed to by the pointer type ('MyType'):
//..
        typedef int   MyType;
        typedef int * MyPtrType;
//..
// Now, we transform 'MyType' to a pointer type to 'MyType' using
// 'bsl::add_pointer' and verify that the resulting type is the same as
// 'MyPtrType':
//..
        ASSERT((bsl::is_same<bsl::add_pointer<MyType>::type,
                             MyPtrType>::value));
//..

      } break;
      case 1: {
        // --------------------------------------------------------------------
        // 'bsl::add_pointer::type'
        //   Ensure that the 'typedef' 'type' of 'bsl::add_pointer' has the
        //   correct type for a variety of template parameter types.
        //
        // Concerns:
        //: 1 'bsl::add_pointer' transforms a non-reference type to a pointer
        //:   type pointing to the original type.
        //:
        //: 2 'bsl::add_pointer' transforms a reference type to a pointer
        //:   type pointing to the type referred to by the reference type.
        //
        // Plan:
        //   Verify that 'bsl::add_pointer::type' has the correct type for
        //   each concern.
        //
        // Testing:
        //   bsl::remove_pointer::type
        // --------------------------------------------------------------------

        if (verbose) printf("\nbsl::add_pointer::type\n"
                            "\n======================\n");

        // C-1
        ASSERT((is_same<add_pointer<int>::type, int *>::value));
        ASSERT((is_same<add_pointer<int const>::type, int const *>::value));
        ASSERT((is_same<add_pointer<int *>::type, int **>::value));
        ASSERT((is_same<add_pointer<TestType>::type, TestType *>::value));

        // C-2
        ASSERT((is_same<add_pointer<int &>::type, int *>::value));
        ASSERT((is_same<add_pointer<int const &>::type, int const *>::value));
        ASSERT((is_same<add_pointer<TestType &>::type, TestType *>::value));

#if defined(BSLS_COMPILERFEATURES_SUPPORT_RVALUE_REFERENCES)
        ASSERT((is_same<add_pointer<int &&>::type, int *>::value));
        ASSERT((is_same<add_pointer<int const &&>::type, int const *>::value));
#endif
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
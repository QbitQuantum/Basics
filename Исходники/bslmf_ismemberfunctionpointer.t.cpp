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

        if (verbose) printf("USAGE EXAMPLE\n"
                            "=============\n");
// Now, we create two 'typedef's -- a function pointer type and a member
// function pointer type:
//..
    typedef int (MyStruct::*MyStructMethodPtr) ();
    typedef int (*MyFunctionPtr) ();
//..
// Finally, we instantiate the 'bsl::is_member_function_pointer' template for
// each of the 'typedef's and assert the 'value' static data member of each
// instantiation:
//..
    ASSERT(false == bsl::is_member_function_pointer<MyFunctionPtr    >::value);
    ASSERT(true  == bsl::is_member_function_pointer<MyStructMethodPtr>::value);
//..
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // 'bsl::is_member_function_pointer::value'
        //   Ensure that the static data member 'value' of
        //   'bsl::is_member_function_pointer' instantiations having various
        //   (template parameter) 'TYPES' has the correct value.
        //
        // Concerns:
        //: 1 'is_member_function_pointer::value' is 'false' when 'TYPE' is a
        //:   (possibly cv-qualified) primitive type.
        //:
        //: 2 'is_member_function_pointer::value' is 'false' when 'TYPE' is a
        //:   (possibly cv-qualified) user-defined type.
        //:
        //: 3 'is_member_function_pointer::value' is 'false' when 'TYPE' is a
        //:   (possibly cv-qualified) pointer type other than a non-static
        //:   member function pointer.
        //:
        //: 4 'is_member_function_pointer::value' is 'true' when 'TYPE' is a
        //:   (possibly cv-qualified) non-static member function pointer type.
        //:
        //: 5 'is_member_function_pointer::value' is 'false' when 'TYPE' is a
        //:   (possibly cv-qualified) function type.
        //
        // Plan:
        //   Verify that 'bsl::is_member_function_pointer::value' has the
        //   correct value for each (template parameter) 'TYPE' in the
        //   concerns.
        //
        // Testing:
        //   bsl::is_member_function_pointer::value
        // --------------------------------------------------------------------

        if (verbose) printf("bsl::is_member_function_pointer\n"
                            "===============================\n");

        // C-1
        TYPE_ASSERT_CVQ_SUFFIX(bsl::is_member_function_pointer, void, false);
        TYPE_ASSERT_CVQ_SUFFIX(bsl::is_member_function_pointer, int,  false);
        TYPE_ASSERT_CVQ_REF   (bsl::is_member_function_pointer, int,  false);

        // C-2
        TYPE_ASSERT_CVQ_SUFFIX(
                 bsl::is_member_function_pointer, EnumTestType,         false);
        TYPE_ASSERT_CVQ_SUFFIX(
                 bsl::is_member_function_pointer, StructTestType,       false);
        TYPE_ASSERT_CVQ_REF   (
                 bsl::is_member_function_pointer, StructTestType,       false);
        TYPE_ASSERT_CVQ_SUFFIX(
                 bsl::is_member_function_pointer, UnionTestType,        false);
        TYPE_ASSERT_CVQ_REF   (
                 bsl::is_member_function_pointer, UnionTestType,        false);
        TYPE_ASSERT_CVQ_SUFFIX(
                 bsl::is_member_function_pointer, Incomplete,           false);
        TYPE_ASSERT_CVQ_REF   (
                 bsl::is_member_function_pointer, Incomplete,           false);
        TYPE_ASSERT_CVQ_SUFFIX(
                 bsl::is_member_function_pointer, BaseClassTestType,    false);
        TYPE_ASSERT_CVQ_REF   (
                 bsl::is_member_function_pointer, BaseClassTestType,    false);
        TYPE_ASSERT_CVQ_SUFFIX(
                 bsl::is_member_function_pointer, DerivedClassTestType, false);
        TYPE_ASSERT_CVQ_REF   (
                 bsl::is_member_function_pointer, DerivedClassTestType, false);

        // C-3
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, int*,                       false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, StructTestType*,            false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, int StructTestType::*,      false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, int StructTestType::* *,    false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, UnionTestType*,             false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, PMD BaseClassTestType::*,   false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, PMD BaseClassTestType::* *, false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, BaseClassTestType*,         false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, DerivedClassTestType*,      false);
        TYPE_ASSERT_CVQ(
           bsl::is_member_function_pointer, Incomplete*,                false);
        TYPE_ASSERT_CVQ_SUFFIX(
                  bsl::is_member_function_pointer, FunctionPtrTestType, false);

        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, int*,                       false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, StructTestType*,            false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, int StructTestType::*,      false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, int StructTestType::* *,    false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, UnionTestType*,             false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, PMD BaseClassTestType::*,   false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, PMD BaseClassTestType::* *, false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, BaseClassTestType*,         false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, DerivedClassTestType*,      false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, Incomplete*,                false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, FunctionPtrTestType,        false);
        TYPE_ASSERT_CVQ_REF(
           bsl::is_member_function_pointer, MethodPtrTestType,          false);

        // C-4
        TYPE_ASSERT_CVQ_SUFFIX(
                   bsl::is_member_function_pointer, MethodPtrTestType,   true);

        // C-5
        TYPE_ASSERT_CVQ_PREFIX(
                          bsl::is_member_function_pointer, int  (int),  false);
        TYPE_ASSERT_CVQ_PREFIX(
                          bsl::is_member_function_pointer, void (void), false);
        TYPE_ASSERT_CVQ_PREFIX(
                          bsl::is_member_function_pointer, int  (void), false);
        TYPE_ASSERT_CVQ_PREFIX(
                          bsl::is_member_function_pointer, void (int),  false);

      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = "
             << testStatus << "." << endl;
    }

    return testStatus;
}
int
main()
    {
    boost::exception_ptr p = boost::copy_exception(test_exception());
    try
        {
        rethrow_exception(p);
        BOOST_TEST(false);
        }
    catch(
    test_exception & )
        {
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    return boost::report_errors();
    }
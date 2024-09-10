void
tester()
    {
    try
        {
        throw_fwd( &boost::exception_test::throw_test_exception<T> );
        BOOST_ASSERT(false);
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        T & y )
            {
#ifdef BOOST_NO_RTTI
            try
                {
                throw;
                }
            catch(
            boost::exception & y )
                {
#endif
                BOOST_TEST(boost::get_error_info<test_data>(y));
                if( int const * d=boost::get_error_info<test_data>(y) )
                    BOOST_TEST(*d==42);
#ifdef BOOST_NO_RTTI
                }
            catch(
            ... )
                {
                BOOST_TEST(false);
                }
#endif
            BOOST_TEST(y.x_==42);
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }
    }
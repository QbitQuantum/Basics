void
test_throw_on_copy()
    {
    try
        {
        try
            {
            throw boost::enable_current_exception(may_throw_on_copy<Throw>());
            }
        catch(
        may_throw_on_copy<Throw> & x )
            {
            x.throw_=true;
            throw;
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }
    catch(
    ... )
        {
        boost::exception_ptr p = boost::current_exception();
        BOOST_TEST(!(p==boost::exception_ptr()));
        BOOST_TEST(p!=boost::exception_ptr());
        BOOST_TEST(p);
        try
            {
            rethrow_exception(p);
            BOOST_TEST(false);
            }
        catch(
        Catch & )
            {
            boost::exception_ptr p = boost::current_exception();
            BOOST_TEST(!(p==boost::exception_ptr()));
            BOOST_TEST(p!=boost::exception_ptr());
            BOOST_TEST(p);
            try
                {
                boost::rethrow_exception(p);
                BOOST_TEST(false);
                }
            catch(
            Catch & )
                {
                }
            catch(
            ... )
                {
                BOOST_TEST(false);
                }
            }
        catch(
        ... )
            {
            BOOST_TEST(false);
            }
        }
    }
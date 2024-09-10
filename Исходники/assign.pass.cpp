int main()
{
    {
        std::nested_exception e0;
        std::nested_exception e;
        e = e0;
        assert(e.nested_ptr() == nullptr);
    }
#ifndef TEST_HAS_NO_EXCEPTIONS
    {
        try
        {
            throw A(2);
            assert(false);
        }
        catch (const A&)
        {
            std::nested_exception e0;
            std::nested_exception e;
            e = e0;
            assert(e.nested_ptr() != nullptr);
            try
            {
                rethrow_exception(e.nested_ptr());
                assert(false);
            }
            catch (const A& a)
            {
                assert(a == A(2));
            }
        }
    }
#endif
}
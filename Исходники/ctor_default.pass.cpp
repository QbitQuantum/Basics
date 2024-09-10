int main()
{
    {
        std::nested_exception e;
        assert(e.nested_ptr() == nullptr);
    }
    {
        try
        {
            throw A(2);
            assert(false);
        }
        catch (const A&)
        {
            std::nested_exception e;
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
}
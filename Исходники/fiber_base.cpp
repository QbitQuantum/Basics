void
fiber_base::rethrow() const
{
    BOOST_ASSERT( has_exception() );

    rethrow_exception( except_);
}
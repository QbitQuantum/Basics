TEST( SQLSelectTest, defaults )
{
    SQL::Select query;
    ASSERT_THROW( query.getSQL(), SQL::malformed_sql );
}
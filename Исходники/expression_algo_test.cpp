    TEST(ExpressionAlgoIsSubsetOf, Compare_NaN) {
        ParsedMatchExpression nan("{x: NaN}");
        ParsedMatchExpression lt("{x: {$lt: 5}}");
        ParsedMatchExpression lte("{x: {$lte: 5}}");
        ParsedMatchExpression gte("{x: {$gte: 5}}");
        ParsedMatchExpression gt("{x: {$gt: 5}}");

        ASSERT_TRUE(expression::isSubsetOf(nan.get(), nan.get()));
        ASSERT_FALSE(expression::isSubsetOf(nan.get(), lt.get()));
        ASSERT_FALSE(expression::isSubsetOf(lt.get(), nan.get()));
        ASSERT_FALSE(expression::isSubsetOf(nan.get(), lte.get()));
        ASSERT_FALSE(expression::isSubsetOf(lte.get(), nan.get()));
        ASSERT_FALSE(expression::isSubsetOf(nan.get(), gte.get()));
        ASSERT_FALSE(expression::isSubsetOf(gte.get(), nan.get()));
        ASSERT_FALSE(expression::isSubsetOf(nan.get(), gt.get()));
        ASSERT_FALSE(expression::isSubsetOf(gt.get(), nan.get()));
    }
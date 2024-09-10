inline
quantity<Unit, Y>
modf(const quantity<Unit, Y>& q1, quantity<Unit, Y>* q2)
{
    using std::modf;

    typedef quantity<Unit,Y> quantity_type;

    return quantity_type::from_value(modf(q1.value(), &quantity_cast<Y&>(*q2)));
}
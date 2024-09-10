    typename quan::where_<
		quan::meta::and_<
			std::is_integral<ValueType>,
     	   quan::meta::neq_<typename quan::meta::denominator<ReciprocalFraction>::type,quan::meta::int32<1> >
     >,
		 quan::fraction_of_revolution<
			  Extent,
			  ReciprocalFraction,
			  ValueType
		 >
    >::type
    modulo( quan::fraction_of_revolution<
        Extent,
        ReciprocalFraction,
        ValueType
    > const & fr)
    {

        QUAN_FLOAT_TYPE v = static_cast<QUAN_FLOAT_TYPE>(fr.numeric_value())/
            quan::meta::eval_rational<ReciprocalFraction>()();
        QUAN_FLOAT_TYPE n;
#ifndef __AVR__
       using std::modf;
#else
      using ::modf;
#endif
       // ValueType fract = modf(v,&n);
        return quan::fraction_of_revolution<
            Extent,
            ReciprocalFraction,
            ValueType
        >(
             quan::arithmetic_convert<ValueType>(modf(v,&n) * quan::meta::eval_rational<ReciprocalFraction>()())
        );

    }
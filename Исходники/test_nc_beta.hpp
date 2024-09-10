void quantile_sanity_check(T& data, const char* type_name, const char* test)
{
#ifndef ERROR_REPORTING_MODE
    typedef Real                   value_type;

    //
    // Tests with type real_concept take rather too long to run, so
    // for now we'll disable them:
    //
    if(!boost::is_floating_point<value_type>::value)
        return;

    std::cout << "Testing: " << type_name << " quantile sanity check, with tests " << test << std::endl;

    //
    // These sanity checks test for a round trip accuracy of one half
    // of the bits in T, unless T is type float, in which case we check
    // for just one decimal digit.  The problem here is the sensitivity
    // of the functions, not their accuracy.  This test data was generated
    // for the forward functions, which means that when it is used as
    // the input to the inverses then it is necessarily inexact.  This rounding
    // of the input is what makes the data unsuitable for use as an accuracy check,
    // and also demonstrates that you can't in general round-trip these functions.
    // It is however a useful sanity check.
    //
    value_type precision = static_cast<value_type>(ldexp(1.0, 1 - boost::math::policies::digits<value_type, boost::math::policies::policy<> >() / 2)) * 100;
    if(boost::math::policies::digits<value_type, boost::math::policies::policy<> >() < 50)
        precision = 1;   // 1% or two decimal digits, all we can hope for when the input is truncated to float

    for(unsigned i = 0; i < data.size(); ++i)
    {
        //
        // Test case 493 fails at float precision: not enough bits to get
        // us back where we started:
        //
        if((i == 493) && boost::is_same<float, value_type>::value)
            continue;

        if(data[i][4] == 0)
        {
            BOOST_CHECK(0 == quantile(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), data[i][4]));
        }
        else if(data[i][4] < 0.9999f)
        {
            value_type p = quantile(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), data[i][4]);
            value_type pt = data[i][3];
            BOOST_CHECK_CLOSE_EX(pt, p, precision, i);
        }
        if(data[i][5] == 0)
        {
            BOOST_CHECK(1 == quantile(complement(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), data[i][5])));
        }
        else if(data[i][5] < 0.9999f)
        {
            value_type p = quantile(complement(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), data[i][5]));
            value_type pt = data[i][3];
            BOOST_CHECK_CLOSE_EX(pt, p, precision, i);
        }
        if(boost::math::tools::digits<value_type>() > 50)
        {
            //
            // Sanity check mode, accuracy of
            // the mode is at *best* the square root of the accuracy of the PDF:
            //
            value_type m = mode(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]));
            if((m == 1) || (m == 0))
                break;
            value_type p = pdf(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), m);
            if(m * (1 + sqrt(precision) * 10) < 1)
            {
                BOOST_CHECK_EX(pdf(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), m * (1 + sqrt(precision) * 10)) <= p, i);
            }
            if(m * (1 - sqrt(precision)) * 10 > boost::math::tools::min_value<value_type>())
            {
                BOOST_CHECK_EX(pdf(boost::math::non_central_beta_distribution<value_type>(data[i][0], data[i][1], data[i][2]), m * (1 - sqrt(precision)) * 10) <= p, i);
            }
        }
    }
#endif
}
    bool test_simd_chyperbolic(std::ostream& out, T& tester)
    {
        using tester_type = T;
        using vector_type = typename tester_type::vector_type;
        using value_type = typename tester_type::value_type;
        using res_type = typename tester_type::res_type;

        vector_type input;
        vector_type vres;
        res_type res(tester.input.size());

        bool success = true;
        bool tmp_success = true;

        std::string val_type = value_type_name<vector_type>();
        std::string shift = std::string(val_type.size(), '-');
        std::string name = tester.name;
        std::string name_shift = std::string(name.size(), '-');
        std::string dash(8, '-');
        std::string space(8, ' ');

        out << dash << name_shift << '-' << shift << dash << std::endl;
        out << space << name << " " << val_type << std::endl;
        out << dash << name_shift << '-' << shift << dash << std::endl
            << std::endl;

        std::string topic = "sinh  : ";
        for (size_t i = 0; i < tester.input.size(); i += tester.size)
        {
            tester.load_vec(input, tester.input, i);
            vres = sinh(input);
            tester.store_vec(vres, res, i);
        }
        tmp_success = check_almost_equal(topic, res, tester.sinh_res, out);
        success = success && tmp_success;
        success &= check_almost_equal(topic, xsimd::sinh(tester.input[0]), tester.sinh_res[0], out);

        topic = "cosh  : ";
        for (size_t i = 0; i < tester.input.size(); i += tester.size)
        {
            tester.load_vec(input, tester.input, i);
            vres = cosh(input);
            tester.store_vec(vres, res, i);
        }
        tmp_success = check_almost_equal(topic, res, tester.cosh_res, out);
        success = success && tmp_success;
        success &= check_almost_equal(topic, xsimd::cosh(tester.input[0]), tester.cosh_res[0], out);

        topic = "tanh  : ";
        for (size_t i = 0; i < tester.input.size(); i += tester.size)
        {
            tester.load_vec(input, tester.input, i);
            vres = tanh(input);
            tester.store_vec(vres, res, i);
        }
        tmp_success = check_almost_equal(topic, res, tester.tanh_res, out);
        success = success && tmp_success;
        success &= check_almost_equal(topic, xsimd::tanh(tester.input[0]), tester.tanh_res[0], out);

        topic = "asinh : ";
        for (size_t i = 0; i < tester.input.size(); i += tester.size)
        {
            tester.load_vec(input, tester.input, i);
            vres = asinh(input);
            tester.store_vec(vres, res, i);
        }
        tmp_success = check_almost_equal(topic, res, tester.asinh_res, out);
        success = success && tmp_success;
        success &= check_almost_equal(topic, xsimd::asinh(tester.input[0]), tester.asinh_res[0], out);

        topic = "acosh : ";
        for (size_t i = 0; i < tester.acosh_input.size(); i += tester.size)
        {
            tester.load_vec(input, tester.acosh_input, i);
            vres = acosh(input);
            tester.store_vec(vres, res, i);
        }
        tmp_success = check_almost_equal(topic, res, tester.acosh_res, out);
        success = success && tmp_success;
        success &= check_almost_equal(topic, xsimd::acosh(tester.acosh_input[0]), tester.acosh_res[0], out);

        topic = "atanh : ";
        for (size_t i = 0; i < tester.atanh_input.size(); i += tester.size)
        {
            tester.load_vec(input, tester.atanh_input, i);
            vres = atanh(input);
            tester.store_vec(vres, res, i);
        }
        tmp_success = check_almost_equal(topic, res, tester.atanh_res, out);
        success = success && tmp_success;
        success &= check_almost_equal(topic, xsimd::atanh(tester.atanh_input[0]), tester.atanh_res[0], out);

        return success;
    }
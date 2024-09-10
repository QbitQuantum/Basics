Eigen::Matrix4f
parse_registration(turtle_input& input, const std::string& guid_0,
                     const std::string& guid_1) {
    std::pair<std::string, bool> t = parse_transformation_string(input, guid_0, guid_1);
    std::istringstream iss(t.first);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    assert(tokens.size() == 16);

    Eigen::Matrix4f m;
    for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < 4; ++j) {
            double value;
            std::stringstream convert_str(tokens[i*4+j]);
            convert_str >> value;
            convert_str.str("");
            m(i, j) = value;
        }
    }

    if (t.second) {
        Eigen::Matrix4f inv = m.inverse();
        m = inv;
    }

    return m;
}
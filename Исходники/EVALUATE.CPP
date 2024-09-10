ski::node eval(ski::node const& n_orig) {
    arg_vector args;
    auto n = n_orig;
    while (true) {
        warn(n_orig);
        while (auto* app = n.get<ski::application>()) {
            args.push_back(n);
            warn("back:", args.back());
            n = app->f;
        }

        bool id = is_identity(n);

        auto result = boost::apply_visitor(do_evaluate(args), n);
        if (!result)
            break;
        if (args.empty())
            n = n_orig.update(*result);
        else if (id)
            n = get_fun(args.back()) = *result;
        else if (result->get<ski::application>())
            n = get_fun(args.back()).update(*result);
        else
            n = get_fun(args.back()).update(ski::application{
                    ski::combinator{'I'},
                    *result});
    }
    while (!args.empty())
        n = ski::application{n, get_arg(extract(args))};
    return n;
}
int main(int argc, char *argv[])
{
    set_main_thread();
    setup_fork_guards();

    wsetlocale(LC_ALL, L"");
    program_name=L"fish_indent";

    env_init();
    input_init();

    /* Types of output we support */
    enum
    {
        output_type_plain_text,
        output_type_ansi,
        output_type_html
    } output_type = output_type_plain_text;

    /* Whether to indent (true) or just reformat to one job per line (false) */
    bool do_indent = true;

    while (1)
    {
        const struct option long_options[] =
        {
            { "no-indent", no_argument, 0, 'i' },
            { "help", no_argument, 0, 'h' },
            { "version", no_argument, 0, 'v' },
            { "html", no_argument, 0, 1 },
            { "ansi", no_argument, 0, 2 },
            { 0, 0, 0, 0 }
        };

        int opt_index = 0;
        int opt = getopt_long(argc, argv, "hvi", long_options, &opt_index);
        if (opt == -1)
            break;

        switch (opt)
        {
            case 0:
            {
                break;
            }

            case 'h':
            {
                print_help("fish_indent", 1);
                exit(0);
                assert(0 && "Unreachable code reached");
                break;
            }

            case 'v':
            {
                fwprintf(stderr, _(L"%ls, version %s\n"), program_name, get_fish_version());
                exit(0);
                assert(0 && "Unreachable code reached");
                break;
            }

            case 'i':
            {
                do_indent = false;
                break;
            }

            case 1:
            {
                output_type = output_type_html;
                break;
            }

            case 2:
            {
                output_type = output_type_ansi;
                break;
            }

            case '?':
            {
                exit(1);
            }
        }
    }

    const wcstring src = read_file(stdin);
    const wcstring output_wtext = prettify(src, do_indent);

    /* Maybe colorize */
    std::vector<highlight_spec_t> colors;
    if (output_type != output_type_plain_text)
    {
        highlight_shell_no_io(output_wtext, colors, output_wtext.size(), NULL, env_vars_snapshot_t::current());
    }

    std::string colored_output;
    switch (output_type)
    {
        case output_type_plain_text:
            colored_output = no_colorize(output_wtext);
            break;

        case output_type_ansi:
            colored_output = ansi_colorize(output_wtext, colors);
            break;

        case output_type_html:
            colored_output = html_colorize(output_wtext, colors);
            break;
    }

    fputs(colored_output.c_str(), stdout);
    return 0;
}
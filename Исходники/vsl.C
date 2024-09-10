// Main VSL program
int main(int argc, char *argv[])
{
    // Set flags
    {
        // SGI CC wants this:
        const char** tmp_argv = (const char**)argv;
        VSEFlags::parse(argc, tmp_argv, "vsllib");
        argv = (char **)tmp_argv;
    }

    // Init toolkit
    Widget toplevel = XtAppInitialize(&app_con, "Vsl",
                                      (XrmOptionDescRec *)0, ZERO,
                                      &argc, argv, (char**)fallback_resources,
                                      ArgList(0), ZERO);

    // Create Viewport
    Arg arglist[10];        // Arguments
    int a = 0;              // Argument counter
    XtSetArg(arglist[a], ARGSTR(XtNallowHoriz), true);
    a++;
    XtSetArg(arglist[a], ARGSTR(XtNallowVert),  true);
    a++;
    Widget viewport = XtCreateManagedWidget("viewport", viewportWidgetClass,
                                            toplevel, arglist, a);

    // Create DocSpace
    a = 0;
    Widget docSpace = XtCreateManagedWidget("docSpace", docSpaceWidgetClass,
                                            viewport, arglist, a);
    XtAddCallback(docSpace, XtNcallback, SelectCB, 0);
    XtAddCallback(docSpace, XtNexposeCallback, ExposeCB, 0);
    XtAddCallback(docSpace, XtNquitCallback, QuitCB, 0);

    // Set font table
    StringBox::fontTable = new FontTable(XtDisplay(toplevel));

    // Fetch name
    string library_file = VSEFlags::library_file;
    if (argc > 1)
    {
        library_file = argv[1];
        if (library_file[0] == '-')
        {
            std::cout << argv[0] << ": usage: " << argv[0] << " [options] "
                      << "VSLLIB [THEMES...]\n\n" << VSEFlags::explain();

            exit(EXIT_FAILURE);
        }
    }

    // Create pic in THEBOX
    {
        // Read library
        long starttime = clock();
        ThemedVSLLib lib(library_file, VSEFlags::optimize_mode());
        long endtime = clock();

        assert(lib.OK());

        if (VSEFlags::show_optimizing_time)
            std::cout << "\nRead & optimizing time: "
                      << (endtime - starttime) / 1000 << " ms\n";

        // Build themes
        StringArray themes;
        for (int i = 2; i < argc; i++)
            themes += argv[i];
        lib.set_theme_list(themes);
        assert(lib.OK());

        if (VSEFlags::assert_library_ok)
            assert(lib.OK());

        if (VSEFlags::dump_library)
            std::cout << lib;

        if (VSEFlags::dump_tree)
            lib.dumpTree(std::cout);

        if (VSEFlags::suppress_eval)
            return EXIT_SUCCESS;

        // Fetch last function def (typically "main")
        VSLDef *def = lib.lastdef();

        if (def == 0)
        {
            std::cerr << argv[0] << ": cannot find last definition (sorry)\n";
            return EXIT_FAILURE;
        }

        // Eval function
        ListBox *arg = vsl_args(argc, argv);

        starttime = clock();
        for (int loop = 1; loop < VSEFlags::loops; loop++)
        {
            Box *result = (Box *)def->eval(arg);
            lib.output(result);
            result->unlink();
        }
        Box *result = (Box *)def->eval(arg);
        lib.output(result);
        endtime = clock();
        arg->unlink();

        // Show eval time
        if (VSEFlags::show_eval_time)
            std::cout << "\nEvaluation time: "
                      << (endtime - starttime) / 1000 << " ms\n";

        if (result && VSEFlags::dump_picture)
            std::cout << "#!" << argv[0] << "\n#include <std.vsl>\n\nmain() -> "
                      << *result << ";\n";

        thebox = result;

        // Stack and library are destroyed upon leaving this block
    }

    if (thebox && !thebox->size().isValid())
    {
        std::cerr << argv[0] << ": result has no size (maybe list?)\n";
        thebox->unlink();
        thebox = 0;
    }

    if (thebox == 0)
    {
        std::cerr << argv[0] << ": evaluation failed (sorry)\n";
        return EXIT_FAILURE;
    }

    // Realize Widget
    XtRealizeWidget(toplevel);

    // Process events
    XtAppMainLoop(app_con);

    // Never reached...
    return EXIT_SUCCESS;
}
void TestArchive::Run() {
    Compile(official_source);
    if (is_interactive) {
        Compile(checker);
    }
    stable_sort(testcases.begin(), testcases.end());
    int test_number = 0;
    os.RunBashCommand("mkdir -p " + tests_location);

    for (auto itr : testcases) {
        if (itr.Type() == DEBUG_TEST) {
            continue;
        }
        std::cerr << GetBloatware() << "\t" << Colored(4, 2, 3, "Generating") << " input for test "
                  << Colored(5, 1, 1, Allign(StrCat("#", test_number), 3)) << '\n';

        std::string input = itr.Input();
        // write input before generating so in case something goes wrong
        // the user has the input that triggered that bug / crash
        os.WriteFile(tests_location + test_prefix + std::to_string(test_number) + ".in", input);
//        Info("Computed .in file and wrote it to\t", test_prefix + std::to_string(test_number));

        if (not is_interactive) {
            EggResult test_result = deploy_eggecutor.Run(official_source, input);
            std::cerr << '\n';
            auto stdok = test_result.stdout;
            if (itr.has_output) {
                stdok = itr.output;
            }
            os.WriteFile(tests_location + test_prefix + std::to_string(test_number) + ".ok", stdok);
        } else {
            auto all_results = deploy_eggecutor.RunInteractive(official_source, checker, input);
            if (itr.Type() == EXAMPLE) {
                os.WriteFile(tests_location + test_prefix + std::to_string(test_number) + ".json",
                             all_results.second.logger);
            }
            std::cerr << "Checker: " << (all_results.second.passed ? Colored(Color::green, "Passed!") : Colored(Color::red, "Not passed")) << 
                 "\t" << Colored(Color::light_magenta, all_results.second.message) << '\n';
        }

        test_number += 1;
    }
}
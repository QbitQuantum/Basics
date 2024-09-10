//////////////////////////////////////////////////////////////////////////////
//! Find the path for a file assuming that
//! files are found in the searchPath.
//!
//! @return the path if succeeded, otherwise 0
//! @param filename         name of the file
//! @param executable_path  optional absolute path of the executable
//////////////////////////////////////////////////////////////////////////////
inline char *sdkFindFilePath(const char *filename, const char *executable_path)
{
    // <executable_name> defines a variable that is replaced with the name of the executable

    // Typical relative search paths to locate needed companion files (e.g. sample input data, or JIT source files)
    // The origin for the relative search may be the .exe file, a .bat file launching an .exe, a browser .exe launching the .exe or .bat, etc
    const char *searchPath[] =
            {
                    "./",                                       // same dir
                    "./common/",                                // "/common/" subdir
                    "./common/data/",                           // "/common/data/" subdir
                    "./data/",                                  // "/data/" subdir
                    "./src/",                                   // "/src/" subdir
                    "./src/<executable_name>/data/",            // "/src/<executable_name>/data/" subdir
                    "./inc/",                                   // "/inc/" subdir
                    "./0_Simple/",                              // "/0_Simple/" subdir
                    "./1_Utilities/",                           // "/1_Utilities/" subdir
                    "./2_Graphics/",                            // "/2_Graphics/" subdir
                    "./3_Imaging/",                             // "/3_Imaging/" subdir
                    "./4_Finance/",                             // "/4_Finance/" subdir
                    "./5_Simulations/",                         // "/5_Simulations/" subdir
                    "./6_Advanced/",                            // "/6_Advanced/" subdir
                    "./7_CUDALibraries/",                       // "/7_CUDALibraries/" subdir
                    "./8_Android/",                             // "/8_Android/" subdir
                    "./samples/",                               // "/samples/" subdir

                    "../",                                      // up 1 in tree
                    "../common/",                               // up 1 in tree, "/common/" subdir
                    "../common/data/",                          // up 1 in tree, "/common/data/" subdir
                    "../data/",                                 // up 1 in tree, "/data/" subdir
                    "../src/",                                  // up 1 in tree, "/src/" subdir
                    "../inc/",                                  // up 1 in tree, "/inc/" subdir

                    "../0_Simple/<executable_name>/data/",       // up 1 in tree, "/0_Simple/<executable_name>/" subdir
                    "../1_Utilities/<executable_name>/data/",    // up 1 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../2_Graphics/<executable_name>/data/",     // up 1 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../3_Imaging/<executable_name>/data/",      // up 1 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../4_Finance/<executable_name>/data/",      // up 1 in tree, "/4_Finance/<executable_name>/" subdir
                    "../5_Simulations/<executable_name>/data/",  // up 1 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../6_Advanced/<executable_name>/data/",     // up 1 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../7_CUDALibraries/<executable_name>/data/",// up 1 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../8_Android/<executable_name>/data/",      // up 1 in tree, "/8_Android/<executable_name>/" subdir
                    "../samples/<executable_name>/data/",        // up 1 in tree, "/samples/<executable_name>/" subdir
                    "../../",                                        // up 2 in tree
                    "../../common/",                                 // up 2 in tree, "/common/" subdir
                    "../../common/data/",                            // up 2 in tree, "/common/data/" subdir
                    "../../data/",                                   // up 2 in tree, "/data/" subdir
                    "../../src/",                                    // up 2 in tree, "/src/" subdir
                    "../../inc/",                                    // up 2 in tree, "/inc/" subdir
                    "../../sandbox/<executable_name>/data/",         // up 2 in tree, "/sandbox/<executable_name>/" subdir
                    "../../0_Simple/<executable_name>/data/",        // up 2 in tree, "/0_Simple/<executable_name>/" subdir
                    "../../1_Utilities/<executable_name>/data/",     // up 2 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../../2_Graphics/<executable_name>/data/",      // up 2 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../../3_Imaging/<executable_name>/data/",       // up 2 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../../4_Finance/<executable_name>/data/",       // up 2 in tree, "/4_Finance/<executable_name>/" subdir
                    "../../5_Simulations/<executable_name>/data/",   // up 2 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../../6_Advanced/<executable_name>/data/",      // up 2 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../../7_CUDALibraries/<executable_name>/data/", // up 2 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../../8_Android/<executable_name>/data/",       // up 2 in tree, "/8_Android/<executable_name>/" subdir
                    "../../samples/<executable_name>/data/",         // up 2 in tree, "/samples/<executable_name>/" subdir
                    "../../../",                                        // up 3 in tree
                    "../../../src/<executable_name>/",                  // up 3 in tree, "/src/<executable_name>/" subdir
                    "../../../src/<executable_name>/data/",             // up 3 in tree, "/src/<executable_name>/data/" subdir
                    "../../../src/<executable_name>/src/",              // up 3 in tree, "/src/<executable_name>/src/" subdir
                    "../../../src/<executable_name>/inc/",              // up 3 in tree, "/src/<executable_name>/inc/" subdir
                    "../../../sandbox/<executable_name>/",              // up 3 in tree, "/sandbox/<executable_name>/" subdir
                    "../../../sandbox/<executable_name>/data/",         // up 3 in tree, "/sandbox/<executable_name>/data/" subdir
                    "../../../sandbox/<executable_name>/src/",          // up 3 in tree, "/sandbox/<executable_name>/src/" subdir
                    "../../../sandbox/<executable_name>/inc/",          // up 3 in tree, "/sandbox/<executable_name>/inc/" subdir
                    "../../../0_Simple/<executable_name>/data/",        // up 3 in tree, "/0_Simple/<executable_name>/" subdir
                    "../../../1_Utilities/<executable_name>/data/",     // up 3 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../../../2_Graphics/<executable_name>/data/",      // up 3 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../../../3_Imaging/<executable_name>/data/",       // up 3 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../../../4_Finance/<executable_name>/data/",       // up 3 in tree, "/4_Finance/<executable_name>/" subdir
                    "../../../5_Simulations/<executable_name>/data/",   // up 3 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../../../6_Advanced/<executable_name>/data/",      // up 3 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../../../7_CUDALibraries/<executable_name>/data/", // up 3 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../../../8_Android/<executable_name>/data/",       // up 3 in tree, "/8_Android/<executable_name>/" subdir
                    "../../../0_Simple/<executable_name>/",        // up 3 in tree, "/0_Simple/<executable_name>/" subdir
                    "../../../1_Utilities/<executable_name>/",     // up 3 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../../../2_Graphics/<executable_name>/",      // up 3 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../../../3_Imaging/<executable_name>/",       // up 3 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../../../4_Finance/<executable_name>/",       // up 3 in tree, "/4_Finance/<executable_name>/" subdir
                    "../../../5_Simulations/<executable_name>/",   // up 3 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../../../6_Advanced/<executable_name>/",      // up 3 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../../../7_CUDALibraries/<executable_name>/", // up 3 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../../../8_Android/<executable_name>/",       // up 3 in tree, "/8_Android/<executable_name>/" subdir
                    "../../../samples/<executable_name>/data/",         // up 3 in tree, "/samples/<executable_name>/" subdir
                    "../../../common/",                                 // up 3 in tree, "../../../common/" subdir
                    "../../../common/data/",                            // up 3 in tree, "../../../common/data/" subdir
                    "../../../data/",                                   // up 3 in tree, "../../../data/" subdir
                    "../../../../",                                // up 4 in tree
                    "../../../../src/<executable_name>/",          // up 4 in tree, "/src/<executable_name>/" subdir
                    "../../../../src/<executable_name>/data/",     // up 4 in tree, "/src/<executable_name>/data/" subdir
                    "../../../../src/<executable_name>/src/",      // up 4 in tree, "/src/<executable_name>/src/" subdir
                    "../../../../src/<executable_name>/inc/",      // up 4 in tree, "/src/<executable_name>/inc/" subdir
                    "../../../../sandbox/<executable_name>/",      // up 4 in tree, "/sandbox/<executable_name>/" subdir
                    "../../../../sandbox/<executable_name>/data/", // up 4 in tree, "/sandbox/<executable_name>/data/" subdir
                    "../../../../sandbox/<executable_name>/src/",  // up 4 in tree, "/sandbox/<executable_name>/src/" subdir
                    "../../../../sandbox/<executable_name>/inc/",   // up 4 in tree, "/sandbox/<executable_name>/inc/" subdir
                    "../../../../0_Simple/<executable_name>/data/",     // up 4 in tree, "/0_Simple/<executable_name>/" subdir
                    "../../../../1_Utilities/<executable_name>/data/",  // up 4 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../../../../2_Graphics/<executable_name>/data/",   // up 4 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../../../../3_Imaging/<executable_name>/data/",    // up 4 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../../../../4_Finance/<executable_name>/data/",    // up 4 in tree, "/4_Finance/<executable_name>/" subdir
                    "../../../../5_Simulations/<executable_name>/data/",// up 4 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../../../../6_Advanced/<executable_name>/data/",   // up 4 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../../../../7_CUDALibraries/<executable_name>/data/", // up 4 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../../../../8_Android/<executable_name>/data/",    // up 4 in tree, "/8_Android/<executable_name>/" subdir
                    "../../../../0_Simple/<executable_name>/",     // up 4 in tree, "/0_Simple/<executable_name>/" subdir
                    "../../../../1_Utilities/<executable_name>/",  // up 4 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../../../../2_Graphics/<executable_name>/",   // up 4 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../../../../3_Imaging/<executable_name>/",    // up 4 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../../../../4_Finance/<executable_name>/",    // up 4 in tree, "/4_Finance/<executable_name>/" subdir
                    "../../../../5_Simulations/<executable_name>/",// up 4 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../../../../6_Advanced/<executable_name>/",   // up 4 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../../../../7_CUDALibraries/<executable_name>/", // up 4 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../../../../8_Android/<executable_name>/",    // up 4 in tree, "/8_Android/<executable_name>/" subdir
                    "../../../../samples/<executable_name>/data/",      // up 4 in tree, "/samples/<executable_name>/" subdir
                    "../../../../common/",                              // up 4 in tree, "../../../common/" subdir
                    "../../../../common/data/",                         // up 4 in tree, "../../../common/data/" subdir
                    "../../../../data/",                                // up 4 in tree, "../../../data/" subdir
                    "../../../../../",                                // up 5 in tree
                    "../../../../../src/<executable_name>/",          // up 5 in tree, "/src/<executable_name>/" subdir
                    "../../../../../src/<executable_name>/data/",     // up 5 in tree, "/src/<executable_name>/data/" subdir
                    "../../../../../src/<executable_name>/src/",      // up 5 in tree, "/src/<executable_name>/src/" subdir
                    "../../../../../src/<executable_name>/inc/",      // up 5 in tree, "/src/<executable_name>/inc/" subdir
                    "../../../../../sandbox/<executable_name>/",      // up 5 in tree, "/sandbox/<executable_name>/" subdir
                    "../../../../../sandbox/<executable_name>/data/", // up 5 in tree, "/sandbox/<executable_name>/data/" subdir
                    "../../../../../sandbox/<executable_name>/src/",  // up 5 in tree, "/sandbox/<executable_name>/src/" subdir
                    "../../../../../sandbox/<executable_name>/inc/",   // up 5 in tree, "/sandbox/<executable_name>/inc/" subdir
                    "../../../../../0_Simple/<executable_name>/data/",     // up 5 in tree, "/0_Simple/<executable_name>/" subdir
                    "../../../../../1_Utilities/<executable_name>/data/",  // up 5 in tree, "/1_Utilities/<executable_name>/" subdir
                    "../../../../../2_Graphics/<executable_name>/data/",   // up 5 in tree, "/2_Graphics/<executable_name>/" subdir
                    "../../../../../3_Imaging/<executable_name>/data/",    // up 5 in tree, "/3_Imaging/<executable_name>/" subdir
                    "../../../../../4_Finance/<executable_name>/data/",    // up 5 in tree, "/4_Finance/<executable_name>/" subdir
                    "../../../../../5_Simulations/<executable_name>/data/",// up 5 in tree, "/5_Simulations/<executable_name>/" subdir
                    "../../../../../6_Advanced/<executable_name>/data/",   // up 5 in tree, "/6_Advanced/<executable_name>/" subdir
                    "../../../../../7_CUDALibraries/<executable_name>/data/", // up 5 in tree, "/7_CUDALibraries/<executable_name>/" subdir
                    "../../../../../8_Android/<executable_name>/data/",    // up 5 in tree, "/8_Android/<executable_name>/" subdir
                    "../../../../../samples/<executable_name>/data/",      // up 5 in tree, "/samples/<executable_name>/" subdir
                    "../../../../../common/",                         // up 5 in tree, "../../../common/" subdir
                    "../../../../../common/data/",                    // up 5 in tree, "../../../common/data/" subdir
            };

    // Extract the executable name
    std::string executable_name;

    if (executable_path != 0)
    {
        executable_name = std::string(executable_path);

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
        // Windows path delimiter
        size_t delimiter_pos = executable_name.find_last_of('\\');
        executable_name.erase(0, delimiter_pos + 1);

        if (executable_name.rfind(".exe") != std::string::npos)
        {
            // we strip .exe, only if the .exe is found
            executable_name.resize(executable_name.size() - 4);
        }

#else
        // Linux & OSX path delimiter
        size_t delimiter_pos = executable_name.find_last_of('/');
        executable_name.erase(0,delimiter_pos+1);
#endif
    }

    // Loop over all search paths and return the first hit
    for (unsigned int i = 0; i < sizeof(searchPath)/sizeof(char *); ++i)
    {
        std::string path(searchPath[i]);
        size_t executable_name_pos = path.find("<executable_name>");

        // If there is executable_name variable in the searchPath
        // replace it with the value
        if (executable_name_pos != std::string::npos)
        {
            if (executable_path != 0)
            {
                path.replace(executable_name_pos, strlen("<executable_name>"), executable_name);
            }
            else
            {
                // Skip this path entry if no executable argument is given
                continue;
            }
        }

#ifdef _DEBUG
        printf("sdkFindFilePath <%s> in %s\n", filename, path.c_str());
#endif

        // Test if the file exists
        path.append(filename);
        FILE *fp;
        FOPEN(fp, path.c_str(), "rb");

        if (fp != NULL)
        {
            fclose(fp);
            // File found
            // returning an allocated array here for backwards compatibility reasons
            char *file_path = (char *) malloc(path.length() + 1);
            STRCPY(file_path, path.length() + 1, path.c_str());
            return file_path;
        }

        if (fp)
        {
            fclose(fp);
        }
    }

    // File not found
    return 0;
}
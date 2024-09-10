static void writeGuardedInclude (OutputStream& out, StringArray paths, StringArray guards)
{
    StringArray uniquePaths (paths);
    uniquePaths.removeDuplicates (false);

    if (uniquePaths.size() == 1)
    {
        out << "#include " << paths[0] << newLine;
    }
    else
    {
        for (int i = paths.size(); --i >= 0;)
        {
            for (int j = i; --j >= 0;)
            {
                if (paths[i] == paths[j] && guards[i] == guards[j])
                {
                    paths.remove (i);
                    guards.remove (i);
                }
            }
        }

        for (int i = 0; i < paths.size(); ++i)
        {
            out << (i == 0 ? "#if " : "#elif ") << guards[i] << newLine
                << " #include " << paths[i] << newLine;
        }

        out << "#else" << newLine
            << " #error \"This file is designed to be used in an Introjucer-generated project!\"" << newLine
            << "#endif" << newLine;
    }
}
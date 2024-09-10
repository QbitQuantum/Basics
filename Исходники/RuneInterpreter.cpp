int main(int argc, char *argv[])
{
    using namespace std;
    bool print_tokens = false, print_ast = false, no_run = false; 
    // Refer whether tokens and ast need to be printed. 
    int name_count = 0;
    // Count the filename inputed.
    string filename;
    // Save the name of file.
    string raw;

    if (argc < 2)
    {
        // A correct call of rune must given 2 or more args;
        show_help();
        return -2;
    }
    else
    {
        for (int i = 1; i < argc; ++i)
        {
            if (argv[i][0] == '-')
            {
                switch(argv[i][1])
                {
                case 't':
                    print_tokens = true;
                    break;
                case 'a':
                    print_ast = true;
                    break;
                case 'n':
                    no_run = true;
                    break;
                default:
                    cout << "unrecognized command line option \'"
                         << argv[i] << '\'';  
                    show_help();
                    return -2;
                }
            }
            else
            {
                filename = argv[i];
                name_count++;
            }
        }
        if (name_count != 1)
        {
            // if more than 1 filenames were inputed, show help and exit.
            show_help();
            return -2;
        }
    }
    raw = read_all_from_file(filename);
    if (raw.size() == 0)
    {
        // **There is a pitfall.
        // **I'm not sure how to get known the existance of file.
        // **So, deal as same when file not exist and empty.
        cout << "file not exist or nothing contained in file.";
        return -3;
    }
    try
    {
        Preprocessor pre;
        vector<string> lines = pre.preprocess(raw);
        // Raw string preprocessed to decommented lines.
        Scanner scn;
        vector<Token> tokens = scn.scan(lines);
        // Scan the lines to a vector of Tokens.
        // Token is defined in "tokenEnum.h".
        if (print_tokens)
        {
            show_tokens(tokens);
        }
        // print Tokens if has option "-tokens".
        Parser psr;
        auto ast = psr.parse(tokens);
        // Parse the Tokens to an Abstract Syntax Tree.
        // AST is defined in "syntexTreeEnum.h".
        if (print_ast)
        {
            cout << "SYNTAX TREE:\n";
            psr.show_tree(ast);
        }
        // print AST if has option "-ast".
        if (!no_run)
        {
            Interpreter itp;
            itp.execute(ast);
            // Interprete the AST.
        }
    } 
    catch (string msg)
    {
        cout << msg << endl;
        return -1;
        // print error message.
    }
	return 0;
}
    void print_to_file(const char * userfile, int lineno, const char* tag,
                       T &obj) {
        std::string msg;
//llvm::errs()<<"I am called in line no"<<__LINE__;

        llvm::raw_string_ostream Msg(msg);
        Msg << obj;
        std::string objS = Msg.str();

        replaceAll(objS, "\n", mendl);
        tagset.insert(tag);
        (*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
              << NBSP << BOLD(" Data : <br>") << objS << EDIV;
        (*OS).flush();
    }
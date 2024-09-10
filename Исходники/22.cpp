 File(const char * name) {
     f = fopen(name, "r");
     if (f == nullptr)
         throw CannotOpenFileException();
 }
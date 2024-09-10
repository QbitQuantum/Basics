 USec MeasureAndPrint(const std::string &test,
                      const std::string &stage,
                      unsigned           amount) const {
   if (amount < 1)
     amount = 1;
   const USec kResTm = Clock().GetDiff(*this) / amount;
   std::cout << "\t * " << test << ": " << stage << ": "
             << "[" << amount << "] "
             << kResTm << " usec"
             << std::endl;
   return kResTm;
 }
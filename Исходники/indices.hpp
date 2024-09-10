 static inline String cv_names(const SInd i) noexcept {
   if (i == 0) {
     return "T";
   } else {
     TERMINATE("unknown variable index: " + std::to_string(i));
   }
 }
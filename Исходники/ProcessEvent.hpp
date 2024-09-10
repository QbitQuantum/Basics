 const bool operator!= ( ProcessEvent const& rhs ) const
 {
     return getTime() != rhs.getTime() ||
             getProcess() != rhs.getProcess();
 }
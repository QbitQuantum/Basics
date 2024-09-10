 std::unique_ptr<SeqPreconditioner> constructPrecond(Operator& opA, const Dune::Amg::SequentialInformation&) const
 {
     const double relax = 0.9;
     std::unique_ptr<SeqPreconditioner> precond(new SeqPreconditioner(opA.getmat(), relax));
     return precond;
 }
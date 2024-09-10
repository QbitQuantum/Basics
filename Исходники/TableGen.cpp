void llvm::PrintError(SMLoc ErrorLoc, const Twine &Msg) {
  SrcMgr.PrintMessage(ErrorLoc, Msg, "error");
}
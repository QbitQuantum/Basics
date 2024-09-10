static void printProfileData(const ProfileData &Profile,
                             llvm::raw_ostream &OS) {
  // Time is first to allow for sorting by it.
  std::vector<std::pair<llvm::TimeRecord, StringRef>> Timers;
  TimeRecord Total;

  for (const auto& P : Profile.Records) {
    Timers.emplace_back(P.getValue(), P.getKey());
    Total += P.getValue();
  }

  std::sort(Timers.begin(), Timers.end());

  std::string Line = "===" + std::string(73, '-') + "===\n";
  OS << Line;

  if (Total.getUserTime())
    OS << "   ---User Time---";
  if (Total.getSystemTime())
    OS << "   --System Time--";
  if (Total.getProcessTime())
    OS << "   --User+System--";
  OS << "   ---Wall Time---";
  if (Total.getMemUsed())
    OS << "  ---Mem---";
  OS << "  --- Name ---\n";

  // Loop through all of the timing data, printing it out.
  for (auto I = Timers.rbegin(), E = Timers.rend(); I != E; ++I) {
    I->first.print(Total, OS);
    OS << I->second << '\n';
  }

  Total.print(Total, OS);
  OS << "Total\n";
  OS << Line << "\n";
  OS.flush();
}
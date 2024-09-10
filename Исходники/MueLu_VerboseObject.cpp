  Teuchos::FancyOStream & VerboseObject::GetOStream(MsgType type, int thisProcRankOnly) const {
    if (!IsPrint(type, thisProcRankOnly))
      return *blackHole_;

    Teuchos::FancyOStream& os = *getOStream();
    if (!(type & ((Extreme | Test) ^ Warnings)))
      os << "\n******* WARNING *******" << std::endl;

    return os;
  }
UChar LayoutTextFragment::previousCharacter() const {
  if (start()) {
    StringImpl* original = completeText().get();
    if (original && start() <= original->length())
      return (*original)[start() - 1];
  }

  return LayoutText::previousCharacter();
}
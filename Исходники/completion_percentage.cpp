void CompletionPercentage::stepWithNMultipleOf100() {
  currentIteration_ += 1;
  currentDiv_ = ldiv(currentIteration_, totalDiv_.quot);

  if (currentDiv_.rem==0) {
    currentOutput_ = boost::lexical_cast<std::string>(currentDiv_.quot) + "%";
    logTee << std::string(precedingOutput_.length(),'\b') << currentOutput_;
    logTee.flush();
    precedingOutput_ = currentOutput_;
  }
}
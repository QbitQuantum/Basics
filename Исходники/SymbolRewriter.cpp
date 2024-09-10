bool RewriteMapParser::
parseRewriteFunctionDescriptor(yaml::Stream &YS, yaml::ScalarNode *K,
                               yaml::MappingNode *Descriptor,
                               RewriteDescriptorList *DL) {
  bool Naked = false;
  std::string Source;
  std::string Target;
  std::string Transform;

  for (auto &Field : *Descriptor) {
    yaml::ScalarNode *Key;
    yaml::ScalarNode *Value;
    SmallString<32> KeyStorage;
    SmallString<32> ValueStorage;
    StringRef KeyValue;

    Key = dyn_cast<yaml::ScalarNode>(Field.getKey());
    if (!Key) {
      YS.printError(Field.getKey(), "descriptor key must be a scalar");
      return false;
    }

    Value = dyn_cast<yaml::ScalarNode>(Field.getValue());
    if (!Value) {
      YS.printError(Field.getValue(), "descriptor value must be a scalar");
      return false;
    }

    KeyValue = Key->getValue(KeyStorage);
    if (KeyValue.equals("source")) {
      std::string Error;

      Source = Value->getValue(ValueStorage);
      if (!Regex(Source).isValid(Error)) {
        YS.printError(Field.getKey(), "invalid regex: " + Error);
        return false;
      }
    } else if (KeyValue.equals("target")) {
      Target = Value->getValue(ValueStorage);
    } else if (KeyValue.equals("transform")) {
      Transform = Value->getValue(ValueStorage);
    } else if (KeyValue.equals("naked")) {
      std::string Undecorated;

      Undecorated = Value->getValue(ValueStorage);
      Naked = StringRef(Undecorated).lower() == "true" || Undecorated == "1";
    } else {
      YS.printError(Field.getKey(), "unknown key for function");
      return false;
    }
  }

  if (Transform.empty() == Target.empty()) {
    YS.printError(Descriptor,
                  "exactly one of transform or target must be specified");
    return false;
  }

  // TODO see if there is a more elegant solution to selecting the rewrite
  // descriptor type
  if (!Target.empty())
    DL->push_back(new ExplicitRewriteFunctionDescriptor(Source, Target, Naked));
  else
    DL->push_back(new PatternRewriteFunctionDescriptor(Source, Transform));

  return true;
}
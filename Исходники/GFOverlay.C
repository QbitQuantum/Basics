//________________________________________________________
TObjArray GFOverlay::FindAllBetween(const TString &text,
				    const char *startStr, const char *endStr) const
{
  TObjArray result; // TObjStrings...

  if (text.Contains(startStr, TString::kIgnoreCase)) {
    Ssiz_t start = text.Index(startStr);
    while (start != kNPOS && start < text.Length()) {
      TString name = this->FindNextBetween(text, start, startStr, endStr);
      if (!name.IsNull()) {
	result.Add(new TObjString(name));
	start = text.Index(startStr, start + name.Length() + TString(endStr).Length());
      } else {
	break;
      }
    }
  }

  return result;
}
// The caller must free the returned buffer. The buffer is guaranteed
// to have a zero terminator.
HBufC8* ConvToUtf8ZL(const TDesC& name16)
{
  // Note that there is no non-leaving variant of this function, such
  // that the result has no maximum size.
  // 
  // Do not know what happens if any 0 values appear in "name16"; this
  // is not documented.
  HBufC8* name8 = CnvUtfConverter::ConvertFromUnicodeToUtf8L(name16);

  // Ensure there is a zero terminator. Quite a lot of work to do this
  // efficiently.
  TPtr8 ptr = name8->Des();
  if (ptr.Length() < ptr.MaxLength()) {
    ptr.PtrZ(); // modifies HBufC8 content
  } else {
    HBufC8* bigger8 = name8->ReAlloc(ptr.Length() + 1);
    if (bigger8) {
      name8 = bigger8; // name8 already deleted by ReAlloc
      name8->Des().PtrZ(); // modifies HBufC8 content
    } else {
      delete name8;
      User::Leave(KErrNoMemory);
    }
  }

  return name8;
}
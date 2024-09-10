void FarFileName::SetName (const FarFileName& name)
{
  *this = FarFileName::MakeName (GetPath(), name.GetName());
}
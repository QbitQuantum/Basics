void
TimeConfigPanel::OnModified(DataField &df)
{
  if (IsDataField(UTCOffset, df))
    SetLocalTime(df.GetAsInteger());
}
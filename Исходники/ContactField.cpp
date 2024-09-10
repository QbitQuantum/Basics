void
BAddressContactField::_PopValue(BString& str, BString& value)
{
	int32 index = str.FindFirst(fDivider, 0);
	printf("%s\n", str.String());
	if (index == B_ERROR && str.Length() < 1) {
		value.SetTo("");
		return;
	}
	str.MoveInto(value, 0, index);
	str.Remove(0,1);
}
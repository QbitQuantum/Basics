bool
DateValidator::TransferFromWindow()
{
    JEWEL_ASSERT (GetWindow()->IsKindOf(CLASSINFO(TextCtrl)));
    return true;
}
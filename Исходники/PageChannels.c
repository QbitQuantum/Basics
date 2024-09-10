

// КАНАЛ 1 -> Инверсия ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Inverse =
{
    Item_Choice, &mpChanA, {"Инверсия", "Inverse"},
    {
        chanInverseRu,
        chanInverseEn
    },
    EmptyFuncBV,
    {
        {DISABLE_RU, DISABLE_EN},
        {ENABLE_RU, ENABLE_EN}
    },
    (int8*)&INVERSE(A), OnChange_ChanA_Inverse, EmptyFuncVII
};

static void OnChange_ChanA_Inverse(bool active)
{
    FPGA_SetRShift(A, RSHIFT_A);
}


// КАНАЛ 1 -> Множитель ---------------------------------------------------------------------------------------------------------------------------------------------------
static const Choice mcChanA_Divider =
{
    Item_Choice, &mpChanA, {"Делитель", "Divider"},
    {
        chanDividerRu,
        chanDividerEn
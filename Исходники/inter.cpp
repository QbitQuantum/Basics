// アカウント変数のセーブ用
static
void inter_accreg_save_sub(struct accreg *reg, io::WriteFile& fp)
{
    if (reg->reg_num > 0)
    {
        FString line = inter_accreg_tostr(reg);
        fp.put_line(line);
    }
}
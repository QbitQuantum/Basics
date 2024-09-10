static void hugsprim_IsDialogMessageW_17(HugsStackPtr hugs_root)
{
    HsPtr arg1;
    HsPtr arg2;
    HsBool res1;
    arg1 = hugs->getPtr();
    arg2 = hugs->getPtr();
    res1 = IsDialogMessageW(arg1, arg2);
    hugs->putBool(res1);
    hugs->returnIO(hugs_root,1);
}
void  C3DTransform::Initialize()
{

    if (false == g_bInitSinCosTable)
    {
        _control87(_MCW_RC, _RC_DOWN); //设置FPU的舍入模式，在Bilinear函数中需要使用汇编加快float->int

        Build_Sin_Cos_Tables();
        g_bInitSinCosTable = true;
    }
}
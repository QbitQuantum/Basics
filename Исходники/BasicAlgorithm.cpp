/*---------------------------------------------------------
函数名称:	ELFhashUnicode
函数描述:	ELF算法计算字符串Hash Unicode版本 转换后使用了
			Ansi版本
输入参数:	pansiKey	需要Hash的字符串
			ulMod		最大Hash值范围
输出参数:
返回值:		Hash值
其他:

更新维护:	2011.3.20    最初版本
			2011.7.16    添加了Ansi申请内存
---------------------------------------------------------*/
ULONG ELFhashUnicode( PUNICODE_STRING pusKey,ULONG ulMod )
{
    //转换ansi字符串
    ANSI_STRING ansiKey;

    //获取的Hash值
    ULONG ulHash;

    //
    //转换成Ansi
    //
    RtlUnicodeStringToAnsiString(
        &ansiKey,
        pusKey,
        TRUE//让RtlUnicodeStringToAnsiString申请内存
    );

    //
    //直接用ansi版本
    //

    ulHash = ELFhashAnsi(&ansiKey,ulMod);

    //
    //释放内存
    //
    RtlFreeAnsiString(&ansiKey);

    return ulHash;
}
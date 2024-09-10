BOOLEAN SymWAddSymbol(IN PCHAR pszSymbolName, IN ULONG64 uSymbolAddress, IN ULONG uOffset, IN ULONG uBitPosition, IN ULONG uBitLength)
{
    return SymAddSymbol(pszSymbolName, uSymbolAddress, uOffset, uBitPosition, uBitLength);
}
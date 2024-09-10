void CurrencyPairItem::setSymbol(QByteArray symb)
{
    symbol=symb.toUpper();
    if(symbol.size()!=6){symbol.clear();return;}

    currAStr=symbol.left(3);
	currAStrLow=currAStr.toLower();

    currBStr=symbol.right(3);
	currBStrLow=currBStr.toLower();


	currAInfo=baseValues_->currencyMap.value(currAStr,CurencyInfo("$"));
	currBInfo=baseValues_->currencyMap.value(currBStr,CurencyInfo("$"));
	
	currASign=currAInfo.sign;
	currBSign=currBInfo.sign;

	currAName=currAInfo.name;
}
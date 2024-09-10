///////////////////////////
//	Divide everything by nNUm
sMoney sMoney::operator /(int nNum)
{
	sMoney Div(*this);
	Div.Copper/=nNum;
	Div.Gold/=nNum;
	Div.Silver/=nNum;
	Div.Plat/=nNum;
	Div.ReCalcBase();
	return Div;
}
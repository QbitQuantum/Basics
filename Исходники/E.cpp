tr1::shared_ptr<AbstractNumber> E::multiply(tr1::shared_ptr<AbstractNumber>number){
    char newSign = '-';
    if (getSign() == number->getSign())
    {
        newSign = '+';
    }

    if(number -> getName() == "E")
	{
	    if (newSign == '+')
        {
            tr1::shared_ptr<AbstractNumber> exp(new SmartInteger(2));
            tr1::shared_ptr<AbstractNumber> me(new E());
            tr1::shared_ptr<AbstractNumber> ans(new Exponent(me, exp));
            return ans;
        }
        else
        {
            tr1::shared_ptr<AbstractNumber> exp(new SmartInteger(-2));
            tr1::shared_ptr<AbstractNumber> me(new E());
            tr1::shared_ptr<AbstractNumber> ans(new Exponent(me, exp));
            return ans;
        }
	}

	else if (number -> getName() == "Exponent")
	{
	    tr1::shared_ptr<Exponent> numExp = tr1::static_pointer_cast<Exponent>(number);
		if (numExp -> getValue("base") -> getName() == "E")
		{
			tr1::shared_ptr<AbstractNumber> exp = numExp->getValue("power");
			tr1::shared_ptr<AbstractNumber> exp2(new SmartInteger(1));
			tr1::shared_ptr<AbstractNumber> me(new E());

			tr1::shared_ptr<AbstractNumber> ans2(new Exponent(me, exp -> add(exp2), newSign));
			return ans2;
		}
	}
	else if (number->getName() == "Radical") {
		 if (abs(number->getValue("value")->toDouble() - toDouble()) < 0.000001 )
		 {
			 tr1::shared_ptr<AbstractNumber> one(new SmartInteger(1));
			 tr1::shared_ptr<AbstractNumber> invertedRoot(new MultExpression(one, number->getValue("root"), '+'));
			 tr1::shared_ptr<AbstractNumber> me(new E());
			 tr1::shared_ptr<AbstractNumber> output(new Exponent(me, invertedRoot->add(one), newSign));
			 return output;
		 }
		 else
         {
            vector<tr1::shared_ptr<AbstractNumber> > M;
            M.push_back(number);
            M.push_back(shared_from_this());
            tr1::shared_ptr<AbstractNumber> ans3(new MultExpression(M, '+'));
            return ans3;
         }
	 }

    else if(number->getName() == "MultExpression")
    {
        return number->multiply(shared_from_this());
    }
    vector<tr1::shared_ptr<AbstractNumber> > M;
    M.push_back(number);
    M.push_back(shared_from_this());
    tr1::shared_ptr<AbstractNumber> ans3(new MultExpression(M, '+'));
    return ans3;

}
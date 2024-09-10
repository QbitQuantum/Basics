void Fraction_expression::oper(){                       //栈顶运算
    int v0,v1,v2,v3;
    QChar ch;
    Fraction Frac;
    ch=c.top();
    c.pop();
    v3=s.top();
    s.pop();
    v2=s.top();
    s.pop();
    v1=s.top();
    s.pop();
    v0=s.top();
    s.pop();
    switch(ch.unicode()){
    case 43:Frac.Add(v0,v1,v2,v3);
        break;
    case 45:Frac.Sub(v0,v1,v2,v3);
        break;
    case 42:Frac.Mul(v0,v1,v2,v3);
        break;
    case 47:Frac.Div(v0,v1,v2,v3);
        break;
    }
    s.push(Frac.getnumer());
    s.push(Frac.getdenom());

}
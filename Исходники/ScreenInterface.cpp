void updateMoney() {
    if( lastMoney == total_money ){
        return;
    }
    //Prevent overflow
    if (total_money > 2000000000)
    total_money = 2000000000;
    else if (total_money < -2000000000)
    total_money = -2000000000;

    std::ostringstream moneyText;
    int money = total_money;

    if(  abs(money) > 100000000 ){
       moneyText << money/1000000 << _("M");
    } else {
        if( abs(money) > 1000000 ){
            moneyText << money/1000000 << " ";
            money %= 1000000;
            money = abs(money);
            moneyText << std::setw(6);
            moneyText << std::setfill('0');
        }
        moneyText << money;
    }
    moneyText << _("$");

    Component* root = getGameView();
    if( !root ) return;
    while( root->getParent() )
        root = root->getParent();
    Component* moneyParagraphComponent = 0;
    moneyParagraphComponent = root->findComponent( "moneyParagraph" );
    if( moneyParagraphComponent == 0 ) {
        return;
    }
    Paragraph* moneyParagraph = getParagraph( *root, "moneyParagraph");
    if( !moneyParagraph ) return;

    moneyParagraph->setText( moneyText.str() );
    lastMoney = total_money;
}
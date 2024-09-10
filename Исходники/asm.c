static void refundAction()
{
    int c50, c10, c5, c1, m;

    if(money == 0)
        return;
    DCM_High(dcmfd);
    m = money;
    c50 = money/50;
    if(c50 > 0){
        coinRefund(&coin50, c50);
        enableWindow(btn_coin50);
    }
    money %= 50;
    c10 = money/10;
    if(c10 > 0){
        coinRefund(&coin10, c10);
        enableWindow(btn_coin10);
    }
    money %= 10;
    c5 = money/5;
    if(c5 > 0){
        coinRefund(&coin5, c5);
        enableWindow(btn_coin5);
    }
    money %= 5;
    c1 = money;
    if(c1 > 0){
        coinRefund(&coin1, c1);
        enableWindow(btn_coin1);
    }
    money = 0;
    sprintf(buf, "(Refund) $50:%d    $10:%d    $5:%d    $1:%d    Total:$%d", c50, c10, c5, c1, m);
    msgShow(buf);
    disableWindow(btn_refund);
    DCM_Off(dcmfd);
}
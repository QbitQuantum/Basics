void drawP1D(){
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    text.SetNDC(1);
    text.SetTextFont(43);
    text.SetTextSize(16);
    text1.SetNDC(1);
    text1.SetTextFont(43);
    text1.SetTextSize(18);
    text2.SetNDC(1);
    text2.SetTextFont(43);
    text2.SetTextSize(20);
    txt.SetNDC(1);//internal symbol
    txt.SetTextFont(43);
    txt.SetTextSize(21);
    txt.SetTextColor(16);
    txt.SetTextAngle(40);
    lab1.SetNDC(1);
    lab2.SetNDC(1);
    lab3.SetNDC(1);
    lab4.SetNDC(1);
    lab1.SetTextSize(17);
    lab2.SetTextSize(16);
    lab3.SetTextSize(16);
    lab4.SetTextSize(15);
    
    lab1.SetTextFont(73);
    lab2.SetTextFont(43);
    lab3.SetTextFont(43);
    lab4.SetTextFont(43);
    line.SetLineStyle(3);
    
   
    readin(0);
    readin(1);
    
    for (int ipt=0; ipt<1; ipt++) {
        int ic = 0;
        drawplot(ipt, ic);
      //  drawcorr(ipt, ic);
    }

    
}
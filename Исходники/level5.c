void game(void){//ゲーム内容
  int j;
  
  gsetnonblock(ENABLE);//ノンブロッキングモードに
  while(1){	
    gclr(win);//画面消去
   
    //防護壁のx座標設定（レベル５になるまで値変化）
    defence_x=rand()%400;
    if(defence_x > 320){//x座標が340を超えたら340以下の数を減らす
      defence_x -= rand()%320;
    }
    LEVEL5();//レベル５の動作
    
    newpen(win, 1);
    level();// レベルの表記
    timecount();//時間の表記
    human();// 棒人間
    input();//入力待ち
    
    for(i=0; i<kosu; i++){
      j = rand() % 16;// 色はランダム
      if(j < 3) j = j + rand() % 10 + 3;//色は３〜１５のどれか 
      if(a > 2){	 //レベル３、４でときどき黒になって消えて見える
	if(rand()%5 == 0) j = 0;
      }
      newpen(win, j);
      fillrect(win, x_sq[i], y_sq[i], w_sq[i], h_sq[i]);//四角	 
      fillcirc(win, x_circ[i], y_circ[i], r_circ[i], r_circ[i]);//円	        
      LEVEL4();//レベル４のみ出る円（半分を埋め尽くす円）
      
      //落下速度dx,dy
      y_sq[i] -= dy;
      y_circ[i] -= dy;
      
      LEVEL2();//レベル２以上で変化させる
    }
    atari();//当たり判定
    
    msleep(time);// 0.1秒止める
    
    count++;
    if(count/10 == 20*a){// カウント１０回＝約１秒とする
      dy += rand()%2+1;//速度変化は毎回変わる
      dx += rand()%2;//揺れる大きさ
      a++;//レベル
      kosu+=rand()%2+1;//増やす個数は毎回変わる 
      dh+=3;//通常四角の縦幅変化量
      dw+=3;//通常四角の横幅変化量
      dr+=3;//通常円の半径の変化量
    }
  }    
}
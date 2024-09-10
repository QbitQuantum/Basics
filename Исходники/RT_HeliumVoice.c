///////////////////////////////////////////////
//                                           //
//              メイン関数                   //
//                                           //
///////////////////////////////////////////////
int main(void){
    /////////////////////////////////
    //                             //
    //  リアルタイム入出力用変数   //
    //                             //
    /////////////////////////////////
    char   key;                                                     // スルーと処理音の切替用変数
    int in1;                                                        // 入力バッファ番号
    int out1;                                                       // 出力バッファ番号
    int flag;                                                       // 入出力状態のフラグ
    int n;                                                          // バッファ用の時刻
    short in_buf[NUM_BUF][BUF_SIZE]={0};                            // 入力バッファ
    WAVEHDR in_hdr[NUM_BUF];                                        // 入力バッファのヘッダ
	HWAVEIN in_hdl = 0;                                             // 入力(録音)デバイスのハンドル
    short out_buf[NUM_BUF][BUF_SIZE]={0};                           // 出力バッファ
    WAVEHDR out_hdr[NUM_BUF];                                       // 出力バッファのヘッダ
    HWAVEOUT out_hdl = 0;                                           // 出力(再生)デバイスのハンドル

    WAVEFORMATEX wave_format_ex = {WAVE_FORMAT_PCM,                 // PCM
                                 1,                                 // モノラル
                                 Fs,                                // サンプリング周波数
                                 2*Fs,                              // 1秒あたりの音データサイズ（byte）
                                 2,                                 // 音データの最小単位（2byte）
                                 16,                                // 量子化ビット（16bit）
                                 0                                  // オプション情報のサイズ（0byte)
                                };


//************************************************************************//

    ///////////////////////////////
    //                           //
    //      信号処理用変数       //
    //                           //
    ///////////////////////////////
    int t   = 0;                                                    // 入力の時刻
    int to  = 0;                                                    // 出力の時刻
    int hflg= 0;                                                    // 素通しと処理音の状態フラグ
    int i;                                                          // forループ用変数
    double s[MEM_SIZE+1]={0};                                       // 入力データ格納用変数
    double y[MEM_SIZE+1]={0};                                       // 出力データ格納用変数
    
    long int l;                                                     // FFT用変数
    double   x[FFT_SIZE+1] ={0};                                    // FFTの入力
    double   x1[FFT_SIZE+1]={0};                                    // 半フレームシフト時の入力保持用
    double   z1[FFT_SIZE+1]={0};                                    // ハーフオーバーラップの出力保持用

    int    j;                                                       // スペクトル包絡補間用
    double KK, r;                                                   // 音速の倍率
    double NEnv[FFT_SIZE+1]={0};                                    // 処理後の対数スペクトル包絡

    ///////////////////////////////
    //                           //
    //       変数の初期設定      //
    //                           //
    ///////////////////////////////

    init();                                                         //ビット反転，乗み係数の計算
    l = 0;                                                          // FFT開始時刻管理
    KK= 1.7;                                                        // 音速の倍率

//************************************************************************//


    ///////////////////////////////////////
    //                                   //
    //    入出力デバイスのオープン       // 
    //                                   //
    ///////////////////////////////////////
    waveInOpen(&in_hdl, 0, &wave_format_ex, 0, 0, CALLBACK_NULL);   // 入力(録音)デバイスオープン
    for (i = 0; i < NUM_BUF; i++){
        memset(&in_hdr[i], 0, sizeof(WAVEHDR));                     // 全入力バッファを初期化
    }
    waveOutOpen(&out_hdl, 0, &wave_format_ex, 0, 0, CALLBACK_NULL); // 出力(再生)デバイスオープン
    waveOutPause(out_hdl);                                          // サウンドデバイスの一時停止
    for (i = 0; i < NUM_BUF; i++){                                  // 全出力バッファを初期化
        memset(&out_hdr[i], 0, sizeof(WAVEHDR));
    }
    ///////////////////////////////////////
    //                                   //
    //    入出力バッファの初期設定       // 
    //                                   //
    ///////////////////////////////////////
    for (i=0;i<NUM_BUF;i++){                                        // バッファの数だけ繰り返し
        out_hdr[i].lpData = (char *)out_buf[i];                     // 出力バッファデータを更新
        out_hdr[i].dwBufferLength = BUF_SIZE * 2;                   // 出力バッファサイズを設定
        out_hdr[i].dwFlags = 0;                                     // 出力フラグのクリア
        waveOutPrepareHeader(out_hdl, &out_hdr[i], sizeof(WAVEHDR));// 出力バッファをロック
        waveOutWrite(out_hdl, &out_hdr[i], sizeof(WAVEHDR));        // 出力バッファを出力待ちキューに送信
        in_hdr[i].lpData = (char *)in_buf[i];                       // 入力バッファデータの更新
        in_hdr[i].dwBufferLength = BUF_SIZE * 2;                    // 入力バッファサイズを設定
        in_hdr[i].dwFlags = 0;                                      // 入力フラグのクリア
        waveInPrepareHeader(in_hdl, &in_hdr[i], sizeof(WAVEHDR));   // 入力バッファをロック
        waveInAddBuffer(in_hdl, &in_hdr[i], sizeof(WAVEHDR));       // 入力バッファを入力待ちキューに送信
    }
    waveOutRestart(out_hdl);                                        // 音声出力開始
    waveInStart(in_hdl);                                            // 音声入力開始

    in1  = 0;                                                       // 入力バッファ番号の初期化
    out1 = 0;                                                       // 出力バッファ番号の初期化
    flag = 0;                                                       // 入出力判定フラグを0(入力)とする

    printf("[space]--> Through <=> Processing\n");                  // [space]で処理切り替え
    printf("[Enter]--> End\n");                                     // [Enter]で終了
    printf("Through\n");                                            // 素通しであることを表示


    ///////////////////////////////////
    //                               //
    //        メインループ           //
    //                               //
    ///////////////////////////////////
    while (1){
        //////////////////////////
        //                      //
        //    出力書出し処理    //
        //                      //
        //////////////////////////
        if (flag == 1){                                             // flag=1なら出力状態
            if ((out_hdr[out1].dwFlags & WHDR_DONE) != 0){          // 出力バッファのフラグ情報が0でないなら処理を実行
                for (n = 0; n < BUF_SIZE; n++){                     // 出力をBUF_SIZEサンプル分だけ書き出す
                    to=(to+1)%MEM_SIZE;                             // 出力時刻の更新
                    out_buf[out1][n] = y[to]*32768;                 // 出力データを記録
                }
                waveOutUnprepareHeader(out_hdl, &out_hdr[out1], sizeof(WAVEHDR)); // 出力バッファをクリーンアップ
                out_hdr[out1].lpData = (char *)out_buf[out1];       // 出力データを更新
//                out_hdr[out1].dwBufferLength = BUF_SIZE * 2;        // 出力バッファサイズを設定
                out_hdr[out1].dwFlags = 0;                          // 出力バッファのフラグ情報を0にする
                waveOutPrepareHeader(out_hdl, &out_hdr[out1], sizeof(WAVEHDR));   // 情報を更新し出力バッファを準備
                waveOutWrite(out_hdl, &out_hdr[out1], sizeof(WAVEHDR));// 出力待ちキューに出力バッファデータを送信
                out1=(out1+1)%NUM_BUF;                              // 出力バッファ番号を更新
                flag = 0;                                           // 入出力フラグを flag=0 (入力状態) にする
            }
        }
        //////////////////////////
        //                      //
        //    入力読込み処理    //
        //                      //
        //////////////////////////
        if ((in_hdr[in1].dwFlags & WHDR_DONE) != 0){                // 入力バッファのフラグ情報が0でないなら処理を実行
            waveInUnprepareHeader(in_hdl, &in_hdr[in1], sizeof(WAVEHDR)); // 録音済みの入力バッファを選択
            for (n = 0; n < BUF_SIZE; n++){                         // BUF_SIZEサンプル分の入力を読込み，処理する
                t=(t+1)%MEM_SIZE;                                   // 入力時刻の更新
            	s[t] = in_buf[in1][n]/32768.0;                      // 入力バッファからデータ読み込み (正規化)
                y[t] = s[t];                                        // 出力＝入力の素通しをつくる
                if(hflg!=0){                                        // 処理状態フラグが0以外なら信号処理を実行


//************************************************************************//

            ////////////////////////////////////////////////////
            //                                                //
            //              Signal Processing                 //
            //                                                //
            //  現在時刻tの入力 s[t] から出力 y[t] をつくる   //
            //                                                //
            //  ※ tは0からMEM_SIZE-1までをループ             //
            //                                                //
            ////////////////////////////////////////////////////

                    x[l] = x1[l];                                   // FFT_SIZE/2までの入力をx[l]に格納
                    x1[l]= x[FFT_SIZE/2+l]=s[t];                    // FFT_SIZE/2以降の入力をx[l]に格納
                    y[t] = (z[l]+z1[l])/FFT_SIZE;                   // IFFTで得た出力
                    z1[l]= z[FFT_SIZE/2+l];                         // ハーフオーバーラップ用に出力記録

                    if( l>=FFT_SIZE/2){                             // 半フレームごとにFFTを実行
                        for(i=0;i<FFT_SIZE;i++){
                            xin[i]=x[i]*0.5*(1.0-cos(2.0*M_PI*i/(double)FFT_SIZE));// 窓関数をかける
                        }
                        cep_FE();                                       // ケプストラム変換
            
                        ////////////////////////////////////////////////////
                        //                                                //
                        //            ケプストラム信号処理                //
                        //                                                //
                        ////////////////////////////////////////////////////
                        // 対数スペクトル包絡処理
                        for(i=0;i<FFT_SIZE/2-1;i++){
                            r=i/KK;                                     // 対応する周波数番号(有理数)
                            j=(int)r;                                   // rの整数部を取得
                            r=r-j;                                      // rの小数部を取得
                            NEnv[i]=(1.0-r)*XEnv[j] + r *XEnv[j+1];     // 線形補間により振幅値を決める
                            if(j>FFT_SIZE/2-1)NEnv[i]=-10;              // ナイキスト周波数を超える分は小さく
                            NEnv[FFT_SIZE-i]=NEnv[i];                   // 対象スペクトルの作成
                        }
                        for(i=0;i<FFT_SIZE;i++){
                            XEnv[i]=NEnv[i];
                        }

                        icep_FE();                                      // 逆変換
                        l=0;
                    }
                    l++;                                            // FFT用の時刻管理

//************************************************************************//

                    y[t]=atan(y[t])/(M_PI/2.0);                     // クリップ防止
                }
            }
            in_hdr[in1].dwFlags = 0;                                // 入力バッファのフラグ情報を0にする
            waveInPrepareHeader(in_hdl, &in_hdr[in1], sizeof(WAVEHDR));   // 情報を更新し入力バッファを準備
            waveInAddBuffer(in_hdl, &in_hdr[in1], sizeof(WAVEHDR)); // 入力待ちキューに入力バッファデータを送信
            in1=(in1+1)%NUM_BUF;                                    // 入力バッファの更新
            flag = 1;                                               // 入出力フラグを flag=1 (出力状態)にする
        }

        ////////////////////////////////////////////////////
        //                                                //
        //        キーボード入力に対する処理の設定        //
        //                                                //
        //                                                //
        //  [デフォルト設定]                              //
        //  ・スペースキーで素通しと信号処理を切り替え    //
        //  ・Enterキーでプログラム終了                   //
        //                                                //
        ////////////////////////////////////////////////////
        if (kbhit()){                                               // キーボード入力があったか
            key = getch();                                          // キーのチェック
            if (key == 32){                                         // スペースキーが押されとき
            	hflg=(hflg+1)%2;                                    // 処理フラグ変更
                if(hflg==1) printf("Processing\n");                 // 処理中であることを表示
                else        printf("Through\n");                    // 素通しであることを表示
            }
            if (key == 13){                                         // Enterキーが押されたとき
                waveInStop(in_hdl);                                 // 入力を停止
                for (i = 0; i < NUM_BUF; i++){                      // 全入力バッファのアンロック
                    if ((in_hdr[i].dwFlags & WHDR_PREPARED) != 0){
                        waveInUnprepareHeader(in_hdl, &in_hdr[i], sizeof(WAVEHDR ));
                    }
                }
                waveInClose(in_hdl);                                // 入力(録音)デバイスのクローズ
                waveOutPause(out_hdl);                              // 出力を停止
                for (i = 0; i < NUM_BUF; i++){
                    if ((out_hdr[i].dwFlags & WHDR_PREPARED) != 0){ // 全出力バッファのアンロック
                        waveOutUnprepareHeader(out_hdl, &out_hdr[i], sizeof(WAVEHDR));
                    }
                }
                waveOutClose(out_hdl);                              // 出力(再生)デバイスのクローズ
                return 0;
            }
        }
    }                                                               //メインループ終わり
}
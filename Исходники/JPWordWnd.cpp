void CJPWordWnd::OnPaint()
{
#define JP_PAINT_X_ 5
    CPaintDC dc(this);
    CDC dcMemory;
    CBitmap bitmap;
    if (!dc.IsPrinting())
    {
        if (dcMemory.CreateCompatibleDC(&dc))
        {
            if (bitmap.CreateCompatibleBitmap(&dc,clientRect.right,clientRect.bottom))
            {
                dcMemory.SelectObject(&bitmap);
                /*CBrush br;
                br.CreateSysColorBrush(CSCB);
                br.CreateSolidBrush(RGB(200,200,200));
                dcMemory.FillRect(&clientRect,&br);*/
                //设置画笔
                CPen pen;
                pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
                CPen *pOldPen = dcMemory.SelectObject(&pen);
                //设置画刷
                CBrush brush;
                brush.CreateSolidBrush( RGB(200,255,000) );
                CBrush* pOldBrush = dcMemory.SelectObject(&brush);
                //填充圆角矩形
                dcMemory.RoundRect(clientRect.left+4, clientRect.top+4, clientRect.right-4, clientRect.bottom-4, 20, 20);

                // 将字体选进DC
                CFont* pOldFont = dcMemory.SelectObject(&fontZhuYin);
                //设置字体背景色
                COLORREF oldBkColor = dcMemory.SetBkColor(RGB(200,255,0));
                COLORREF oldTextColor = dcMemory.SetTextColor(RGB(0,0,0));

                //设置裁剪区域
                CRgn rgn ;
                rgn.CreateRoundRectRgn(clientRect.left+6, clientRect.top+6, clientRect.right-8, clientRect.bottom-8, 20, 20);
                dcMemory.SelectClipRgn(&rgn);


                if(bInit)
                {
                    //cout<<"paint^"<<endl;
                    allBaseX = JP_PAINT_X_;
                    allBaseY = 0;
                    //一行总体高度,换行时使用
                    int rowHeight = -1;
                    //单个注音字符的绘制宽度，绘制声调线时用
                    int charZhuYinWidth = -1;
                    // 注音字符高度
                    int charZhuYinHeight = -1;

                    // 单词字符高度
                    int charWordHeight = -1;

                    //声调线高度
                    int toneHeight = 0;//10 ;

                    //绘制声调线的纵向基准
                    int toneBaseY = allBaseY + 5 ;

                    //绘制注音的纵向基准
                    int zhuYinBaseY = toneBaseY + toneHeight + 2 ;

                    //绘制单词的纵向基准
                    int wordBaseY = -1 ;


                    //循环绘制各个单词和注音
                    for(int i=0 ; i< jpword.wordCount ; i++ )
                    {
                        //取得当前单词
                        CString currentWord = CString( jpword.getWordAt(i).c_str());
                        //取得当前注音
                        CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
                        //取得单词长度（字符数）
                        int wordLen = jpword.getWordLengthAt(i);
                        //取得注音长度（字符数）
                        int zhuYinLen = jpword.getZhuYinLengthAt(i);
                        //将注音字体选进DC
                        dcMemory.SelectObject(&fontZhuYin);
                        //计算注音占据的矩形区域
                        CRect rcZhuYin = CRect(0,0,0,0);
                        dcMemory.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
                        // 计算字符的宽度和高度
                        if(zhuYinLen > 0)
                        {
                            //获取注音字符的绘制宽度
                            charZhuYinWidth = rcZhuYin.Width() / zhuYinLen;
                            //获取注音字符的绘制高度
                            charZhuYinHeight = rcZhuYin.Height();
                        }
                        //当前注音为空
                        else
                        {
                            //用字符わ来计算
                            dcMemory.DrawText( _T("わ"), &rcZhuYin, DT_CALCRECT);
                            //获取注音字符的绘制宽度
                            charZhuYinWidth = rcZhuYin.Width();
                            //获取注音字符的绘制高度
                            charZhuYinHeight = rcZhuYin.Height();
                        }

                        //获取单词纵向绘制基准位置（只有第一次需要计算）			}
                        if(wordBaseY==-1)
                        {
                            wordBaseY = zhuYinBaseY + charZhuYinHeight +3;
                        }

                        //选择单词绘制字体
                        dcMemory.SelectObject(&fontWord);
                        //计算单词占据的矩形区域
                        CRect rcWord = CRect(0,0,0,0);
                        dcMemory.DrawText( currentWord , &rcWord, DT_CALCRECT);

                        //获取单词字体绘制高度
                        if(charWordHeight==-1)
                        {
                            //获取注音字符的绘制高度
                            charWordHeight = rcWord.Height();
                        }

                        //计算一行单词的高度（包括声调，注音和单词）（只有第一次需要计算）
                        if(rowHeight==-1)
                        {
                            rowHeight = toneHeight + charZhuYinHeight + charWordHeight +10 ;
                        }

                        //取出两个矩形中的较大宽度
                        int finalWidth = rcWord.Width();
                        if(rcWord.Width()<rcZhuYin.Width())
                        {
                            finalWidth = rcZhuYin.Width();
                        }

                        //如果横向基准+绘制区域宽度 大于窗口宽度则折行显示
                        if( finalWidth + allBaseX > clientRect.Width() )
                        {
                            //横向位置从头开始
                            allBaseX = JP_PAINT_X_;
                            //纵向位置 = 字体高度+
                            allBaseY += rowHeight ;

                        }
                        //当前显示模式为单词模式
                        if( showMode==sm_show_word )
                        {
                            //选择单词字体
                            dcMemory.SelectObject( fontWord );
                            //移动新矩形至单词基准位置
                            CPoint pos(allBaseX, wordBaseY + allBaseY);
                            CSize size(finalWidth , rcWord.Height());
                            CRect rc( pos,size );
                            //绘制单词
                            dcMemory.DrawText( currentWord, rc, DT_CENTER );
                        }
                        //注音模式
                        else if( showMode==sm_show_zhuyin )
                        {
                            //选择注音字体
                            dcMemory.SelectObject( fontZhuYin );
                            CPoint pos(allBaseX, zhuYinBaseY + allBaseY);
                            CSize size(finalWidth , rcZhuYin.Height());
                            CRect rc( pos,size );
                            //移动新矩形至注音基准位置

                            //如果当前词没有注音则绘制单词，否则绘制注音
                            if( currentZhuYin.IsEmpty() )
                            {
                                //绘制单词
                                dcMemory.DrawText( currentWord, rc, DT_CENTER );
                            }
                            else
                            {
                                //绘制注音
                                dcMemory.DrawText( currentZhuYin,rc, DT_CENTER );
                            }
                            /*
                            //声调信息必须为3的倍数，否则不绘制
                            if( jpword.tone.size()%3 == 0 )
                            {
                            //绘制声调线
                            for( size_t i=0; i<jpword.tone.size(); i+=3 )
                            {

                            //声调类型
                            int style = jpword.tone[i];
                            //划横线
                            dcMemory.MoveTo( jpword.tone[i+1]*charZhuYinWidth  ,toneBaseY + allBaseY );
                            dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth  ,toneBaseY + allBaseY );
                            //画下降线
                            if( style == CJPWordInfoEx::jp_tone_down )
                            {
                            dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
                            }

                            }
                            }*/

                        }
                        //正常模式
                        else
                        {
                            //选择单词字体
                            dcMemory.SelectObject( fontWord );
                            CPoint pos(allBaseX, wordBaseY + allBaseY);
                            CSize size(finalWidth , rcWord.Height());
                            CRect rc( pos,size );
                            //移动新矩形至单词基准位置
                            //绘制单词
                            dcMemory.DrawText( currentWord, rc, DT_CENTER );
                            //选择注音字体
                            dcMemory.SelectObject( fontZhuYin );
                            //移动新矩形至注音基准位置
                            pos = CPoint(allBaseX, zhuYinBaseY + allBaseY);
                            size = CSize(finalWidth , rcZhuYin.Height());
                            rc = CRect( pos,size );
                            //绘制注音
                            dcMemory.DrawText( currentZhuYin,rc, DT_CENTER );
                            /*
                            //声调信息必须为3的倍数，否则不绘制
                            if( jpword.tone.size()%3 == 0 )
                            {
                            //绘制声调线
                            for( size_t i=0; i<jpword.tone.size(); i+=3 )
                            {

                            //声调类型
                            int style = jpword.tone[i];
                            //划横线
                            dcMemory.MoveTo( jpword.tone[i+1]*charZhuYinWidth +6 ,toneBaseY + allBaseY );
                            dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth -6 ,toneBaseY + allBaseY );
                            //画下降线
                            if( style == CJPWordInfoEx::jp_tone_down )
                            {
                            dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
                            }

                            }
                            }
                            */
                        }


                        //计算下一个横向基准位置
                        allBaseX += finalWidth+2;
                    }
                }
                //恢复画笔
                dcMemory.SelectObject( pOldPen);
                pen.DeleteObject();
                //恢复画刷
                dcMemory.SelectObject( pOldBrush );
                brush.DeleteObject();
                //释放裁剪区域
                dcMemory.SelectClipRgn(NULL);
                // 恢复旧字体
                dcMemory.SelectObject( pOldFont );
                dcMemory.SetTextColor( oldTextColor );
                dcMemory.SetBkColor( oldBkColor );
                dc.BitBlt(clientRect.left,clientRect.top,clientRect.right,clientRect.bottom,&dcMemory,0,0,SRCCOPY);
                bitmap.DeleteObject();
            }
        }
    }
}
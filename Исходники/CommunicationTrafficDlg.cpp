void CCommunicationTrafficDlg::OnBnClickedCopy()
{
//--------------------------------------------------------------------------------------------------------------------

   
    CArray <int, int> aryListSel;
    int nCount= m_DataList.GetSelCount();
    aryListSel.SetSize(nCount);
    m_DataList.GetSelItems(nCount, aryListSel.GetData()); 

  //  aryListSel中存的就是选中列的index值，如果需要取内容，加以下语句：
        CString str,content;
        for (int i= nCount-1; i>= 0; i--)
        {
            m_DataList.GetText(aryListSel.GetAt(i), (CString&)str);
            str+=_T("\n");
            content==str;
        }


//--------------------------------------------------------------------------------------------------------------------
     
    HGLOBAL hClip; 
    //定义一个HGLOBAL句柄变量用来指向分配的内存块
    if (OpenClipboard())
    {
        EmptyClipboard();                            //将剪贴板内容清空
        hClip=GlobalAlloc(GMEM_MOVEABLE,content.GetLength()+1); 
        //在堆上分配可移动的内存块，程序返回一个内存句柄
        char * buff;                                 //定义指向字符型的指针变量
        buff=(char*)GlobalLock(hClip);
        //对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加1
        strcpy(buff,(char*)content.GetBuffer());
        //将用户输入的数据复制到指针变量中，实际上就是复制到分配的内存块中
        GlobalUnlock(hClip);
        //数据写入完毕，进行解锁操作，并将引用计数器数字减1
        SetClipboardData(CF_TEXT,hClip);
        //将存放有数据的内存块放入剪贴板的资源管理中
        CloseClipboard();
        //关闭剪贴板，释放剪贴板资源的占用权
      
    }
//--------------------------------------------------------------------------------------------------------------------
}
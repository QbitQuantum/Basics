    // 通过ole的方式读取单元格内容，由于ole才支持公式，所以tokit只在单元格含公式时才调用本接口，除此之外通过libxl库来调用，因为libxl读取速度快很多
    std::string& ole_get_cell_str(COleSafeArray &ole_safe_array, int row, int col)
    {
        static const int prec=std::numeric_limits<long long>::digits10 + 10; // 18
        static COleVariant vResult;
        static CString str;

        //字符串
        static long read_address[2];
        static VARIANT val;
        static std::string result;

        read_address[0] = row;
        read_address[1] = col;
        ole_safe_array.GetElement(read_address, &val);
        vResult = val;

        switch(vResult.vt){
        case VT_BSTR:
        {
            //字符串
            const wchar_t *w = vResult.bstrVal;
            // const std::wstring wstr(w);
            return strtool::wstring2string(w);
        }
        //单元格空的
        case VT_EMPTY:
        //整数
        case VT_INT:
            result = "";
            break;
        //8字节的数字 
        case VT_R8:
        {
            static std::ostringstream oss;
            oss.str("");
            oss.precision(prec);//覆盖默认精度

            oss << vResult.dblVal;
            result = oss.str();
            break;
        }
        //时间格式
        case VT_DATE:
        {
            SYSTEMTIME st;
            VariantTimeToSystemTime(vResult.date, &st);
            CTime tm(st); 
            str = tm.Format("%Y-%m-%d");
            break;
        }

        default:
            result = "";
            break;
        }

        return result;
    }
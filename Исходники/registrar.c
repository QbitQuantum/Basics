static HRESULT do_process_key(LPCOLESTR *pstr, HKEY parent_key, strbuf *buf, BOOL do_register)
{
    LPCOLESTR iter = *pstr;
    HRESULT hres;
    LONG lres;
    HKEY hkey = 0;
    strbuf name;
    
    enum {
        NORMAL,
        NO_REMOVE,
        IS_VAL,
        FORCE_REMOVE,
        DO_DELETE
    } key_type = NORMAL; 

    static const WCHAR wstrNoRemove[] = {'N','o','R','e','m','o','v','e',0};
    static const WCHAR wstrForceRemove[] = {'F','o','r','c','e','R','e','m','o','v','e',0};
    static const WCHAR wstrDelete[] = {'D','e','l','e','t','e',0};
    static const WCHAR wstrval[] = {'v','a','l',0};

    iter = *pstr;
    hres = get_word(&iter, buf);
    if(FAILED(hres))
        return hres;
    strbuf_init(&name);

    while(buf->str[1] || buf->str[0] != '}') {
        key_type = NORMAL;
        if(!lstrcmpiW(buf->str, wstrNoRemove))
            key_type = NO_REMOVE;
        else if(!lstrcmpiW(buf->str, wstrForceRemove))
            key_type = FORCE_REMOVE;
        else if(!lstrcmpiW(buf->str, wstrval))
            key_type = IS_VAL;
        else if(!lstrcmpiW(buf->str, wstrDelete))
            key_type = DO_DELETE;

        if(key_type != NORMAL) {
            hres = get_word(&iter, buf);
            if(FAILED(hres))
                break;
        }
        TRACE("name = %s\n", debugstr_w(buf->str));
    
        if(do_register) {
            if(key_type == IS_VAL) {
                hkey = parent_key;
                strbuf_write(buf->str, &name, -1);
            }else if(key_type == DO_DELETE) {
                TRACE("Deleting %s\n", debugstr_w(buf->str));
                lres = RegDeleteTreeW(parent_key, buf->str);
            }else {
                if(key_type == FORCE_REMOVE)
                    RegDeleteTreeW(parent_key, buf->str);
                lres = RegCreateKeyW(parent_key, buf->str, &hkey);
                if(lres != ERROR_SUCCESS) {
                    WARN("Could not create(open) key: %08x\n", lres);
                    hres = HRESULT_FROM_WIN32(lres);
                    break;
                }
            }
        }else if(key_type != IS_VAL && key_type != DO_DELETE) {
            strbuf_write(buf->str, &name, -1);
            lres = RegOpenKeyW(parent_key, buf->str, &hkey);
              if(lres != ERROR_SUCCESS)
                WARN("Could not open key %s: %08x\n", debugstr_w(name.str), lres);
        }

        if(key_type != DO_DELETE && *iter == '=') {
            iter++;
            hres = get_word(&iter, buf);
            if(FAILED(hres))
                break;
            if(buf->len != 1) {
                WARN("Wrong registry type: %s\n", debugstr_w(buf->str));
                hres = DISP_E_EXCEPTION;
                break;
            }
            if(do_register) {
                switch(buf->str[0]) {
                case 's':
                    hres = get_word(&iter, buf);
                    if(FAILED(hres))
                        break;
                    lres = RegSetValueExW(hkey, name.len ? name.str :  NULL, 0, REG_SZ, (PBYTE)buf->str,
                            (lstrlenW(buf->str)+1)*sizeof(WCHAR));
                    if(lres != ERROR_SUCCESS) {
                        WARN("Could set value of key: %08x\n", lres);
                        hres = HRESULT_FROM_WIN32(lres);
                        break;
                    }
                    break;
                case 'd': {
                    WCHAR *end;
                    DWORD dw;
                    if(*iter == '0' && iter[1] == 'x') {
                        iter += 2;
                        dw = strtolW(iter, &end, 16);
                    }else {
                        dw = strtolW(iter, &end, 10);
                    }
                    iter = end;
                    lres = RegSetValueExW(hkey, name.len ? name.str :  NULL, 0, REG_DWORD,
                            (PBYTE)&dw, sizeof(dw));
                    if(lres != ERROR_SUCCESS) {
                        WARN("Could set value of key: %08x\n", lres);
                        hres = HRESULT_FROM_WIN32(lres);
                        break;
                    }
                    break;
                }
                default:
                    WARN("Wrong resource type: %s\n", debugstr_w(buf->str));
                    hres = DISP_E_EXCEPTION;
                };
                if(FAILED(hres))
                    break;
            }else {
                if(*iter == '-')
                    iter++;
                hres = get_word(&iter, buf);
                if(FAILED(hres))
                    break;
            }
        }else if(key_type == IS_VAL) {
            WARN("value not set!\n");
            hres = DISP_E_EXCEPTION;
            break;
        }

        if(key_type != IS_VAL && key_type != DO_DELETE && *iter == '{' && isspaceW(iter[1])) {
            hres = get_word(&iter, buf);
            if(FAILED(hres))
                break;
            hres = do_process_key(&iter, hkey, buf, do_register);
            if(FAILED(hres))
                break;
        }

        TRACE("%x %x\n", do_register, key_type);
        if(!do_register && (key_type == NORMAL || key_type == FORCE_REMOVE)) {
            TRACE("Deleting %s\n", debugstr_w(name.str));
            RegDeleteKeyW(parent_key, name.str);
        }

        if(hkey && key_type != IS_VAL)
            RegCloseKey(hkey);
        hkey = 0;
        name.len = 0;
        
        hres = get_word(&iter, buf);
        if(FAILED(hres))
            break;
    }

    HeapFree(GetProcessHeap(), 0, name.str);
    if(hkey && key_type != IS_VAL)
        RegCloseKey(hkey);
    *pstr = iter;
    return hres;
}
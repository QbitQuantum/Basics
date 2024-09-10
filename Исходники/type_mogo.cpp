    void FillVObjectDefaultValue(const CEntityParent* pEntity, const string& strAttri, VOBJECT& v, const string& strDefault)
    {
        if(strDefault.empty())
        {
            FillVObjectInitValue(pEntity, strAttri, v);
            return;
        }

        switch(v.vt)
        {
            case V_UINT8:
            {
                v.vv.u8 = (uint8_t)atoi(strDefault.c_str());
                break;
            }
            case V_INT8:
            {
                v.vv.i8 = (int8_t)atoi(strDefault.c_str());
                break;
            }
            case V_UINT16:
            {
                v.vv.u16 = (uint16_t)atoi(strDefault.c_str());
                break;
            }
            case V_INT16:
            {
                v.vv.i16 = (int16_t)atoi(strDefault.c_str());
                break;
            }
            case V_UINT32:
            {
                v.vv.u32 = (uint32_t)atoll(strDefault.c_str());
                break;
            }
            case V_INT32:
            {
                v.vv.i32 = (int32_t)atoll(strDefault.c_str());
                break;
            }
            case V_UINT64:
            {
                v.vv.u64 = (uint64_t)atoll(strDefault.c_str());
                break;
            }
            case V_INT64:
            {
                v.vv.i64 = (int64_t)atoll(strDefault.c_str());
                break;
            }
            case V_FLOAT32:
            {
                v.vv.f32 = (float32_t)atof(strDefault.c_str());
                break;
            }
            case V_FLOAT64:
            {
                v.vv.f64 = (float64_t)atof(strDefault.c_str());
                break;
            }
            case V_STR:
            {
                v.vv.s = new string(strDefault);
                break;
            }
            case V_BLOB:
            {
                v.vv.p = new charArrayDummy;
                break;
            }
            case V_LUATABLE:
            {
                lua_State* L = GetWorld()->GetLuaState();

#ifdef __USE_MSGPACK

                if( LuaUnpickleFromBlob(L, (char*)strDefault.c_str(), (uint16_t)strDefault.size()))
#else
                if( LuaUnpickleFromString(L, strDefault) )
#endif
                {
                    CLuaCallback& cb = GetWorld()->GetLuaTables();
                    v.vv.i32 = (int32_t)cb.Ref(L);
                    break;
                }
                else
                {
                    //初始化失败,give warning,todo
                    v.vv.i32 = -1;
                }
                break;
            }
            case V_LUA_OBJECT:
            {
                v.vv.i32 = -1;
                break;
            }
            case V_REDIS_HASH:
            {
                lua_State* L = GetWorld()->GetLuaState();
                CRedisHash* p = CreateRedisHash(L);
                p->SetEntity(pEntity, strAttri);
                v.vv.p = p;
                break;
            }
            default:
            {
                //nothing to do
            }
        }

    }
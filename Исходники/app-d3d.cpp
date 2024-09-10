char* app_display_querymodes()
{
    IDXGIFactory* factory;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
        return NULL;

    IDXGIAdapter* adapter;
    uint adapter_id = 0;
    DXGI_ADAPTER_DESC desc;
    char gpu_desc[128];
    size_t outsz;

    /* start json data (adapter array) */
    json_t jroot = json_create_arr();

    /* read adapters */
    while (factory->EnumAdapters(adapter_id, &adapter) != DXGI_ERROR_NOT_FOUND)  {
        adapter->GetDesc(&desc);
        str_widetomb(gpu_desc, desc.Description, sizeof(gpu_desc));

        json_t jadapter = json_create_obj();
        json_additem_toarr(jroot, jadapter);

        json_additem_toobj(jadapter, "name", json_create_str(gpu_desc));
        json_additem_toobj(jadapter, "id", json_create_num((fl64)adapter_id));

        /* enumerate monitors */
        json_t joutputs = json_create_arr();
        json_additem_toobj(jadapter, "outputs", joutputs);

        IDXGIOutput* output;
        uint output_id = 0;

        while (adapter->EnumOutputs(output_id, &output) != DXGI_ERROR_NOT_FOUND)    {
            json_t joutput = json_create_obj();
            json_additem_toarr(joutputs, joutput);

            json_additem_toobj(joutput, "id", json_create_num((fl64)output_id));

            /* enumerate modes */
            json_t jmodes = json_create_arr();
            json_additem_toobj(joutput, "monitors", jmodes);

            uint mode_cnt;
            HRESULT hr = output->GetDisplayModeList(DEFAULT_DISPLAY_FORMAT, 0, &mode_cnt, NULL);
            if (SUCCEEDED(hr))  {
                DXGI_MODE_DESC* modes = (DXGI_MODE_DESC*)ALLOC(sizeof(DXGI_MODE_DESC) * mode_cnt, 0);
                ASSERT(modes);
                output->GetDisplayModeList(DEFAULT_DISPLAY_FORMAT, 0, &mode_cnt, modes);
                for (uint i = 0; i < mode_cnt; i++)   {
                    if (modes[i].RefreshRate.Denominator != 1)
                        continue;

                    json_t jmode = json_create_obj();
                    json_additem_toobj(jmode, "width", json_create_num((fl64)modes[i].Width));
                    json_additem_toobj(jmode, "height", json_create_num((fl64)modes[i].Height));
                    json_additem_toobj(jmode, "refresh-rate",
                        json_create_num((fl64)modes[i].RefreshRate.Numerator));
                    json_additem_toarr(jmodes, jmode);
                }
                FREE(modes);
            }

            output_id ++;
        }

        adapter->Release();
        adapter_id ++;
    }

    factory->Release();

    char* r = json_savetobuffer(jroot, &outsz, FALSE);
    json_destroy(jroot);

    return r;
}
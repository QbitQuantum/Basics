static GstCaps *
gst_dshowvideosrc_get_caps (GstBaseSrc * basesrc, GstCaps *filter)
{
    HRESULT hres = S_OK;
    IBindCtx *lpbc = NULL;
    IMoniker *videom;
    DWORD dwEaten;
    GstDshowVideoSrc *src = GST_DSHOWVIDEOSRC (basesrc);
    gunichar2 *unidevice = NULL;

    if (src->caps) {
        return gst_caps_ref (src->caps);
    }

    if (!src->device) {
        src->device =
            gst_dshow_getdevice_from_devicename (&CLSID_VideoInputDeviceCategory,
                    &src->device_name);
        if (!src->device) {
            GST_ERROR ("No video device found.");
            return NULL;
        }
    }

    unidevice =
        g_utf8_to_utf16 (src->device, strlen (src->device), NULL, NULL, NULL);

    if (!src->video_cap_filter) {
        hres = CreateBindCtx (0, &lpbc);
        if (SUCCEEDED (hres)) {
            hres =
                MkParseDisplayName (lpbc, (LPCOLESTR) unidevice, &dwEaten, &videom);
            if (SUCCEEDED (hres)) {
                hres = videom->BindToObject (lpbc, NULL, IID_IBaseFilter,
                                             (LPVOID *) & src->video_cap_filter);
                videom->Release ();
            }
            lpbc->Release ();
        }
    }

    if (!src->caps) {
        src->caps = gst_caps_new_empty ();
    }

    if (src->video_cap_filter && gst_caps_is_empty (src->caps)) {
        /* get the capture pins supported types */
        IPin *capture_pin = NULL;
        IEnumPins *enumpins = NULL;
        HRESULT hres;

        hres = src->video_cap_filter->EnumPins (&enumpins);
        if (SUCCEEDED (hres)) {
            while (enumpins->Next (1, &capture_pin, NULL) == S_OK) {
                IKsPropertySet *pKs = NULL;
                hres =
                    capture_pin->QueryInterface (IID_IKsPropertySet, (LPVOID *) & pKs);
                if (SUCCEEDED (hres) && pKs) {
                    DWORD cbReturned;
                    GUID pin_category;
                    RPC_STATUS rpcstatus;

                    hres =
                        pKs->Get (AMPROPSETID_Pin,
                                  AMPROPERTY_PIN_CATEGORY, NULL, 0, &pin_category, sizeof (GUID),
                                  &cbReturned);

                    /* we only want capture pins */
                    if (UuidCompare (&pin_category, (UUID *) & PIN_CATEGORY_CAPTURE,
                                     &rpcstatus) == 0) {
                        {
                            GstCaps *caps =
                                gst_dshowvideosrc_getcaps_from_streamcaps (src, capture_pin);
                            if (caps) {
                                gst_caps_append (src->caps, caps);
                            } else {
                                caps = gst_dshowvideosrc_getcaps_from_enum_mediatypes (src, capture_pin);
                                if (caps)
                                    gst_caps_append (src->caps, caps);
                            }
                        }
                    }
                    pKs->Release ();
                }
                capture_pin->Release ();
            }
            enumpins->Release ();
        }
    }

    if (unidevice) {
        g_free (unidevice);
    }

    if (src->caps) {
        if (filter) {
            return gst_caps_intersect_full (filter, src->caps,
                                            GST_CAPS_INTERSECT_FIRST);
        } else {
            return gst_caps_ref (src->caps);
        }
    }

    return NULL;
}
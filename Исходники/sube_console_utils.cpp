void SUBE_CREATE_DEFAULT_SUBE_DEPO_UNITE_ENT_HESAPLARI()
{
    SQL_QUERY query ( DB );

    query.PREPARE_SELECT ( "sub_subeler","sube_id" );
    if ( query.SELECT() > 0 ) {
        return;
    }

    query.PREPARE_INSERT   (   " sub_subeler","sube_id","sube_kodu, sube_adi,sube_port_cekler_hsp_id, "
                               " sube_tah_cekler_hsp_id,           sube_tem_cekler_hsp_id,           sube_kar_cekler_hsp_id, "
                               " sube_port_snt_hsp_id,             sube_tah_snt_hsp_id,              sube_tem_snt_hsp_id, "
                               " sube_pro_snt_hsp_id,              sube_port_snt_ileri_trh_hsp_id,   sube_tah_snt_ileri_trh_hsp_id, "
                               " sube_tem_snt_ileri_trh_hsp_id,    sube_borc_snt_hsp_id,             sube_borc_snt_ileri_trh_hsp_id, "
                               " sube_sup_alacaklar_hsp_id,        sube_tah_edlmyn_cekler_hsp_id,    sube_tah_edlmyn_snt_hsp_id, "
                               " sube_yurtici_satis_hsp_id,        sube_hizmet_urt_maliyet_hsp_id, "
                               " sube_prs_gdrlr_hsp_id         , sube_sarf_malzemeleri_hsp_id ,"
                               " sube_imalattan_giris_hsp_id    , "
                               " kasa_ent_hesap_id              ,                                    "
                               " cari_alici_ent_hesap_id        , cari_satici_ent_hesap_id ,         "
                               " banka_ent_hesap_id             , ver_cek_ent_hesap_id             , "
                               " odeme_emirleri_ent_hesap_id    ,                                    "
                               " pos_ent_hesap_id               ,                                    "
                               " kk_ent_hesap_id                , prk_gider_ent_hesap_id           , "
                               " urunler_ent_hesap_id           ,                                    "
                               " hizmetler_ent_hesap_id         , demirbaslar_ent_hesap_id,          "
                               " pos_kom_gideri_ent_hesap_id    ,                                    "
                               " prs_avanslari_ent_hesap_id     , personel_borclari_ent_hesap_id   , "
                               " prs_damga_vergisi_ent_hesap_id , personel_vergi_ent_hesap_id      , "
                               " prk_gelir_ent_hesap_id         ,                                    "
                               " prs_ssk_isci_payi_hesap_id     ,                                    "
                               " prs_ssk_isveren_payi_hesap_id  ,                                    "
                               " prs_issizlik_sgk_isci_hsp_id   ,                                    "
                               " prs_issizlik_sgk_isv_hsp_id    ,                                    "
                               " asg_gecim_ind_hesap_id         ,                                    "
                               " isveren_payi_giderleri_hps_id  ,                                    "
                               " bir_amortismanlar_hsp_id       ,                                    "
                               " amor_giderleri_hsp_id          ,                                    "
                               " sgdp_prim_yuzde_isc_hsp_id     , sgdp_prim_yuzde_isv_hsp_id        ,"
                               " kidem_tazminati_hesap_id       , ihbar_tazminati_hesap_id          ,"
                               " dmr_satis_kar_ent_hesap_id     , dmr_satis_zarar_ent_hesap_id      ,"
                               " sendika_odeme_hesap_id         , smmm_alinan_hizmet_hesap_id       ,"
                               " smmm_gelir_vergisi_hesap_id    , smmm_satilan_hizmet_hesap_id      ,"
                               " isy_5510_nolu_kanun_hesap_id   , satistan_iade_hesap_id            ,"
                               " ortaklara_borclar_hesap_id   ");

    query.SET_VALUE ( ":sube_kodu"                          , "MRK"                   );
    query.SET_VALUE ( ":sube_adi"                           , "MERKEZ"                );
    query.SET_VALUE ( ":sube_port_cekler_hsp_id"            , MUH_GET_HESAP_ID("101") );
    query.SET_VALUE ( ":sube_tah_cekler_hsp_id"             , MUH_GET_HESAP_ID("101") );
    query.SET_VALUE ( ":sube_tem_cekler_hsp_id"             , MUH_GET_HESAP_ID("101") );
    query.SET_VALUE ( ":sube_kar_cekler_hsp_id"             , MUH_GET_HESAP_ID("101") );
    query.SET_VALUE ( ":sube_port_snt_hsp_id"               , MUH_GET_HESAP_ID("121") );
    query.SET_VALUE ( ":sube_tah_snt_hsp_id"                , MUH_GET_HESAP_ID("121") );
    query.SET_VALUE ( ":sube_tem_snt_hsp_id"                , MUH_GET_HESAP_ID("121") );
    query.SET_VALUE ( ":sube_pro_snt_hsp_id"                , MUH_GET_HESAP_ID("121") );
    query.SET_VALUE ( ":sube_port_snt_ileri_trh_hsp_id"     , MUH_GET_HESAP_ID("221") );
    query.SET_VALUE ( ":sube_tah_snt_ileri_trh_hsp_id"      , MUH_GET_HESAP_ID("221") );
    query.SET_VALUE ( ":sube_tem_snt_ileri_trh_hsp_id"      , MUH_GET_HESAP_ID("221") );
    query.SET_VALUE ( ":sube_borc_snt_hsp_id"               , MUH_GET_HESAP_ID("321") );
    query.SET_VALUE ( ":sube_borc_snt_ileri_trh_hsp_id"     , MUH_GET_HESAP_ID("421") );
    query.SET_VALUE ( ":sube_sup_alacaklar_hsp_id"          , MUH_GET_HESAP_ID("128") );
    query.SET_VALUE ( ":sube_tah_edlmyn_cekler_hsp_id"      , MUH_GET_HESAP_ID("101") );
    query.SET_VALUE ( ":sube_tah_edlmyn_snt_hsp_id"         , MUH_GET_HESAP_ID("121") );
    query.SET_VALUE ( ":sube_yurtici_satis_hsp_id"          , MUH_GET_HESAP_ID("600") );
    query.SET_VALUE ( ":sube_hizmet_urt_maliyet_hsp_id"     , MUH_GET_HESAP_ID("740") );
    query.SET_VALUE ( ":sube_prs_gdrlr_hsp_id"              , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":sube_sarf_malzemeleri_hsp_id"       , MUH_GET_HESAP_ID("710") );
    query.SET_VALUE ( ":sube_imalattan_giris_hsp_id"        , MUH_GET_HESAP_ID("152") );
    query.SET_VALUE ( ":kasa_ent_hesap_id"                  , MUH_GET_HESAP_ID("100") );
    query.SET_VALUE ( ":cari_alici_ent_hesap_id"            , MUH_GET_HESAP_ID("120") );
    query.SET_VALUE ( ":cari_satici_ent_hesap_id"           , MUH_GET_HESAP_ID("320") );
    query.SET_VALUE ( ":banka_ent_hesap_id"                 , MUH_GET_HESAP_ID("102") );
    query.SET_VALUE ( ":ver_cek_ent_hesap_id"               , MUH_GET_HESAP_ID("103") );
    query.SET_VALUE ( ":odeme_emirleri_ent_hesap_id"        , MUH_GET_HESAP_ID("103") );
    query.SET_VALUE ( ":pos_ent_hesap_id"                   , MUH_GET_HESAP_ID("108") );
    query.SET_VALUE ( ":kk_ent_hesap_id"                    , MUH_GET_HESAP_ID("300") );
    query.SET_VALUE ( ":prk_gider_ent_hesap_id"             , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":urunler_ent_hesap_id"               , MUH_GET_HESAP_ID("153") );
    query.SET_VALUE ( ":hizmetler_ent_hesap_id"             , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":demirbaslar_ent_hesap_id"           , MUH_GET_HESAP_ID("255") );
    query.SET_VALUE ( ":pos_kom_gideri_ent_hesap_id"        , MUH_GET_HESAP_ID("780") );
    query.SET_VALUE ( ":prs_avanslari_ent_hesap_id"         , MUH_GET_HESAP_ID("196") );
    query.SET_VALUE ( ":personel_borclari_ent_hesap_id"     , MUH_GET_HESAP_ID("335") );
    query.SET_VALUE ( ":prs_damga_vergisi_ent_hesap_id"     , MUH_GET_HESAP_ID("360") );
    query.SET_VALUE ( ":personel_vergi_ent_hesap_id"        , MUH_GET_HESAP_ID("360") );
    query.SET_VALUE ( ":prk_gelir_ent_hesap_id"             , MUH_GET_HESAP_ID("600") );
    query.SET_VALUE ( ":prs_ssk_isci_payi_hesap_id"         , MUH_GET_HESAP_ID("361") );
    query.SET_VALUE ( ":prs_ssk_isveren_payi_hesap_id"      , MUH_GET_HESAP_ID("361") );
    query.SET_VALUE ( ":prs_issizlik_sgk_isci_hsp_id"       , MUH_GET_HESAP_ID("361") );
    query.SET_VALUE ( ":prs_issizlik_sgk_isv_hsp_id"        , MUH_GET_HESAP_ID("361") );
    query.SET_VALUE ( ":asg_gecim_ind_hesap_id"             , MUH_GET_HESAP_ID("360") );
    query.SET_VALUE ( ":isveren_payi_giderleri_hps_id"      , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":bir_amortismanlar_hsp_id"           , MUH_GET_HESAP_ID("257") );
    query.SET_VALUE ( ":amor_giderleri_hsp_id"              , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":sgdp_prim_yuzde_isc_hsp_id"         , MUH_GET_HESAP_ID("361") );
    query.SET_VALUE ( ":sgdp_prim_yuzde_isv_hsp_id"         , MUH_GET_HESAP_ID("361") );
    query.SET_VALUE ( ":kidem_tazminati_hesap_id"           , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":ihbar_tazminati_hesap_id"           , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":dmr_satis_kar_ent_hesap_id"         , MUH_GET_HESAP_ID("679") );
    query.SET_VALUE ( ":dmr_satis_zarar_ent_hesap_id"       , MUH_GET_HESAP_ID("689") );
    query.SET_VALUE ( ":sendika_odeme_hesap_id"             , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":smmm_alinan_hizmet_hesap_id"        , MUH_GET_HESAP_ID("770") );
    query.SET_VALUE ( ":smmm_gelir_vergisi_hesap_id"        , MUH_GET_HESAP_ID("360") );
    query.SET_VALUE ( ":smmm_satilan_hizmet_hesap_id"       , MUH_GET_HESAP_ID("600") );
    query.SET_VALUE ( ":isy_5510_nolu_kanun_hesap_id"       , MUH_GET_HESAP_ID("602") );
    query.SET_VALUE ( ":satistan_iade_hesap_id"             , MUH_GET_HESAP_ID("610") );
    query.SET_VALUE ( ":ortaklara_borclar_hesap_id"         , MUH_GET_HESAP_ID("331") );

    int sube_id = query.INSERT();

    query.PREPARE_INSERT ( "sub_depolar ","depo_id", "depo_kodu, depo_adi, sube_id ");

    query.SET_VALUE      ( ":sube_id", sube_id );
    query.SET_VALUE      (":depo_kodu","001");
    query.SET_VALUE      (":depo_adi","MERKEZ DEPO");

    int depo_id = query.INSERT();


    query.PREPARE_INSERT ( "sub_uniteler ","unite_id", "sube_id, unite_adi, order_number, "
                             "bilgisayar_id, depo_id, irsaliye_belge_seri, fatura_belge_seri, "
                             "tahsilat_makbuzu_belge_seri, odeme_makbuzu_belge_seri, "
                             "irsaliye_belge_numarasi, fatura_belge_numarasi, "
                             "tahsilat_makbuzu_belge_num, odeme_makbuzu_belge_num , "
                             "muh_kasa_hesap_id, irsaliyeli_fat_belge_seri , "
                             "irsaliyeli_fat_belge_numarasi ");

    query.SET_VALUE      ( ":unite_adi"                     , "MERKEZ KASA");
    query.SET_VALUE      ( ":order_number"                  , 1024);
    query.SET_VALUE      ( ":irsaliyeli_fat_belge_seri"     , "A");
    query.SET_VALUE      ( ":irsaliye_belge_seri"           , "A");
    query.SET_VALUE      ( ":fatura_belge_seri"             , "A");
    query.SET_VALUE      ( ":tahsilat_makbuzu_belge_seri"   , "A");
    query.SET_VALUE      ( ":odeme_makbuzu_belge_seri"      , "A");
    query.SET_VALUE      ( ":irsaliyeli_fat_belge_numarasi" , QVariant ( 1 ).toString() );
    query.SET_VALUE      ( ":irsaliye_belge_numarasi"       , QVariant ( 1 ).toString() );
    query.SET_VALUE      ( ":fatura_belge_numarasi"         , QVariant ( 1 ).toString() );
    query.SET_VALUE      ( ":tahsilat_makbuzu_belge_num"    , QVariant ( 1 ).toString());
    query.SET_VALUE      ( ":odeme_makbuzu_belge_num"       , QVariant ( 1 ).toString() );
    query.SET_VALUE      ( ":sube_id"                       , sube_id );
    query.SET_VALUE      ( ":bilgisayar_id"                 , BILGISAYAR_ID() );
    query.SET_VALUE      ( ":depo_id"                       , depo_id );
    query.SET_VALUE      ( ":muh_kasa_hesap_id"             , MUH_GET_HESAP_ID("100"));

    query.INSERT();
}
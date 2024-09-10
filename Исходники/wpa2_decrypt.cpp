TEST_F(WPA2DecryptTest, DecryptTKIPUsingBeacon) {
    Crypto::WPA2Decrypter decrypter;
    decrypter.add_ap_data("libtinstest", "NODO");
    for(size_t i = 0; i < 7; ++i) {
        RadioTap radio(tkip_packets[i], tkip_packets_size[i]);
        if(i > 4) {
            ASSERT_TRUE(decrypter.decrypt(radio));
            if(i == 5)
                check_tkip_packet5(radio);
            else
                check_tkip_packet6(radio);
        }
        else 
            ASSERT_FALSE(decrypter.decrypt(radio));
    }
}
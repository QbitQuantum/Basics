TEST_F(WPA2DecryptTest, DecryptCCMPQosUsingBeacon) {
    Crypto::WPA2Decrypter decrypter;
    decrypter.add_ap_data("password1", "Testing");
    for(size_t i = 0; i < 6; ++i) {
        RadioTap radio(ccmp_qos_packets[i], ccmp_qos_packets_size[i]);
        if (i > 4) {
            ASSERT_TRUE(decrypter.decrypt(radio));
            EXPECT_TRUE(radio.find_pdu<ARP>() != 0);
        }
        else { 
            ASSERT_FALSE(decrypter.decrypt(radio));
        }
    }
}
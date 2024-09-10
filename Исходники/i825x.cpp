    virtual void do_send_packet(const void* data, uint32_t length) override {
        REQUIRE(length <= 1500);

        if (!(ioreg(reg::STATUS) & STATUS_LU)) {
            dbgout() << "[i825x] Link not up. Dropping packet\n";
            return;
        }

        // prepare descriptor
        auto& td = tx_desc_[tx_tail_];
        tx_tail_ = (tx_tail_ + 1) % num_tx_descriptors;
        REQUIRE(td.upper.fields.status == 0);
        td.buffer_addr = virt_to_phys(data);
        td.lower.data = length | TXD_CMD_RS | TXD_CMD_EOP | TXD_CMD_IFCS;
        td.upper.data = 0;
        _mm_mfence();
        ioreg(reg::TDT0, tx_tail_);

        //dbgout() << "Waiting for packet to be sent.\n";
        for (uint32_t timeout = 100; !td.upper.fields.status; ) {
            __halt();
            if (!timeout--) {
#if 0
                // Dump stats
                constexpr uint32_t nstats = 0x100 / 4;
                static uint32_t stats[nstats];
                for (uint32_t i = 0; i < nstats; ++i) {
                    stats[i] += ioreg(static_cast<reg>(0x4000 + i * 4));
                    dbgout() << as_hex(stats[i]);
                    dbgout() << ((i % 8 == 7) ? '\n' : ' ');
                }
#endif
                dbgout() << "Transfer NOT done. Timed out! STATUS = " << as_hex(ioreg(reg::STATUS)) << " TDH = " << ioreg(reg::TDH0) << " TDT " <<  ioreg(reg::TDT0) << "\n";
#if 0
                for (uint32_t i = 0; i < num_tx_descriptors; ++i) {
                    dbgout() << as_hex(tx_desc_[i].buffer_addr) << " ";
                    dbgout() << as_hex(tx_desc_[i].lower.data) << " ";
                    dbgout() << as_hex(tx_desc_[i].upper.data) << " ";
                    dbgout() << ((i % 3 == 2) ? '\n' : ' ');
                }
                dbgout() << "\n";
#endif
                return;
            }
        }
        //dbgout() << "[i825x] TX Status = " << as_hex(td.upper.fields.status) << "\n";
        REQUIRE(td.upper.fields.status == TXD_STAT_DD);
        td.upper.data = 0; // Mark ready for re-use
        REQUIRE(ioreg(reg::TDH0) == ioreg(reg::TDT0));

    }
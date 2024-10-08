void NewRefereeModule::run() {
    QUdpSocket socket;

    if (!socket.bind(ProtobufRefereePort, QUdpSocket::ShareAddress)) {
        throw runtime_error("Can't bind to shared referee port");
    }

    multicast_add(&socket, RefereeAddress);

    _packets.reserve(4);

    _running = true;
    while (_running) {
        if (!_useExternalRef) continue;

        char buf[65536];

        if (!socket.waitForReadyRead(500)) {
            continue;
        }

        QHostAddress host;
        quint16 port = 0;
        qint64 size = socket.readDatagram(buf, sizeof(buf), &host, &port);
        if (size < 1) {
            fprintf(stderr, "NewRefereeModule: %s/n",
                    (const char*)socket.errorString().toLatin1());
            ::usleep(100000);
            continue;
        }

        NewRefereePacket* packet = new NewRefereePacket;
        packet->receivedTime = RJ::timestamp();
        this->received_time = packet->receivedTime;
        if (!packet->wrapper.ParseFromArray(buf, size)) {
            fprintf(stderr,
                    "NewRefereeModule: got bad packet of %d bytes from %s:%d\n",
                    (int)size, (const char*)host.toString().toLatin1(), port);
            fprintf(stderr, "Packet: %s\n", buf);
            fprintf(stderr, "Address: %s\n", RefereeAddress);
            continue;
        }

        _mutex.lock();
        _packets.push_back(packet);

        stage = (Stage)packet->wrapper.stage();
        command = (Command)packet->wrapper.command();
        sent_time = packet->wrapper.packet_timestamp();
        stage_time_left = packet->wrapper.stage_time_left();
        command_counter = packet->wrapper.command_counter();
        command_timestamp = packet->wrapper.command_timestamp();
        yellow_info.ParseRefboxPacket(packet->wrapper.yellow());
        blue_info.ParseRefboxPacket(packet->wrapper.blue());
        ballPlacementx = packet->wrapper.designated_position().x();
        ballPlacementy = packet->wrapper.designated_position().y();

        _mutex.unlock();
    }
}
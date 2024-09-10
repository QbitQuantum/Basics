void VnaPowerCorrections::setCorrections(QChar wave, uint port, QRowVector values_dB) {
    QString scpi = "SENS%1:CORR:POW:DATA \'%2%3\',";
    scpi = scpi.arg(_channelIndex);
    scpi = scpi.arg(wave.toUpper());
    scpi = scpi.arg(port);

    QByteArray _scpi = scpi.toLocal8Bit();
    _scpi.append(toBlockDataFormat(values_dB));
    _vna->binaryWrite(_scpi);
}
void PlayPanel::setTempo(double val)
      {
      int tempo = lrint(val * 60.0);
      tempoLabel->setText(QString("%1 BPM").arg(tempo, 3, 10, QLatin1Char(' ')));
      }
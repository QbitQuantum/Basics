void PowerManagementConfigGui::onMessageReceived(const QString &response)
{
    QStringList breakdown = response.split(",");
    int size = breakdown.size();
    if (size <= 0) return;
    QChar command = breakdown[0].at(1);
// Check for ident response
    if (command == 'E')
    {
        if (size != 4) return;
        PowerManagementConfigUi.firmwareVersion->setText("Firmware version : " + breakdown[2]);
        PowerManagementConfigUi.boardVersion->setText("Interface Board Version: " + breakdown[3]);
        return;
    }
    QChar battery = breakdown[0].at(2);
    QChar parameter = breakdown[0].at(2);
    int controlByte = 0;
    if (size > 1) controlByte = breakdown[1].simplified().toInt();
// Error Code
    switch (command.toAscii())
    {
// Show Measured Quiescent Current
        case 'Q':
        {
            if (size < 2) break;
            quiescentCurrent = breakdown[1].simplified();
            int test = breakdown[2].simplified().toInt();
            if (test < 6)
                PowerManagementConfigUi.calibrateProgressBar->setValue(test+1);
            else
            {
                PowerManagementConfigUi.quiescentCurrent
                        ->setText(QString("%1 A").arg(quiescentCurrent.
                                  toFloat()/256,0,'f',3));
                this->setEnabled(true);
                PowerManagementConfigUi.calibrateProgressBar->setVisible(false);
                PowerManagementConfigUi.calibrateProgressBar->setValue(0);
            }
            break;
        }
// Show measured battery resistance
        case 'R':
        {
            if (size < 2) break;
            QString batteryResistance = QString("%1 m").arg(breakdown[1]
                                         .simplified().toFloat()/65.536,0,'f',0)
                                         .append(QChar(0x03A9));
            if (battery == '1')
                PowerManagementConfigUi.battery1Resistance
                    ->setText(batteryResistance);
            else if (battery == '2')
                PowerManagementConfigUi.battery2Resistance
                    ->setText(batteryResistance);
            else if (battery == '3')
                PowerManagementConfigUi.battery3Resistance
                    ->setText(batteryResistance);
            break;
        }
// Show battery type and capacity
        case 'T':
        {
            if (size < 3) break;
            int batteryType = breakdown[1].simplified().toInt();
            int batteryCapacity = breakdown[2].simplified().toInt();
            if (battery == '1')
            {
                PowerManagementConfigUi.battery1TypeCombo
                    ->setCurrentIndex(batteryType);
                PowerManagementConfigUi.battery1CapacitySpinBox
                    ->setValue(batteryCapacity);
            }
            else if (battery == '2')
            {
                PowerManagementConfigUi.battery2TypeCombo
                    ->setCurrentIndex(batteryType);
                PowerManagementConfigUi.battery2CapacitySpinBox
                    ->setValue(batteryCapacity);
            }
            else if (battery == '3')
            {
                PowerManagementConfigUi.battery3TypeCombo
                    ->setCurrentIndex(batteryType);
                PowerManagementConfigUi.battery3CapacitySpinBox
                    ->setValue(batteryCapacity);
            }
            break;
        }
// Show battery absorption phase voltage and current limits
        case 'A':
        {
            if (size < 3) break;
            float absorptionVoltage = breakdown[2].simplified().toFloat()/256;
            float bulkCurrentScale = breakdown[1].simplified().toFloat();
            if (battery == '1')
            {
                PowerManagementConfigUi.battery1AbsorptionVoltage
                    ->setValue(absorptionVoltage);
                float battery1Capacity = PowerManagementConfigUi.
                            battery1CapacitySpinBox->value();
                PowerManagementConfigUi.battery1AbsorptionCurrent
                    ->setValue(battery1Capacity/bulkCurrentScale);
            }
            else if (battery == '2')
            {
                PowerManagementConfigUi.battery2AbsorptionVoltage
                    ->setValue(absorptionVoltage);
                float battery2Capacity = PowerManagementConfigUi.
                            battery2CapacitySpinBox->value();
                PowerManagementConfigUi.battery2AbsorptionCurrent
                    ->setValue(battery2Capacity/bulkCurrentScale);
            }
            else if (battery == '3')
            {
                PowerManagementConfigUi.battery3AbsorptionVoltage
                    ->setValue(absorptionVoltage);
                float battery3Capacity = PowerManagementConfigUi.
                            battery3CapacitySpinBox->value();
                PowerManagementConfigUi.battery3AbsorptionCurrent
                    ->setValue(battery3Capacity/bulkCurrentScale);
            }
            break;
        }
// Show battery float phase voltage and current limits
        case 'F':
        {
            if (size < 3) break;
            float floatVoltage = breakdown[2].simplified().toFloat()/256;
            float floatCurrentScale = breakdown[1].simplified().toFloat();
            if (battery == '1')
            {
                PowerManagementConfigUi.battery1FloatVoltage
                    ->setValue(floatVoltage);
                float battery1Capacity = PowerManagementConfigUi.
                            battery1CapacitySpinBox->value();
                PowerManagementConfigUi.battery1FloatCurrent
                    ->setValue(battery1Capacity/floatCurrentScale);
            }
            else if (battery == '2')
            {
                PowerManagementConfigUi.battery2FloatVoltage
                    ->setValue(floatVoltage);
                float battery2Capacity = PowerManagementConfigUi.
                            battery2CapacitySpinBox->value();
                PowerManagementConfigUi.battery2FloatCurrent
                    ->setValue(battery2Capacity/floatCurrentScale);
            }
            else if (battery == '3')
            {
                PowerManagementConfigUi.battery3FloatVoltage
                    ->setValue(floatVoltage);
                float battery3Capacity = PowerManagementConfigUi.
                            battery3CapacitySpinBox->value();
                PowerManagementConfigUi.battery3FloatCurrent
                    ->setValue(battery3Capacity/floatCurrentScale);
            }
            break;
        }
/* Show control settings */
        case 'D':
        {
            if (size < 2) break;
            bool dataMessage = ((controlByte & (1<<3)) > 0);
            if (dataMessage)
                PowerManagementConfigUi.dataMessageCheckbox->setChecked(true);
            else
                PowerManagementConfigUi.dataMessageCheckbox->setChecked(false);
            bool debugMessage = ((controlByte & (1<<4)) > 0);
            if (debugMessage)
                PowerManagementConfigUi.debugMessageCheckbox->setChecked(true);
            else
                PowerManagementConfigUi.debugMessageCheckbox->setChecked(false);
            break;
        }
// Show current time settings from the system
        case 'H':
        {
            if (size < 2) break;
            QDateTime systemTime =
                QDateTime::fromString(breakdown[1].simplified(),Qt::ISODate);
            PowerManagementConfigUi.date->setText(systemTime.date().toString("dd.MM.yyyy"));
            PowerManagementConfigUi.time->setText(systemTime.time().toString("H.mm.ss"));
            break;
        }
// Operational State values for "reset missing" buttons.
        case 'O':
        {
            int healthState = (controlByte >> 6) & 0x03;
            if (battery == '1')
            {
                if (healthState == 0)
                {
                    PowerManagementConfigUi.resetMissing1Button->
                        setStyleSheet("background-color:lightgreen;");
                    PowerManagementConfigUi.resetMissing1Button->setText("");
                }
                else if (healthState == 1)
                {
                    PowerManagementConfigUi.resetMissing1Button->
                        setStyleSheet("background-color:orange;");
                    PowerManagementConfigUi.resetMissing1Button->setText("");
                }
                else if (healthState == 2)
                {
                    PowerManagementConfigUi.resetMissing1Button->
                        setStyleSheet("background-color:white;");
                    PowerManagementConfigUi.resetMissing1Button->setText("X");
                }
            }
            else if (battery == '2')
            {
                if (healthState == 0)
                {
                    PowerManagementConfigUi.resetMissing2Button->
                        setStyleSheet("background-color:lightgreen;");
                    PowerManagementConfigUi.resetMissing2Button->setText("");
                }
                else if (healthState == 1)
                {
                    PowerManagementConfigUi.resetMissing2Button->
                        setStyleSheet("background-color:orange;");
                    PowerManagementConfigUi.resetMissing2Button->setText("");
                }
                else if (healthState == 2)
                {
                    PowerManagementConfigUi.resetMissing2Button->
                        setStyleSheet("background-color:white;");
                    PowerManagementConfigUi.resetMissing2Button->setText("X");
                }
            }
            else if (battery == '3')
            {
                if (healthState == 0)
                {
                    PowerManagementConfigUi.resetMissing3Button->
                        setStyleSheet("background-color:lightgreen;");
                    PowerManagementConfigUi.resetMissing3Button->setText("");
                }
                else if (healthState == 1)
                {
                    PowerManagementConfigUi.resetMissing3Button->
                        setStyleSheet("background-color:orange;");
                    PowerManagementConfigUi.resetMissing3Button->setText("");
                }
                else if (healthState == 2)
                {
                    PowerManagementConfigUi.resetMissing3Button->
                        setStyleSheet("background-color:white;");
                    PowerManagementConfigUi.resetMissing3Button->setText("X");
                }
            }
            break;
        }
// Show tracking parameters
        case 't':
        {
            if (size < 3) break;
// Low voltage and critical voltage thresholds.
            if (parameter == 'V')
            {
                float lowVoltage = (float)breakdown[1].simplified().toInt()/256;
                float criticalVoltage = (float)breakdown[2].simplified().toInt()/256;
                PowerManagementConfigUi.lowVoltageDoubleSpinBox
                    ->setValue(lowVoltage);
                PowerManagementConfigUi.criticalVoltageDoubleSpinBox
                    ->setValue(criticalVoltage);
            }
// Low SoC and critical SoC thresholds.
            else if (parameter == 'S')
            {
                int lowSoC = (float)breakdown[1].simplified().toInt()/256;
                int criticalSoC = (float)breakdown[2].simplified().toInt()/256;
                PowerManagementConfigUi.lowSoCSpinBox
                    ->setValue(lowSoC);
                PowerManagementConfigUi.criticalSoCSpinBox
                    ->setValue(criticalSoC);
            }
/* Monitor strategy byte. Bit 0 is to allow charger and load on the same
battery; bit 1 is to maintain an isolated battery in normal conditions. */
            else if (parameter == 's')
            {
                int monitorStrategy = (float)breakdown[1].simplified().toInt();
                bool separateLoad = (monitorStrategy & 1) > 0;
                PowerManagementConfigUi.loadChargeCheckBox
                    ->setChecked(separateLoad);
                bool preserveIsolation = (monitorStrategy & 2) > 0;
                PowerManagementConfigUi.isolationMaintainCheckBox
                    ->setChecked(preserveIsolation);
            }
            break;
        }
// Show charger parameters
        case 'c':
        {
            if (size < 3) break;
            if (parameter == 'R')
            {
                int restTime = (float)breakdown[1].simplified().toInt();
                int absorptionTime = (float)breakdown[2].simplified().toInt();
                PowerManagementConfigUi.restTimeSpinBox
                    ->setValue(restTime);
                PowerManagementConfigUi.absorptionTimeSpinBox
                    ->setValue(absorptionTime);
            }
            else if (parameter == 'D')
            {
                int dutyCycleMin = (float)breakdown[1].simplified().toInt()/256;
                PowerManagementConfigUi.minimumDutyCycleSpinBox
                    ->setValue(dutyCycleMin);
            }
            else if (parameter == 'F')
            {
                int floatTime = (float)breakdown[1].simplified().toInt();
                int floatSoC = (float)breakdown[2].simplified().toInt()/256;
                PowerManagementConfigUi.floatDelaySpinBox
                    ->setValue(floatTime);
                PowerManagementConfigUi.floatBulkSoCSpinBox
                    ->setValue(floatSoC);
            }
/* Charger strategy byte. Bit 0 is to suppress the absortion phase for EMI. */
            else if (parameter == 's')
            {
                int chargerStrategy = (float)breakdown[1].simplified().toInt();
                bool suppressAbsorptionPhase = (chargerStrategy & 1) > 0;
                PowerManagementConfigUi.absorptionMuteCheckbox
                    ->setChecked(suppressAbsorptionPhase);
            }
            break;
        }
    }
}
void
dmz::QtPluginGraph::_update_power_law (
    const BarStruct *LastBar,
    const Float64 EndOfXAxis) {

    Boolean foundFirstBar (False);
    Float32 offset = _spaceWidth;

    Float64 p (0.0);
    Float64 q (0.0);
    Float64 nonZeroCount (0.0);
    Float64 x (0.0);
    Float64 y (0.0);
    Float64 sumX (0.0);
    Float64 sumY (0.0);
    Float64 sumXY (0.0);
    Float64 sumX2 (0.0);

    HashTableUInt32Iterator it;
    BarStruct *bar (_ascendingOrder ? _barTable.get_first (it) : _barTable.get_last (it));

    while (bar) {

        if (!foundFirstBar && bar->count) {
            foundFirstBar = True;
        }

        if (foundFirstBar) {

            if (bar->Id == 0) {
                x = 1.0;
            }
            else {
                x = log (Float64 (bar->Id));
            }

            if (bar->height < 0.0f) {

                y = log (-bar->height);
                sumY += y;
                sumX += x;
                sumXY += x * y;
                sumX2 += x * x;
                nonZeroCount++;
            }
        }

        if (LastBar == bar) {
            bar = 0;
        }
        else {

            bar = (_ascendingOrder ? _barTable.get_next (it) : _barTable.get_prev (it));
        }
    }

    if (nonZeroCount > 0.0) {

        q = ((nonZeroCount * sumXY) - (sumX * sumY)) /
            ((nonZeroCount * sumX2) - (sumX * sumX));

        p = exp ((sumY - (q * sumX)) / nonZeroCount);
    }

    foundFirstBar = false;
    QPainterPath path;

    bar = (_ascendingOrder ? _barTable.get_first (it) : _barTable.get_last (it));

    const Float32 Offset (_barWidth * 0.5f);

    while (bar) {

        if (!foundFirstBar && bar->count) {

            path.moveTo (bar->offset + Offset, -local_power (p, q, bar->Id));
            foundFirstBar = True;
        }
        else if (foundFirstBar) {

            path.lineTo (bar->offset + Offset, -local_power (p, q, bar->Id));
        }

        if (LastBar == bar) {
            bar = 0;
        }
        else {

            bar = (_ascendingOrder ? _barTable.get_next (it) : _barTable.get_prev (it));
        }
    }

    if (path.elementCount () > 1) {

        if (!_powerLawPath) {

            _powerLawPath = new QGraphicsPathItem;
            _powerLawPath->setPen (_powerStroke);
            _powerLawPath->setZValue (2.0);
            if (_scene) {
                _scene->addItem (_powerLawPath);
            }
        }

        if (_powerLawPath) {

            _powerLawPath->setPath (path);
        }

        if (!_powerLabel) {

            _powerLabel = new QGraphicsTextItem;
            _powerLabel->setPos (260.0, -_barHeight);
            if (_scene) {
                _scene->addItem (_powerLabel);
            }
        }

        if (_powerLabel) {

            _powerLabel->setPlainText (
                QString::fromAscii ("Exponent = ") + QString::number (q));
        }
    }
    else if (_scene) {

        if (_powerLawPath) {

            _scene->removeItem (_powerLawPath);
            delete _powerLawPath;
            _powerLawPath = 0;
        }

        if (_powerLabel) {

            _scene->removeItem (_powerLabel);
            delete _powerLabel;
            _powerLabel = 0;
        }
    }
}
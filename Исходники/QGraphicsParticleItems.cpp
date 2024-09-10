void QGraphicsParticleItems::updateParticles() {
    if (_subject == NULL) {
        return;
    }

    int numberOfParticleItems = _particleItems.size();
    const int numberOfSubjectPoints = _subject->GetNumberOfPoints();
    
    if (numberOfParticleItems != numberOfSubjectPoints) {
        createParticles(_subject);
        numberOfParticleItems = numberOfSubjectPoints;
    }

    bool useColorByLabel = true;
    bool useColorFromScalar = !useColorByLabel && _useScalars && _scalars.size() == numberOfSubjectPoints;
    if (useColorFromScalar) {
        _hsvFunc->SetMinimumInputValue(_scalars.min_value());
        _hsvFunc->SetMaximumInputValue(_scalars.max_value());
    } else if (useColorByLabel) {
        _hsvFunc->SetMinimumInputValue(0);
        _hsvFunc->SetMaximumInputValue(5);
    }

    assert(_particleItems.size() == _subject->GetNumberOfPoints());
    
    QBrush grayBrush(Qt::gray, Qt::SolidPattern);
    for (int j = 0; j < numberOfParticleItems; j++) {
        Particle& p = _subject->operator[](j);
        if (_isHide) {
            _particleItems[j]->hide();
        } else {
            _particleItems[j]->show();
        }
        
        RealIndex x;
        if (_useParticleX) {
            _subject->ComputeIndexX(p, x);
        } else {
            _subject->ComputeIndexZ(p, x);
        }
        _particleItems[j]->setPos(x[0], x[1]);

        if (p.enabled) {
            if (_isParticleSelected && j != _particleSelectedId) {
                _particleItems[j]->setBrush(grayBrush);
                _particleItems[j]->setOpacity(0.3);
            } else {
                RGBA color;
                if (useColorFromScalar) {
                    color = _hsvFunc->operator()(_scalars[j]);
                } else if (useColorByLabel) {
                    color = _hsvFunc->operator()(p.label);
                } else {
                    color = _hsvFunc->operator()(j);
                }
                if (_refSubject != NULL && _refSubject->operator[](j).outlier) {
                    _particleItems[j]->setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    _particleItems[j]->setOpacity(1);
                } else {
                    _particleItems[j]->setBrush(QBrush(qRgb(color[0], color[1], color[2]), Qt::SolidPattern));
                    _particleItems[j]->setOpacity(0.3);
                }
            }
        } else {
            _particleItems[j]->hide();
        }
    }
}
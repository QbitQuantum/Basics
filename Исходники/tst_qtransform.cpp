    void checkCompositionDecomposition()
    {
        // GIVEN
        Qt3DCore::QTransform t;
        Qt3DCore::QTransform t2;
        QMatrix4x4 m = Qt3DCore::QTransform::rotateAround(QVector3D(0.1877f, 0.6868f, 0.3884f), 45.0f, QVector3D(0.0f, 0.0f, 1.0f));

        // WHEN
        t.setMatrix(m);
        t2.setScale3D(t.scale3D());
        t2.setRotation(t.rotation());
        t2.setTranslation(t.translation());

        // THEN
        QCOMPARE(t.scale3D(), t2.scale3D());
        QCOMPARE(t.rotation(), t2.rotation());
        QCOMPARE(t.translation(), t2.translation());

        // Note: t.matrix() != t2.matrix() since different matrices
        // can result in the same scale, rotation, translation
    }
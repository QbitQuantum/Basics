    void checkCreationData()
    {
        // GIVEN
        QJoint joint;

        joint.setScale(QVector3D(3.5f, 2.0f, 1.3f));
        joint.setRotation(QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 30.0f));
        joint.setTranslation(QVector3D(3.0f, 2.0f, 1.0f));
        QMatrix4x4 ibm;
        ibm.scale(5.2f);
        joint.setInverseBindMatrix(ibm);

        // WHEN
        QVector<Qt3DCore::QNodeCreatedChangeBasePtr> creationChanges;

        {
            Qt3DCore::QNodeCreatedChangeGenerator creationChangeGenerator(&joint);
            creationChanges = creationChangeGenerator.creationChanges();
        }

        // THEN
        {
            QCOMPARE(creationChanges.size(), 1);

            const auto creationChangeData
                = qSharedPointerCast<QNodeCreatedChange<QJointData>>(creationChanges.first());
            const QJointData data = creationChangeData->data;

            QCOMPARE(joint.id(), creationChangeData->subjectId());
            QCOMPARE(joint.isEnabled(), true);
            QCOMPARE(joint.isEnabled(), creationChangeData->isNodeEnabled());
            QCOMPARE(joint.metaObject(), creationChangeData->metaObject());
            QCOMPARE(joint.scale(), data.scale);
            QCOMPARE(joint.rotation(), data.rotation);
            QCOMPARE(joint.translation(), data.translation);
            QCOMPARE(joint.inverseBindMatrix(), data.inverseBindMatrix);
        }

        // WHEN
        joint.setEnabled(false);

        {
            Qt3DCore::QNodeCreatedChangeGenerator creationChangeGenerator(&joint);
            creationChanges = creationChangeGenerator.creationChanges();
        }

        // THEN
        {
            QCOMPARE(creationChanges.size(), 1);

            const auto creationChangeData
                = qSharedPointerCast<QNodeCreatedChange<QJointData>>(creationChanges.first());
            const QJointData data = creationChangeData->data;

            QCOMPARE(joint.id(), creationChangeData->subjectId());
            QCOMPARE(joint.isEnabled(), false);
            QCOMPARE(joint.isEnabled(), creationChangeData->isNodeEnabled());
            QCOMPARE(joint.metaObject(), creationChangeData->metaObject());
            QCOMPARE(joint.scale(), data.scale);
            QCOMPARE(joint.rotation(), data.rotation);
            QCOMPARE(joint.translation(), data.translation);
            QCOMPARE(joint.inverseBindMatrix(), data.inverseBindMatrix);
        }
    }
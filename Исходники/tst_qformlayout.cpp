void tst_QFormLayout::setLayout()
{
    QFormLayout layout;

    QHBoxLayout l1;
    QHBoxLayout l2;
    QHBoxLayout l3;
    QHBoxLayout l4;

    QCOMPARE(layout.count(), 0);
    QCOMPARE(layout.rowCount(), 0);

    layout.setLayout(5, QFormLayout::LabelRole, &l1);
    QCOMPARE(layout.count(), 1);
    QCOMPARE(layout.rowCount(), 6);

    layout.setLayout(3, QFormLayout::FieldRole, &l2);
    layout.setLayout(3, QFormLayout::LabelRole, &l3);
    QCOMPARE(layout.count(), 3);
    QCOMPARE(layout.rowCount(), 6);

    // should be ignored and generate warnings
    layout.setLayout(3, QFormLayout::FieldRole, &l4);
    layout.setLayout(-1, QFormLayout::FieldRole, &l4);
    QCOMPARE(layout.count(), 3);
    QCOMPARE(layout.rowCount(), 6);

    {
        int row = -1;
        QFormLayout::ItemRole role = QFormLayout::ItemRole(-123);
        layout.getLayoutPosition(&l1, &row, &role);
        QCOMPARE(row, 5);
        QCOMPARE(int(role), int(QFormLayout::LabelRole));
    }

    {
        int row = -1;
        QFormLayout::ItemRole role = QFormLayout::ItemRole(-123);
        layout.getLayoutPosition(&l2, &row, &role);
        QCOMPARE(row, 3);
        QCOMPARE(int(role), int(QFormLayout::FieldRole));
    }

    {
        int row = -1;
        QFormLayout::ItemRole role = QFormLayout::ItemRole(-123);
        layout.getLayoutPosition(&l3, &row, &role);
        QCOMPARE(row, 3);
        QCOMPARE(int(role), int(QFormLayout::LabelRole));
    }

    {
        int row = -1;
        QFormLayout::ItemRole role = QFormLayout::ItemRole(-123);
        layout.getLayoutPosition(&l4, &row, &role);
        QCOMPARE(row, -1);
        QCOMPARE(int(role), -123);
    }

    {
        int row = -1;
        QFormLayout::ItemRole role = QFormLayout::ItemRole(-123);
        layout.getLayoutPosition(0, &row, &role);
        QCOMPARE(row, -1);
        QCOMPARE(int(role), -123);
    }
}
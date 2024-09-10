void MyWidget::process()
{
    ui->plainTextEdit->clear();
    variant = ui->comboBox->currentIndex();
    print(QString("Variant %1").arg(variant));
    print(QString("[%1; %2]").arg(x0(), 0, 'g', 5).arg(xFinish(), 0, 'g', 3));

    //calc

    qreal x = x0(), y = y0(), z = z0();
    for (int i = 1; x < xFinish() || qFuzzyCompare(x, xFinish()); ++i)
    {
        qreal k1 = h() * f(x, y, z);
        qreal q1 = h() * g(x, y, z);

        qreal k2 = h() * f(x + h() / 2.0, y + k1 / 2.0, z + q1 / 2.0);
        qreal q2 = h() * g(x + h() / 2.0, y + k1 / 2.0, z + q1 / 2.0);

        qreal k3 = h() * f(x + h() / 2.0, y + k2 / 2.0, z + q2 / 2.0);
        qreal q3 = h() * g(x + h() / 2.0, y + k2 / 2.0, z + q2 / 2.0);

        qreal k4 = h() * f(x + h(), y + k3, z + q3);
        qreal q4 = h() * g(x + h(), y + k3, z + q3);

        print(QString("#%1").arg(i));
        print(QString("y(%1) = %2").arg(x, 0, 'g', 5).arg(y, 0, 'g', 5));
        print(QString("y_ex(%1) = %2").arg(x, 0, 'g',5).arg(yt(x), 0, 'g', 5));
        print(QString("error(%1) = %2").arg(x, 0, 'g',5).arg(ypo(y, x), 0, 'g', 5));

        x += h();
        y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        z += (q1 + 2.0 * q2 + 2.0 * q3 + q4) / 6.0;

    }
}
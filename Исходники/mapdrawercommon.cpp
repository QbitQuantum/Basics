QPolygonF minigis::shiftPolygonDifficult(const QPolygonF &origin, qreal delta, bool closed)
{
    if (qFuzzyIsNull(delta))
        return origin;

    QPolygonF path = origin;

    QPolygonF norm;
    // ----------------- Поиск нормалей к оригинальному полигону
    int N = path.size();
    for (int i = 1; i < N; ++i) {
        QPointF vect = path.at(i) - path.at(i-1);
        double len = lengthR2(vect);
        if (qFuzzyIsNull(len)) {
            path.remove(i);
            --N;
            --i;
            continue;
        }
        vect /= len;
        norm.append(QPointF(vect.y() * delta, -vect.x() * delta));
    }
    // ----
    if (closed) {
        QPointF vect = path.first() - path.last();
        double len = lengthR2(vect);
        if (qFuzzyIsNull(len))
            path.remove(path.size() - 1);
        else {
            vect /= len;
            norm.append(QPointF(vect.y() * delta, -vect.x() * delta));
        }
    }
    // ------------------

    QVector<QLineF> lines;
    // -------------------------- Построение смещенных линий
    for (int i = 1; i < path.size(); ++i)
        lines.append(QLineF(path.at(i) + norm.at(i-1), path.at(i-1) + norm.at(i-1)));
    // ----
    if (closed)
        lines.append(QLineF(path.first() + norm.last(), path.last() + norm.last()));
    // ------------------

    QPolygonF shell;
    if (lines.isEmpty())
        return shell;

    // -------------------------- Построение смещенного полигона
    N = lines.size();
    for (int i = 1; i < N; ++i) {
        QPointF tmp;
        QLineF::IntersectType type = lines.at(i-1).intersect(lines.at(i), &tmp);
        qreal ang = lines.at(i-1).angleTo(lines.at(i));
        if (type != QLineF::NoIntersection)
            shell.append(tmp);
        else {
            if (qFuzzyCompare(ang, qreal(180)))
                shell.append(lines.at(i).p2() - 2 * norm.at(i));
            shell.append(lines.at(i).p2());
        }
    }
    // ----
    if (closed) {
        QPointF tmp;
        QLineF::IntersectType type = lines.last().intersect(lines.first(), &tmp);
        qreal ang = lines.last().angleTo(lines.first());
        if (type != QLineF::NoIntersection)
            shell.append(tmp);
        else {
            if (qFuzzyCompare(ang, qreal(180)))
                shell.append(lines.first().p2() - 2 * norm.first());
            shell.append(lines.first().p2());
        }
        shell.append(shell.first());
    }
    else {
        shell.prepend(lines.first().p2());
        shell.append(lines.last().p1());
    }
    // ------------------

    // -------------------------- обрезание острых углов
    int k  = 0;
    N = lines.size();
    for (int i = 1; i < N; ++i) {
        double ang = lines.at(i-1).angleTo(lines.at(i));

        bool first  = (120 < ang && ang < 180 && delta < 0) || (180 < ang && ang < 240 && delta > 0);
        bool second = (120 < ang && ang < 180 && delta > 0) || (180 < ang && ang < 240 && delta < 0);
        if (first) {
            int num = closed ? 1 : 0;
            QPointF v = shell.at(i + k - num) - path.at(i);
            v /= lengthR2(v);
            QPointF start = path.at(i) + v * qAbs(delta);
            QLineF tmp(start, start + QPointF(-v.y(), v.x()));
            QPointF a;
            if (tmp.intersect(lines.at(i  ), &a) != QLineF::NoIntersection)
                shell.replace(i + k - num, a);
            if (tmp.intersect(lines.at(i-1), &a) != QLineF::NoIntersection)
                shell.insert(i + k - num, a);
            ++k;
        }
        else if (second) {
            // TODO: cut corner
        }
    }
    // ----
    if (closed) {
        double ang = lines.last().angleTo(lines.first());

        int num = lines.size();
        int shellNum = (num + k - 1) % shell.size();
        bool first  = (120 < ang && ang < 180 && delta < 0) || (180 < ang && ang < 240 && delta > 0);
        bool second = (180 < ang && ang < 240 && delta < 0) || (120 < ang && ang < 180 && delta > 0);
        if (first) {
            QPointF v = shell.at(shellNum) - path.at(num % path.size());
            v /= lengthR2(v);
            QPointF start = path.at(num % path.size()) + v * qAbs(delta);
            QLineF tmp(start, start + QPointF(-v.y(), v.x()));
            QPointF a;
            if (tmp.intersect(lines.first(), &a) != QLineF::NoIntersection)
                shell.replace(shellNum, a);
            if (tmp.intersect(lines.last() , &a) != QLineF::NoIntersection)
                shell.insert(shellNum, a);
        }
        else if (second) {
            // TODO: cut corner
        }
    }
    // ------------------

    return shell;
}
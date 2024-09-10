QString NG::DotVisitor::vertexID(const Soprano::Node & node)
{
    if(node.isBlank()) {
        static QString blankTemplate("blank%1");
        d->vnum++;
        return blankTemplate.arg(QString::number(d->vnum));
    } else {
        QHash< Soprano::Node , int >::const_iterator fit =
            d->vertices.find(node);
        if(fit == d->vertices.end()) {
            // Write new node
            d->vnum++;
            d->vertices.insert(node, d->vnum);
            return QString::number(d->vnum);
        } else {
            return QString::number(fit.value());
        }
    }

}
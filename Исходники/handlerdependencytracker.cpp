void HandlerDependencyTracker::writeGraph(QList<int> indexPermutation)
{
    if(!mEnabled) {
        return;
    }

    QString filename = "handlers.gv";

    QString graph = "digraph {\n  node [shape = \"rectangle\", style = \"filled\", fillcolor = \"forestgreen\"];\n\n";

    QMap<QString, QString> names;

    // Declare each node.
    int idx = 1;
    QString idxStr;
    foreach(QString label, mEvents) {
        names.insert(label, QString("event_%1").arg(idx));
        idxStr = (idx-1) < indexPermutation.length() ? QString::number(indexPermutation.at(idx-1)) : "";
        idxStr = idx == mEvents.length() ? "B" : idxStr;
        graph += QString("  %1 [label = \"%2\", xlabel = \"%3\"];\n").arg(names[label], label, idxStr);
        idx++;
    }
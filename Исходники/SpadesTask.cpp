void SpadesLogParser::parseErrOutput(const QString &partOfLog){
    lastPartOfLog=partOfLog.split(QRegExp("(\n|\r)"));
    lastPartOfLog.first()=lastErrLine+lastPartOfLog.first();
    lastErrLine=lastPartOfLog.takeLast();
    foreach(QString buf, lastPartOfLog){
        if(buf.contains("== Error == ")
            || buf.contains(" ERROR ")){
                coreLog.error("Spades: " + buf);
                setLastError(buf);
        }else if (buf.contains("== Warning == ")
                  || buf.contains(" WARN ")){
            algoLog.info(buf);
        }else {
            algoLog.trace(buf);
        }
    }
}
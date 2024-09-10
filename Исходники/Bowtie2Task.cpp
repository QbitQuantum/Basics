void Bowtie2AlignTask::prepare() {
    {
        QStringList indexSuffixes;
        indexSuffixes << ".1.bt2" << ".2.bt2" << ".3.bt2" << ".4.bt2" << ".rev.1.bt2" << ".rev.2.bt2";

        if(settings.indexFileName.isEmpty()) {
            if(settings.prebuiltIndex) {
                QString indexName = QFileInfo(settings.refSeqUrl.getURLString()).fileName();
                for (int i = 0; i < indexSuffixes.size(); ++i) {
                    indexName.remove(indexSuffixes[i]);
                }
                settings.indexFileName = settings.refSeqUrl.dirPath() + "/" + indexName;
            } else {
                settings.indexFileName = settings.resultFileName.dirPath() + "/" + settings.resultFileName.baseFileName();
            }
        }
    }

    QStringList arguments;
    arguments.append(settings.getCustomValue(Bowtie2Task::OPTION_MODE, "--end-to-end").toString());

    arguments.append("-N");
    arguments.append(settings.getCustomValue(Bowtie2Task::OPTION_MISMATCHES, 0).toString());

    arguments.append(QString("-L"));
    arguments.append(settings.getCustomValue(Bowtie2Task::OPTION_SEED_LEN, 20).toString());

    arguments.append(QString("--dpad"));
    arguments.append(settings.getCustomValue(Bowtie2Task::OPTION_DPAD, 15).toString());

    arguments.append(QString("--gbar"));
    arguments.append(settings.getCustomValue(Bowtie2Task::OPTION_GBAR, 4).toString());

    {
        int seed = settings.getCustomValue(Bowtie2Task::OPTION_SEED, -1).toInt();
        if(-1 != seed) {
            arguments.append(QString("--seed"));
            arguments.append(QString::number(seed));
        }
    }

    {
        int threads = settings.getCustomValue(Bowtie2Task::OPTION_THREADS, 1).toInt();
        arguments.append(QString("--threads"));
        arguments.append(QString::number(threads));
    }

    if (settings.getCustomValue(Bowtie2Task::OPTION_NOMIXED, false).toBool()) {
        arguments.append("--no-mixed");
    }
    if (settings.getCustomValue(Bowtie2Task::OPTION_NODISCORDANT, false).toBool()) {
        arguments.append("--no-discordant");
    }
    if(settings.getCustomValue(Bowtie2Task::OPTION_NOFW, false).toBool()) {
        arguments.append("--nofw");
    }
    if(settings.getCustomValue(Bowtie2Task::OPTION_NORC, false).toBool()) {
        arguments.append("--norc");
    }
    if(settings.getCustomValue(Bowtie2Task::OPTION_NOOVERLAP, false).toBool()) {
        arguments.append("--no-overlap");
    }
    if(settings.getCustomValue(Bowtie2Task::OPTION_NOCONTAIN, false).toBool()) {
        arguments.append("--no-contain");
    }

    // We assume all datasets have the same format
    // QSEQ format is not supported
    if(!settings.shortReadSets.isEmpty())
    {
        QList<GUrl> shortReadUrls = settings.getShortReadUrls();
        QList<FormatDetectionResult> detectionResults = DocumentUtils::detectFormat(shortReadUrls.first());
        if(!detectionResults.isEmpty()) {
            if(detectionResults.first().format->getFormatId() == BaseDocumentFormats::FASTA) {
                arguments.append("-f");
            } else if(detectionResults.first().format->getFormatId() == BaseDocumentFormats::RAW_DNA_SEQUENCE) {
                arguments.append("-r");
            } else if (detectionResults.first().format->getFormatId() == BaseDocumentFormats::FASTQ) {
                arguments.append("-q");
            }else{
                setError(tr("Unknown short reads format %1").arg(detectionResults.first().format->getFormatId()));
            }
        }
    } else {
        setError("Short read list is empty!");
        return;
    }

    arguments.append(settings.indexFileName);
    {
        // we assume that all datasets have same library type
        ShortReadSet::LibraryType libType = settings.shortReadSets.at(0).type;
        int setCount = settings.shortReadSets.size();

        // unpaired reeds
        if (libType == ShortReadSet::SingleEndReads ) {
            QStringList readUrlsArgument;
            for(int index = 0;index < setCount;index++) {
                readUrlsArgument.append(settings.shortReadSets[index].url.getURLString());
            }
            arguments.append("-U");
            arguments.append(readUrlsArgument.join(","));
        } else {
            // paired reeds: mate 1s and 2s
            QStringList upstreamReads,downstreamReads;

            for ( int i = 0; i<setCount; ++i) {
                const ShortReadSet& set = settings.shortReadSets.at(i);
                if (set.order == ShortReadSet::UpstreamMate) {
                    upstreamReads.append(set.url.getURLString());
                } else {
                    downstreamReads.append(set.url.getURLString());
                }
            }

            if ( upstreamReads.count() != downstreamReads.count() ) {
                setError("Unequal number of upstream and downstream reads!");
                return;
            }

            arguments.append("-1");
            arguments.append(upstreamReads.join(","));
            arguments.append("-2");
            arguments.append(downstreamReads.join(","));
        }
    }
    arguments.append("-S");
    arguments.append(settings.resultFileName.getURLString());

    ExternalToolRunTask *task = new ExternalToolRunTask(ET_BOWTIE2_ALIGN, arguments, new ExternalToolLogParser());
    addSubTask(task);
}
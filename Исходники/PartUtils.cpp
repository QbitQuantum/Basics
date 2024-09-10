QString
findPartitionPathForMountPoint( const FstabEntryList& fstab,
                                const QString& mountPoint )
{
    if ( fstab.isEmpty() )
        return QString();

    for ( const FstabEntry& entry : fstab )
    {
        if ( entry.mountPoint == mountPoint )
        {
            QProcess readlink;
            QString partPath;

            if ( entry.partitionNode.startsWith( "/dev" ) ) // plain dev node
            {
                partPath = entry.partitionNode;
            }
            else if ( entry.partitionNode.startsWith( "LABEL=" ) )
            {
                partPath = entry.partitionNode.mid( 6 );
                partPath.remove( "\"" );
                partPath.replace( "\\040", "\\ " );
                partPath.prepend( "/dev/disk/by-label/" );
            }
            else if ( entry.partitionNode.startsWith( "UUID=" ) )
            {
                partPath = entry.partitionNode.mid( 5 );
                partPath.remove( "\"" );
                partPath = partPath.toLower();
                partPath.prepend( "/dev/disk/by-uuid/" );
            }
            else if ( entry.partitionNode.startsWith( "PARTLABEL=" ) )
            {
                partPath = entry.partitionNode.mid( 10 );
                partPath.remove( "\"" );
                partPath.replace( "\\040", "\\ " );
                partPath.prepend( "/dev/disk/by-partlabel/" );
            }
            else if ( entry.partitionNode.startsWith( "PARTUUID=" ) )
            {
                partPath = entry.partitionNode.mid( 9 );
                partPath.remove( "\"" );
                partPath = partPath.toLower();
                partPath.prepend( "/dev/disk/by-partuuid/" );
            }

            // At this point we either have /dev/sda1, or /dev/disk/by-something/...

            if ( partPath.startsWith( "/dev/disk/by-" ) ) // we got a fancy node
            {
                readlink.start( "readlink", { "-en", partPath });
                if ( !readlink.waitForStarted( 1000 ) )
                    return QString();
                if ( !readlink.waitForFinished( 1000 ) )
                    return QString();
                if ( readlink.exitCode() != 0 || readlink.exitStatus() != QProcess::NormalExit )
                    return QString();
                partPath = QString::fromLocal8Bit(
                               readlink.readAllStandardOutput() ).trimmed();
            }

            return partPath;
        }
    }

    return QString();
}
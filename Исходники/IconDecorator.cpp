QIcon IconDecorator::getIconByName(const QString &name)
{
    static QHash<QString, QIcon> icons;
    if (icons.isEmpty()) {
        icons.insert(QLatin1String("Dir.Headers"), createIcon(QStyle::SP_DirIcon, QIcon(QLatin1String(":/cov/icons/headers.png"))));
        icons.insert(QLatin1String("Dir.Sources"), createIcon(QStyle::SP_DirIcon, QIcon(QLatin1String(":/cov/icons/sources.png"))));
        icons.insert(QLatin1String("Dir.Project"), createIcon(QStyle::SP_DirIcon, QIcon(QLatin1String(":/cov/icons/qt_project.png"))));
        icons.insert(QLatin1String("Dir.Other"), createIcon(QStyle::SP_DirIcon, QIcon()));
        icons.insert(QLatin1String("File.Headers"), createIcon(QStyle::SP_FileIcon, QIcon(QLatin1String(":/cov/icons/headers.png"))));
        icons.insert(QLatin1String("File.Sources"), createIcon(QStyle::SP_FileIcon, QIcon(QLatin1String(":/cov/icons/sources.png"))));
    }

    return icons.value(name);
}
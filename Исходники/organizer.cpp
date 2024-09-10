Organizer::Organizer()
{
    if (!createDB())
    {
        perror("Open DB");
        exit(errno);
    }

    createTable("CREATE TABLE fic(size integer,path varchar(1000) UNIQUE, md5 varchar(16));");

    createTable("CREATE TABLE dir(empty bool,path varchar(1000) UNIQUE, modif datetime);");
}
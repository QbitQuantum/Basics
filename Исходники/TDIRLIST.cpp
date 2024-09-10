void TDirListBox::showDirs( TDirCollection *dirs )
{
    const indentSize = 2;
    int indent = indentSize;

    char buf[MAXPATH+16];
    memset( buf, ' ', sizeof( buf ) );
    char *name = buf + sizeof(buf) - (MAXFILE+MAXEXT);

    char *org = name - strlen(pathDir);
    strcpy( org, pathDir );

    char *curDir = dir;
    char *end = dir + 3;
    char hold = *end;
    *end = EOS;         // mark end of drive name
    strcpy( name, curDir );
    dirs->insert( new TDirEntry( org, name ) );

    *end = hold;        // restore full path
    curDir = end;
    while( (end = strchr( curDir, '\\' )) != 0 )
        {
        *end = EOS;
        strncpy( name, curDir, size_t(end-curDir) );
        name[size_t(end-curDir)] = EOS;
        dirs->insert( new TDirEntry( org - indent, dir ) );
        *end = '\\';
        curDir = end+1;
        indent += indentSize;
        }

    cur = dirs->getCount() - 1;

    end = strrchr( dir, '\\' );
    char path[MAXPATH];
    strncpy( path, dir, size_t(end-dir+1) );
    end = path + unsigned(end-dir)+1;
    strcpy( end, "*.*" );

    Boolean isFirst = True;
    ffblk ff;
    int res = findfirst( path, &ff, FA_DIREC );
    while( res == 0 )
        {
        if( (ff.ff_attrib & FA_DIREC) != 0 && ff.ff_name[0] != '.' )
            {
            if( isFirst )
                {
                memcpy( org, firstDir, strlen(firstDir)+1 );
                isFirst = False;
                }
            else
                memcpy( org, middleDir, strlen(middleDir)+1 );
            strcpy( name, ff.ff_name );
            strcpy( end, ff.ff_name );
            dirs->insert( new TDirEntry( org - indent, path ) );
            }
        res = findnext( &ff );
        }
    findclose( &ff );

    char *p = dirs->at(dirs->getCount()-1)->text();
    char *i = strchr( p, graphics[0] );
    if( i == 0 )
        {
        i = strchr( p, graphics[1] );
        if( i != 0 )
            *i = graphics[0];
        }
    else
        {
        *(i+1) = graphics[2];
        *(i+2) = graphics[2];
        }
}
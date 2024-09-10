// Packet when user login (chck user and pass and active)
bool CLoginServer::pakUserLogin( CLoginClient* thisclient, CPacket* P )
{
    if ( thisclient->isLoggedIn ) return false;
    MYSQL_ROW row;

    string temp_string;
    string temp_password;
    temp_string.reserve(17);
    temp_password.reserve(33);

    temp_string.assign( (const char*)&P->Buffer, 32, (P->Size-6-32)>16?16:P->Size-6-32 );
    temp_password.assign((const char*)&P->Buffer, 0, 32 );

    EscapeMySQL(temp_password.c_str(),thisclient->password,-1,true);    //client sends already in MD5 form (or should...)

    if (!thisclient->hasGameGuard && Config.checkGameGuard )
    {
        Log(MSG_HACK, "Warning, user [ %s ] tried logging in without gameguard", temp_string.c_str());
        BEGINPACKET( pak, 0x708 );
        ADDBYTE( pak, 10 );
        ADDDWORD( pak, 0);
        thisclient->SendPacket( &pak );
        return false;
    }

    BEGINPACKET( pak, 0x708 );

    if(!EscapeMySQL(temp_string.c_str(),thisclient->username,16,true))
    {
        return false;
    }

    MYSQL_RES *result = DB->QStore( "SELECT id,password,accesslevel,online,active FROM accounts WHERE username='******'", thisclient->username.c_str() );
    if(result == NULL)
        return false;

    if( mysql_num_rows( result ) == 1 )
    {
        row = mysql_fetch_row(result);
        int res = 0;
        #ifdef _WIN32
            res = _stricmp( row[1], thisclient->password.c_str() );
        #else
            res = strcasecmp( row[1], thisclient->password.c_str() );
        #endif
        if ( res == 0 )
        {
            //Account is Active
           if(atoi(row[4])==1)
            {
                // Activation Fix By Rifke
                Log( MSG_INFO, "Success login '%s' : Account verfified.", thisclient->username.c_str() );

                // characters is already logged
                if(atoi(row[3])==1)
                {
                    Log(MSG_WARNING, "Account %s try re-login", thisclient->username.c_str() );
                    ADDBYTE( pak, 4 );
                    ADDDWORD( pak, 0 );
                    thisclient->SendPacket( &pak );

                    //relogin crash fixed by zrose.
                    BEGINPACKET( pak2, 0x502 );
                    ADDBYTE    ( pak2, 1 );
                    ADDDWORD   ( pak2, atoi(row[0]) );
                    cryptPacket( (char*)&pak2, NULL );

                    DB->QFree( );
                    for(UINT i=0;i<ServerList.size();i++)
                        send( ServerList.at(i)->sock , (char*)&pak2, pak2.Size, 0 );

                    DB->QExecute( "update accounts set online=0 WHERE username='******'", thisclient->username.c_str());
                    return false;
                }

                thisclient->accesslevel = atoi(row[2]);

                //LMA: banned handled after this check.
                if( thisclient->accesslevel >0 && thisclient->accesslevel < Config.MinimumAccessLevel )
                { //The server are under inspection
                    ADDBYTE( pak, 0 );
                    ADDDWORD( pak, 0 );
                    thisclient->SendPacket( &pak );
                    DB->QFree( );
                    return true;
                }

                if ( thisclient->accesslevel > 0 )
                {
                    thisclient->userid = atoi(row[0]);
                    thisclient->isLoggedIn = true;
                    DB->QFree( );

                    //new code.
                    ADDBYTE( pak, 0x80 );
                    if(thisclient->accesslevel==300)
                    {
                        //GM level 1
                        ADDWORD( pak, 256 );
                    }
                    else if(thisclient->accesslevel==400)
                    {
                        //GM level 2
                        ADDWORD( pak, 512 );
                    }
                    else if(thisclient->accesslevel==500)
                    {
                        //admin.
                        ADDWORD( pak, 768 );
                    }
                    else
                    {
                        //standard user.
                        ADDWORD( pak, 100 );
                    }

                    ADDWORD( pak, 0x0000);

                    result = DB->QStore( "SELECT id,name FROM channels WHERE type=1" );
                    if(result==NULL) return false;
                    while( row = mysql_fetch_row(result) )
                    {
                        ADDBYTE( pak, 30 + atoi(row[0]));
                        ADDSTRING( pak, row[1] );
                        ADDBYTE( pak, 0 );
                        ADDBYTE(pak, atoi( row[0] ) );
                        ADDBYTE( pak, 0 );
                        ADDWORD( pak, 0 );
                    }
                    DB->QFree( );
                }else{
                    //BANNED
                    ADDBYTE( pak, 5 );
                    ADDDWORD( pak, 0 );
                    DB->QFree( );
                }
            }else{
                // Not activated
                Log( MSG_INFO, "Account %s not verified ", thisclient->username.c_str() );
                ADDBYTE( pak, 9 );
                ADDDWORD( pak, 0 );
                DB->QFree( );
            }
        }else{
            //BAD PASSWORD
            ADDBYTE( pak, 3 );
            ADDDWORD( pak, 0 );
            DB->QFree( );
        }
    }
    else
    {
        //BAD USERNAME
        ADDBYTE( pak, 2 );
        ADDDWORD( pak, 0 );
        DB->QFree( );
    }


    /*
    1 - general error   | 4 - your account is already logged
    6 - topup account   | 7 - cannot connect to server please try again
    8 - server exceeded | 9 - account have not been verified
    10 - login failed   | 11 - ip capacity is full
    */

    thisclient->SendPacket ( &pak );
    return true;
}
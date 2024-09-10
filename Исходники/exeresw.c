static FullTypeRecord *findExeTypeRecord( ResTable *restab,
                            WResTypeInfo *type )
/*********************************************************/
{
    FullTypeRecord      *exe_type;
    StringItem16        *exe_type_name;

    for( exe_type = restab->Dir.Head; exe_type != NULL;
                exe_type = exe_type->Next ) {
        if( type->TypeName.IsName && !(exe_type->Info.type & 0x8000) ) {
            /* if they are both names */
            exe_type_name = (StringItem16 *)((char *)restab->Str.StringBlock +
                            (exe_type->Info.type - restab->Dir.TableSize));
            if( exe_type_name->NumChars == type->TypeName.ID.Name.NumChars
                && !memicmp( exe_type_name->Name, type->TypeName.ID.Name.Name,
                             exe_type_name->NumChars ) ) break;
        } else if( !(type->TypeName.IsName) && exe_type->Info.type & 0x8000 ) {
            /* if they are both numbers */
            if( type->TypeName.ID.Num == (exe_type->Info.type & ~0x8000) ) {
                break;
            }
        }
    }

    if( exe_type == NULL ) {
        /* this is a new type */
        exe_type = addExeTypeRecord( restab, type );
    }

    return( exe_type );
} /* findExeTypeRecord */
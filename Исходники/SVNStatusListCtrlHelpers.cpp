bool CSVNStatusListCtrl::CSorter::operator()
( const FileEntry* entry1
 , const FileEntry* entry2) const
{
#define SGN(x) ((x)==0?0:((x)>0?1:-1))

    int result = 0;
    switch (sortedColumn)
    {
    case 19:
        {
            if (result == 0)
            {
                __int64 fileSize1 = entry1->isfolder ? 0 : entry1->working_size != (-1) ? entry1->working_size : entry1->GetPath().GetFileSize();
                __int64 fileSize2 = entry2->isfolder ? 0 : entry2->working_size != (-1) ? entry2->working_size : entry2->GetPath().GetFileSize();

                result = int(fileSize1 - fileSize2);
            }
        }
    case 18:
        {
            if (result == 0)
            {
                __int64 writetime1 = entry1->GetPath().GetLastWriteTime();
                __int64 writetime2 = entry2->GetPath().GetLastWriteTime();

                FILETIME* filetime1 = (FILETIME*)(__int64*)&writetime1;
                FILETIME* filetime2 = (FILETIME*)(__int64*)&writetime2;

                result = CompareFileTime(filetime1,filetime2);
            }
        }
    case 17:
        {
            if (result == 0)
            {
                result = SGN(entry1->last_commit_date - entry2->last_commit_date);
            }
        }
    case 16:
        {
            if (result == 0)
            {
                result = entry1->remoterev - entry2->remoterev;
            }
        }
    case 15:
        {
            if (result == 0)
            {
                result = entry1->last_commit_rev - entry2->last_commit_rev;
            }
        }
    case 14:
        {
            if (result == 0)
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->last_commit_author, entry2->last_commit_author);
                else
                    result = StrCmpI(entry1->last_commit_author, entry2->last_commit_author);
            }
        }
    case 13:
        {
            if (result == 0)
            {
                result = (int)(entry1->lock_date - entry2->lock_date);
            }
        }
    case 12:
        {
            if (result == 0)
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->lock_comment, entry2->lock_comment);
                else
                    result = StrCmpI(entry1->lock_comment, entry2->lock_comment);
            }
        }
    case 11:
        {
            if (result == 0)
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->lock_owner, entry2->lock_owner);
                else
                    result = StrCmpI(entry1->lock_owner, entry2->lock_owner);
            }
        }
    case 10:
        {
            if (result == 0)
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->url, entry2->url);
                else
                    result = StrCmpI(entry1->url, entry2->url);
            }
        }
    case 9:
        {
            if (result == 0)
            {
                result = entry1->depth - entry2->depth;
            }
        }
    case 8:
        {
            if (result == 0)
            {
                result = entry1->remotepropstatus - entry2->remotepropstatus;
            }
        }
    case 7:
        {
            if (result == 0)
            {
                result = entry1->remotetextstatus - entry2->remotetextstatus;
            }
        }
    case 6:
        {
            if (result == 0)
            {
                result = entry1->propstatus - entry2->propstatus;
            }
        }
    case 5:
        {
            if (result == 0)
            {
                result = entry1->textstatus - entry2->textstatus;
            }
        }
    case 4:
        {
            if (result == 0)
            {
                result = entry1->remotestatus - entry2->remotestatus;
            }
        }
    case 3:
        {
            if (result == 0)
            {
                result = entry1->status - entry2->status;
            }
        }
    case 2:
        {
            if (result == 0)
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->path.GetFileExtension(), entry2->path.GetFileExtension());
                else
                    result = StrCmpI(entry1->path.GetFileExtension(), entry2->path.GetFileExtension());
            }
        }
    case 1:
        {
            // do not sort by file/dirname if the sorting isn't done by this specific column but let the second-order
            // sorting be done by path
            if ((result == 0)&&(sortedColumn == 1))
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->path.GetFileOrDirectoryName(), entry2->path.GetFileOrDirectoryName());
                else
                    result = StrCmpI(entry1->path.GetFileOrDirectoryName(), entry2->path.GetFileOrDirectoryName());
            }
        }
    case 0:     // path column
        {
            if (result == 0)
            {
                if (s_bSortLogical)
                    result = StrCmpLogicalW(entry1->path.GetWinPath(), entry2->path.GetWinPath());
                else
                    result = StrCmpI(entry1->path.GetWinPath(), entry2->path.GetWinPath());
            }
        }
    default:
        if ((result == 0) && (sortedColumn > 0))
        {
            // N/A props are "less than" empty props

            const CString& propName = columnManager->GetName (sortedColumn);

            auto propEntry1 = control->m_PropertyMap.find(entry1->GetPath());
            auto propEntry2 = control->m_PropertyMap.find(entry2->GetPath());
            bool entry1HasProp = (propEntry1 != control->m_PropertyMap.end()) && propEntry1->second.HasProperty (propName);
            bool entry2HasProp = (propEntry2 != control->m_PropertyMap.end()) && propEntry2->second.HasProperty (propName);

            if (entry1HasProp)
            {
                result = entry2HasProp
                    ? propEntry1->second[propName].Compare
                    (propEntry2->second[propName])
                    : 1;
            }
            else
            {
                result = entry2HasProp ? -1 : 0;
            }
        }
    } // switch (m_nSortedColumn)
    if (!ascending)
        result = -result;

    return result < 0;
}
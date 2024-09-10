void CatalogManager::deleteIndex(string indexName)
{
    if (!indexExisted(indexName))                   //如果没有这个索引
    {
        printf("Failed to delete index %s. Index does not existed.\n", indexName.c_str());
        return;
    }
    else                                            //有这个索引
    {
        BufferManager buffer;
        CatalogPage catalog;
        IndexCatalogPage indexPage;
        string s,tableName,attrName;
        int i,num,n,x;
        
        s=indexLocation(indexName);                 //找到这个索引
        tableName="";                               //分割字符串
        attrName="";
        i=0;
        while (s[i]!=' ')
        {
            tableName=tableName+s[i];
            i++;
        }
        
        while (s[i]==' ')
            i++;
        
        while (s[i]!=0)
        {
            attrName=attrName+s[i];
            i++;
        }
        
        printf("#%s#  @%s@  *%s*\n",indexName.c_str(), tableName.c_str(), attrName.c_str());
        printf("~%s~\n",primaryKey(tableName).c_str());
        if (indexName == tableName+attrName && primaryKey(tableName) == attrName)
        {
            printf("Failed to delete index %s. Default index on primary key cannot be deleted.\n",indexName.c_str());
            return;
        }
        
        indexPage.pageIndex=1;
        buffer.readPage(indexPage);
        n=*(int*)indexPage.pageData;
        i=1;
        while (i<=n)                                //开始在indexCatalogPage里逐条检查，删除这个索引
        {
            x=indexPage.readPrevDel(i);
            if (x==0)                               //如果当前条未被删除
            {
                s=indexPage.readIndexName(i);
                if (s==indexName)                   //如果找到要删的这条索引
                {
                    indexPage.deleteIndex(i);       //删掉它
                    break;
                }
            }
            else                                    //如果当前条已被删除，则最后一条位置后移
                n++;

            i++;
        }
        
        buffer.writePage(indexPage);
        catalog.tableName = tableName;              //在catalogPage里面的对应属性上修改索引总数
        buffer.readPage(catalog);
        num = (int)catalog.pageData[0];
        for (i=0; i<num; i++) {
            if (catalog.readAttrName(i) == attrName)
            {
                catalog.modifyAttrIndexNum(i,-1);
                buffer.writePage(catalog);
                if (catalog.readAttrIndexNum(i)==0)
                {
                    BufferManager bm;
                    string filePath=bm.indexFilePath(tableName, attrName);
                    if (bm.indexFileIsExist(tableName, attrName))
                        bm.deleteIndexFile(tableName, attrName);
                }

                break;
            }
        }

        printf("Deleted index %s successfully!\n",indexName.c_str());
    }
}
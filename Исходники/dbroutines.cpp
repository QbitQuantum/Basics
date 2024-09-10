int DBWorker::GenerateBathch(char* batch_name)
{
    int idbatches=0;
    try {
        sql::PreparedStatement *PrepStmt;
        sql::ResultSet *res;

        PrepStmt = con->prepareStatement(
                       "INSERT INTO batches(name) VALUES(?)"
                   );
        PrepStmt->setString(1,batch_name);
        PrepStmt->execute();

        PrepStmt = con->prepareStatement(
                       "SELECT LAST_INSERT_ID()"
                   );
        res = PrepStmt->executeQuery();
        delete PrepStmt;
        res->next();
        idbatches = res->getInt(1);
        delete res;

        PrepStmt = con->prepareStatement(
                       "INSERT INTO batch_elem(idbatches,bat_order,idobjectives) VALUES(?,?,?)"
                   );
        PrepStmt->setInt(1,idbatches);

        int i=1;
        CMyProblem P(0,0);
        for(int n=21; n<=30; n++)
        {
            while (i<=(n-20)*6)
            {
                char buff[256];
                sprintf(buff, "b%d-%d_%d",idbatches,n,i);
                //P.GenerateRandomProblem(n,3,buff);
                P.GenerateRandomProblemWNC(n,3+((n-20)*6-i-1)/3,buff);
                int idproblems = P.WriteToDB();
                int idobjectives = GenerateDefaultObjective(idproblems);
                PrepStmt->setInt(2,i);
                PrepStmt->setInt(3,idobjectives);
                PrepStmt->execute();
                i++;
            }
        }


        delete PrepStmt;
    }
    catch (sql::SQLException &e) {
        SQLError(e);
    }
    return idbatches;
}
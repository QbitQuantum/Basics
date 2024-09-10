/**
 * refreshReport()
 *
 * Fills the report body with data.
 */
void salesByServiceDetailReport::refreshReport()
{
    repBody->clear();
    if (!myBillableID) return;

    ADB     DB;
    QDate   sDate = this->startDateCal->date();
    QDate   eDate = this->endDateCal->date();
    QString companyName;
    QString customerName;
    QString tmpStr;
    double  grandTotal = 0.00;

    QApplication::setOverrideCursor(waitCursor);

    if (myIsPackage) {
        PackagesDB  PDB;
        PDB.get(myBillableID);
        tmpStr = tmpStr.sprintf("Sales Detail Report\n%s (Package)", PDB.getStr("Description"));
        setTitle(tmpStr);

        //debug(1,"select AcctsRecv.TransDate, AcctsRecv.PackageItem, Packages.InternalID, Packages.PackageTag, AcctsRecv.Amount, Customers.CustomerID, Customers.FullName, Customers.ContactName from AcctsRecv, Packages, Customers where Packages.InternalID = AcctsRecv.PackageItem and AcctsRecv.TransType = 0 and AcctsRecv.ItemID = %d and AcctsRecv.TransDate  >= '%04d-%02d-%02d' and AcctsRecv.TransDate <= '%04d-%02d-%02d' and Customers.CustomerID = AcctsRecv.CustomerID order by Customers.CustomerID\n", myBillableID, sDate.year(), sDate.month(), sDate.day(), eDate.year(), eDate.month(), eDate.day());
        DB.query("select AcctsRecv.TransDate, AcctsRecv.PackageItem, Packages.InternalID, Packages.PackageTag, AcctsRecv.Amount, Customers.CustomerID, Customers.FullName, Customers.ContactName from AcctsRecv, Packages, Customers where Packages.InternalID = AcctsRecv.PackageItem and AcctsRecv.TransType = 0 and AcctsRecv.PackageItem = %d and AcctsRecv.TransDate  >= '%04d-%02d-%02d' and AcctsRecv.TransDate <= '%04d-%02d-%02d' and Customers.CustomerID = AcctsRecv.CustomerID order by Customers.CustomerID", myBillableID, sDate.year(), sDate.month(), sDate.day(), eDate.year(), eDate.month(), eDate.day());

    } else {
        // Get the title.
        BillablesDB BDB;
        BDB.get(myBillableID);
        tmpStr = tmpStr.sprintf("Sales Detail Report\n%s", BDB.getStr("Description"));
        setTitle(tmpStr);

        // Two queries, one for standalone billables, one for packages.
        DB.query("select AcctsRecv.TransDate, AcctsRecv.ItemID, Billables.ItemID, AcctsRecv.Amount, AcctsRecv.StatementNo, Customers.CustomerID, Customers.FullName, Customers.ContactName from AcctsRecv, Billables, Customers where Billables.ItemNumber = AcctsRecv.ItemID and AcctsRecv.TransType = 0 and AcctsRecv.ItemID = %d and AcctsRecv.PackageItem = 0 and AcctsRecv.TransDate  >= '%04d-%02d-%02d' and AcctsRecv.TransDate <= '%04d-%02d-%02d' and Customers.CustomerID = AcctsRecv.CustomerID order by Customers.CustomerID", myBillableID, sDate.year(), sDate.month(), sDate.day(), eDate.year(), eDate.month(), eDate.day());
    }
    // Both queries return compatible result sets for a single pass
    // through the returned rows.
    if (DB.rowCount) while (DB.getrow()) {
        customerName = "";
        companyName  = "";
        // Check for a company name.
        if (strlen(DB.curRow["ContactName"])) {
            customerName = DB.curRow["ContactName"];
            companyName  = DB.curRow["FullName"];
        } else {
            customerName = DB.curRow["FullName"];
        }
        new Q3ListViewItem(repBody, 
                DB.curRow["TransDate"],
                DB.curRow["Amount"], 
                DB.curRow["CustomerID"],
                customerName,
                companyName,
                DB.curRow["StatementNo"]
                );
        grandTotal += atof(DB.curRow["Amount"]);
    }
    tmpStr = tmpStr.sprintf("%.2f", grandTotal);
    new Q3ListViewItem(repBody, "Total", tmpStr);

    QApplication::restoreOverrideCursor();
}
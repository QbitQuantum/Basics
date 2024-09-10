int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connect("localhost", 5988, String::EMPTY, String::EMPTY);

        Array<CIMInstance> cimInstance;
        try
        {
            cimInstance = client.enumerateInstances(
                             NAMESPACE,
                             CIMName("PG_WBEMSLPTemplate"));
        }
        catch (Exception& e)
        {
            cout<<e.getMessage()<<endl;
        }

        // There should be one instance
        if (cimInstance.size() == 0)
        {
            cout << "+++++ Error: enumerateInstances on WBEMSLPTemplate"\
                   << endl;
            cout << "+++++ Test failed" << endl;
            return 1;
        }
        else
        {

            Array<CIMObjectPath> instanceNames = client.enumerateInstanceNames(
                                                  NAMESPACE,
                                                 CIMName("PG_WBEMSLPTemplate"));



            for (Uint32 i = 0; i < instanceNames.size(); i++)
            {
                CIMInstance cimInstance1 = client.getInstance(
                                              NAMESPACE,instanceNames[i]);
                Uint32 NumProperties;
                cout << "Getting all properties for WBEMSLPTemplate \
                instance ....  "<< i+1 <<"\n";

                NumProperties = cimInstance1.getPropertyCount();
                for(Uint32 j=0;j<NumProperties;j++)
                {
                    CIMProperty cimProperty=cimInstance1.getProperty(j);
                    CIMValue cimValue=cimProperty.getValue();
                    CIMName cimName=cimProperty.getName();
                    cout << cimName.getString() << " is "  << \
                                 cimValue.toString() << "\n";
                }
            }
         }
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

     cout << "+++++ SLP Test Passed +++++"<< endl;
     return 0;
}
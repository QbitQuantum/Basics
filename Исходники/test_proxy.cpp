int main(int argc, char* argv[]){
    Ice::CommunicatorPtr ic = EasyIce::initialize(argc, argv);
    Ice::PropertiesPtr prop = ic->getProperties();
    prop->setProperty("Test.Adapter.Endpoints", "tcp -h localhost -p 65000");

    Ice::ObjectPtr obj = new IceMX::Metrics();
    Ice::ObjectAdapterPtr adapter = ic->createObjectAdapter("Test.Adapter");
    adapter->add(obj, ic->stringToIdentity("metric"));

    std::cout<<"\n### EXAMPLE with easyiceconfig::proxies::createProxy() ###"<<std::endl;

    /// Exception due empty proxy
    try{
        easyiceconfig::proxies::createProxy<IceMX::MetricsPrx>(ic, "Test.Proxy", false);
    } catch (Ice::ProxyParseException ex){
        std::cout<<"Expected ProxyParseException\n"<<ex<<std::endl;
    }

    IceMX::MetricsPrx pxr;
    /// All ok (1)
    /// Proxy from string do not create entry at Properties
    pxr = easyiceconfig::proxies::createProxy<IceMX::MetricsPrx>(ic, "metric:tcp -h localhost -p 65000", true);
    easyiceconfig::debug::printProperties(prop);

    /// All ok (2)
    prop->setProperty("Test.Proxy", "metric:tcp -h localhost -p 65000");
    pxr = easyiceconfig::proxies::createProxy<IceMX::MetricsPrx>(ic, "Test.Proxy", false);
    easyiceconfig::debug::printProperties(prop);

    // Using it
    std::cout << "Gathering some info" << std::endl;
    std::cout << pxr->ice_id() << std::endl;
    std::cout << pxr->ice_toString() << std::endl;


    std::cout<<"\n### EXAMPLE with EasyIce::EasyProxy ###"<<std::endl;

    EasyIce::EasyProxy<IceMX::MetricsPrx> proxy(ic, "bad endpoint definition", true);
    if (proxy){
        //do stuff
    }else
        std::cout<<proxy.exception()<<std::endl;


    // copying
    EasyIce::EasyProxy<IceMX::MetricsPrx> p2;
    p2 = EasyIce::EasyProxy<IceMX::MetricsPrx>(ic, "bad endpoint definition", true);
    try{
    p2 = EasyIce::createProxy<IceMX::MetricsPrx>(ic, "bad endpoint definition", true);
    }catch(Ice::Exception){}

    ic->shutdown();
}
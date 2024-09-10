void try_set(zmqpp::socket& socket, zmqpp::socket_option const& option, CheckType const& value, std::string const& option_name, std::string const& value_type)
{
    BOOST_CHECKPOINT("setting option " << option_name << " against set type '" << value_type << "'");
    try
    {
        socket.set(option, value);
        BOOST_CHECK_MESSAGE(typeid(CheckType) == typeid(WantedType), "expected exception setting option '" << option_name << "' against type '" << value_type << "'");
    }
    catch(zmqpp::zmq_internal_exception const& e)
    {
        BOOST_CHECK_MESSAGE(false, "threw internal exception " << e.zmq_error() << " '" << e.what() << "' setting option '" << option_name << "' against type '" << value_type << "'");
    }
    catch(zmqpp::exception const& e)
    {
        BOOST_CHECK_MESSAGE(typeid(CheckType) != typeid(WantedType), "threw unexpected exception '" << e.what() << "' setting option '" << option_name << "' against type '" << value_type << "'");
    }
}
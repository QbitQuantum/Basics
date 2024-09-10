/* Some error occured at lower levels. Logging it and deactivating the current session seems legit.
 */
void ServerProtocolDispatcher::handle_error(
    boost::system::error_code error)
{
  std::cout << "ServerProtocolDispatcher::handle_error: " << error.message() << std::endl;
  _active = false;
}
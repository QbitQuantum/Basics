void twitch_irc::handle_write(const boost::system::error_code &error)
{
    if (error) {
        cerr << error.message() << endl;
    }
}
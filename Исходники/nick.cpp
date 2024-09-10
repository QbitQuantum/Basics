string Nick::getLongName() const
{
	return getNickname()  + "!" +
	       getIdentname() + "@" +
	       getHostname();
}
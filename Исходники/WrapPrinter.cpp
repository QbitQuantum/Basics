void
WrapPrinter::operator()(const boost::shared_ptr<WrapIP>& ip) const
{
	outstream << "IP: " << std::endl << "\tsrc: " << ip->getSrcAddressString() << " dst:" << ip->getDstAddressString() << std::endl;
	outstream << "\thead_len: " << ip->getHeaderLength() << ", ver: " << ip->getVersion() << std::endl;
	outstream << "\tip_len: " << ip->getLength() << ", payload_len: " << ip->getPayloadLength() << std::endl;
}
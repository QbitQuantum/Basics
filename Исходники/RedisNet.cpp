void		RedisNet::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
//	boost::lock_guard<boost::mutex>	lock(mutex_);
	boost::mutex::scoped_lock		lock(mutex_);
//	cerr << "HandleWrite() bytes_transferred : " << bytes_transferred << endl;
//	memmove_s(&writeBuffer_[position_ - bytes_transferred], REDIS_NET_BUFFER_SIZE, &writeBuffer_[position_], bytes_transferred);
	memmove_s(&writeBuffer_[0], REDIS_NET_BUFFER_SIZE, &writeBuffer_[bytes_transferred], bytes_transferred);
	position_ -= bytes_transferred;
}
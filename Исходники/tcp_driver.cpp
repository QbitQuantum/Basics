void Binlog_tcp_driver::handle_net_packet(const boost::system::error_code& err, std::size_t bytes_transferred)
{
  if (err)
  {
    Binary_log_event * ev= create_incident_event(175, err.message().c_str(), m_binlog_offset);
    m_event_queue->push_front(ev);
    return;
  }

  if (bytes_transferred > MAX_PACKAGE_SIZE || bytes_transferred == 0)
  {
    std::ostringstream os;
    os << "Expected byte size to be between 0 and "
       << MAX_PACKAGE_SIZE
       << " number of bytes; got "
       << bytes_transferred
       << " instead.";
    Binary_log_event * ev= create_incident_event(175, os.str().c_str(), m_binlog_offset);
    m_event_queue->push_front(ev);
    return;
  }

  //assert(m_waiting_event != 0);
  //std::cerr << "Committing '"<< bytes_transferred << "' bytes to the event stream." << std::endl;
  m_event_stream_buffer.commit(bytes_transferred);
  /*
    If the event object doesn't have an event length it means that the header
    hasn't been parsed. If the event stream also contains enough bytes
    we make the assumption that the next bytes waiting in the stream is
    the event header and attempt to parse it.
   */
  if (m_waiting_event->event_length == 0 && m_event_stream_buffer.size() >= 19)
  {
    /*
      Copy and remove from the event stream, the remaining bytes might be
      dynamic payload.
     */
    //std::cerr << "Consuming event stream for header. Size before: " << m_event_stream_buffer.size() << std::endl;
    proto_event_packet_header(m_event_stream_buffer, m_waiting_event);
    //std::cerr << " Size after: " << m_event_stream_buffer.size() << std::endl;
  }

  //std::cerr << "Event length: " << m_waiting_event->header()->event_length << " and available payload size is " << m_event_stream_buffer.size()+LOG_EVENT_HEADER_SIZE-1 <<  std::endl;
  if (m_waiting_event->event_length == m_event_stream_buffer.size() + LOG_EVENT_HEADER_SIZE - 1)
  {
    /*
     If the header length equals the size of the payload plus the
     size of the header, the event object is complete.
     Next we need to parse the payload buffer
     */
    std::istream is(&m_event_stream_buffer);
    Binary_log_event * event= parse_event(is, m_waiting_event);

    m_event_stream_buffer.consume(m_event_stream_buffer.size());

    m_event_queue->push_front(event);

    /*
      Note on memory management: The pushed Binary_log_event will be
      deleted in user land.
    */
    delete m_waiting_event;
    m_waiting_event= 0;
  }

  if (!m_shutdown)
    GET_NEXT_PACKET_HEADER;

}
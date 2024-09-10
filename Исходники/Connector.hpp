        boost::system::error_code Connector::connect(
            SocketType & peer1, 
            NetName const & netname, 
            boost::system::error_code & ec)
        {
            typedef typename SocketType::protocol_type::socket socket;
            typedef typename socket::endpoint_type endpoint_type;

            socket & peer(peer1); // we should use the real socket type, not the child type

            if (netname.is_digit()) {
                return connect(peer, netname.endpoint(), ec);
            }
            if (!started_) {
                canceled_ = canceled_forever_;
                stat_.reset();
                connect_started_ = false;
                boost::asio::detail::mutex::scoped_lock lock(mutex_);
                if (canceled_) {
                    ec = boost::asio::error::operation_aborted;
                    canceled_ = false;
                } else {
                    lock.unlock();
                    resolver_iterator_ = resolver_.resolve(netname, ec);
                    lock.lock();
                }
                stat_.resolve_time = stat_.elapse();
                if (ec) {
                    return ec;
                } else if (canceled_) {
                    canceled_ = false;
                    return ec = boost::asio::error::operation_aborted;
                }
                started_ = true;
            }
            ResolverIterator end;
            for (; resolver_iterator_ != end; ++resolver_iterator_) {
                if (!connect_started_) {
                    Endpoint const & e = *resolver_iterator_;
                    {
                        boost::asio::detail::mutex::scoped_lock lock(mutex_);
                        if (canceled_) {
                            ec = boost::asio::error::operation_aborted;
                            canceled_ = false;
                        } else {
                            if (peer.is_open()) {
                                peer.close(ec);
                            }
                            boost::asio::socket_base::non_blocking_io cmd1(non_block_);
#ifndef UNDER_CE
                            boost::asio::socket_base::receive_time_out cmd2(time_out_);
#endif
                            ec || peer.open(endpoint_type(e).protocol(), ec) 
                                || peer.io_control(cmd1, ec) 
#ifndef UNDER_CE
                                || peer.set_option(cmd2, ec)
#endif
                                ;
                        }
                    }
                    if (ec) {
                        break;
                    }
                    LOG_TRACE("[connect] try server, ep: " << e.to_string());
                    start_connect(peer, e, ec);
                } else {
                    ec = boost::asio::error::would_block;
                }
                if (ec == boost::asio::error::would_block) {
                    pool_connect(peer, ec);
                }
                if (ec != boost::asio::error::would_block) {
                    if (!ec) {
                        post_connect(peer, ec);
                    } else {
                        boost::system::error_code ec1;
                        post_connect(peer, ec1);
                    }
                }
                if (!ec || ec == boost::asio::error::would_block || canceled_) {
                    break;
                }
                LOG_DEBUG("[connect] failed, ep: " << 
                    resolver_iterator_->to_string() << ",ec: " << ec.message());
            } // for
            if ((!ec || ec == boost::asio::error::would_block) && canceled_) {
                ec = boost::asio::error::operation_aborted;
            }
            if (ec != boost::asio::error::would_block) {
                stat_.connect_time = stat_.elapse();
                started_ = false;
                canceled_ = false;
            }
            return ec;
        }
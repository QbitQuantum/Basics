err_code_t ConnectionPool::waitPoll() {
  if (m_nActiveConn == 0) {
    if (m_nInvalidKey > 0) {
      return RET_INVALID_KEY_ERR;
    } else {
      // hard server error
      return RET_MC_SERVER_ERR;
    }
  }
  nfds_t n_fds = m_nActiveConn;
  pollfd_t pollfds[n_fds];

  Connection* fd2conn[n_fds];

  pollfd_t* pollfd_ptr = NULL;
  nfds_t fd_idx = 0;

  for (std::vector<Connection*>::iterator it = m_activeConns.begin(); it != m_activeConns.end();
       ++it, ++fd_idx) {
    Connection* conn = *it;
    pollfd_ptr = &pollfds[fd_idx];
    pollfd_ptr->fd = conn->socketFd();
    pollfd_ptr->events = POLLOUT;
    fd2conn[fd_idx] = conn;
  }

  err_code_t ret_code = RET_OK;
  while (m_nActiveConn) {
    int rv = poll(pollfds, n_fds, m_pollTimeout);
    if (rv == -1) {
      markDeadAll(pollfds, keywords::kPOLL_ERROR);
      ret_code = RET_POLL_ERR;
      break;
    } else if (rv == 0) {
      log_warn("poll timeout. (m_nActiveConn: %d)", m_nActiveConn);
      // NOTE: MUST reset all active TCP connections after timeout.
      markDeadAll(pollfds, keywords::kPOLL_TIMEOUT);
      ret_code = RET_POLL_TIMEOUT_ERR;
      break;
    } else {
      err_code_t err;
      for (fd_idx = 0; fd_idx < n_fds; fd_idx++) {
        pollfd_ptr = &pollfds[fd_idx];
        Connection* conn = fd2conn[fd_idx];

        if (pollfd_ptr->revents & (POLLERR | POLLHUP | POLLNVAL)) {
          markDeadConn(conn, keywords::kCONN_POLL_ERROR, pollfd_ptr);
          ret_code = RET_CONN_POLL_ERR;
          m_nActiveConn -= 1;
          goto next_fd;
        }

        // send
        if (pollfd_ptr->revents & POLLOUT) {
          // POLLOUT send
          ssize_t nToSend = conn->send();
          if (nToSend == -1) {
            markDeadConn(conn, keywords::kSEND_ERROR, pollfd_ptr);
            ret_code = RET_SEND_ERR;
            m_nActiveConn -= 1;
            goto next_fd;
          } else {
            // start to recv if any data is sent
            pollfd_ptr->events |= POLLIN;

            if (nToSend == 0) {
              // debug("[%d] all sent", pollfd_ptr->fd);
              pollfd_ptr->events &= ~POLLOUT;
              if (conn->m_counter == 0) {
                // just send, no recv for noreply
                --this->m_nActiveConn;
              }
            }
          }
        }

        // recv
        if (pollfd_ptr->revents & POLLIN) {
          // POLLIN recv
          ssize_t nRecv = conn->recv();
          if (nRecv == -1 || nRecv == 0) {
            markDeadConn(conn, keywords::kRECV_ERROR, pollfd_ptr);
            ret_code = RET_RECV_ERR;
            m_nActiveConn -= 1;
            goto next_fd;
          }

          conn->process(err);
          switch (err) {
            case RET_OK:
              pollfd_ptr->events &= ~POLLIN;
              --m_nActiveConn;
              break;
            case RET_INCOMPLETE_BUFFER_ERR:
              break;
            case RET_PROGRAMMING_ERR:
              markDeadConn(conn, keywords::kPROGRAMMING_ERROR, pollfd_ptr);
              ret_code = RET_PROGRAMMING_ERR;
              m_nActiveConn -= 1;
              goto next_fd;
              break;
            case RET_MC_SERVER_ERR:
              // soft server error
              markDeadConn(conn, keywords::kSERVER_ERROR, pollfd_ptr);
              ret_code = RET_MC_SERVER_ERR;
              m_nActiveConn -= 1;
              goto next_fd;
              break;
            default:
              NOT_REACHED();
              break;
          }
        }

next_fd: {}
      } // end for
    }
  }
  return ret_code;
}
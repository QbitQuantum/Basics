HLE::ReturnCode TicketReader::Unpersonalise(HLE::IOSC& iosc)
{
  const auto ticket_begin = m_bytes.begin();

  // IOS uses IOSC to compute an AES key from the peer public key and the device's private ECC key,
  // which is used the decrypt the title key. The IV is the ticket ID (8 bytes), zero extended.
  using namespace HLE;
  IOSC::Handle public_handle;
  ReturnCode ret =
      iosc.CreateObject(&public_handle, IOSC::TYPE_PUBLIC_KEY, IOSC::SUBTYPE_ECC233, PID_ES);
  if (ret != IPC_SUCCESS)
    return ret;

  const auto public_key_iter = ticket_begin + offsetof(Ticket, server_public_key);
  ret = iosc.ImportPublicKey(public_handle, &*public_key_iter, nullptr, PID_ES);
  if (ret != IPC_SUCCESS)
    return ret;

  IOSC::Handle key_handle;
  ret = iosc.CreateObject(&key_handle, IOSC::TYPE_SECRET_KEY, IOSC::SUBTYPE_AES128, PID_ES);
  if (ret != IPC_SUCCESS)
    return ret;

  ret = iosc.ComputeSharedKey(key_handle, IOSC::HANDLE_CONSOLE_KEY, public_handle, PID_ES);
  if (ret != IPC_SUCCESS)
    return ret;

  std::array<u8, 16> iv{};
  std::copy_n(ticket_begin + offsetof(Ticket, ticket_id), sizeof(Ticket::ticket_id), iv.begin());

  std::array<u8, 16> key{};
  ret = iosc.Decrypt(key_handle, iv.data(), &*ticket_begin + offsetof(Ticket, title_key),
                     sizeof(Ticket::title_key), key.data(), PID_ES);
  // Finally, IOS copies the decrypted title key back to the ticket buffer.
  if (ret == IPC_SUCCESS)
    std::copy(key.cbegin(), key.cend(), ticket_begin + offsetof(Ticket, title_key));

  return ret;
}
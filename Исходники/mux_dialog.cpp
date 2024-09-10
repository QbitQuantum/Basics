void
mux_process::process_input(bool end_of_process) {
  if (!m_dialog)
    return;

  std::string input;
  auto in = GetInputStream();
  if (in)
    while (in->CanRead())
      input += in->GetC();

  if (end_of_process)
    input += "\n";

  if (!input.empty())
    m_dialog->add_input(input);
}
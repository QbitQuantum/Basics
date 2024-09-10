            std::string ParagraphStream::read() throw(IOException)
            {

              StringBuilder *paragraph = new StringBuilder();

              while (true)
              {
                std::string line = samples->read();

                // The last paragraph in the input might not
                // be terminated well with a new line at the end.

                if (line == "" || line == "")
                {
                  if (paragraph->length() > 0)
                  {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
                    return paragraph->toString();
                  }
                }
                else
                {
                  paragraph->append(line)->append('\n');
                }

                if (line == "")
                  return 0;
              }
            }
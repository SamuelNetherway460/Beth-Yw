


/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains the code responsible for opening and closing file
  streams. The actual handling of the data from that stream is handled
  by the functions in data.cpp. See the header file for additional comments.
 */

#include "input.h"

/*
  Initialises an InputSource.

  @param source
    A unique identifier for a source (i.e. the location).
*/
InputSource::InputSource(const std::string& source) : source(source) {}

/*
  Gets the std::string source.

  @return
    A non-modifiable value for the source passed into the constructor.
*/
std::string InputSource::getSource() const noexcept {
  return source;
}


/*
  Constructs a file-based source.

  @param path
    The complete path for a file to import.

  @example
    InputFile input("data/areas.csv");
*/
InputFile::InputFile(const std::string &filePath) : InputSource(filePath) {
}

/*
  Destructor for the file-based source.
 */
InputFile::~InputFile() {
  is.close();
}

/*
  Opens a file stream to the file path retrievable from getSource()
  and returns a reference to the stream.

  @return
    A standard input stream reference

  @throws
    std::runtime_error if there is an issue opening the file, with the message:
    InputFile::open: Failed to open file <file name>

  @example
    InputFile input("data/areas.csv");
    input.open();
*/
std::istream& InputFile::open() {
  is.open(source);
  if (is.is_open() == 0) throw std::runtime_error("InputFile::open: Failed to open file " + source);
  return is;
}

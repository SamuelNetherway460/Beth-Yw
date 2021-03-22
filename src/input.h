#ifndef INPUT_H_
#define INPUT_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 955794

  This file contains declarations for the input source handlers. There are
  two classes: InputSource and InputFile. InputSource is abstract (i.e. it
  contains a pure virtual function). InputFile is a concrete derivation of
  InputSource, for input from files.
 */

#include <string>
#include <fstream>

/*
  InputSource is an abstract/purely virtual base class for all input source 
  types. In future versions of our application, we may support multiple input 
  data sources such as files and web pages.
*/
class InputSource {
protected:
  std::string source;

  InputSource(const std::string& source);

public:
  std::string getSource() const noexcept;
};

/*
  Source data that is contained within a file.
*/
class InputFile : public InputSource {
private:
  std::ifstream is;

public:

  InputFile(const std::string &filePath);
  ~InputFile();

  std::istream& open();
};

#endif // INPUT_H_
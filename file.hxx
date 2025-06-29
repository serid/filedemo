#include <cstring>
#include <fstream>
#include <iostream>

namespace file {
  class File {
  private:
    std::fstream stream;
    std::string filepath;
    std::ios_base::openmode mode;
  public:
    File(const std::string& filepath, std::ios_base::openmode mode)
      : filepath(filepath), mode(mode), stream(filepath, mode) {
      if (!this->stream)
        throw std::runtime_error(filepath + ": " + std::strerror(errno));
    }

    auto read_line() -> std::string {
      if ((this->mode & std::ios::in) == 0)
        throw std::runtime_error(filepath + " not open for reading");
      std::string line;
      std::getline(this->stream, line); // still admits lines terminated by EOF instead of \n
      if (line.length() == 0)
        throw std::runtime_error("expected a line, found EOF");
      return line;
    }

    void write_line(std::string_view s) {
      if ((this->mode & std::ios::out) == 0)
        throw std::runtime_error(filepath + " not open for writing");
      this->stream << s << std::endl;
    }

    ~File() = default;
  };
}

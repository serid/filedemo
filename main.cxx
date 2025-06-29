#include <iostream>

#include "file.hxx"

int main() {
  {
    file::File file1("doeg.txt", std::ios::out);

    file1.write_line("Hello");
    file1.write_line("world");
  }
  { // Open file for reading and appending
    file::File file1("doeg.txt", std::ios::in | std::ios::out | std::ios::app);
    std::cout << file1.read_line() << std::endl; // Prints "Hello"
    file1.write_line("spb"); // Appends "spb" to file end
  }
  {
    file::File file1("doeg.txt", std::ios::in);
    try {
      std::cout << file1.read_line() << std::endl; // Prints "Hello"
      std::cout << file1.read_line() << std::endl; // Prints "world"
      std::cout << file1.read_line() << std::endl; // Prints "spb"
      std::cout << file1.read_line() << std::endl; // throws
    } catch (const std::runtime_error& e) {
      std::cout << "error: " << e.what() << std::endl;
    }
  }
  { // Without append, rewrites bytes
    file::File file1("doeg.txt", std::ios::in | std::ios::out);
    file1.read_line(); // Skip "Hello"

    // On Linux, replaces 3 bytes "wor" with 3 bytes "t\n".
    // Results may vary depending on line separator size on host OS.
    file1.write_line("to"); 
  }
  {
    try { // Writing throws when file is open in input mode
      file::File file1("doeg.txt", std::ios::in);
      file1.write_line("h");
    } catch (const std::runtime_error& e) {
      std::cout << "error: " << e.what() << std::endl;
    }
    try { // Opening a non-existend file is allowed, but reading will throw
      file::File file1("nonexistent.txt", std::ios::in);
      file1.read_line();
    } catch (const std::runtime_error& e) {
      std::cout << "error: " << e.what() << std::endl;
    }
  }
}

#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  std::stringstream output;
  string output_str;
  long h = (seconds / (60 * 60));
  seconds -= h * ((60 * 60));
  long m = (seconds / (60));
  seconds -= m * (60);

  output << std::setw(2) << std::setfill('0') << h << ":" ;
  output << std::setw(2) << std::setfill('0') << m << ":" ;
  output << std::setw(2) << std::setfill('0') << seconds;
  output >> output_str;

  return output_str;
}
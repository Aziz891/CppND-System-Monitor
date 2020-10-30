#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(void) {
  getCPU();
  System::fetchProcesses();
};

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }
void System::getCPU() {
  string line;
  std::vector<bool> check(2, false);
  string key;

  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kCpuinfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
     
      std::istringstream linestream(line);
      while (std::getline(linestream, key, ':')) {
        if (check[0]) {
          cpu_.name = key;
          check[1] = true;
        }

        if (key == "model name\t") {
          check[0] = true;
        }
      }
      if (check[0] && check[1]) break;
    }
  }
  //
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  std::sort(processes_.begin(), processes_.end(), []( auto &_1st,  auto &_2nd){
        return _1st.CpuUtilization() > _2nd.CpuUtilization(); 
    });
  return processes_; }
void System::fetchProcesses() {
  processes_.clear();
  vector<int> vec_int_pid = LinuxParser::Pids();

  for (size_t i = 0; i < vec_int_pid.size(); i++) {
    processes_.push_back(Process{vec_int_pid[i]});
  }
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }
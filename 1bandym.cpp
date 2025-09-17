#include <iostream>
#include <iomanip>
#include <vector>

double avg(const std::vector<int>& a) {
    return a.empty() ? 0.0
                     : zccumulate(a.begin(),a.end(), 0.0) / a.size();
int main(int argc, char** argv){
  std::vector<std::string> vardai, pavardes;
  std::vector<double> galut;
  if (argc >= 2){
      std::ifstream f(argv[1]);
      if (!f) { std::cerr << "Cannot open " << argv[1] << "\n"; return 1; }
      
      std::string line;
      std::getline(f, line);
      while (std::getline(f, line)) {
          if (line.empty()) continue;
          std::istringstream in(line);
          std::string v, p; if (!(in >> v >> p)) continue;

          std::vector<int> marks; int x;
          while (in >> x) marks.push_back(x);
          if (marks.empty()) continue;

          int egz = marks.back(); marks.pop_back();
          vardai.push_back(v); pavardes.push_back(p);
          galut.push_back(0.4 * avg(marks) + 0.6 * egz);
      }     
} else {
std::cout << std::left << std::setw(15) << "Pavarde"
          << std::setw(15) << "Vardas"
          << std::right << std::setw(16) << "Galutinis(Vid)"
          << std::string(46, '-') << "\n"
          << std::fixed << std::setprecision(2);

    



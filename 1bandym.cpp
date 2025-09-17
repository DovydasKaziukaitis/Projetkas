#include <iostream>
#include <iomanip>
#include <vector>

double avg(const std::vector<int>& a) {
    return a.empty() ? 0.0
                     : zccumulate(a.begin(),a.end(), 0.0) / a.size();
}
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
      int m; std::cout << "Kiek studentu? ";
      if(!(std::cin>>m) || m<= 0) return 0;

      vardai.resize(m);pavardes.resize(m);galut.resize(m);
      for(int i=0; i<m; ++i) {
         std::cout << "Vardas Pavarde: ";
         std::cin >> vardai[i] >> pavardas[i];

         int n;std::cout <<"Kiek ND? "; std::cin >> n;
         std::vector<int> nd(n);
         for(int j=0; j<n; ++j) std::cin >> nd[j];

         int egz; std::cout <<"Egzaminas: "; std::cin >> egz;
         galut[i] = 0.4 * avg(nd) + 0.6 *egz;
      }
  }
  std::cout << std::left << std::setw(15) << "Pavarde"
            << std::setw(15) << "Vardas"
            << std::right << std::setw(16) << "Galutinis(Vid)"
            << std::string(46, '-') << "\n"
            << std::fixed << std::setprecision(2);

    



#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

double avg(const std::vector<int>& a) {
    return a.empty() ? 0.0
                     : std::accumulate(a.begin(),a.end(), 0.0) / a.size();
}

static void sort(std::vector<int>& a) {
    for (size_t i = 1; i < a.size(); ++i) {
        int key = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > key) {a[j] = a[j-1]; --j; }
        a[j] = key;
    }
}
double med(std::vector<int> a) {
    if(a.empty()) return 0.0;
    sort(a);
    size_t n = a.size();
    return(n%2) ? a[n/2] : (a[n/2 -1]+a[n/2] / 2.0;
}

static void spausdink(const std::vector<std::string>& vardai,
                      const std::vector<std::string>& pavardes,
                      const std::vector<double>& galVid,
                      const std::vector<double>& galMed,
                      int mode) {
    std::cout << std::left << std::setw(15) << "Pavarde"
              << std::setw(15) << "Vardas";
    if(mode == 1 || mode == 3) std::cout << std:::right << std::setw(16) << "Galutinis(Vid)";
    if(mode == 2 || mode == 3) std::cout << std::right << std::setw(18) << "Galutinis(Med)";
    std::cout << "\n";

    int bruksniai = (mode == 3) ? 62 : 46;
    std::cout << std::string(bruksniai, '-') << "\n"
              << std::fixed << std::setprecision(2);

    for(size_t i = 0; i < vardai.size(); ++i) {
        std::cout << std::left << std::setw(15) << pavardes[i]
                  << std::setw(15) << vardai[i];
        if(mode == 1 || mode == 3) std::cout << std::right << std::setw(16) << galVid[i];
        if(mode == 2 || mode == 3) std::cout << std::right << std::setw(18) << galMed[i];
        std::cout << "\n";
    }
}
    
    
int main(int argc, char** argv){
  int mode = 3;
  std::cout << "Pasirinkite rezultata: 1-Vid. 2-Med. 3-Abu = "
  if(!(std::cin >> mode) || mode < 1 || mode > 3) mode = 3;
  std::string dump; std::getline(std::cin, dump);
  std::vector<std::string> vardai, pavardes;
  std::vector<double> galut, galutMed;
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
          galutMed.push_back(0.4 * med(marks) + 0.6*egz);
      }     
  } else {
      int m; std::cout << "Kiek studentu? ";
      if(!(std::cin>>m) || m<= 0) return 0;
      std::getline(std::cin, dump);

      vardai.resize(m);pavardes.resize(m);galut.resize(m);galutMed.resize(m);
      for(int i=0; i<m; ++i) {
         std::cout << "Vardas Pavarde: ";
         std::cin >> vardai[i] >> pavardes[i];
         std::getline(std::cin, dump);

         std::cout << "Iveskite visus ND balus vienoje eiluteje ";
         std::string ndLine; std::getLine(std::cin, ndLine);
         std::istringstream nds(ndLine);
         std::vector<int> nd; int v, while(nds >> v) nd.push_back(v);

         std::cout << "Egzamino balas: ";
         int egz; std::cin >> egz;
         std::getline(std::cin, dump);
         
         galut[i] = 0.4 * avg(nd) + 0.6 *egz;
         galutMed[i] = 0.4 * med(nd) + 0.6 *egz;
      }
  }
  std::cout << std::left << std::setw(15) << "Pavarde"
            << std::setw(15) << "Vardas"
  if(mode == 1 || mode == 3) std::cout << std::right << std::setw(16) << "Galutinis(Vid)";
  if(mode == 2 || mode == 3) std::cout << std::right << std::setw(18) << "Galutinis(Med)";
  std::cout << "\n";

  int bruksniai = (mode == 3) ? 62 : 46;
  std::cout << std::string(bruksniai, '-')
            << std::fixed << std::setprecision(2);
  for(size_t i=0; i<galut.size(); ++i)
      std::cout << std::left << std::setw(15) << pavardes[i]
                << std::setw(15) << vardai[i]
      if(mode == 1 || mode == 3) std::cout << std::right << std::setw(16) << galut[i];
      if(mode == 2 || mode == 3) std::cout << std::right << std::setw(18) << galutMed[i];
      std::cout << "\n";
   }
}


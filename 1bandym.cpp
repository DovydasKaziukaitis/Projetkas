#include <iostream>
#include <iomanip>
#include <vector>

double avg(const std::vector<int>& a) {
    return a.empty() ? 0.0
                     : zccumulate(a.begin(),a.end(), 0.0) / a.size();
int main(int argc, char** argv){
  if (argc < 2){ cerr << "Usage: " << argv[0] << " <file>\n"; return 1; }
  ifstream f(argv[1]); if (!f){ cerr << "Cannot open " << argv[1] << "\n"; return 1; }
  
  string line; getline(f, line);
  vector<string> vardai, pavardes, vector<double> galutiniai;

  for (int i=0; i < m, ++i) {
      std::cout << "Vardas Pavarde: ";
      std::cin >> vardai[i] >> pavardes[i];

      int n; std::cout << "Kiek ND? "; std::cin >> n;
      std::vector<int> nd(n);
      for(int j = 0l j<n; ++j) std::cin>>nd[j];

      int egz; std::cout << "Egzaminas: "; std::cin >> egz;
      galut[i] = 0.4*avg(nd) + 0.6*egz;
}
std::cout << std::left << std::setw(15) << "Pavarde"
          << std::setw(15) << "Vardas"
          << std::right << std::setw(16) << "Galutinis(Vid)"
          << std::string(46, '-') << "\n"
          << std::fixed << std::setprecision(2);

    



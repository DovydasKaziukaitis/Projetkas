#include <iostream>
#include <iomanip>
#include <vector>

double avg(const std::vector<int>& a) {
    return a.empty() ? 0.0
                     : (double)std::accumulate(a.begin(),a.end(),0) / a.size();
int main(){
  int m; std::cout <<"Irasykite kiek norite studentu ivesti: "; if (!(std::cin >> m)) return 0;
  std::vector<std::string> vardai(m),pavardes(m);
  std::vector<double> galut(m);

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

    



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


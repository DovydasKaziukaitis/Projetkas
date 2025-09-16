#include <iostream>
#include <iomanip>
#include <vector>

int main(){
  int m;
  std::cout <<"Irasykite kiek norite studentu ivesti: ";
  if (!(std::cin >> m || m<= 0) {
      std::cerr <<"neteisingas skaicius";
      return 1;
  }

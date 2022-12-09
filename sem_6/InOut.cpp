#include "euro_house.hpp"
#include "house.hpp"

int main() {
  House semerka("Dorm N7", "Pervomayskaya 30k7", 5, 1);
  EuroHouse trinashka("Dorm N13", "Lichchevskaya 2", 11, 2, 5, 5);
  std::string file_name;
  std::cin >> file_name;
  semerka.FOut(file_name);
  semerka.FIn(file_name);
}
#include "euro_house.hpp"
#include "house.hpp"

int main() {
  House semerka("Dorm N7", "Pervomayskaya 30k7", 5, 1);
  EuroHouse trinashka("Dorm N13", "Lichchevskaya 2", 11, 2, 5, 5);

  std::cout << "semerka's name\t" << semerka.GetName() << '\n';
  std::cout << "trinashka's name\t" << trinashka.GetName() << '\n';
  std::cout << "semerka's adr\t" << semerka.GetAddress() << '\n';
  std::cout << "trinashka's adr\t" << trinashka.GetAddress() << '\n';
  std::cout << "semerka's floors\t" << semerka.GetFloors() << '\n';
  std::cout << "trinashka's floors\t" << trinashka.GetFloors() << '\n';
  std::cout << "semerka's porchs\t" << semerka.GetPorchs() << '\n';
  std::cout << "trinashka's porchs\t" << trinashka.GetPorchs() << '\n';
  std::cout << "\ttrinashka's therm efficiency\t" << trinashka.GetTherm()
            << '\n';
  std::cout << "\ttrinashka's electrical efficiency\t"
            << trinashka.GetElectric() << '\n';
}
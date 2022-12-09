#include "euro_house.hpp"
#include "house.hpp"

int main() {
  std::string home_name;
  std::string euro_name;
  std::string home_adr;
  std::string euro_adr;
  size_t home_floors;
  size_t euro_floors;
  size_t home_porks;
  size_t euro_porks;
  size_t euro_therm;
  size_t euro_electric;

  std::cout << "home_name:\t";
  std::cin >> home_name;
  std::cout << "\neuro_name:\t";
  std::cin >> euro_name;
  std::cout << "\nhome_adr:\t";
  std::cin >> home_adr;
  std::cout << "\neuro_adr:\t";
  std::cin >> euro_adr;
  std::cout << "\nhome_floors:\t";
  std::cin >> home_floors;
  std::cout << "\neuro_floors:\t";
  std::cin >> euro_floors;
  std::cout << "\nhome_porks:\t";
  std::cin >> home_porks;
  std::cout << "\neuro_porks:\t";
  std::cin >> euro_porks;
  std::cout << "\n\teuro_therm:\t";
  std::cin >> euro_therm;
  std::cout << "\n\teuro_electric:\t";
  std::cin >> euro_electric;
  
  House home(home_name, home_adr, home_floors, home_porks);
  EuroHouse euro(euro_name, euro_adr, euro_floors, euro_porks, euro_therm, euro_electric);

  std::cout << home.GetName() << '\n';
  std::cout << home.GetAddress() << '\n';
  std::cout << home.GetFloors() << '\n';
  std::cout << home.GetPorchs() << '\n';

  std::cout << euro.GetName() << '\n';
  std::cout << euro.GetAddress() << '\n';
  std::cout << euro.GetFloors() << '\n';
  std::cout << euro.GetPorchs() << '\n';
  std::cout << euro.GetTherm() << '\n';
  std::cout << euro.GetElectric() << '\n';
}
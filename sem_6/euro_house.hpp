#include "house.hpp"

class EuroHouse : public House {
 public:
  EuroHouse(std::string name, std::string adr, size_t floors, size_t porchs,
            size_t therm, size_t electric)
      : House(name, adr, floors, porchs),
        therm_eff(therm),
        electrical_eff(electric) {}

  ~EuroHouse() { std::cout << "Тут был деструктор!!! \n"; }

  size_t GetTherm() { return therm_eff; }

  size_t GetElectric() { return electrical_eff; }

  void SetTherm(size_t new_therm) { therm_eff = new_therm; }

  void SetElectric(size_t new_electric) { electrical_eff = new_electric; }

  void FOut(std::string file_name = "output.txt") {
    std::ofstream file;
    file.open(file_name);
    file << name << '\n';
    file << address << '\n';
    file << floors << '\n';
    file << porchs << '\n';
    file << therm_eff << '\n';
    file << electrical_eff << '\n';
    file << "eof" << '\n';
    file.close();
    std::cout << "Объект записан в файл\n";
  }

 private:
  size_t therm_eff;
  size_t electrical_eff;
};
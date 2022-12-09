#pragma once

#include <fstream>
#include <iostream>
#include <string>

class House {
 public:
  House(std::string name, std::string adr, size_t floors, size_t porchs)
      : name(name), address(adr), floors(floors), porchs(porchs) {}

  ~House() { std::cout << "Тут был деструктор! \n"; }

  std::string GetName() { return name; }

  std::string GetAddress() { return address; }

  size_t GetFloors() { return floors; }

  size_t GetPorchs() { return porchs; }

  void SetName(std::string new_name) { name = new_name; }

  void SetAddress(std::string new_address) { address = new_address; }

  void SetFloors(size_t new_floors) { floors = new_floors; }

  void SetPorchs(size_t new_porchs) { porchs = new_porchs; }

  void FOut(std::string file_name = "output.txt") {
    std::ofstream file;
    file.open(file_name);
    file << name << '\n';
    file << address << '\n';
    file << floors << '\n';
    file << porchs << '\n';
    file << "eof" << '\n'; // костыль на случай если мы захотим записывать несколько объектов в одном файле
    file.close();
    std::cout << "Объект записан в файл\n";
  }

  void FIn(std::string file_name = "output.txt") {
    std::string str;
    std::ifstream file(file_name);
    if (file.is_open()) {
      while (std::getline(file, str) && str != "eof") {
        std::cout << str << '\n';
      }
      file.close();
      std::cout << "Файл прочитан\n";
    } else {
      std::cout << "Файл не открыть!\n";
    }
  }

 protected:
  std::string name;
  std::string address;
  size_t floors;
  size_t porchs;
};

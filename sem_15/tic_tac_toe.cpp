#include <iostream>
#include <optional>

class TicTacToe {
 public:
  TicTacToe(const size_t size) : kSize(size) {
    storage_ = new int*[kSize];
    for (size_t i = 0; i < kSize; ++i) {
      storage_[i] = new int[kSize];
      for (size_t j = 0; j < kSize; ++j) {
        storage_[i][j] = i + kSize * j + 1;
      }
    }
  }

  ~TicTacToe() {
    for (size_t i = 0; i < kSize; ++i) {
      delete[] storage_[i];
    }
    delete[] storage_;
  }

  bool TurnX(size_t location) {
    size_t i = (location - 1) % kSize;
    size_t j = (location - 1) / kSize;
    if (storage_[i][j] == -1 || storage_[i][j] == -2) {
      std::cout << "This cell has been chosen!!\n";
      return true;
    }
    storage_[i][j] = -1;
    ++current_;
    return false;
  }

  bool TurnO(size_t location) {
    size_t i = (location - 1) % kSize;
    size_t j = (location - 1) / kSize;
    if (storage_[i][j] == -1 || storage_[i][j] == -2) {
      std::cout << "This cell has been chosen!!\n";
      return true;
    }
    storage_[i][j] = -2;
    ++current_;
    return false;
  }

  std::optional<int> Check() {
    bool is_winner_1 = true;
    bool is_winner_2 = true;
    for (size_t i = 0; i < kSize; ++i) {
      is_winner_1 = true;
      is_winner_2 = true;

      for (size_t j = 0; j < kSize - 1; ++j) {
        is_winner_1 = is_winner_1 && (storage_[i][j] == storage_[i][j + 1]);
        is_winner_2 = is_winner_2 && (storage_[j][i] == storage_[j + 1][i]);
      }
      if (is_winner_1) {
        return storage_[i][0];
      }
      if (is_winner_2) {
        return storage_[0][i];
      }
    }
    is_winner_1 = true;
    is_winner_2 = true;
    for (size_t i = 0; i < kSize - 1; ++i) {
      is_winner_1 = is_winner_1 && (storage_[i][i] == storage_[i + 1][i + 1]);
      is_winner_2 = is_winner_2 && (storage_[i][kSize - 1 - i] ==
                                    storage_[i + 1][kSize - 2 - i]);
    }
    if (is_winner_1) {
      return storage_[0][0];
    }
    if (is_winner_2) {
      return storage_[0][kSize - 1];
    }
    return {};
  }

  void Print() {
    for (size_t i = 0; i < kSize; ++i) {
      for (size_t j = 0; j < kSize; ++j) {
        if (storage_[i][j] == -1) {
          std::cout << 'X' << "  ";
        } else if (storage_[i][j] == -2) {
          std::cout << 'O' << "  ";
        } else {
          std::cout << storage_[i][j] << "  ";
        }
      }
      std::cout << '\n' << '\n';
    }
  }

  size_t GetCurrent() { return current_; }

  size_t GetSize() { return kSize; }

 private:
  const size_t kSize;
  size_t current_ = 0;
  int** storage_;
};

int main() {
  size_t size;

  std::cout << "Enter size:\t";
  std::cin >> size;

  TicTacToe game(size);

  size_t location;

  std::optional<int> res = {};

  game.Print();

  while (game.GetCurrent() < game.GetSize() * game.GetSize()) {
    do {
      std::cout << "First player's turn:\t";
      std::cin >> location;
    } while (game.TurnX(location));

    game.Print();

    res = game.Check();

    if (res.has_value()) {
      if (res == -1) {
        std::cout << "First player has won!\n";
      } else if (res == -2) {
        std::cout << "Second player has won!\n";
      } else {
        std::cout << "Error 'res' \n";
      }
      break;
    }

    do {
      std::cout << "Second player's turn:\t";
      std::cin >> location;
    } while (game.TurnO(location));

    game.Print();

    res = game.Check();

    if (res.has_value()) {
      if (res == -1) {
        std::cout << "First player has won!\n";
      } else if (res == -2) {
        std::cout << "Second player has won!\n";
      } else {
        std::cout << "Error 'res' \n";
      }
      break;
    }
  }
}
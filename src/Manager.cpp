#include "google_dino_ai/Manager.hpp"

#include <algorithm>
#include <stdexcept>

#include "google_dino_ai/solvers/RNA.hpp"

using namespace google_dino_ai;

class ManagerPrivate {

public:
  static ManagerPrivate& instance()
  {
    static ManagerPrivate singleton;
    return singleton;
  }

  std::vector<Dinosaur>& Dinosaurs()
  {
    return this->dinosaurs;
  }

  Dinosaur& BestDino() {
    return this->dinosaurs[best_dino];
  }

  void ChangeBestDino(size_t index) {
    if (index <= this->dinosaurs.size()) {
      this->best_dino = index;
    } else {
      throw std::out_of_range("");
    }
  }

private:
  ManagerPrivate() = default;

  std::vector<Dinosaur> dinosaurs;
  size_t best_dino;
};

namespace manager {
std::vector<Dinosaur>& getAllDinosaurs()
{
  return ManagerPrivate::instance().Dinosaurs();
}

template <>
Span<Dinosaur> getDinosaurs<RNA>()
{
  auto& dinosaurs = ManagerPrivate::instance().Dinosaurs();
  
  auto stop = 
    std::partition_point(begin(dinosaurs), end(dinosaurs), [](const auto& dino){
      auto result = dynamic_cast<RNA*>(dino.solver.get());
      return static_cast<bool>(result);
    });

  size_t size = std::distance(begin(dinosaurs), stop);

  return Span<Dinosaur>(begin(dinosaurs), size);
}

Dinosaur& getBestDino() {
  return ManagerPrivate::instance().BestDino();
}

void changeBestDino(size_t index) {
  ManagerPrivate::instance().ChangeBestDino(index);
}


}  // manager


template <> Span<Dinosaur> manager::getDinosaurs<RNA>();

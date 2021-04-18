#ifndef GOOGLE_DINO_AI_GOOGLE_DINO_AI_MANAGER_H
#define GOOGLE_DINO_AI_GOOGLE_DINO_AI_MANAGER_H

#include <vector>

#include "google_dino_ai/Definicoes.h"
#include "google_dino_ai/Tipos.h"

class Manager {

public:
  static Manager& instance()
  {
    static Manager singleton;
    return singleton;
  }

  std::vector<Dinossauro>& getDinosaurs()
  {
    return this->Dinossauros;
  }

private:
  Manager() = default;

  std::vector<Dinossauro> Dinossauros = std::vector<Dinossauro>(POPULACAO_TAMANHO);
};

namespace manager {
  std::vector<Dinossauro>& getDinosaurs()
  {
    return Manager::instance().getDinosaurs();
  }
}  // manager

#endif  // GOOGLE_DINO_AI_GOOGLE_DINO_AI_MANAGER_H

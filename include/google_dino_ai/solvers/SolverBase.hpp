#ifndef GOOGLE_DINO_AI_SOLVERS_SOLVER_BASE_HPP_
#define GOOGLE_DINO_AI_SOLVERS_SOLVER_BASE_HPP_

#include <array>
#include <memory>

#include "google_dino_ai/tipos/RedeNeural.hpp"

namespace google_dino_ai {

class SolverBase {
public:
  
  virtual std::array<double, 3> process(const std::array<double, 6>& input) = 0;
  
  virtual ~SolverBase() = default;
};

using SolverBasePtr = std::unique_ptr<SolverBase>;

}  // namespace google_dino_ai
#endif  // GOOGLE_DINO_AI_SOLVERS_SOLVER_BASE_HPP_

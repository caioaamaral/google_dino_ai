#ifndef GOOGLE_DINO_AI_SOLVERS_RNA_HPP_
#define GOOGLE_DINO_AI_SOLVERS_RNA_HPP_

#include <array>
#include <vector>

#include "google_dino_ai/tipos/RedeNeural.hpp"
#include "google_dino_ai/solvers/SolverBase.hpp"

namespace google_dino_ai {

class RNA : public SolverBase {
public:

  RNA();
  std::array<double, 3> process(const std::array<double, 6>& input) override;
  void reset(const std::vector<double>* weights);

  int TamanhoDNA;
  std::vector<double> DNA;
  // double Fitness;
  RedeNeural* network;
};

using RNAPtr = std::unique_ptr<RNA>;


}  // namespace google_dino_ai
#endif  // GOOGLE_DINO_AI_SOLVERS_RNA_HPP_

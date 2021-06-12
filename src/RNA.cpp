#include "google_dino_ai/solvers/RNA.hpp"

#include <algorithm>

#include "google_dino_ai/Definicoes.h"
#include "google_dino_ai/RedeNeural.h"

namespace google_dino_ai {

double getRandomValue()
{
    return (rand()%20001/10.0) - 1000.0;
    //return (rand()%201/10.0) - 10.0;
    //return (rand()%2001/1000.0) - 1.0;
    //return (rand()%2001/10000.0) - 0.1;

    //return rand()%3 - 1;
}

void fillDna(std::vector<double>& dna, const std::vector<double>* weights = nullptr)
{
  if (!weights) {
    std::generate(begin(dna), end(dna), getRandomValue);
  } else {
    std::generate(begin(dna), end(dna), [i = 0, &weights]() mutable { return weights->at(i++); });
  }
}

void initializeNeuralNetwork(RedeNeural* network, const std::vector<double>* weights,
                                            std::vector<double>& dna_out)
{
  fillDna(dna_out, weights);
  RNA_CopiarVetorParaCamadas(network, &dna_out.front());
}

RNA::RNA() {
  this->network = RNA_CriarRedeNeural(DINO_BRAIN_QTD_LAYERS, DINO_BRAIN_QTD_INPUT,
                                      DINO_BRAIN_QTD_HIDE, DINO_BRAIN_QTD_OUTPUT);
  
  auto tamanho = RNA_QuantidadePesos(this->network);
  this->DNA.resize(tamanho);

  initializeNeuralNetwork(this->network, nullptr, this->DNA);
}

std::array<double, 3> RNA::process(const std::array<double, 6>& input)
{ 
  std::array<double, 3> output{};
  RNA_CopiarParaEntrada(this->network, input.begin());     /// Enviando informações para a rede neural
  RNA_CalcularSaida(this->network);                        /// Calculando a decisão da rede
  RNA_CopiarDaSaida(this->network, output.begin());        /// Extraindo a decisão para vetor ''saida''

  return output;
}

void RNA::reset(const std::vector<double>* weights) {
  initializeNeuralNetwork(this->network, weights, this->DNA);
}

}  // namespace google_dino_ai

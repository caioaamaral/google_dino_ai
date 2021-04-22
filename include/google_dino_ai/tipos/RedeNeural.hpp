/*
 * Copyright (c) 2020, SENAI CIMATEC
 */

#ifndef GOOGLE_DINO_AI_REDENEURAL_HPP_
#define GOOGLE_DINO_AI_REDENEURAL_HPP_

namespace google_dino_ai {

struct Neuronio
{
  double* Peso;
  double  Erro;
  double  Saida;
  int QuantidadeLigacoes;
};

struct Camada
{
  Neuronio* Neuronios;
  int QuantidadeNeuronios;
};

struct RedeNeural
{
  Camada  CamadaEntrada;
  Camada* CamadaEscondida;
  Camada  CamadaSaida;
  int QuantidadeEscondidas;
};

}  // namespace google_dino_ai
#endif  // GOOGLE_DINO_AI_REDENEURAL_HPP_

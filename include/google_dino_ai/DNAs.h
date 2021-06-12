#include "google_dino_ai/Definicoes.h"
#include "google_dino_ai/FuncoesAuxiliares.h"
#include "google_dino_ai/Manager.hpp"

    double* DNADaVez[POPULACAO_TAMANHO];

    double MediaFitnessPopulacao[LARG_GRAFICO];
    double MediaFitnessFilhos[LARG_GRAFICO];
    double BestFitnessPopulacao[LARG_GRAFICO];

    int GeracaoCompleta = 0;

double BestFitnessGeracao()
{
    double Maior = 0;
    auto Dinossauros = manager::getDinosaurs<RNA>();
    for(const auto& Dinosaur : Dinossauros)
    {
      if(Dinosaur.Fitness > Maior)
      {
          Maior = Dinosaur.Fitness;
      }
    }
    return Maior;
}

double MediaFitnessGeracao()
{
    double Media = 0;
    auto Dinossauros = manager::getDinosaurs<RNA>();
    for(const auto& Dinosaur : Dinossauros)
    {
        Media += Dinosaur.Fitness;
    }
    Media = Media/(double)POPULACAO_TAMANHO;
    return Media;
}

double BestFitnessEver()
{
    double Maior = 0;
    for(int i=0; i<GeracaoCompleta; i++)
    {
        if(BestFitnessPopulacao[i] > Maior)
        {
            Maior = BestFitnessPopulacao[i];
        }
    }
    return Maior;
}


void InicializarDNA()
{
    auto Dinossauros = manager::getDinosaurs<RNA>();
    int TamanhoDNA = dynamic_cast<RNA*>(Dinossauros[0].solver.get())->DNA.size();

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        DNADaVez[i] = (double*)malloc(TamanhoDNA*sizeof(double));
        for(int j=0; j<TamanhoDNA; j++)
        {
            DNADaVez[i][j] = getRandomValue();
        }
    }
}

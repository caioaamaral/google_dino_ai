#ifndef GOOGLE_DINO_AI_GOOGLE_DINO_AI_TIPOS_H
#define GOOGLE_DINO_AI_GOOGLE_DINO_AI_TIPOS_H

#include "google_dino_ai/Definicoes.h"
#include "google_dino_ai/tipos/Sprites.hpp"
#include "google_dino_ai/tipos/RedeNeural.hpp"

using namespace google_dino_ai;

struct Obstaculo
{
    double X, Y;
    int Tipo;
    Sprite* sprite[2];
    int TimerFrames;
    int FrameAtual;
};

struct Chao
{
    double X, Y;
    Sprite sprite;
};

struct Montanha
{
    double X[2], Y[2];
    Sprite sprite[2];
};
struct Nuvem
{
    double X, Y;
    Sprite sprite;
};

struct Grafico
{
    double MediaFitness[LARG_GRAFICO];
    double MelhorFitness[LARG_GRAFICO];
};

#endif  // GOOGLE_DINO_AI_GOOGLE_DINO_AI_TIPOS_H

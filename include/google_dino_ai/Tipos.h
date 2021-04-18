#ifndef GOOGLE_DINO_AI_GOOGLE_DINO_AI_TIPOS_H
#define GOOGLE_DINO_AI_GOOGLE_DINO_AI_TIPOS_H

#define LARG_GRAFICO            600
#define CHAO_QUANTIDADE         30
#define MONTANHA_QUANTIDADE     3
#define NUVEM_QUANTIDADE        15

#define QTD_SPRITE_CACTUS       6
#define MAX_OBSTACULOS          7

enum States : int {
  Standing = 0,
  Lying,
  Jumping,
  Died,
  Flying
};

struct Dinossauro
{
    double X, Y;
    double VelocidadeY;
    int Frame;
    int SpriteAtual;
    States Estado;
    Sprite sprite[10];
    int TimerFrame;
    int ResetarFitness;

    int FrameAviao;
    int TimerFrameAviao;
    double AviaoDeslocamento;
    double AviaoCooldown;

    int TamanhoDNA;
    double* DNA;
    double Fitness;

    RedeNeural* Cerebro;
};

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

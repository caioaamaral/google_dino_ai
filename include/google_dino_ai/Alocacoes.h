#include "google_dino_ai/Manager.hpp"


void AlocarDinossauro(int ControladorCor)
{
    auto& Dinossauros = manager::getAllDinosaurs();

    for(int i = 0; i < 10; i++)
    {
        Dinossauros[QuantidadeDinossauros].sprite[i] = makeDinoSprite(i, Cores[ControladorCor]);
    }

    Dinossauros[QuantidadeDinossauros].TimerFrame       = pig::CriarTimer();
    Dinossauros[QuantidadeDinossauros].TimerFrameAviao  = pig::CriarTimer();
    Dinossauros[QuantidadeDinossauros].ResetarFitness   = 1;
    Dinossauros[QuantidadeDinossauros].solver = std::make_unique<RNA>();

    InicializarDinossauro(QuantidadeDinossauros, NULL, 0, 0);

    QuantidadeDinossauros++;
}


void AlocarDinossauros()
{
    auto& Dinossauros = manager::getAllDinosaurs();
    Dinossauros.resize(POPULACAO_TAMANHO);

    int controlador_cor = 0;

    for(int i = 0; i < Dinossauros.size(); i++)
    {
        AlocarDinossauro(controlador_cor);
        controlador_cor = (controlador_cor+1)%8;
    }
}


void AlocarObstaculos()
{
    for(int i=0; i<MAX_OBSTACULOS; i++)
    {
        obstaculo[i].TimerFrames = pig::CriarTimer();
    }
}

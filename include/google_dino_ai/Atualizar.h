#include <pig/PIG_Timers.h>

#include "google_dino_ai/tipos/Dinosaur.hpp"
#include "google_dino_ai/Manager.hpp"

void AtualizarMelhorDinossauro()
{
    auto& Dinossauros = manager::getAllDinosaurs();
    if(MODO_JOGO == 1)
    {
        manager::changeBestDino(0);
    }

    if(manager::getBestDino().Estado == States::Died)
    {
        for(int i=0; i<POPULACAO_TAMANHO; i++)
        {
            if(Dinossauros[i].Estado != States::Died)
            {
                manager::changeBestDino(i);
                break;
            }
        }
    }
}

void AtualizarFramePassaro()
{
    for(int i=0; i<MAX_OBSTACULOS; i++)
    {
        if(pig::TempoDecorrido(obstaculo[i].TimerFrames) >= 0.2)
        {
            obstaculo[i].FrameAtual = (obstaculo[i].FrameAtual + 1)%2;
            pig::ReiniciarTimer(obstaculo[i].TimerFrames);
        }
    }
}

void AtualizarFrameDinossauro()
{
    auto& Dinossauros = manager::getAllDinosaurs();
    for(int i = 0; i < Dinossauros.size(); i++)
    {
        if(pig::TempoDecorrido(Dinossauros[i].TimerFrame) >= 0.1)
        {
            Dinossauros[i].Frame = (Dinossauros[i].Frame + 1)%2;
            pig::ReiniciarTimer(Dinossauros[i].TimerFrame);
        }
    }
}

void AtualizarFrameAviao()
{
    auto& Dinossauros = manager::getAllDinosaurs();
    for(int i = 0; i < Dinossauros.size(); i++)
    {
        if(pig::TempoDecorrido(Dinossauros[i].TimerFrameAviao) >= 0.03)
        {
            Dinossauros[i].FrameAviao = (Dinossauros[i].FrameAviao + 1)%2;
            pig::ReiniciarTimer(Dinossauros[i].TimerFrameAviao);
        }
    }
}

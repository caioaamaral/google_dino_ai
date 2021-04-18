#include <pig/PIG_Timers.h>

void AtualizarMelhorDinossauro()
{
    auto& Dinossauros = manager::getDinosaurs();
    if(MODO_JOGO == 1)
    {
        MelhorDinossauro = &Dinossauros[0];
    }

    if(MelhorDinossauro->Estado == 3)
    {
        for(int i=0; i<POPULACAO_TAMANHO; i++)
        {
            if(Dinossauros[i].Estado != 3)
            {
                MelhorDinossauro = &Dinossauros[i];
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
    auto& Dinossauros = manager::getDinosaurs();
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
    auto& Dinossauros = manager::getDinosaurs();
    for(int i = 0; i < Dinossauros.size(); i++)
    {
        if(pig::TempoDecorrido(Dinossauros[i].TimerFrameAviao) >= 0.03)
        {
            Dinossauros[i].FrameAviao = (Dinossauros[i].FrameAviao + 1)%2;
            pig::ReiniciarTimer(Dinossauros[i].TimerFrameAviao);
        }
    }
}

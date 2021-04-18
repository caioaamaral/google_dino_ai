#include "google_dino_ai/Manager.h"


void AlocarDinossauro(int ControladorCor)
{
    int tamanho;
    auto& Dinossauros = manager::getDinosaurs();

    for(int i = 0; i < 10; i++)
    {
        Dinossauros[QuantidadeDinossauros].sprite[i] = makeDinoSprite(i, Cores[ControladorCor]);
    }

    Dinossauros[QuantidadeDinossauros].TimerFrame       = pig::CriarTimer();
    Dinossauros[QuantidadeDinossauros].TimerFrameAviao  = pig::CriarTimer();
    Dinossauros[QuantidadeDinossauros].ResetarFitness   = 1;

    Dinossauros[QuantidadeDinossauros].Cerebro = RNA_CriarRedeNeural(DINO_BRAIN_QTD_LAYERS,
                                                                     DINO_BRAIN_QTD_INPUT,
                                                                     DINO_BRAIN_QTD_HIDE,
                                                                     DINO_BRAIN_QTD_OUTPUT);

    tamanho = RNA_QuantidadePesos(Dinossauros[QuantidadeDinossauros].Cerebro);

    Dinossauros[QuantidadeDinossauros].TamanhoDNA = tamanho;
    Dinossauros[QuantidadeDinossauros].DNA = (double*)malloc(tamanho*sizeof(double));

    InicializarDinossauro(QuantidadeDinossauros, NULL, 0, 0);

    QuantidadeDinossauros++;
}


void AlocarDinossauros()
{
    auto& Dinossauros = manager::getDinosaurs();
    Dinossauros.reserve(POPULACAO_TAMANHO);
    Dinossauros.assign(POPULACAO_TAMANHO, Dinossauro());

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

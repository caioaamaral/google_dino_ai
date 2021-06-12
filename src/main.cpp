#include <thread>
#include <chrono>

#include <pig/Bibliotecas_Basicas.h>
#include <pig/pig.h>                        ///   Biblioteca Grafica
#include "Sprites.h"                    ///   Todos os códigos sobre sprite
#include "RedeNeural.h"                 ///   Código da rede neural
#include "Tipos.h"                      ///   Definições de structs
#include "Variaveis.h"                  ///   Variaveis globais
#include "FuncoesAuxiliares.h"
#include "DNAs.h"
#include "Desenhar.h"
#include "GeradorObstaculos.h"
#include "Inicializar.h"
#include "Alocacoes.h"
#include "Colisao.h"
#include "Movimentar.h"
#include "Atualizar.h"
#include "InputsRedeNeural.h"   /// Funções que captam a informação para entregar para a rede neural


void UpdateStates(); 
/*
 * Função chamada pela Thread secundária responsavel por
 * atualizar os estados de cada objeto.
*/


void AplicarGravidade()
{
    auto& Dinossauros = manager::getAllDinosaurs();
    for(int i = 0; i < Dinossauros.size(); i++)
    {
        if(Dinossauros[i].Y > 15)
        {
            if(Dinossauros[i].Estado != States::Flying)
            {
                Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY - (0.08);
            }
            else
            {
                if(Dinossauros[i].VelocidadeY <= 0)
                {
                    Dinossauros[i].VelocidadeY = 0;
                }
                else
                {
                    Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY - (0.08);
                }
            }

            Dinossauros[i].Y = Dinossauros[i].Y + Dinossauros[i].VelocidadeY;
        }
        else
        {
            Dinossauros[i].VelocidadeY = 0;
            Dinossauros[i].Y = 15;
            if(Dinossauros[i].Estado == States::Jumping)
                Dinossauros[i].Estado = States::Standing;
        }
    }
}

void ControlarEstadoDinossauros()  /// Função responsavel por calcular a decisão da rede neural e aplicar no dinossauro (ou seja, é a função que faz ele pular, abaixar ou usar o aviao)
{
    bool Abaixar = false, Pular = false, Aviao = false;
    std::array<double, 3> Saida{};
    std::array<double, 6> Entrada{};
    auto& Dinossauros = manager::getAllDinosaurs();
    for(int i = 0; i < QuantidadeDinossauros; i++)
    {
        if(Dinossauros[i].Estado != States::Died)
        {
            Entrada[0] = DistanciaProximoObstaculo(Dinossauros[i].X);            
            Entrada[1] = LarguraProximoObstaculo(Dinossauros[i].X);              
            Entrada[2] = AlturaProximoObstaculo(Dinossauros[i].X);               
            Entrada[3] = ComprimentoProximoObstaculo(Dinossauros[i].X);
            Entrada[4] = fabs(VELOCIDADE);
            Entrada[5] = Dinossauros[i].Y;

            Saida = Dinossauros[i].solver->process(Entrada);

            if(Saida[0] == 0.0)
                Pular = false;
            else
                Pular = true;

            if(Saida[1] == 0.0)
                Abaixar = false;
            else
                Abaixar = true;

            if(Saida[2] == 0.0)
                Aviao = false;
            else
                Aviao = true;


            if(MODO_JOGO == 1 && i == 0)
            {
                Pular = false;
                Abaixar = false;
                Aviao = false;

                if(PIG_meuTeclado[TECLA_CIMA] == 1)
                {
                    Pular = true;
                }
                if(PIG_meuTeclado[TECLA_BAIXO] == 1)
                {
                    Abaixar = true;
                }
                if(PIG_meuTeclado[TECLA_BARRAESPACO] == 1)
                {
                    Aviao = true;
                }

                Saida[0] = Abaixar;
                Saida[1] = Pular;
                Saida[2] = Aviao;
            }

            if(DINO_BRAIN_QTD_OUTPUT == 2)
                Aviao = 0;

            if(Dinossauros[i].Estado != States::Flying)
            {
                if(Dinossauros[i].Estado != States::Jumping)
                {
                    Dinossauros[i].Estado = States::Standing;
                }
                if(Abaixar && Dinossauros[i].Estado != States::Jumping)
                {
                    Dinossauros[i].Estado = States::Lying;
                }
                if(Abaixar && Dinossauros[i].Estado == States::Jumping)
                {
                    if(Dinossauros[i].VelocidadeY > 0)
                        Dinossauros[i].VelocidadeY = 0;
                    Dinossauros[i].Y = Dinossauros[i].Y - 2;
                }
                if(Pular && Dinossauros[i].Estado != States::Jumping)
                {
                    Dinossauros[i].Estado = States::Jumping;
                    Dinossauros[i].Y = Dinossauros[i].Y + 1;

                    Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY + 4.0;
                }
                if(Aviao && Dinossauros[i].AviaoCooldown <= 0)
                {
                    Dinossauros[i].Estado = States::Flying;
                    Dinossauros[i].Y = Dinossauros[i].Y + 1;
                    if(Dinossauros[i].VelocidadeY <= 0.5 && Dinossauros[i].Y < 25)
                    {
                        Dinossauros[i].VelocidadeY = Dinossauros[i].VelocidadeY + 4.0;
                    }
                    Dinossauros[i].AviaoCooldown = 4000.0;
                }
            }
            else
            {
                if(Dinossauros[i].AviaoDeslocamento >= 820.0)
                {
                    Dinossauros[i].AviaoDeslocamento = 0;
                    Dinossauros[i].Estado = States::Jumping;
                }
                else
                {
                    Dinossauros[i].AviaoDeslocamento = Dinossauros[i].AviaoDeslocamento + fabs(VELOCIDADE);
                }
            }
            Dinossauros[i].AviaoCooldown = Dinossauros[i].AviaoCooldown - fabs(VELOCIDADE);


            if(Dinossauros[i].Estado == States::Standing)
            {
                Dinossauros[i].SpriteAtual = 0 + Dinossauros[i].Frame;
            }
            if(Dinossauros[i].Estado == States::Lying)
            {
                Dinossauros[i].SpriteAtual = 2 + Dinossauros[i].Frame;
            }
            if(Dinossauros[i].Estado == States::Jumping)
            {
                Dinossauros[i].SpriteAtual = 4 + Dinossauros[i].Frame;
            }
            if(Dinossauros[i].Estado == States::Died)
            {
                Dinossauros[i].SpriteAtual = 6 + Dinossauros[i].Frame;
            }
            if(Dinossauros[i].Estado == States::Flying)
            {
                Dinossauros[i].SpriteAtual = 8 + Dinossauros[i].Frame;
            }
        }
    }
}

void InicializarNovaPartida()
{
    GerarListaObstaculos();
    CarregarListaObstaculos();

    DistanciaAtual = 0;
    VELOCIDADE = -3;
    DinossaurosMortos = 0;

    InicializarObstaculos();
    auto Dinossauros = manager::getDinosaurs<RNA>();

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        auto rna_solver = static_cast<RNA*>(Dinossauros[i].solver.get());
        InicializarDinossauro(i, 300 + (rand()%200 - 100), 15);
    }
}

void EncerrarPartida()
{
    if(DistanciaAtual > DistanciaRecorde)
    {
        DistanciaRecorde = DistanciaAtual;
        SalvarRedeArquivo();
    }
}

void CarregarRede()
{
    FILE* f = fopen("rede","rb");

    auto* first_dino_solver =
      dynamic_cast<RNA*>(manager::getDinosaurs<RNA>()[0].solver.get());

    fread(&first_dino_solver->TamanhoDNA, 1, sizeof(int), f); // use ->DNA.size()
    fread(DNADaVez[0], first_dino_solver->TamanhoDNA, sizeof(double), f);
    fclose(f);
}

void ConfiguracoesIniciais()
{
    CriarJanela("Google Dinosaur", 0);
    std::cout << "JANELA CRIADA\n";

    InicializarSprites();

    InicializarChao();
    InicializarMontanhas();
    InicializarNuvens();

    AlocarDinossauros();
    AlocarObstaculos();
    CarregarListaObstaculos();
    InicializarGrafico();

    TimerGeral          = pig::CriarTimer();
    Fonte               = CriarFonteNormal(PIG_RESOURCES_PATH"/arial.ttf", 15, PRETO,      0, PRETO);
    FonteVermelha       = CriarFonteNormal(PIG_RESOURCES_PATH"/arial.ttf", 15, VERMELHO,   0, PRETO);
    FonteAzul           = CriarFonteNormal(PIG_RESOURCES_PATH"/arial.ttf", 15, AZUL,       0, PRETO);
    DistanciaRecorde    = 0;
    Geracao             = 0;

    InicializarDNA();
    std::cout << "STARTING APP\n\n"; 
    InicializarNovaPartida();
    std::cout << "STARTED\n\n"; 
    

}

void RandomMutations()
{
    static double RangeRandom =
      static_cast<RNA*>(manager::getDinosaurs<RNA>()[0].solver.get())->DNA.size();

    RNA* Vetor[POPULACAO_TAMANHO];
    const Dinosaur* Temp;

    if(Geracao < LARG_GRAFICO)
    {
        GeracaoCompleta = Geracao+1;
        BestFitnessPopulacao[Geracao] = BestFitnessGeracao();
        MediaFitnessPopulacao[Geracao] = MediaFitnessGeracao();
    }
    else
    {
        for(int i=0; i<LARG_GRAFICO-1; i++)
        {
            BestFitnessPopulacao[i] = BestFitnessPopulacao[i+1];
            MediaFitnessPopulacao[i] = MediaFitnessPopulacao[i+1];
        }
        BestFitnessPopulacao[GeracaoCompleta] = BestFitnessGeracao();
        MediaFitnessPopulacao[GeracaoCompleta] = MediaFitnessGeracao();
    }

    auto Dinossauros = manager::getDinosaurs<RNA>();
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Vetor[i] = static_cast<RNA*>(Dinossauros[i].solver.get());
    }

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        for(int j=0; j<POPULACAO_TAMANHO-1; j++)
        {
            if(Dinossauros[j].Fitness < Dinossauros[j+1].Fitness)
            {
                std::iter_swap(Dinossauros.begin()+j, Dinossauros.begin()+j+1);
            }
        }
    }

    int Step = 1;
    for(int i=0; i<Step; i++)  /// Clonando individuos
    {
        for(int j=Step+i; j<POPULACAO_TAMANHO; j+=Step)
        {
            for(int k=0; k<Vetor[j]->DNA.size(); k++)
            {
                Vetor[j]->DNA[k] = Vetor[i]->DNA[k];        /// individuo 'j' recebe dna do individuo 'i'
            }
        }
    }

    for(int j=Step; j<POPULACAO_TAMANHO; j++)  /// Aplicando random mutations
    {
        int tipo;
        int mutations = (rand()%(int)RangeRandom)+1;

        for(int k=0; k<mutations; k++)
        {
            tipo = rand()%3;

            int indice = rand()%Vetor[j]->DNA.size();
            switch(tipo)
            {
                case 0:
                {
                    Vetor[j]->DNA[indice] = getRandomValue();       /// Valor Aleatorio

                }   break;
                case 1:
                {
                    double number = (rand()%10001)/10000.0 + 0.5;
                    Vetor[j]->DNA[indice] *= number;   /// Multiplicação aleatoria

                }   break;
                case 2:
                {
                    double number = getRandomValue()/100.0;
                    Vetor[j]->DNA[indice] += number; /// Soma aleatoria

                }   break;
            }
        }
    }

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Dinossauros[i].ResetarFitness = 1;
    }

    printf("Range Random: %f\n", RangeRandom);
    RangeRandom = RangeRandom*0.99;
    if(RangeRandom < 20)
    {
        RangeRandom = 20;
    }

    Geracao++;
}

void VerificarFimDePartida()
{
    if(DinossaurosMortos == POPULACAO_TAMANHO)
    {
        EncerrarPartida();
        if(MODO_JOGO == 0)
        {
            RandomMutations();
        }
        InicializarNovaPartida();
    }
}

int main(int argc, char* args[])
{
    ConfiguracoesIniciais();

    std::thread secondary_thread(UpdateStates);

    while(PIG_JogoRodando == 1)
    {
        Desenhar();
        EncerrarDesenho();
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    secondary_thread.join();
    FinalizarJanela();

    return 0;
}

void UpdateStates()
{
    while(PIG_JogoRodando == 1)
    {
      AtualizarJanela();
      VerificarTeclas();
      if(pig::TempoDecorrido(TimerGeral) >= Periodo)
      {
        MovimentarChao();
        MovimentarMontanhas();
        MovimentarNuvem();
        MovimentarObstaculos();
        MovimentarDinossauros();
        AtualizarFramePassaro();
        AtualizarFrameDinossauro();
        AtualizarFrameAviao();
        AtualizarMelhorDinossauro();
        AplicarGravidade();
        AplicarColisao();
        ControlarEstadoDinossauros();
        if(fabs(VELOCIDADE) < 8)
        {
            VELOCIDADE = VELOCIDADE - 0.0005;
        }
        DistanciaAtual = DistanciaAtual + fabs(VELOCIDADE);
        if(DistanciaAtual > 1000000 && DistanciaAtual > DistanciaRecorde)
        {
            //SalvarRedeArquivo();
            DinossaurosMortos = POPULACAO_TAMANHO;
        }
        VerificarFimDePartida();
        pig::ReiniciarTimer(TimerGeral);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

#ifndef GOOGLE_DINO_AI_DINOSAUR_HPP_
#define GOOGLE_DINO_AI_DINOSAUR_HPP_

#include <array>

#include "google_dino_ai/solvers/SolverBase.hpp"
#include "google_dino_ai/solvers/RNA.hpp"
#include "google_dino_ai/tipos/Sprites.hpp"
#include "google_dino_ai/tipos/RedeNeural.hpp"

namespace google_dino_ai {

enum States : int {
  Standing = 0,
  Lying,
  Jumping,
  Died,
  Flying
};

struct Dinosaur {
  // Dinosaur() = default;

  // Dinosaur(SolverBasePtr&& solver) : solver(new RNA()) {
  //   // this->solver(new RNA());
  // }
  
  // Dinosaur(const Dinosaur& other) : solver(new RNA()) {

  // }

  // Dinosaur& operator=(Dinosaur&& other) {
  //   // this->solver = std::nove(std::make_unique<SolverBase>());
  //   // this->X = other.X;
  //   // this->Y = other.Y;
  //   // this->VelocidadeY = other.VelocidadeY;
  //   // this->Frame = other.Frame;
  //   // this->SpriteAtual = other.SpriteAtual;
  //   // this->Estado = other.Estado;
  //   // this->sprite = other.sprite;
  //   // this->TimerFrame = other.TimerFrame;
  //   // this->ResetarFitness = other.ResetarFitness;
  //   // this->FrameAviao = other.FrameAviao;
  //   // this->TimerFrameAviao = other.TimerFrameAviao;
  //   // this->AviaoDeslocamento = other.AviaoDeslocamento;
  //   // this->AviaoCooldown = other.AviaoCooldown;
  //   // this->DNA = other.DNA;
  //   // this->Fitness = other.Fitness;
  //   // this->Cerebro = other.Cerebro;
  //   return *this;
  // }

  // Dinosaur& operator=(const Dinosaur& other) {
  //   // this->solver = std::move(other.solver);
  //   // this->X = other.X;
  //   // this->Y = other.Y;
  //   // this->VelocidadeY = other.VelocidadeY;
  //   // this->Frame = other.Frame;
  //   // this->SpriteAtual = other.SpriteAtual;
  //   // this->Estado = other.Estado;
  //   // this->sprite = other.sprite;
  //   // this->TimerFrame = other.TimerFrame;
  //   // this->ResetarFitness = other.ResetarFitness;
  //   // this->FrameAviao = other.FrameAviao;
  //   // this->TimerFrameAviao = other.TimerFrameAviao;
  //   // this->AviaoDeslocamento = other.AviaoDeslocamento;
  //   // this->AviaoCooldown = other.AviaoCooldown;
  //   // this->DNA = other.DNA;
  //   // this->Fitness = other.Fitness;
  //   // this->Cerebro = other.Cerebro;
  //   return *this;
  // }

  // odometry
  double X, Y;
  double VelocidadeY;
  int Frame;
  int SpriteAtual;
  States Estado;

  // image
  std::array<Sprite, 10> sprite;

  // misc
  double Fitness;
  int ResetarFitness;
  int TimerFrame;
  int FrameAviao;
  int TimerFrameAviao;
  double AviaoDeslocamento;
  double AviaoCooldown;

  // solver
  SolverBasePtr solver;

  // neuralnetwork stuff
  // double* DNA;
  // double Fitness;
  // RedeNeural* Cerebro;
};

}  // namespace google_dino_ai
#endif  // GOOGLE_DINO_AI_DINOSAUR_HPP_

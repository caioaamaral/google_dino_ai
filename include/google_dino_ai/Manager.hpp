#ifndef GOOGLE_DINO_AI_GOOGLE_DINO_AI_MANAGER_HPP
#define GOOGLE_DINO_AI_GOOGLE_DINO_AI_MANAGER_HPP

#include <vector>

#include "google_dino_ai/tipos/Dinosaur.hpp"

// namespace google_dino_ai {
using namespace google_dino_ai;

template<typename T, typename Container = std::vector<T>>
class Span {
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  const iterator begin_;
  std::size_t len_;

public:
    Span(iterator it, std::size_t len) noexcept
        : begin_{it}, len_{len}
    {}

    const_reference operator[](size_t i) const noexcept {
        return *(this->begin_ + i);
    }

    reference operator[](size_t i) noexcept {
        return *(this->begin_ + i);
    }

    std::size_t size() const noexcept {
        return this->len_;
    }

    const_iterator begin() const noexcept {
        return this->begin_;
    }

    iterator begin() noexcept {
        return this->begin_;
    }

    iterator end() noexcept {
        return this->begin_ + this->len_;
    }

    const_iterator end() const noexcept {
        return this->begin_ + this->len_;
    }
};

namespace manager {
std::vector<Dinosaur>& getAllDinosaurs();

template <typename T>
Span<Dinosaur> getDinosaurs();

Dinosaur& getBestDino();

void changeBestDino(size_t index);

}  // namespace manager
// }  // namespace google_dino_ai

#endif  // GOOGLE_DINO_AI_GOOGLE_DINO_AI_MANAGER_HPP

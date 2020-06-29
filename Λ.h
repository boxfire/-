#pragma once

#include <type_traits>

constexpr decltype(auto) curry(auto&& λ) {
  return [λ{std::forward(λ)}](auto&&... α) constexpr {
    if constexpr(std::is_invocable_v<decltype(λ), decltype(α)...>) return λ(std::forward(α)...);
    else return curry([λ{std::forward(λ)}, ...α{std::forward(α)}](auto&&... β) constexpr -> std::invoke_result_t<decltype(λ), decltype(α)..., decltype(β)...> {
      return λ(std::forward(α)..., std::forward(β)...);
    });
  };
};


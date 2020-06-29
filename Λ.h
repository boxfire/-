#pragma once

#include <type_traits>

constexpr decltype(auto) curry(auto&& λ) {
  return [λ{std::move(λ)}](auto&&... α) constexpr {
    if constexpr(std::is_invocable_v<decltype(λ), decltype(α)...>) return λ(std::move(α)...);
    else return curry([λ{std::move(λ)}, ...α{std::move(α)}](auto&&... β) constexpr -> std::invoke_result_t<decltype(λ), decltype(α)..., decltype(β)...> {
      return λ(std::move(α)..., std::move(β)...);
    });
  };
};


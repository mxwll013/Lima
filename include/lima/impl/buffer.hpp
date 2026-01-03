// --------------------------------------------------------------------------------
// Echo Engine Project - Apache 2.0 License
// https://echoengine.org
// Module : Lima - Logging
// Copyright (c) 2025 Echo Engine Project contributors
// --------------------------------------------------------------------------------

#ifndef LM_IMPL_BUFFER_HPP
#define LM_IMPL_BUFFER_HPP

#include "sierra/primitives.hpp"

#include <array>

namespace lm::impl {

constexpr usize BUFFER_SIZE = 0X1000;

// Using a global format buffer to avoid dynamic and repeated allocation.
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
inline thread_local std::array<char, BUFFER_SIZE> fmt_buffer{};

} // namespace lm::impl

#endif // LM_IMPL_BUFFER_HPP

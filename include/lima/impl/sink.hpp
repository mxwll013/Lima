// --------------------------------------------------------------------------------
// Echo Engine Project - Apache 2.0 License
// https://echoengine.org
// Module : Lima - Logging
// Copyright (c) 2025 Echo Engine Project contributors
// --------------------------------------------------------------------------------

#ifndef LM_IMPL_SINK_HPP
#define LM_IMPL_SINK_HPP

#include "lima/impl/buffer.hpp"

#include "sierra/primitives.hpp"

#include <unistd.h>

namespace lm::impl {

constexpr i32 STDOUT_FD = STDOUT_FILENO;
constexpr i32 STDERR_FD = STDERR_FILENO;

inline void   writeFD(usize len, i32 dst) noexcept;

void          writeFD(usize len, i32 dst) noexcept {
    ::write(dst, fmt_buffer.data(), len);
}

} // namespace lm::impl

#endif // LM_IMPL_SINK_HPP

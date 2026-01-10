// --------------------------------------------------------------------------------
// Echo Engine Project - Apache 2.0 License
// https://echoengine.org
// Module : Lima - Logging
// Copyright (c) 2025 Echo Engine Project contributors
// --------------------------------------------------------------------------------

#ifndef LM_IMPL_SINK_HPP
#define LM_IMPL_SINK_HPP

#include "lima/impl/buffer.hpp"

#include <sierra/prims.hpp>
#include <sierra/target.hpp>

namespace lm::impl {

enum class SinkOutput : u8 {
    CONSOLE_OUT,
    CONSOLE_ERR,
};

template<SinkOutput O>
struct [[nodiscard]] Sink {
    inline static void write(usize len) noexcept;
};

} // namespace lm::impl

#ifdef SRR_TARGET_UNIX

    #include <unistd.h>

namespace lm::impl {

[[nodiscard]] consteval Fd getFd(SinkOutput out) noexcept {
    switch (out) {
    case SinkOutput::CONSOLE_OUT: return STD_OUT;
    case SinkOutput::CONSOLE_ERR: return STD_ERR;
    }
}

template<SinkOutput O>
inline void Sink<O>::write(usize len) noexcept {
    const Fd dst = getFd(O);
    ::write(dst, fmt_buffer.data(), len);
}

} // namespace lm::impl

#endif // SRR_TARGET_UNIX

#endif // LM_IMPL_SINK_HPP

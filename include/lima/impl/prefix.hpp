// --------------------------------------------------------------------------------
// Echo Engine Project - Apache 2.0 License
// https://echoengine.org
// Module : Lima - Logging
// Copyright (c) 2025 Echo Engine Project contributors
// --------------------------------------------------------------------------------

#ifndef LM_IMPL_COLOR_HPP
#define LM_IMPL_COLOR_HPP

#include "lima/impl/buffer.hpp"
#include "lima/impl/sink.hpp"

#include <sierra/prims.hpp>
#include <sierra/utils/char.hpp>

#include <array>
#include <string_view>

namespace lm::impl {

enum class Level : u8 {
    DEBUG,
    INFO,
    WARN,
    ERR,
    FATAL,
    COUNT,
};

consteval impl::SinkOutput output(impl::Level level) noexcept {
    switch (level) {
    case impl::Level::DEBUG: [[fallthrough]];
    case impl::Level::INFO : [[fallthrough]];
    case impl::Level::COUNT: return impl::SinkOutput::CONSOLE_OUT;
    case impl::Level::WARN : [[fallthrough]];
    case impl::Level::ERR  : [[fallthrough]];
    case impl::Level::FATAL: return impl::SinkOutput::CONSOLE_ERR;
    }
}

struct LevelData {
    std::string_view color;
    std::string_view name;
};

constexpr std::string_view ANSI_RESET = "\033[0m";

constexpr std::array<LevelData, static_cast<usize>(Level::COUNT)> LEVEL_DATA{
    {
     { .color = "\033[32m", .name = "DEBUG" },
     { .color = "\033[34m", .name = "INFO" },
     { .color = "\033[33m", .name = "WARN" },
     { .color = "\033[31m", .name = "ERR" },
     { .color = "\033[35m", .name = "FATAL" },
     }
};

template<Level L>
[[nodiscard]] inline char *prefix() noexcept;

template<Level L>
[[nodiscard]] static consteval LevelData data() noexcept;

[[nodiscard]] inline static char *str(std::string_view str, char *ptr) noexcept;

template<Level L>
static consteval LevelData data() noexcept {
    return LEVEL_DATA.at(static_cast<usize>(L));
}

inline static char *str(std::string_view str, char *ptr) noexcept {
    for (const char &chr : str) *ptr++ = chr;
    return ptr;
}

template<>
inline char *prefix<Level::COUNT>() noexcept {
    return fmt_buffer.data();
}

template<Level L>
char *prefix() noexcept {
    char               *ptr  = fmt_buffer.data();

    constexpr LevelData DATA = data<L>();

    *ptr++                   = utils::BRACKET_OPEN;
    ptr                      = str(DATA.color, ptr);
    ptr                      = str(DATA.name, ptr);
    ptr                      = str(ANSI_RESET, ptr);
    *ptr++                   = utils::BRACKET_CLOSE;
    *ptr++                   = utils::SPACE;

    return ptr;
}

} // namespace lm::impl

#endif // LM_IMPL_COLOR_HPP

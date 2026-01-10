/*
--------------------------------------------------------------------------------
Echo Engine Project - Apache 2.0 License

Part of the Echo Engine Project, a modular C++ engine designed for
flexibility, maintainability, and scalability.

To ensure consistency across all modules, the Sierra Style Guide establishes
comprehensive coding conventions, formatting rules, and tooling configurations.
This includes rules for C++ formatting, language server behavior,
static analysis, and guidelines for naming, structure and module interaction.

All contributors are expected to adhere to the Sierra Style Guide,
ensuring that code across the entire ecosystem is readable, maintainable,
and compatible with the project’s tools and pipelines.

By following these conventions, developers help maintain a cohesive
and professional codebase across the Echo Engine Project.

- https://echoengine.org
- https://docs.echoengine.org
- https://style.echoengine.org

Module : Lima - Logging
Copyright (c) 2025 Echo Engine Project contributors
--------------------------------------------------------------------------------
*/

#ifndef LM_LIMA_HPP
#define LM_LIMA_HPP

#include "lima/impl/buffer.hpp"
#include "lima/impl/prefix.hpp"
#include "lima/impl/sink.hpp"

#include <sierra/prims.hpp>

#include <__format/format_functions.h>

#define LM_LOG(l, ...) lm::log<lm::impl::Level::l>(__VA_ARGS__)

#define LM_DEBUG(...)  LM_LOG(DEBUG, __VA_ARGS__)
#define LM_INFO(...)   LM_LOG(INFO, __VA_ARGS__)
#define LM_WARN(...)   LM_LOG(WARN, __VA_ARGS__)
#define LM_ERR(...)    LM_LOG(ERR, __VA_ARGS__)
#define LM_FATAL(...)  LM_LOG(FATAL, __VA_ARGS__)
#define LM_PRINT(...)  LM_LOG(COUNT, __VA_ARGS__)

namespace lm {

template<impl::Level L, typename... V>
void log(std::format_string<V...> fmt, V &&...args);

template<impl::Level L, typename... V>
void log(std::format_string<V...> fmt, V &&...args) {
    char *start     = impl::fmt_buffer.data();
    char *ptr       = impl::prefix<L>();

    ptr             = std::format_to(ptr, fmt, std::forward<V>(args)...);

    *ptr++          = '\n';

    const usize len = static_cast<usize>(ptr - start);
    impl::writeFD(len, impl::STDOUT_FD);
}

} // namespace lm

#endif // LM_LIMA_HPP

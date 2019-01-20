#pragma once

#include <filesystem>
#include <glm/vec2.hpp>
#include <graphics/texture.hpp>

namespace moka
{
    std::byte* texture_load(
        const std::filesystem::path& path,
        int& width,
        int& height,
        host_format& format,
        host_format requested_format = host_format::auto_detect);

    float* texture_load_hdr(
        const std::filesystem::path& path,
        int& width,
        int& height,
        host_format& format,
        host_format requested_format = host_format::auto_detect);

    void free_texture(void* data);
} // namespace moka

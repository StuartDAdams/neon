#pragma once

#include <ostream>
#include <graphics/colour.hpp>
#include <asset_importer/texture_importer.hpp>
#include <vector>
#include <utility>
#include <graphics/buffer/vertex_buffer.hpp>
#include <graphics/buffer/index_buffer.hpp>
#include <graphics/shader.hpp>
#include <graphics/program.hpp>
#include <graphics/texture.hpp>
#include <graphics/device/graphics_visitor.hpp>

namespace moka
{
	class command_list;

	enum class alpha_mode : uint8_t
	{
		blend, // The rendered output is combined with the background using the normal painting operation(i.e.the Porter and Duff over operator). This mode is used to simulate geometry such as guaze cloth or animal fur.
		mask, // The rendered output is either fully opaque or fully transparent depending on the alpha value and the specified alpha cutoff value. This mode is used to simulate geometry such as tree leaves or wire fences.
		opaque // The rendered output is fully opaque and any alpha value is ignored.
	};

    enum class attribute
    {
        position,  
        normal,    
        tangent,   
        bitangent, 
        color0,    
        color1,  
        color2,    
        color3,    
        indices,   
        weight,    
        tex_coord0, 
        tex_coord1, 
        tex_coord2, 
        tex_coord3, 
        tex_coord4, 
        tex_coord5, 
        tex_coord6, 
        tex_coord7,
        extension
    };

    template<typename T>
    struct basic_rectangle
    {
        T x, y, width, height;

		constexpr basic_rectangle(const T x, const T y, const T width, const T height) noexcept
            : x{ x }, y{ y }, width{ width }, height{ height }
        {}
    };

    using rectangle = basic_rectangle<int>;

    enum class primitive_type : uint8_t
    {
		points
		, lines
		, line_loop
		, line_strip
		, triangles
		, triangle_strip
		, triangle_fan
    };

    enum class toggle : uint8_t
    {
        enable,
        disable
    };

    enum class cull_face : uint8_t
    {
        front,
        back,
        front_and_back
    };

    enum class blend_function_factor : uint8_t
    {
        zero,                      
        one,                       
        src_colour,                
        one_minus_src_colour,      
        dst_colour,                
        one_minus_dst_colour,      
        src_alpha,                 
        one_minus_src_alpha,       
        dst_alpha,                 
        one_minus_dst_alpha,       
        constant_colour,           
        one_minus_constant_colour,  
        constant_alpha,            
        one_minus_constant_alpha   
    };

	enum class blend_equation : uint8_t
	{
		func_add,
		func_subtract,
		func_reverse_subtract,
		min,
		max
	};

    enum class shader_attribute : uint8_t
    {
        position,   
        normal,     
        tangent,    
        bitangent,  
        color0,     
        color1,     
        color2,     
        color3,     
        indices,    
        weight,     
        tex_coord0, 
        tex_coord1, 
        tex_coord2, 
        tex_coord3, 
        tex_coord4, 
        tex_coord5, 
        tex_coord6, 
        tex_coord7, 
    };

    enum class parameter_type : uint8_t
    {
        texture, //!< sampler
        vec3, //!< 3 floats vector uniform
        vec4, //!< 4 floats vector uniform
        mat3, //!< 3x3 matrix uniform
        mat4, //!< 4x4 matrix uniform
		float32, //! single floating point uniform
		null //!< value not yet assigned to
    };

	enum class face : uint8_t
	{
		front,
		back,
		front_and_back
	};

	struct uniform_data
	{
		std::string name;
		parameter_type type;
		size_t count;
		size_t buffer_start;
		size_t buffer_end;
	};

	struct texture_binding
	{
		texture handle;
		size_t unit;
	};

	struct draw_call;

    /**
     * \brief render_context abstracts the native rendering API.
     */
    class graphics_api : public graphics_visitor
    {
	public:
        virtual ~graphics_api() = default;
		graphics_api() = default;
		graphics_api(const graphics_api& rhs) = default;
		graphics_api(graphics_api&& rhs) = default;
		graphics_api& operator=(const graphics_api& rhs) = default;
		graphics_api& operator=(graphics_api&& rhs) = default;

		virtual void visit(clear_command& cmd) = 0;
		virtual void visit(draw_command& cmd) = 0;
		virtual void visit(viewport_command& cmd) = 0;
		virtual void visit(scissor_command& cmd) = 0;
		virtual void visit(fill_vertex_buffer_command& cmd) = 0;
		virtual void visit(fill_index_buffer_command& cmd) = 0;

		virtual void submit(command_list&& commands) = 0;
		virtual void submit_and_swap(command_list&& commands) = 0;

		virtual program make_program(const shader& vertex_handle, const shader& fragment_handle) = 0;
        virtual shader make_shader(shader_type type, const std::string& source) = 0;
        virtual vertex_buffer make_vertex_buffer(const void* vertices, size_t size, vertex_layout&& decl, buffer_usage use) = 0;
		virtual index_buffer make_index_buffer(const void* indices, size_t size, index_type type, buffer_usage use) = 0;
		virtual texture make_texture(const void* pixels, const glm::ivec2& resolution, texture_components components, texture_wrap_mode wrap_mode, bool has_mipmaps) = 0;
    };
}
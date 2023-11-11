
#pragma once

#ifndef tinygizmo_example_util_hpp
#define tinygizmo_example_util_hpp

#include <functional>
#include <vector>

#define GLEW_STATIC
#define GL_GLEXT_PROTOTYPES
#include <glad/glad.h>

#include "Core/gCommon.h"

#define GLFW_INCLUDE_GLU
#include "GLFW\glfw3.h"

#include "gGizmo.hpp"
#include "linalg.h"



struct ray { linalg::aliases::float3 origin; linalg::aliases::float3 direction; };

struct rect
{
    int x0, y0, x1, y1;
    int width() const { return x1 - x0; }
    int height() const { return y1 - y0; }
    linalg::aliases::int2 dims() const { return{ width(), height() }; }
    float aspect_ratio() const { return (float)width() / height(); }
};

ray get_ray_from_pixel(const linalg::aliases::float2& pixel, const rect& viewport, Camera)
{
    const float x = 2 * (pixel.x - viewport.x0) / viewport.width() - 1, y = 1 - 2 * (pixel.y - viewport.y0) / viewport.height();
    const linalg::aliases::float4x4 inv_view_proj = inverse(camera.get_viewproj_matrix(viewport.aspect_ratio()));
    const linalg::aliases::float4 p0 = mul(inv_view_proj, linalg::aliases::float4(x, y, -1, 1)), p1 = mul(inv_view_proj, linalg::aliases::float4(x, y, +1, 1));
    return{ camera.position, p1.xyz() * p0.w - p0.xyz() * p1.w };
}



#endif 
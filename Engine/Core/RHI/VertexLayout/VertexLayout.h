#pragma once

#include <glm/glm.hpp>  // TODO : 이후 자체 Math 클래스 를 제작 하면 없애도록.

namespace VertexLayout
{
    struct PosColor
    {
        glm::vec2 pos;
        glm::vec3 color;
    };
}
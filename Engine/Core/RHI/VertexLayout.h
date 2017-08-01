#pragma once

#include "glm/glm.hpp"

struct VertexAttribute
{
    uint32_t location;
    uint32_t offset;
    VertexElementType format;
};

struct VertexDescription
{
    uint32_t stride;
    std::vector<VertexAttribute> attributes;
};

// TODO : 이후 Shader Editor, 저장소 생기면 삭제.
namespace VertexLayout
{
    struct PosColor
    {
        glm::vec2 pos;
        glm::vec3 color;

        static VertexDescription GetVertexDescription()
        {
            VertexDescription description;
            description.stride = sizeof(PosColor);
            description.attributes.resize(2);
           
            uint32_t offset = 0;
            description.attributes[0].location = 0;
            description.attributes[0].offset = 0;
            description.attributes[0].format = VertexElementType::VET_Float2;

            offset += sizeof(glm::vec2);
            description.attributes[1].location = 1;
            description.attributes[1].offset = offset;
            description.attributes[1].format = VertexElementType::VET_Float3;

            return description;
        }
    };
}
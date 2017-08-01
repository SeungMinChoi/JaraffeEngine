#pragma once

static inline VkFormat JFToVkFormat(VertexElementType Type)
{
    switch (Type)
    {
    case VET_Float1:
        return VK_FORMAT_R32_SFLOAT;
    case VET_Float2:
        return VK_FORMAT_R32G32_SFLOAT;
    case VET_Float3:
        return VK_FORMAT_R32G32B32_SFLOAT;
    case VET_PackedNormal:
        return VK_FORMAT_R8G8B8A8_UNORM;
    case VET_UByte4:
        return VK_FORMAT_R8G8B8A8_UINT;
    case VET_UByte4N:
        return VK_FORMAT_R8G8B8A8_UNORM;
    case VET_Color:
        return VK_FORMAT_B8G8R8A8_UNORM;
    case VET_Short2:
        return VK_FORMAT_R16G16_SINT;
    case VET_Short4:
        return VK_FORMAT_R16G16B16A16_SINT;
    case VET_Short2N:
        return VK_FORMAT_R16G16_SNORM;
    case VET_Half2:
        return VK_FORMAT_R16G16_SFLOAT;
    case VET_Half4:
        return VK_FORMAT_R16G16B16A16_SFLOAT;
    case VET_Short4N:		// 4 X 16 bit word: normalized 
        return VK_FORMAT_R16G16B16A16_SNORM;
    case VET_UShort2:
        return VK_FORMAT_R16G16_UINT;
    case VET_UShort4:
        return VK_FORMAT_R16G16B16A16_UINT;
    case VET_UShort2N:		// 16 bit word normalized to (value/65535.0:value/65535.0:0:0:1)
        return VK_FORMAT_R16G16_UNORM;
    case VET_UShort4N:		// 4 X 16 bit word unsigned: normalized 
        return VK_FORMAT_R16G16B16A16_UNORM;
    case VET_Float4:
        return VK_FORMAT_R32G32B32A32_SFLOAT;
    case VET_URGB10A2N:
        return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
    default:
        break;
    }

    return VK_FORMAT_UNDEFINED;
}
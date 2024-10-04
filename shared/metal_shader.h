#ifdef __APPLE__
#ifndef METAL_SHADER_H
#define METAL_SHADER_H

#include <Metal/Metal.hpp>

/**
 * @brief Loads and compiles vertex and fragment shaders and links them into a Metal pipeline state.
 *
 * @param device The Metal device used for rendering.
 * @return MTL::RenderPipelineState* The created Metal pipeline state.
 */
MTL::RenderPipelineState* loadMetalShaderProgram(MTL::Device* device);

/**
 * @brief Initializes vertex positions buffer for Metal rendering.
 *
 * @param device The Metal device used for rendering.
 * @return MTL::Buffer* The buffer containing the vertex positions data.
 */
MTL::Buffer* setupMetalVertexPositionsBuffer(MTL::Device* device);

/**
 * @brief Initializes vertex colors buffer for Metal rendering.
 *
 * @param device The Metal device used for rendering.
 * @return MTL::Buffer* The buffer containing the vertex colors data.
 */
MTL::Buffer* setupMetalVertexColorsBuffer(MTL::Device* device);

#endif // METAL_SHADER_H
#endif // __APPLE__


#ifdef __APPLE__
#ifndef METAL_SHADER_H
#define METAL_SHADER_H

#include <Metal/Metal.h>

/**
 * @brief Loads and compiles vertex and fragment shaders and links them into a Metal pipeline state.
 *
 * @return id<MTLRenderPipelineState> The created Metal pipeline state.
 */
id<MTLRenderPipelineState> loadMetalShaderProgram();

/**
 * @brief Initializes vertex data for Metal rendering.
 *
 * @return id<MTLBuffer> The buffer containing the vertex data.
 */
id<MTLBuffer> setupMetalVertexBuffer();

#endif
#endif

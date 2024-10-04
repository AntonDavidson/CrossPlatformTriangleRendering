#ifdef __APPLE__

#ifndef METAL_UTILS_H
#define METAL_UTILS_H


#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

void setMetalView(void* view);
/**
 * @brief Initializes Metal components such as device and command queue.
 */
void initMetal();

/**
 * @brief Renders using Metal.
 */
void renderMetal();

#endif


#endif

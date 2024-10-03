#ifdef __APPLE__

#ifndef METAL_UTILS_H
#define METAL_UTILS_H

#include <Metal/Metal.h>

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
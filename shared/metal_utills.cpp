#ifdef __APPLE__

#include "metal_utils.h"
#include "metal_shader.h"

// Metal-specific objects for rendering
id<MTLDevice> device;                          // The Metal device, which represents the GPU
id<MTLCommandQueue> commandQueue;              // The command queue, which sends commands to the GPU
id<MTLRenderPipelineState> pipelineState;      // The pipeline state, which contains the configuration for rendering
id<MTLBuffer> vertexBuffer;                    // The vertex buffer, which contains vertex data for rendering

/**
 * @brief Initializes Metal and sets up resources for rendering.
 *
 * This function sets up the Metal device, command queue, pipeline state, and vertex buffer.
 * These resources are necessary for rendering with Metal on iOS. The pipeline state and vertex
 * buffer are created through helper functions, which handle shader compilation and buffer setup.
 */
void initMetal() {
    // Create the Metal device
    device = MTLCreateSystemDefaultDevice();

    // Create a command queue for sending commands to the GPU
    commandQueue = [device newCommandQueue];

    // Load shaders and create a render pipeline state object
    pipelineState = loadMetalShaderProgram();

    // Set up the vertex buffer for the triangle
    vertexBuffer = setupMetalVertexBuffer();
}

/**
 * @brief Renders a frame using Metal.
 *
 * This function creates a command buffer and render pass descriptor, then sets up the
 * render command encoder to configure the pipeline state and vertex buffer for drawing.
 * It draws a triangle using the vertex data and commits the command buffer to the GPU.
 */
void renderMetal() {
    // Create a new command buffer for this frame
    id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];

    // Configure the render pass descriptor with a clear color and store action
    MTLRenderPassDescriptor *passDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    passDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;             // Clear the framebuffer
    passDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0); // Black background color
    passDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;           // Store the final image

    // Create a render command encoder with the render pass descriptor
    id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:passDescriptor];

    // Set the pipeline state (shaders and render configuration) for this draw call
    [renderEncoder setRenderPipelineState:pipelineState];

    // Set the vertex buffer containing the triangle's vertex data
    [renderEncoder setVertexBuffer:vertexBuffer offset:0 atIndex:0];

    // Draw a triangle using the vertex data
    [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

    // Finish encoding the commands for this render pass
    [renderEncoder endEncoding];

    // Present the drawable and commit the command buffer for execution
    [commandBuffer presentDrawable:[passDescriptor colorAttachments][0].texture];
    [commandBuffer commit];
}

#endif

#ifdef __APPLE__

#include "metal_utills.h"
#include "metal_shader.h"
#include <cassert>
#include <MetalKit/MetalKit.hpp>
#include <Metal/Metal.hpp>

// Metal-specific objects for rendering
MTL::Device* device;                         // The Metal device, which represents the GPU
MTL::CommandQueue* commandQueue;             // Command queue for submitting render commands
MTL::RenderPipelineState* PSO;               // Pipeline state object for rendering
MTL::Buffer* vertexPositionsBuffer;          // Buffer for storing vertex positions
MTL::Buffer* vertexColorsBuffer;             // Buffer for storing vertex colors
MTK::View* mtkView = nullptr; 

/**
 * @brief Initializes Metal and sets up resources for rendering.
 *
 * This function sets up the Metal device, command queue, pipeline state, and vertex buffers.
 * These resources are necessary for rendering with Metal on iOS.
 */


void setMetalView(void* view) {
    mtkView = reinterpret_cast<MTK::View*>(view);  // Cast void* back to MTKView
}

void initMetal() {
    // Create the Metal device
    device = MTL::CreateSystemDefaultDevice();

    // Create a command queue for sending commands to the GPU
    commandQueue = device->newCommandQueue();

    // Load shaders and create a render pipeline state object
    PSO = loadMetalShaderProgram(device);

    // Set up the vertex buffers for the triangle
    vertexPositionsBuffer = setupMetalVertexPositionsBuffer(device);
    vertexColorsBuffer = setupMetalVertexColorsBuffer(device);
}

/**
 * @brief Renders a frame using Metal.
 *
 * This function creates a command buffer and render pass descriptor, then sets up the
 * render command encoder to configure the pipeline state and vertex buffers for drawing.
 * It draws a triangle using the vertex data and commits the command buffer to the GPU.
 */
void renderMetal() {
    // Get the current drawable from MTKView
    MTL::Drawable* drawable = mtkView->currentDrawable();
    if (!drawable) return;

    // Create a new command buffer for this frame
    MTL::CommandBuffer* commandBuffer = commandQueue->commandBuffer();

    // Configure the render pass descriptor with a clear color and store action
    MTL::RenderPassDescriptor* passDescriptor = mtkView->currentRenderPassDescriptor();
    if (!passDescriptor) return;

    passDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
    passDescriptor->colorAttachments()->object(0)->setClearColor(MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0));
    passDescriptor->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);

    // Create a render command encoder with the render pass descriptor
    MTL::RenderCommandEncoder* renderEncoder = commandBuffer->renderCommandEncoder(passDescriptor);

    // Set the pipeline state (shaders and render configuration) for this draw call
    renderEncoder->setRenderPipelineState(PSO);

    // Set the vertex buffers containing the triangle's vertex data
    renderEncoder->setVertexBuffer(vertexPositionsBuffer, 0, 0);  // Binding positions buffer to index 0
    renderEncoder->setVertexBuffer(vertexColorsBuffer, 0, 1);     // Binding colors buffer to index 1

    // Draw a triangle using the vertex data
    renderEncoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), NS::UInteger(3));


    // Finish encoding the commands for this render pass
    renderEncoder->endEncoding();

    // Present the drawable and commit the command buffer for execution
    commandBuffer->presentDrawable(drawable);
    commandBuffer->commit();
}

#endif // __APPLE__

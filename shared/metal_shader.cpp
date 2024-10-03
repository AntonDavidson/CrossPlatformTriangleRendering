#ifdef __APPLE
#include "metal_shader.h"
#include <Metal/Metal.h>

/**
 * @brief Loads and compiles the Metal shader program, creating a render pipeline state.
 *
 * This function initializes the Metal render pipeline by loading the vertex and fragment shaders,
 * creating a pipeline descriptor, and building a pipeline state object. It returns the pipeline state
 * that will be used for rendering. If there is an error during pipeline creation, it logs the error.
 *
 * @return id<MTLRenderPipelineState> The compiled pipeline state object for rendering.
 */
id<MTLRenderPipelineState> loadMetalShaderProgram() {
    // Get the Metal device (GPU)
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();

    // Prepare error variable to catch any issues during pipeline creation
    NSError* error = nil;

    // Load the vertex and fragment shader functions from the default Metal library
    id<MTLFunction> vertexFunction = [device newFunctionWithName:@"vertex_main"];
    id<MTLFunction> fragmentFunction = [device newFunctionWithName:@"fragment_main"];

    // Set up the pipeline descriptor and attach the shaders
    MTLRenderPipelineDescriptor *pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDescriptor.vertexFunction = vertexFunction;
    pipelineDescriptor.fragmentFunction = fragmentFunction;

    // Configure the pixel format for the color attachment
    pipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;

    // Create the pipeline state object from the descriptor
    id<MTLRenderPipelineState> pipelineState = [device newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];

    // Log an error message if pipeline state creation failed
    if (error) {
        NSLog(@"Error creating pipeline state: %@", error.localizedDescription);
    }

    return pipelineState;
}

/**
 * @brief Sets up the vertex buffer containing the triangle's vertex data.
 *
 * This function initializes a Metal buffer with the coordinates for a simple triangle.
 * It creates the buffer in shared memory so that both the CPU and GPU can access it.
 * The buffer is returned so that it can be used in rendering.
 *
 * @return id<MTLBuffer> The Metal buffer containing the vertex data for rendering.
 */
id<MTLBuffer> setupMetalVertexBuffer() {
    // Define vertex data for a triangle
    static const float vertexData[] = {
            0.0f,  0.5f, 0.0f,  // Top vertex
            -0.5f, -0.5f, 0.0f, // Bottom left vertex
            0.5f, -0.5f, 0.0f   // Bottom right vertex
    };

    // Create a Metal buffer on the device for vertex data storage
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    return [device newBufferWithBytes:vertexData
                               length:sizeof(vertexData)
                              options:MTLResourceStorageModeShared];
}
#endif

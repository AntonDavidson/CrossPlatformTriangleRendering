#ifdef __APPLE__

#include "metal_shader.h"
#include <Foundation/Foundation.hpp>
#include <simd/simd.h>

/**
 * @brief Loads and compiles the Metal shader program using the Metal C++ API.
 *
 * This function initializes the Metal render pipeline by compiling vertex and fragment shaders,
 * creating a pipeline descriptor, and building a pipeline state object.
 *
 * @param device A pointer to the MTL::Device instance.
 * @return MTL::RenderPipelineState* The compiled pipeline state object for rendering.
 */
MTL::RenderPipelineState* loadMetalShaderProgram(MTL::Device* device) {
    NS::Error* error = nullptr;

    // Shader source code as a string
    const char* shaderSrc = R"(
        #include <metal_stdlib>
        using namespace metal;

        struct v2f {
            float4 position [[position]];
            half3 color;
        };

        v2f vertex vertexMain(uint vertexId [[vertex_id]], device const float3* positions [[buffer(0)]], device const float3* colors [[buffer(1)]]) {
            v2f o;
            o.position = float4(positions[vertexId], 1.0);
            o.color = half3(colors[vertexId]);
            return o;
        }

        half4 fragment fragmentMain(v2f in [[stage_in]]) {
            return half4(in.color, 1.0);
        }
    )";

    // Create the shader library from source code
    MTL::Library* library = device->newLibrary(NS::String::string(shaderSrc, NS::UTF8StringEncoding), nullptr, &error);
    if (!library) {
        __builtin_printf("Error creating library: %s", error->localizedDescription()->utf8String());
        assert(false);
    }

    // Create vertex and fragment functions
    MTL::Function* vertexFunction = library->newFunction(NS::String::string("vertexMain", NS::UTF8StringEncoding));
    MTL::Function* fragmentFunction = library->newFunction(NS::String::string("fragmentMain", NS::UTF8StringEncoding));

    // Create a pipeline descriptor
    MTL::RenderPipelineDescriptor* pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipelineDescriptor->setVertexFunction(vertexFunction);
    pipelineDescriptor->setFragmentFunction(fragmentFunction);
    pipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

    // Create the pipeline state object
    MTL::RenderPipelineState* PSO = device->newRenderPipelineState(pipelineDescriptor, &error);
    if (!PSO) {
        __builtin_printf("Error creating pipeline state: %s", error->localizedDescription()->utf8String());
        assert(false);
    }

    // Release temporary objects
    vertexFunction->release();
    fragmentFunction->release();
    pipelineDescriptor->release();
    library->release();

    return PSO;
}

/**
 * @brief Initializes vertex positions buffer for Metal rendering.
 *
 * @param device A pointer to the MTL::Device instance.
 * @return MTL::Buffer* The buffer containing the vertex positions data.
 */
MTL::Buffer* setupMetalVertexPositionsBuffer(MTL::Device* device) {
    const simd::float3 positions[] = {
        { 0.0f,  0.5f, 0.0f },  // Vertex 1
        { -0.5f, -0.5f, 0.0f }, // Vertex 2
        { 0.5f, -0.5f, 0.0f }   // Vertex 3
    };

    // Use MTL::ResourceStorageModeShared for iOS instead of MTL::ResourceStorageModeManaged
    MTL::Buffer* vertexBuffer = device->newBuffer(positions, sizeof(positions), MTL::ResourceStorageModeShared);

    // Check if the buffer was created successfully
    if (!vertexBuffer) {
        __builtin_printf("Failed to create vertex positions buffer!");
        return nullptr;
    }

    return vertexBuffer;
}

/**
 * @brief Initializes vertex colors buffer for Metal rendering.
 *
 * @param device A pointer to the MTL::Device instance.
 * @return MTL::Buffer* The buffer containing the vertex colors data.
 */
MTL::Buffer* setupMetalVertexColorsBuffer(MTL::Device* device) {
    const simd::float3 colors[] = {
        { 1.0f, 0.5f, 0.0f },  // Orange for Vertex 1
        { 1.0f, 0.5f, 0.0f },  // Orange for Vertex 2
        { 1.0f, 0.5f, 0.0f }   // Orange for Vertex 3
    };
    
    // Use MTL::ResourceStorageModeShared for iOS
    MTL::Buffer* colorBuffer = device->newBuffer(colors, sizeof(colors), MTL::ResourceStorageModeShared);
    
    // Check if the buffer was created successfully
    if (!colorBuffer) {
        __builtin_printf("Failed to create vertex colors buffer!");
        return nullptr;
    }
    
    return colorBuffer;}

#endif // __APPLE__

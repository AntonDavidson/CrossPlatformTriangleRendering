#ifdef ANDROID

#include <GLES3/gl3.h>
#include "opengl_utils.h"

/**
 * @brief Sets up the vertex buffer and vertex array object (VAO) for rendering a triangle.
 *
 * This function initializes OpenGL buffers necessary for drawing a triangle.
 * It defines the vertices of the triangle, loads them into a Vertex Buffer Object (VBO),
 * and configures the Vertex Array Object (VAO) to use these vertices.
 *
 * @param vao Reference to the Vertex Array Object that will be created and configured.
 */
void setupTriangle(GLuint& vao) {
    // Define the vertices for a triangle
    GLfloat vertices[] = {
            0.0f,  0.5f, 0.0f,  // Top vertex
            -0.5f, -0.5f, 0.0f, // Bottom left vertex
            0.5f, -0.5f, 0.0f   // Bottom right vertex
    };

    GLuint vbo;  // Vertex Buffer Object ID

    // Generate a VAO to store the vertex attribute configurations
    glGenVertexArrays(1, &vao);

    // Generate a VBO to store the vertex data
    glGenBuffers(1, &vbo);

    // Bind the VAO (all subsequent configurations will be saved to this VAO)
    glBindVertexArray(vao);

    // Bind the VBO and load the vertex data into the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify the format of the vertex data (position attribute)
    glVertexAttribPointer(
        0,                  // Attribute index (matches the layout in the shader)
        3,                  // Number of components per vertex attribute (x, y, z)
        GL_FLOAT,           // Data type of each component
        GL_FALSE,           // Do not normalize the data
        3 * sizeof(GLfloat),// Stride (byte offset between consecutive vertex attributes)
        (GLvoid*)0          // Offset in the buffer where the position data starts
    );

    // Enable the vertex attribute at index 0
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO to avoid accidental modifications
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

#endif
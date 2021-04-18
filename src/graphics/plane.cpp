#include "graphics/plane.h"

#include <vector>

#include "graphics/shader.h"

namespace graphics {
bool Plane::isInitialized = false;
std::weak_ptr<Buffer<1, GL_ARRAY_BUFFER>> Plane::vbo_weak;

Plane::Plane() {
    if (!(vbo = Plane::vbo_weak.lock())) {
        vbo = std::make_shared<Buffer<1, GL_ARRAY_BUFFER>>();
        vbo_weak = vbo;
    }
    initialize();
}

void Plane::bindVBO() const { vbo->bind(); }

void Plane::generateVertices() {
    if (!Plane::isInitialized) {
        std::vector<GLfloat> vertices{-30.0f, 0.0f, -30.0f, 0.0f, 1.0f,   0.0f,  0.0f, 1.0f,  -30.0f, 0.0f, 30.0f,
                                      0.0f,   1.0f, 0.0f,   1.0f, 1.0f,   30.0f, 0.0f, 30.0f, 0.0f,   1.0f, 0.0f,
                                      1.0f,   0.0f, 30.0f,  0.0f, -30.0f, 0.0f,  1.0f, 0.0f,  0.0f,   0.0f};
        Plane::vbo->bind();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        Plane::isInitialized = true;
    }
}

void Plane::render(Program* shaderProgram) {
    if (texture) {
        shaderProgram->setUniform("useTexture", 1);
        shaderProgram->setUniform("diffuseTexture", texture->getIndex());
    } else {
        shaderProgram->setUniform("useTexture", 0);
        shaderProgram->setUniform<3>("baseColor", baseColor);
    }
    shaderProgram->setUniform("model", modelMatrix);
    shaderProgram->setUniform("invtransmodel", inverseTransposeModel);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
}  // namespace graphics

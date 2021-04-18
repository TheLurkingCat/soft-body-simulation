#include "graphics/rigidbody.h"

namespace graphics {
Rigidbody::Rigidbody() { glGenVertexArrays(1, &vao); }

Rigidbody::Rigidbody(const Rigidbody& other) : Rigidbody() {
    // We MUST NOT copy the vao and vbo since they will be destroyed in destructor
    this->modelMatrix = other.modelMatrix;
    this->inverseTransposeModel = other.inverseTransposeModel;
    this->baseColor = other.baseColor;
    this->texture = other.texture;
}

Rigidbody::~Rigidbody() { glDeleteVertexArrays(1, &vao); }

void Rigidbody::setModelMatrix(const  Eigen::Transform<float, 3, Eigen::Affine>& _modelMatrix) {
    modelMatrix = _modelMatrix;
    inverseTransposeModel = modelMatrix.inverse().matrix().transpose();
}

void Rigidbody::setTexture(const std::shared_ptr<Texture>& _texture) { texture = _texture; }

void Rigidbody::setTexture(const Eigen::Vector4f& color) { baseColor = color; }

void Rigidbody::initialize() {
    generateVertices();
    glBindVertexArray(vao);
    bindVBO();
    // Vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    glBindVertexArray(0);
}
}  // namespace graphics

#pragma once
#include <memory>
#include <vector>

#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "glad/gl.h"

#include "texture.h"
#include "util/types.h"

namespace graphics {
class Program;
class Rigidbody {
 public:
    Rigidbody();
    Rigidbody(const Rigidbody& other);
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    void setModelMatrix(const  Eigen::Transform<float, 3, Eigen::Affine>& _modelMatrix);
    void setTexture(const std::shared_ptr<Texture>& texture);
    void setTexture(const Eigen::Vector4f& color);

    void initialize();

    virtual void generateVertices() = 0;
    virtual void render(Program* shaderProgram) = 0;

 protected:
    virtual ~Rigidbody();
    virtual void bindVBO() const = 0;
    GLuint vao = 0;

     Eigen::Transform<float, 3, Eigen::Affine> modelMatrix =  Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    Eigen::Matrix4f inverseTransposeModel = Eigen::Matrix4f::Identity();
    Eigen::Vector4f baseColor = Eigen::Vector4f::UnitX();
    std::shared_ptr<Texture> texture = nullptr;
};
}  // namespace graphics

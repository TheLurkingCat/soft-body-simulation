#pragma once
#include <array>
#include <memory>
#include <vector>

#include "Eigen/Dense"

#include "shader.h"
#include "simulation/cube.h"
#include "texture.h"
#include "util/types.h"

namespace graphics {
class SoftCube final {
 private:
    const Eigen::Transform<float, 3, Eigen::Affine> modelMatrix = Eigen::Transform<float, 3, Eigen::Affine>::Identity();
    const Eigen::Matrix4f inverseTransposeModel = Eigen::Matrix4f::Identity();
    GLuint cubeVAO[6], structVAO, shearVAO, bendingVAO, particleVAO;
    GLuint cubeVBO[6], vertexVBO, normalVBO[6], textureCoordVBO;
    GLuint cubeEBO[2], structEBO, shearEBO, bendingEBO;

    simulation::Cube* cube;

    std::array<std::shared_ptr<Texture>, 6> textures;
    std::vector<GLfloat> fullVertices;
    std::vector<GLfloat> normalBuffer;
    std::vector<GLfloat> faceVertices;
    std::vector<GLuint> structIndices;
    std::vector<GLuint> shearIndices;
    std::vector<GLuint> bendingIndices;
    Eigen::Vector4f baseColor = Eigen::Vector4f::UnitX();

    void calculateIndices();
    void calculateTextureCoords();
    void initializeBuffers();
    void allocateBuffers();
    void updateSingleFace(int face);

 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    explicit SoftCube(simulation::Cube* _cube);
    SoftCube(const SoftCube&) = delete;
    SoftCube(SoftCube&&) = delete;
    SoftCube& operator=(const SoftCube&) = delete;
    ~SoftCube();

    void setTextures(const std::array<std::shared_ptr<Texture>, 6>& _textures);

    void update();

    void renderCube(Program* shaderProgram);
    void renderPoints(Program* shaderProgram);
    void renderLines(Program* shaderProgram, simulation::Spring::SpringType springType);
};
class SkyBox {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    SkyBox();
    SkyBox(const SkyBox&) = delete;
    SkyBox& operator=(const SkyBox&) = delete;
    ~SkyBox();

    void setTexture(const std::shared_ptr<CubeTexture>& _texture);
    void render(Program* shaderProgram);

 private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    std::shared_ptr<CubeTexture> texture = nullptr;
    static std::vector<GLfloat> vertices;
    static std::vector<GLuint> indices;
};
}  // namespace graphics

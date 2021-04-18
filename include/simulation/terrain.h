#pragma once
#include <memory>

#include "Eigen/Dense"

#include "cube.h"
#include "util/types.h"

namespace simulation {
class Terrain;

enum class TerrainType : char { Plane, Sphere, Bowl, TiltedPlane };

class TerrainFactory final {
 public:
    // no instance, only static usage
    TerrainFactory() = delete;
    static std::unique_ptr<Terrain> CreateTerrain(TerrainType type);
};

// a virtual class
class Terrain {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    virtual ~Terrain() = default;
     Eigen::Transform<float, 3, Eigen::Affine> getModelMatrix();

    virtual TerrainType getType() = 0;
    virtual void handleCollision(Cube& cube) = 0;

 protected:
     Eigen::Transform<float, 3, Eigen::Affine> modelMatrix =  Eigen::Transform<float, 3, Eigen::Affine>::Identity();
};

class PlaneTerrain final : public Terrain {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    friend class TerrainFactory;

    PlaneTerrain();

    TerrainType getType() override;
    void handleCollision(Cube& cube) override;

 private:
    Eigen::Vector4f position = Eigen::Vector4f(0.0f, -1.0f, 0.0f, 0.0f);
    Eigen::Vector4f normal = Eigen::Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
};

class SphereTerrain final : public Terrain {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    friend class TerrainFactory;

    SphereTerrain();

    TerrainType getType() override;
    void handleCollision(Cube& cube) override;

 private:
    Eigen::Vector4f position = Eigen::Vector4f(0.0f, -1.0f, 0.0f, 0.0f);
    float radius = 3.0f;
};

class BowlTerrain final : public Terrain {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    friend class TerrainFactory;

    BowlTerrain();

    TerrainType getType() override;
    void handleCollision(Cube& cube) override;

 private:
    Eigen::Vector4f position = Eigen::Vector4f(2.0f, 7.0f, 1.0f, 0.0f);
    float radius = 7.0f;
};

class TiltedPlaneTerrain final : public Terrain {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    friend class TerrainFactory;

    TiltedPlaneTerrain();

    TerrainType getType() override;
    void handleCollision(Cube& cube) override;

 private:
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector4f normal = Eigen::Vector4f(1.0, 1.0, 0.0, 0.0f);
};
}  // namespace simulation

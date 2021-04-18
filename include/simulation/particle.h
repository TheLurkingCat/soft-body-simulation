#pragma once
#include <vector>

#include "Eigen/Dense"
#include "Eigen/StdVector"
#include "util/types.h"

namespace simulation {
class Particle {
 private:
    Eigen::Vector4f position = Eigen::Vector4f::Zero();
    Eigen::Vector4f velocity = Eigen::Vector4f::Zero();
    Eigen::Vector4f force = Eigen::Vector4f::Zero();

 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    //==========================================
    //  getter
    //==========================================
    Eigen::Vector4f getPosition() const;
    Eigen::Vector4f getVelocity() const;
    Eigen::Vector4f getAcceleration() const;
    Eigen::Vector4f getForce() const;
    //==========================================
    //  setter
    //==========================================
    void setPosition(const Eigen::Vector4f &_position);
    void setVelocity(const Eigen::Vector4f &_velocity);
    void setAcceleration(const Eigen::Vector4f &_acceleration);
    void setForce(const Eigen::Vector4f &_force);
    //==========================================
    //  method
    //==========================================
    void addPosition(const Eigen::Vector4f &_position);
    void addVelocity(const Eigen::Vector4f &_velocity);
    void addAcceleration(const Eigen::Vector4f &_acceleration);
    void addForce(const Eigen::Vector4f &_force);
};

using particleColl = std::vector<Particle, Eigen::aligned_allocator<Particle>>;
}  // namespace simulation

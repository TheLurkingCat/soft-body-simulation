#pragma once
#include <vector>

#include "particle.h"
#include "spring.h"
#include "util/types.h"

namespace simulation {
class Cube {
 public:
    // You need this for alignment otherwise it may crash
    // Ref: https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Cube();
    Cube(const Eigen::Vector4f &a_kInitPos, const float cubeLength, const int numAtEdge, const float dSpringCoef,
         const float dDamperCoef);
    //==========================================
    //  getter
    //==========================================

    int getParticleNum() const;  // return number of particles in the cube
    int getSpringNum() const;    // return number of springs in the cube
    int getNumAtEdge() const;    // return number of particles at edge
    // return index used to access particle at face
    unsigned int getPointMap(const int a_ciSide, const int a_ciI, const int a_ciJ);
    // get a particle in container according to index
    Particle &getParticle(int particleIdx);
    particleColl *getParticlePointer();
    // get a spring in container according to index
    Spring &getSpring(int springIdx);

    //==========================================
    //  setter
    //==========================================

    void setSpringCoef(const float springCoef, const Spring::SpringType springType);
    void setSpringCoef(const float springCoef);
    void setDamperCoef(const float damperCoef, const Spring::SpringType springType);
    void setDamperCoef(const float damperCoef);

    //==========================================
    //  method
    //==========================================
    // set rotation and offset of the cube
    void resetCube(const Eigen::Vector4f &offset, const float &rotate);
    // add gravity
    void addForceField(const Eigen::Vector4f &force);
    void computeInternalForce();
    // delegate collision detection to terrain

 private:
    float springCoefStruct;  // spring coefficient
    float springCoefShear;
    float springCoefBending;
    float damperCoefStruct;
    float damperCoefShear;
    float damperCoefBending;

    int particleNumPerEdge;  // number of particles at cube's edge
    int particleNumPerFace;  // number of particles at cube's face
    float cubeLength;
    Eigen::Vector4f initialPosition;

    particleColl particles;
    std::vector<Spring> springs;

    //==========================================
    //  internal method
    //==========================================
    void initializeParticle();
    void initializeSpring();

    void updateSpringCoef(const float springCoef, const Spring::SpringType springType);
    void updateSpringCoef(const float springCoef);
    void updateDamperCoef(const float damperCoef, const Spring::SpringType springType);
    void updateDamperCoef(const float damperCoef);

    Eigen::Vector4f computeSpringForce(const Eigen::Vector4f &positionA, const Eigen::Vector4f &positionB, const float springCoef,
                                   const float restLength);
    Eigen::Vector4f computeDamperForce(const Eigen::Vector4f &positionA, const Eigen::Vector4f &positionB,
                                   const Eigen::Vector4f &velocityA, const Eigen::Vector4f &velocityB, const float damperCoef);
};
using cubeColl = std::vector<Cube, Eigen::aligned_allocator<Cube>>;
}  // namespace simulation

#include "simulation/cube.h"

#include "Eigen/Dense"

#include "util/helper.h"
namespace simulation {
constexpr float g_cdK = 2500.0f;
constexpr float g_cdD = 50.0f;

Cube::Cube()
    : springCoefStruct(g_cdK),
      springCoefShear(g_cdK),
      springCoefBending(g_cdK),
      damperCoefStruct(g_cdD),
      damperCoefShear(g_cdD),
      damperCoefBending(g_cdD),
      particleNumPerEdge(10),
      cubeLength(2.0),
      initialPosition(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 0.0f)) {
    particleNumPerFace = particleNumPerEdge * particleNumPerEdge;
    initializeParticle();
    initializeSpring();
}

Cube::Cube(const Eigen::Vector4f &a_kInitPos, const float cubeLength, const int numAtEdge, const float dSpringCoef,
           const float dDamperCoef)
    : springCoefStruct(dSpringCoef),
      springCoefShear(dSpringCoef),
      springCoefBending(dSpringCoef),
      damperCoefStruct(dDamperCoef),
      damperCoefShear(dDamperCoef),
      damperCoefBending(dDamperCoef),
      particleNumPerEdge(numAtEdge),
      cubeLength(cubeLength),
      initialPosition(a_kInitPos) {
    particleNumPerFace = numAtEdge * numAtEdge;
    initializeParticle();
    initializeSpring();
}

int Cube::getParticleNum() const { return static_cast<int>(particles.size()); }

int Cube::getSpringNum() const { return static_cast<int>(springs.size()); }

int Cube::getNumAtEdge() const { return particleNumPerEdge; }

unsigned int Cube::getPointMap(const int a_ciSide, const int a_ciI, const int a_ciJ) {
    int r = -1;

    switch (a_ciSide) {
        case 1:  // [a_ciI][a_ciJ][0] bottom face
            r = particleNumPerFace * a_ciI + particleNumPerEdge * a_ciJ;
            break;
        case 6:  // [a_ciI][a_ciJ][9] top face
            r = particleNumPerFace * a_ciI + particleNumPerEdge * a_ciJ + particleNumPerEdge - 1;
            break;
        case 2:  // [a_ciI][0][a_ciJ] front face
            r = particleNumPerFace * a_ciI + a_ciJ;
            break;
        case 5:  // [a_ciI][9][a_ciJ] back face
            r = particleNumPerFace * a_ciI + particleNumPerEdge * (particleNumPerEdge - 1) + a_ciJ;
            break;
        case 3:  // [0][a_ciI][a_ciJ] left face
            r = particleNumPerEdge * a_ciI + a_ciJ;
            break;
        case 4:  // [9][a_ciI][a_ciJ] ra_ciIght face
            r = particleNumPerFace * (particleNumPerEdge - 1) + particleNumPerEdge * a_ciI + a_ciJ;
            break;
    }

    return r;
}

Particle &Cube::getParticle(int particleIdx) { return particles[particleIdx]; }

particleColl *Cube::getParticlePointer() { return &particles; }

Spring &Cube::getSpring(int springIdx) { return springs[springIdx]; }

void Cube::setSpringCoef(const float springCoef, const Spring::SpringType springType) {
    if (springType == Spring::SpringType::STRUCT) {
        springCoefStruct = springCoef;
        updateSpringCoef(springCoef, Spring::SpringType::STRUCT);
    } else if (springType == Spring::SpringType::SHEAR) {
        springCoefShear = springCoef;
        updateSpringCoef(springCoef, Spring::SpringType::SHEAR);
    } else if (springType == Spring::SpringType::BENDING) {
        springCoefBending = springCoef;
        updateSpringCoef(springCoef, Spring::SpringType::BENDING);
    }
}

void Cube::setSpringCoef(const float springCoef) { updateSpringCoef(springCoef); }

void Cube::setDamperCoef(const float damperCoef, const Spring::SpringType springType) {
    if (springType == Spring::SpringType::STRUCT) {
        damperCoefStruct = damperCoef;
        updateDamperCoef(damperCoef, Spring::SpringType::STRUCT);
    } else if (springType == Spring::SpringType::SHEAR) {
        damperCoefShear = damperCoef;
        updateDamperCoef(damperCoef, Spring::SpringType::SHEAR);
    } else if (springType == Spring::SpringType::BENDING) {
        damperCoefBending = damperCoef;
        updateDamperCoef(damperCoef, Spring::SpringType::BENDING);
    }
}

void Cube::setDamperCoef(const float damperCoef) { updateDamperCoef(damperCoef); }

void Cube::resetCube(const Eigen::Vector4f &offset, const float &rotate) {
    float dTheta = util::radians(rotate);  //  change angle from degree to
                                           //  radian

    for (unsigned int uiI = 0; uiI < particles.size(); uiI++) {
        int i = uiI / particleNumPerFace;
        int j = (uiI / particleNumPerEdge) % particleNumPerEdge;
        int k = uiI % particleNumPerEdge;
        float offset_x = (float)((i - particleNumPerEdge / 2) * cubeLength / (particleNumPerEdge - 1));
        float offset_y = (float)((j - particleNumPerEdge / 2) * cubeLength / (particleNumPerEdge - 1));
        float offset_z = (float)((k - particleNumPerEdge / 2) * cubeLength / (particleNumPerEdge - 1));

        Eigen::Vector3f RotateVec(offset_x, offset_y, offset_z);  //  vector from center of cube to the particle

        Eigen::AngleAxis<float> rotation(dTheta, Eigen::Vector3f(1.0f, 0.0f, 1.0f).normalized());
        Eigen::Vector4f temp = Eigen::Vector4f::Zero();
        temp.head<3>() = rotation * RotateVec;

        particles[uiI].setPosition(initialPosition + offset + temp);
        particles[uiI].setForce(Eigen::Vector4f::Zero());
        particles[uiI].setVelocity(Eigen::Vector4f::Zero());
    }
}

void Cube::addForceField(const Eigen::Vector4f &force) {
    for (unsigned int uiI = 0; uiI < particles.size(); uiI++) {
        particles[uiI].setAcceleration(force);
    }
}

void Cube::computeInternalForce() {
    // TODO
    // You need to compute the internal force (spring and damper)
    // for each particle here.
}

Eigen::Vector4f Cube::computeSpringForce(const Eigen::Vector4f &positionA, const Eigen::Vector4f &positionB,
                                         const float springCoef, const float restLength) {
    Eigen::Vector4f springForce = positionA - positionB;
    // TODO
    return springForce;
}

Eigen::Vector4f Cube::computeDamperForce(const Eigen::Vector4f &positionA, const Eigen::Vector4f &positionB,
                                         const Eigen::Vector4f &velocityA, const Eigen::Vector4f &velocityB,
                                         const float damperCoef) {
    Eigen::Vector4f damperForce = positionA - positionB;
    // TODO
    return damperForce;
}

void Cube::initializeParticle() {
    for (int i = 0; i < particleNumPerEdge; i++) {
        for (int j = 0; j < particleNumPerEdge; j++) {
            for (int k = 0; k < particleNumPerEdge; k++) {
                Particle Particle;
                float offset_x = (float)((i - particleNumPerEdge / 2) * cubeLength / (particleNumPerEdge - 1));
                float offset_y = (float)((j - particleNumPerEdge / 2) * cubeLength / (particleNumPerEdge - 1));
                float offset_z = (float)((k - particleNumPerEdge / 2) * cubeLength / (particleNumPerEdge - 1));
                Particle.setPosition(Eigen::Vector4f(initialPosition(0) + offset_x, initialPosition(1) + offset_y,
                                                     initialPosition(2) + offset_z, 0.0f));
                particles.push_back(Particle);
            }
        }
    }
}

void Cube::initializeSpring() {
    int iParticleID = 0;
    int iNeighborID = 1;
    Eigen::Vector4f SpringStartPos = particles[iParticleID].getPosition();
    Eigen::Vector4f SpringEndPos = particles[iNeighborID].getPosition();
    float length = (SpringStartPos - SpringEndPos).norm();
    // Here is sample code for connecting struct spring along z-direction
    for (int i = 0; i < particleNumPerEdge; i++) {
        for (int j = 0; j < particleNumPerEdge; j++) {
            for (int k = 0; k < particleNumPerEdge - 1; k++) {
                //  connect spring along z-direction
                iParticleID = i * particleNumPerFace + j * particleNumPerEdge + k;
                iNeighborID = i * particleNumPerFace + j * particleNumPerEdge + k + 1;
                // Same as:
                // Spring s = Spring(iParticleID, iNeighborID, length, springCoefStruct, damperCoefStruct,
                //                   Spring::SpringType::STRUCT);
                // springs.push_back(s);
                springs.emplace_back(iParticleID, iNeighborID, length, springCoefStruct, damperCoefStruct,
                                     Spring::SpringType::STRUCT);
            }
        }
    }
    // TODO
    // You need to connect all spring: 3 struct, 3 bend, 10 shear per particle
    // You may find some useful facts in Cube::getPointMap function
}

void Cube::updateSpringCoef(const float a_cdSpringCoef, const Spring::SpringType a_cSpringType) {
    for (unsigned int uiI = 0; uiI < springs.size(); uiI++) {
        if (springs[uiI].getType() == a_cSpringType) {
            springs[uiI].setSpringCoef(a_cdSpringCoef);
        }
    }
}

void Cube::updateSpringCoef(const float a_cdSpringCoef) {
    for (unsigned int uiI = 0; uiI < springs.size(); uiI++) {
        springs[uiI].setSpringCoef(a_cdSpringCoef);
    }
}

void Cube::updateDamperCoef(const float a_cdDamperCoef, const Spring::SpringType a_cSpringType) {
    for (unsigned int uiI = 0; uiI < springs.size(); uiI++) {
        if (springs[uiI].getType() == a_cSpringType) {
            springs[uiI].setDamperCoef(a_cdDamperCoef);
        }
    }
}

void Cube::updateDamperCoef(const float a_cdDamperCoef) {
    for (unsigned int uiI = 0; uiI < springs.size(); uiI++) {
        springs[uiI].setDamperCoef(a_cdDamperCoef);
    }
}
}  //  namespace simulation

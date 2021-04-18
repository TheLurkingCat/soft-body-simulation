#include "simulation/terrain.h"

#include <stdexcept>

#include "util/helper.h"

namespace simulation {
// Factory
std::unique_ptr<Terrain> TerrainFactory::CreateTerrain(TerrainType type) {
    switch (type) {
        case simulation::TerrainType::Plane:
            return std::make_unique<PlaneTerrain>();
        case simulation::TerrainType::Sphere:
            return std::make_unique<SphereTerrain>();
        case simulation::TerrainType::Bowl:
            return std::make_unique<BowlTerrain>();
        case simulation::TerrainType::TiltedPlane:
            return std::make_unique<TiltedPlaneTerrain>();
        default:
            throw std::invalid_argument("TerrainFactory::CreateTerrain : invalid TerrainType");
            break;
    }
    return nullptr;
}
// Terrain

Eigen::Transform<float, 3, Eigen::Affine> Terrain::getModelMatrix() { return modelMatrix; }

// Note:
// You should update each particles' velocity (base on the equation in
// slide) and force (contact force : resist + friction) in handleCollision function

// PlaneTerrain //

PlaneTerrain::PlaneTerrain() {
    modelMatrix.translate(Eigen::Vector3f(0.0f, position[1], 0.0f));
    normal.normalize();
}

TerrainType PlaneTerrain::getType() { return TerrainType::Plane; }

void PlaneTerrain::handleCollision(Cube& cube) {
    constexpr float epsilon = 0.01f;
    constexpr float coefRestitution = 0.8f;
    constexpr float coefFriction = 0.3f;
    // TODO
}

// SphereTerrain //

SphereTerrain::SphereTerrain() {
    modelMatrix.translate(position.head<3>()).scale(Eigen::Vector3f(radius, radius, radius));
}

TerrainType SphereTerrain::getType() { return TerrainType::Sphere; }

void SphereTerrain::handleCollision(Cube& cube) {
    constexpr float epsilon = 0.01f;
    constexpr float coefRestitution = 0.8f;
    constexpr float coefFriction = 0.3f;
    // TODO
}

// BowlTerrain //

BowlTerrain::BowlTerrain() { modelMatrix.translate(position.head<3>()).scale(Eigen::Vector3f(radius, radius, radius)); }

TerrainType BowlTerrain::getType() { return TerrainType::Bowl; }

void BowlTerrain::handleCollision(Cube& cube) {
    constexpr float epsilon = 0.01f;
    constexpr float coefRestitution = 0.8f;
    constexpr float coefFriction = 0.3f;
    // TODO
}

// TiltedPlaneTerrain //

TiltedPlaneTerrain::TiltedPlaneTerrain() {
    modelMatrix.rotate(util::rotateDegree(0, 0, -45));
    normal.normalize();
}

TerrainType TiltedPlaneTerrain::getType() { return TerrainType::TiltedPlane; }

void TiltedPlaneTerrain::handleCollision(Cube& cube) {
    constexpr float epsilon = 0.01f;
    constexpr float coefRestitution = 0.8f;
    constexpr float coefFriction = 0.3f;
    // TODO
}
}  // namespace simulation

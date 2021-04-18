#include "simulation/integrator.h"

#include <vector>

#include "Eigen/Dense"
namespace simulation {
// --------------------------------
// Factory
// --------------------------------
std::unique_ptr<Integrator> IntegratorFactory::CreateIntegrator(IntegratorType type) {
    switch (type) {
        case simulation::IntegratorType::ExplicitEuler:
            return std::make_unique<ExplicitEulerIntegrator>();
        case simulation::IntegratorType::ImplicitEuler:
            return std::make_unique<ImplicitEulerIntegrator>();
        case simulation::IntegratorType::MidpointEuler:
            return std::make_unique<MidpointEulerIntegrator>();
        case simulation::IntegratorType::RungeKuttaFourth:
            return std::make_unique<RungeKuttaFourthIntegrator>();
        default:
            throw std::invalid_argument("TerrainFactory::CreateTerrain : invalid TerrainType");
            break;
    }
    return nullptr;
}

// --------------------------------
// ExplicitEulerIntegrator
// --------------------------------

IntegratorType ExplicitEulerIntegrator::getType() { return IntegratorType::ExplicitEuler; }

void ExplicitEulerIntegrator::integrate(MassSpringSystem& particleSystem) {
    // TODO
}

// --------------------------------
// ImplicitEulerIntegrator
// --------------------------------

IntegratorType ImplicitEulerIntegrator::getType() { return IntegratorType::ImplicitEuler; }

void ImplicitEulerIntegrator::integrate(MassSpringSystem& particleSystem) {
    // TODO
}

// --------------------------------
// MidpointEulerIntegrator
// --------------------------------

IntegratorType MidpointEulerIntegrator::getType() { return IntegratorType::MidpointEuler; }

void MidpointEulerIntegrator::integrate(MassSpringSystem& particleSystem) {
    // For midpoint euler, the deltaTime passed in will be correct,
    // but the deltaTime the resolve function referenced will be handled by the
    // MassSpringSystem class.

    // TODO
}

// --------------------------------
// RungeKuttaFourthIntegrator
// --------------------------------

IntegratorType RungeKuttaFourthIntegrator::getType() { return IntegratorType::RungeKuttaFourth; }

void RungeKuttaFourthIntegrator::integrate(MassSpringSystem& particleSystem) {
    // TODO
}
}  // namespace simulation

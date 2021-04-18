#include "simulation/particle.h"

namespace simulation {
//==========================================
//  getter
//==========================================
Eigen::Vector4f Particle::getPosition() const { return position; }
Eigen::Vector4f Particle::getVelocity() const { return velocity; }
Eigen::Vector4f Particle::getAcceleration() const { return force; }
Eigen::Vector4f Particle::getForce() const { return force; }

//==========================================
//  setter
//==========================================

void Particle::setPosition(const Eigen::Vector4f &_position) { position = _position; }

void Particle::setVelocity(const Eigen::Vector4f &_velocity) { velocity = _velocity; }

void Particle::setAcceleration(const Eigen::Vector4f &_acceleration) { force = _acceleration; }

void Particle::setForce(const Eigen::Vector4f &_force) { force = _force; }

//==========================================
//  method
//==========================================

void Particle::addPosition(const Eigen::Vector4f &_position) { position += _position; }

void Particle::addVelocity(const Eigen::Vector4f &_velocity) { velocity += _velocity; }

void Particle::addAcceleration(const Eigen::Vector4f &_acceleration) { force += _acceleration; }

void Particle::addForce(const Eigen::Vector4f &_force) { force += _force; }
}  // namespace simulation

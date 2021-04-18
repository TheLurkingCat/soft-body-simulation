#pragma once

#include "Eigen/Dense"
#include "types.h"

namespace util {
constexpr double PI = 3.141592653589793238;
constexpr float radians(float angle) { return static_cast<float>(angle * PI / 180.0); }
constexpr float toRadian(float angle) { return static_cast<float>(double{angle} * PI / 180.0); }
Eigen::Matrix4f perspective(float fovy, float aspect, float zNear, float zFar);
Eigen::Quaternionf rotateDegree(float x, float y, float z);
Eigen::Matrix4f lookAt(const Eigen::Vector4f& eye, const Eigen::Vector4f& center, const Eigen::Vector4f& up);
Eigen::Matrix4f ortho(float left, float right, float bottom, float top, float zNear, float zFar);
}  // namespace util

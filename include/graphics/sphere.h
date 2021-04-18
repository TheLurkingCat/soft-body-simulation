#pragma once
#include <memory>

#include "buffer.h"
#include "rigidbody.h"

namespace graphics {
class Sphere final : public Rigidbody {
 public:
    enum class RenderMode : int { WIREFRAME, FILLED };
    Sphere(RenderMode m = RenderMode::FILLED);
    void bindVBO() const override;
    void generateVertices() override;
    void render(Program* shaderProgram) override;

 private:
    const RenderMode mode;
    std::shared_ptr<Buffer<1, GL_ARRAY_BUFFER>> vbo = nullptr;
    std::shared_ptr<Buffer<2, GL_ELEMENT_ARRAY_BUFFER>> ebo = nullptr;
    static std::weak_ptr<Buffer<1, GL_ARRAY_BUFFER>> vbo_weak;
    static std::weak_ptr<Buffer<2, GL_ELEMENT_ARRAY_BUFFER>> ebo_weak;
    static bool isInitialized;
};
}  // namespace graphics

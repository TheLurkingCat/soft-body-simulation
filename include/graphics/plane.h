#pragma once
#include <memory>
#include <vector>

#include "glad/gl.h"

#include "buffer.h"
#include "rigidbody.h"

class Program;

namespace graphics {
class Plane final : public Rigidbody {
 public:
    Plane();
    void bindVBO() const override;
    void generateVertices() override;
    void render(Program* shaderProgram) override;

 private:
    std::shared_ptr<Buffer<1, GL_ARRAY_BUFFER>> vbo = nullptr;
    static std::weak_ptr<Buffer<1, GL_ARRAY_BUFFER>> vbo_weak;
    static bool isInitialized;
};
}  // namespace graphics

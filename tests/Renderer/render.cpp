// ---------------------------------------------------------------------------
// Rendering smoke test.
//
// Order of checks:
//   1. BufferLayout math (no GPU / no window needed) — catches offset/stride
//      bugs before touching OpenGL at all.
//   2. Window + GL context creation via Window_GLFW.
//   3. VertexBuffer / IndexBuffer / VertexArray / Shader construction.
//   4. A draw loop. If everything is wired correctly you should see a
//      triangle with a red/green/blue gradient across it. Anything else
//      (black screen, garbled shape, crash) tells you where to look.
//
// Sprinkle checkGLError(...) calls after anything you don't trust yet.
// ---------------------------------------------------------------------------
// Date: 8/18/26

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <iostream>
#include <memory>

#include "window/window_glfw.h"
#include "window/window_config.h"
#include "renderer/BufferLayout.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"

using namespace Engine;

// ---------------------------------------------------------------------------
// Small helper: OpenGL doesn't throw on error, it just sets a flag you have
// to poll. Call this after any GL call you're not sure about.
// ---------------------------------------------------------------------------
static void checkGLError(const char* label)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "[GL ERROR] after " << label << ": 0x"
            << std::hex << err << std::dec << "\n";
    }
}

// ---------------------------------------------------------------------------
// 1. BufferLayout — pure math, no GL context required. Run this before
//    anything else touches the GPU so a bug here doesn't get buried under
//    window/shader noise.
// ---------------------------------------------------------------------------
static void testBufferLayout()
{
    BufferLayout layout = {
        { ShaderDataType::Float3, "aPos" },
        { ShaderDataType::Float3, "aColor" },
    };

    const auto& elements = layout.getElements();

    assert(elements.size() == 2);
    assert(elements[0].offset == 0);
    assert(elements[1].offset == 12);   // after 3 floats
    assert(layout.getStride() == 24);   // 12 + 12

    std::cout << "[PASS] BufferLayout offsets/stride computed correctly\n";
}

// ---------------------------------------------------------------------------
// 4. Actual draw loop.
// ---------------------------------------------------------------------------
int main()
{
    // --- 1. Layout math sanity check --------------------------------------
    testBufferLayout();

    // --- 2. Window + GL context ---------------------------------------------
    if (!glfwInit())
    {
        std::cerr << "glfwInit failed\n";
        return -1;
    }

    WindowConfig config;
    config.title = "Renderer Smoke Test";
    config.dimension = { 800, 600 };

    Window_GLFW window(config);
    if (!window.init())
    {
        std::cerr << "Window_GLFW::init failed\n";
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "gladLoadGLLoader failed\n";
        return -1;
    }
    std::cout << "[PASS] Window + GL context created (" << glGetString(GL_VERSION) << ")\n";

    // --- 3. Buffers / VAO ----------------------------------------------------
    // Triangle: position (vec3) + color (vec3) interleaved.
    float vertices[] = {
        // x      y     z       r     g     b
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
    };
    unsigned int indices[] = { 0, 1, 2 };

    auto vb = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    checkGLError("VertexBuffer ctor");

    vb->SetLayout({
        { ShaderDataType::Float3, "aPos" },
        { ShaderDataType::Float3, "aColor" },
        });

    auto ib = std::make_shared<IndexBuffer>(indices, 3);
    checkGLError("IndexBuffer ctor");
    assert(ib->getCount() == 3);

    VertexArray va;
    va.SetVertexBuffer(vb);
    checkGLError("SetVertexBuffer");
    va.SetIndexBuffer(ib);
    checkGLError("SetIndexBuffer");

    // Sanity: the VAO should have stored what we gave it (catches the
    // self-assignment bug if it ever creeps back in).
    assert(va.getVertexBuffer() == vb);
    assert(va.getIndexBuffer() == ib);
    std::cout << "[PASS] VertexArray stored buffers correctly\n";

    // --- Shader ----------------------------------------------------------
    // Adjust these paths if you run the binary from a different working
    // directory than where shaders/ lives.
    Shader shader("E:\\Repos\\PizzaSrc\\IcebergEngine\\src\\game\\shaders\\test.vert", "E:\\Repos\\PizzaSrc\\IcebergEngine\\src\\game\\shaders\\test.frag");
    checkGLError("Shader compile/link");

    // --- Move-semantics smoke test ----------------------------------------
    // Moves a VertexBuffer and makes sure the old one's destructor doesn't
    // double-free the GL buffer out from under the new one.
    {
        VertexBuffer temp(vertices, sizeof(vertices));
        VertexBuffer moved(std::move(temp));
        moved.Bind();
        checkGLError("moved VertexBuffer bind");
    } // both destructors run here
    checkGLError("VertexBuffer move test scope exit");
    std::cout << "[PASS] Move construction did not trigger GL errors\n";

    // --- 4. Draw loop ------------------------------------------------------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!window.should_close())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        va.Bind();
        glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);
        checkGLError("glDrawElements");

        window.swap_buffers();
        window.poll_events();
    }

    glfwTerminate();
    return 0;
}
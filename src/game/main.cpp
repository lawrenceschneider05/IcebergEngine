// Unit tests for Engine::Camera / Engine::Entity
//
// NOTE: Entity.h had a const-correctness bug that prevented this code from
// compiling at all: getTransform() (and getModelMatrix()) were not marked
// `const`, but Camera::getViewMatrix() const and Camera::getForwardVector()
// const call getTransform() on a const Camera*. That's a hard compile error
// under any standards-conforming compiler (g++ needs -fpermissive to even
// limp through it). Fix applied in Entity.h:
//
//   const glm::mat4 getModelMatrix() const { ... }
//   const Transform& getTransform() const { return _transform; }
//
// Build:  g++ -std=c++17 main.cpp -o camera_tests
// Run:    ./camera_tests

#include "Scene/Camera.h"
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <glm/gtc/epsilon.hpp>

using namespace Engine;

static int g_tests = 0;
static int g_failures = 0;

static void check(bool cond, const char* name) {
    ++g_tests;
    if (!cond) {
        ++g_failures;
        std::printf("[FAIL] %s\n", name);
    }
    else {
        std::printf("[ OK ] %s\n", name);
    }
}

static bool nearlyEqual(float a, float b, float eps = 1e-4f) {
    return std::fabs(a - b) < eps;
}

static bool vecNearlyEqual(const glm::vec3& a, const glm::vec3& b, float eps = 1e-4f) {
    return nearlyEqual(a.x, b.x, eps) && nearlyEqual(a.y, b.y, eps) && nearlyEqual(a.z, b.z, eps);
}

static bool matNearlyEqual(const glm::mat4& a, const glm::mat4& b, float eps = 1e-4f) {
    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r)
            if (!nearlyEqual(a[c][r], b[c][r], eps)) return false;
    return true;
}

// ---------------------------------------------------------------------
// Entity tests
// ---------------------------------------------------------------------

void test_entity_default_transform_gives_identity_model_matrix() {
    Transform t; // identity: pos 0, rot 0, scale 1
    Entity e(t);
    glm::mat4 model = e.getModelMatrix();
    check(matNearlyEqual(model, glm::mat4(1.0f)),
        "Entity: default transform produces identity model matrix");
}

void test_entity_translation_only() {
    Transform t;
    t.position = glm::vec3(3.0f, -2.0f, 5.0f);
    Entity e(t);
    glm::mat4 model = e.getModelMatrix();
    glm::vec3 translated = glm::vec3(model * glm::vec4(0, 0, 0, 1));
    check(vecNearlyEqual(translated, t.position),
        "Entity: translation-only transform moves origin to position");
}

void test_entity_scale_only() {
    Transform t;
    t.scale = glm::vec3(2.0f, 3.0f, 4.0f);
    Entity e(t);
    glm::mat4 model = e.getModelMatrix();
    glm::vec3 scaled = glm::vec3(model * glm::vec4(1, 1, 1, 1));
    check(vecNearlyEqual(scaled, glm::vec3(2.0f, 3.0f, 4.0f)),
        "Entity: scale-only transform scales unit point correctly");
}

void test_entity_getTransform_is_const_callable() {
    // This is a compile-time property as much as a runtime one: if this
    // function compiles at all, the const-correctness bug is fixed.
    Transform t;
    t.position = glm::vec3(1, 2, 3);
    const Entity e(t);
    const Transform& got = e.getTransform();
    check(vecNearlyEqual(got.position, glm::vec3(1, 2, 3)),
        "Entity: getTransform() is callable on a const Entity and returns correct data");
}

// ---------------------------------------------------------------------
// Camera tests
// ---------------------------------------------------------------------

void test_camera_default_up_vector() {
    Transform t;
    Camera cam(CameraProperties{}, t);
    check(vecNearlyEqual(cam.getUpVector(), glm::vec3(0, 1, 0)),
        "Camera: getUpVector() returns world up (0,1,0)");
}

void test_camera_forward_vector_no_rotation() {
    // rotation = (0,0,0) -> forward.x = cos(0)*cos(0)=1, y = sin(0)=0, z = sin(0)*cos(0)=0
    Transform t; // no rotation
    Camera cam(CameraProperties{}, t);
    glm::vec3 fwd = cam.getForwardVector();
    check(vecNearlyEqual(fwd, glm::vec3(1, 0, 0)),
        "Camera: forward vector with zero rotation is (1,0,0) per this formula");
}

void test_camera_forward_vector_yaw_90() {
    // rotation.y = 90 deg -> forward.x = cos(90)*cos(0) = 0, z = sin(90)*cos(0) = 1
    Transform t;
    t.rotation = glm::vec3(0.0f, 90.0f, 0.0f);
    Camera cam(CameraProperties{}, t);
    glm::vec3 fwd = cam.getForwardVector();
    check(vecNearlyEqual(fwd, glm::vec3(0, 0, 1), 1e-3f),
        "Camera: forward vector with 90 deg yaw is (0,0,1)");
}

void test_camera_forward_vector_is_normalized() {
    Transform t;
    t.rotation = glm::vec3(37.0f, 123.0f, 0.0f); // rotation.z is unused by the formula
    Camera cam(CameraProperties{}, t);
    glm::vec3 fwd = cam.getForwardVector();
    check(nearlyEqual(glm::length(fwd), 1.0f, 1e-4f),
        "Camera: forward vector is always unit length");
}

void test_camera_view_matrix_matches_manual_lookAt() {
    Transform t;
    t.position = glm::vec3(0.0f, 0.0f, 5.0f);
    // no rotation -> forward = (1,0,0), up = (0,1,0)
    Camera cam(CameraProperties{}, t);
    glm::mat4 expected = glm::lookAt(t.position, t.position + glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 actual = cam.getViewMatrix();
    check(matNearlyEqual(actual, expected),
        "Camera: view matrix matches glm::lookAt(pos, pos+forward, up)");
}

void test_camera_projection_matrix_matches_manual_perspective() {
    CameraProperties props;
    props.fov = 60.0f;
    props.aspectRatio = 1920.0f / 1080.0f;
    props.nearPlane = 0.5f;
    props.farPlane = 250.0f;
    Transform t;
    Camera cam(props, t);
    glm::mat4 expected = glm::perspective(glm::radians(props.fov), props.aspectRatio, props.nearPlane, props.farPlane);
    glm::mat4 actual = cam.getProjectionMatrix();
    check(matNearlyEqual(actual, expected),
        "Camera: projection matrix matches glm::perspective() with same properties");
}

void test_camera_view_matrix_is_const_callable() {
    // Compile-time check: proves the const-correctness fix actually works
    // for the method the bug report was originally about.
    Transform t;
    const Camera cam(CameraProperties{}, t);
    glm::mat4 v = cam.getViewMatrix();
    check(true, "Camera: getViewMatrix() compiles and runs on a const Camera");
    (void)v;
}

int main() {
    test_entity_default_transform_gives_identity_model_matrix();
    test_entity_translation_only();
    test_entity_scale_only();
    test_entity_getTransform_is_const_callable();

    test_camera_default_up_vector();
    test_camera_forward_vector_no_rotation();
    test_camera_forward_vector_yaw_90();
    test_camera_forward_vector_is_normalized();
    test_camera_view_matrix_matches_manual_lookAt();
    test_camera_projection_matrix_matches_manual_perspective();
    test_camera_view_matrix_is_const_callable();

    std::printf("\n%d/%d tests passed\n", g_tests - g_failures, g_tests);
    return g_failures == 0 ? 0 : 1;
}
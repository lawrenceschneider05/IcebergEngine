#pragma once
#include "Entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

    struct CameraProperties {
        float fov{ 45.0f };
        float aspectRatio{ 16.0f / 9.0f };
        float nearPlane{ 0.1f };
        float farPlane{ 100.0f };
    };

    class Camera : public Entity {
    public:                               
		
		Camera(const CameraProperties& properties, const Transform& transform) :
			Entity(transform), _properties(properties){}
			
		glm::mat4 getViewMatrix() const {
			const Transform& t = getTransform();
			glm::mat4 view = glm::lookAt(t.position, t.position + getForwardVector(), getUpVector());
			return view;
		}

		glm::mat4 getProjectionMatrix() const {
			return glm::perspective(glm::radians(_properties.fov), _properties.aspectRatio, _properties.nearPlane, _properties.farPlane);
		}

		glm::vec3 getForwardVector() const {
			const Transform& t = getTransform();
			glm::vec3 forward;
			forward.x = cos(glm::radians(t.rotation.y)) * cos(glm::radians(t.rotation.x));
			forward.y = sin(glm::radians(t.rotation.x));
			forward.z = sin(glm::radians(t.rotation.y)) * cos(glm::radians(t.rotation.x));
			return glm::normalize(forward);
		}

		glm::vec3 getUpVector() const {
			return glm::vec3(0.0f, 1.0f, 0.0f);
		}

    private:
        CameraProperties _properties;
    };

} // namespace Engine
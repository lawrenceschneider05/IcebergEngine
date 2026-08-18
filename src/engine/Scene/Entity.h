#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

	struct Transform {

		glm::vec3 position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

	};

	class Entity {
	public:
		Entity(Transform& transform)
			: _transform{ transform } {
		}

		const glm::mat4 getModelMatrix() const {
			glm::mat4 model = glm::translate(glm::mat4(1.0f), _transform.position);
			model = glm::rotate(model, glm::radians(_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, _transform.scale);
			return model;
		}

		const Transform& getTransform() const { return _transform; }

	private:
		void cleanup();

		Transform _transform;
		// Connect to mesh and texture

	};

}
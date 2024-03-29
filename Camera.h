#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Transform.h"

class Camera
{
public:
	Camera(const glm::vec3& position, float fov, float ratio, float zNear, float zFar);
	~Camera();
	inline glm::mat4 getViewMatrix() const {
		return glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	glm::mat4 getProjectionMatrix() {
		return m_perspective;
	}
	
	void move(const glm::vec3& dir, const float& amt);
	glm::vec3 getLeft();
	glm::vec3 getRight();
	glm::vec3 getForward();
	void rotateX(const float& angle);
	void rotateY(const float& angle);

private:
	glm::vec3 m_yAxis;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	glm::mat4 m_perspective;
};


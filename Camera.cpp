#include "Camera.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(const glm::vec3& position, float fov, float ratio, float zNear, float zFar) {
	m_perspective = glm::perspective(fov, ratio, zNear, zFar);
	m_position = position;
	m_forward = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);
	m_yAxis = glm::vec3(0, 1, 0);
}


Camera::~Camera() {
}


void Camera::move(const glm::vec3& dir, const float& amt) {
	this->m_position += dir*amt;
}


glm::vec3 Camera::getLeft() {
	return glm::cross(m_up, m_forward);
}


glm::vec3 Camera::getRight() {
	return glm::cross(m_forward, m_up);
}


void Camera::rotateX(const float& angle) {
	glm::vec3 hAxis = glm::cross(m_yAxis, m_forward);
	hAxis = glm::normalize(hAxis);

	float cosHalfAngle = glm::cos(glm::radians(angle / 2));
	float sinHalfAngle = glm::sin(glm::radians(angle / 2));
	glm::quat q(cosHalfAngle, m_yAxis*sinHalfAngle);

	m_forward = glm::rotate(q, m_forward);
	m_forward = glm::normalize(m_forward);

	m_up = glm::cross(m_forward, hAxis);
	m_up = glm::normalize(m_up);
}


void Camera::rotateY(const float& angle) {
	glm::vec3 hAxis = glm::cross(m_yAxis, m_forward);
	hAxis = glm::normalize(hAxis);

	float cosHalfAngle = glm::cos(glm::radians(angle / 2));
	float sinHalfAngle = glm::sin(glm::radians(angle / 2));
	glm::quat q(cosHalfAngle, hAxis*sinHalfAngle);

	m_forward = glm::rotate(q, m_forward);
	m_forward = glm::normalize(m_forward);

	m_up = glm::cross(m_forward, hAxis);
	m_up = glm::normalize(m_up);
}
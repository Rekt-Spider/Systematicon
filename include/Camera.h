#pragma once
#include <glad/glad.h>
#include <glm-1.0.1/glm/glm.hpp>
#include <glm-1.0.1/glm/gtc/matrix_transform.hpp>

	enum Camera_Movement
	{
			STILL,
			FORWARD,
			BACKWARD,
			RIGHT,
			LEFT
	};

	enum Camera_Setting_Toggles
	{
			DEFAULT,
			LOCK_MOVEMENT,
			LOCK_ZOOM,
			LOCK_ON_OBJECT
	};

	const float YAW         = -90.0f;
	const float PITCH       =  0.0f;
	const float SPEED       =  2.5f;
	const float SENSITIVITY =  0.01f;
	const float FOV         =  45.0f;

class Camera
{
public:
	//camera properties
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	//euler angles
	float Yaw;
	float Pitch;
	//cameraOptions
	float MovementSpeed;
	float MouseSensitivity;
	float Fov;
	//settings toggled
	bool MovementLock;
	bool ZoomLock;
	
	//constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	//dayerteq - walk in the cold

	//constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	//returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction = STILL, float deltaTime = 0.0F, Camera_Setting_Toggles toggle = DEFAULT);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true, Camera_Setting_Toggles toggle = DEFAULT);
	void ProcessMouseScroll(float yoffset);
private:
	void updateCameraVectors();
};
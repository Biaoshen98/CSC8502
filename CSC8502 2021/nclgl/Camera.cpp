#include "Camera.h"
#include "Window.h"
#include <algorithm>
float mode = 0;
float speedmode = 0;
float numTime = 0;
void Camera::UpdateCamera(float dt)
{
	Matrix4 rotation = Matrix4::Rotation(yaw, Vector3(0, 1, 0)); //(0, 1, 0) around the y axis

	Vector3 forward = rotation * Vector3(0, 0, -1);
	Vector3 right = rotation * Vector3(1, 0, 0);
	float speed = 0;
	if (speedmode == 0)
	{
		speed = 300.0f * dt;
	}
	else
	{
		speed = 900.0f * dt;
	}
	
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_1))//start to move camera automatic.
	{
		mode = 0;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_2))//stop moving camera automatic.
	{
		mode = 1;
	}
	if(mode == 0)
	{
		if (yaw < 0)
		{
			yaw += 360.0f;
		}
		if (yaw > 360.0f)
		{
			yaw -= 360.0f;
		}
		pitch = std::min(pitch, 90.0f);
		pitch = std::max(pitch, -90.0f);
		numTime = dt + numTime;
		if (numTime < 20) {
			position += forward * speed;
			position -= right * speed;
			yaw = yaw - 5 * dt;
		}
		if (numTime > 20 && numTime < 40) {
			yaw = yaw - 5 * dt;
		}
		if (numTime > 40 && numTime < 60) {
			pitch = pitch - 5 * dt;
		}
		if (numTime > 60 && numTime < 80) {
			pitch = pitch + 5 * dt;
		}
		if (numTime > 80 && numTime < 100) {
			position.y -= speed;
			position += right * speed;
		}
		if (numTime > 100 && numTime < 120) {
			yaw = yaw + 5 * dt;
		}
	}
	if (mode == 1)
	{
		pitch -= Window::GetMouse()->GetRelativePosition().y;
		yaw -= Window::GetMouse()->GetRelativePosition().x;

		pitch = std::min(pitch, 90.0f);
		pitch = std::max(pitch, -90.0f);

		if (yaw < 0)
		{
			yaw += 360.0f;
		}
		if (yaw > 360.0f)
		{
			yaw -= 360.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W))//press W go forward
		{
			position += forward * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S))//press S go back
		{
			position -= forward * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A))//press A go left
		{
			position -= right * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D))//press D go right
		{
			position += right * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE))//press space go up
		{
			position.y += speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_C))//press C go down
		{
			position.y -= speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT))//press SHIFT go quickly
		{
			speedmode = 1;
		}
		else
		{
			speedmode = 0;
		}
	}

}

Matrix4 Camera::BuildViewMatrix()
{
	return	Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) *
			Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) *
			Matrix4::Translation(-position);
}
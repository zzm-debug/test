#include"CameraManager.h"

CameraManager* CameraManager::manager = nullptr;

CameraManager::CameraManager()
{
	camera = new Camera();
}

CameraManager* CameraManager::instance()
{
	if (!manager) manager = new CameraManager();
	return manager;
}

Camera* CameraManager::get_camera()
{
	return camera;
}
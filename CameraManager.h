#include"Camera.h"

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

class CameraManager
{
public:

	CameraManager();
	static CameraManager* instance();

	Camera* get_camera();

private:
	static CameraManager* manager;
	Camera* camera=nullptr;
};

#endif // !CAMERAMANAGER_H


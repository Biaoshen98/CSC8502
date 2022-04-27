#pragma once
#include "SceneNode.h"

class CubeRobot :public SceneNode
{
public:
	CubeRobot(Mesh* cube);
	~CubeRobot(void) {};
	void Update(float dt) override;

protected:
	SceneNode* tree_1;
	SceneNode* tree_2;
	SceneNode* tree_3;
	SceneNode* tree_4;
	SceneNode* tree_5;
	SceneNode* tree_6;
	SceneNode* tree_7;
	SceneNode* tree_8;
	SceneNode* tree_9;
	SceneNode* tree_10;
};
#pragma once
#include "SceneNode.h"

class Grass :public SceneNode
{
public:
	Grass(Mesh* grassmesh);
	~Grass(void) {};
	void Update(float dt) override;

protected:
	SceneNode* grass_1;
	SceneNode* grass_2;
	SceneNode* grass_3;
	SceneNode* grass_4;
	SceneNode* grass_5;
	SceneNode* grass_6;
	SceneNode* grass_7;
	SceneNode* grass_8;
	SceneNode* grass_9;
	SceneNode* grass_10;
	SceneNode* grass_11;
	SceneNode* grass_12;
	SceneNode* grass_13;
	SceneNode* grass_14;
	SceneNode* grass_15;
	SceneNode* grass_16;
	SceneNode* grass_17;
	SceneNode* grass_18;
	SceneNode* grass_19;
	SceneNode* grass_20;
};
#include "Grass.h"

Grass::Grass(Mesh* grassmesh)
{
	SetMesh(grassmesh);

	SceneNode* body = new SceneNode(grassmesh);
	body->SetModelScale(Vector3(30, 30, 30));
	body->SetTransform(Matrix4::Translation(Vector3(2050, 500, 2100)));
	AddChild(body);

	grass_1 = new SceneNode(grassmesh);
	grass_1->SetModelScale(Vector3(30, 30, 30));
	grass_1->SetTransform(Matrix4::Translation(Vector3(150, 0, 10)));
	grass_1->SetTransform(grass_1->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_1);

	grass_2 = new SceneNode(grassmesh);
	grass_2->SetModelScale(Vector3(30, 30, 30));
	grass_2->SetTransform(Matrix4::Translation(Vector3(250, 0, 150)));
	//tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(-10.0f*2.5, Vector3(1, 0, 0)));
	grass_2->SetTransform(grass_2->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_2);

	grass_3 = new SceneNode(grassmesh);
	grass_3->SetModelScale(Vector3(30, 30, 30));
	grass_3->SetTransform(Matrix4::Translation(Vector3(400, 0, 250)));
	grass_3->SetTransform(grass_3->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_3);

	grass_4 = new SceneNode(grassmesh);
	grass_4->SetModelScale(Vector3(30, 30, 30));
	grass_4->SetTransform(Matrix4::Translation(Vector3(550, 0, 250)));
	grass_4->SetTransform(grass_4->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_4);

	grass_5 = new SceneNode(grassmesh);
	grass_5->SetModelScale(Vector3(30, 30, 30));
	grass_5->SetTransform(Matrix4::Translation(Vector3(850, 75, 300)));
	grass_5->SetTransform(grass_5->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_5);

	grass_6 = new SceneNode(grassmesh);
	grass_6->SetModelScale(Vector3(30, 30, 30));
	grass_6->SetTransform(Matrix4::Translation(Vector3(1050, 90, 350)));
	grass_6->SetTransform(grass_6->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_6);

	grass_7 = new SceneNode(grassmesh);
	grass_7->SetModelScale(Vector3(30, 30, 30));
	grass_7->SetTransform(Matrix4::Translation(Vector3(1200, 90, 150)));
	grass_7->SetTransform(grass_7->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_7);

	grass_8 = new SceneNode(grassmesh);
	grass_8->SetModelScale(Vector3(30, 30, 30));
	grass_8->SetTransform(Matrix4::Translation(Vector3(1200, 90, 500)));
	grass_8->SetTransform(grass_8->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_8);

	grass_9 = new SceneNode(grassmesh);
	grass_9->SetModelScale(Vector3(30, 30, 30));
	grass_9->SetTransform(Matrix4::Translation(Vector3(1200, 90, 300)));
	grass_9->SetTransform(grass_9->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_9);

	grass_10 = new SceneNode(grassmesh);
	grass_10->SetModelScale(Vector3(30, 30, 30));
	grass_10->SetTransform(Matrix4::Translation(Vector3(1000, 0, 150)));
	grass_10->SetTransform(grass_10->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_10);

	grass_11 = new SceneNode(grassmesh);
	grass_11->SetModelScale(Vector3(30, 30, 30));
	grass_11->SetTransform(Matrix4::Translation(Vector3(750, 0, 500)));
	grass_11->SetTransform(grass_11->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_11);

	grass_12 = new SceneNode(grassmesh);
	grass_12->SetModelScale(Vector3(30, 30, 30));
	grass_12->SetTransform(Matrix4::Translation(Vector3(950, 0, 700)));
	grass_12->SetTransform(grass_12->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_12);

	grass_13 = new SceneNode(grassmesh);
	grass_13->SetModelScale(Vector3(30, 30, 30));
	grass_13->SetTransform(Matrix4::Translation(Vector3(1500, 0, -100)));
	grass_13->SetTransform(grass_13->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_13);

	grass_14 = new SceneNode(grassmesh);
	grass_14->SetModelScale(Vector3(30, 30, 30));
	grass_14->SetTransform(Matrix4::Translation(Vector3(1400, 0, 300)));
	grass_14->SetTransform(grass_14->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_14);

	grass_15 = new SceneNode(grassmesh);
	grass_15->SetModelScale(Vector3(30, 30, 30));
	grass_15->SetTransform(Matrix4::Translation(Vector3(1480, 0, 100)));
	grass_15->SetTransform(grass_15->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_15);

	grass_16 = new SceneNode(grassmesh);
	grass_16->SetModelScale(Vector3(30, 30, 30));
	grass_16->SetTransform(Matrix4::Translation(Vector3(1300, 0, -100)));
	grass_16->SetTransform(grass_16->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_16);

	grass_17 = new SceneNode(grassmesh);
	grass_17->SetModelScale(Vector3(30, 30, 30));
	grass_17->SetTransform(Matrix4::Translation(Vector3(1350, 0, 700)));
	grass_17->SetTransform(grass_17->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_17);

	grass_18 = new SceneNode(grassmesh);
	grass_18->SetModelScale(Vector3(30, 30, 30));
	grass_18->SetTransform(Matrix4::Translation(Vector3(1450, 0, 500)));
	grass_18->SetTransform(grass_18->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_18);

	grass_19 = new SceneNode(grassmesh);
	grass_19->SetModelScale(Vector3(30, 30, 30));
	grass_19->SetTransform(Matrix4::Translation(Vector3(1200, 0, 1000)));
	grass_19->SetTransform(grass_19->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_19);

	grass_20 = new SceneNode(grassmesh);
	grass_20->SetModelScale(Vector3(30, 30, 30));
	grass_20->SetTransform(Matrix4::Translation(Vector3(1100, 0, 800)));
	grass_20->SetTransform(grass_20->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(grass_20);

#pragma region task 7

	body->SetBoundingRadius(15.0f);
	grass_1->SetBoundingRadius(5.0f);

	grass_2->SetBoundingRadius(18.0f);
	grass_3->SetBoundingRadius(18.0f);

	grass_4->SetBoundingRadius(18.0f);
	grass_5->SetBoundingRadius(18.0f);

#pragma endregion

}
float numdt = 0;
int a = 0;
void Grass::Update(float dt)
{
	//transform = transform * Matrix4::Rotation(30.0f * dt, Vector3(0, 1, 0));
	numdt = dt + numdt;
	a = numdt / 3;
	if (a % 2 == 1) {
		//tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(-10.0f * dt, Vector3(0, 1, 0)));
		//tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(-10.0f * dt, Vector3(1, 0, 0)));
		grass_1->SetTransform(grass_1->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_2->SetTransform(grass_2->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_3->SetTransform(grass_3->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_4->SetTransform(grass_4->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_5->SetTransform(grass_5->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_6->SetTransform(grass_6->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_7->SetTransform(grass_7->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_8->SetTransform(grass_8->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_9->SetTransform(grass_9->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_10->SetTransform(grass_10->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_11->SetTransform(grass_11->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_12->SetTransform(grass_12->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_13->SetTransform(grass_13->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_14->SetTransform(grass_14->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_15->SetTransform(grass_15->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_16->SetTransform(grass_16->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_17->SetTransform(grass_17->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_18->SetTransform(grass_18->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_19->SetTransform(grass_19->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		grass_20->SetTransform(grass_20->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
	}
	else {
		//tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(10.0f * dt, Vector3(0, 1, 0)));
		//tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(10.0f * dt, Vector3(1, 0, 0)));
		grass_1->SetTransform(grass_1->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_2->SetTransform(grass_2->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_3->SetTransform(grass_3->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_4->SetTransform(grass_4->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_5->SetTransform(grass_5->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_6->SetTransform(grass_6->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_7->SetTransform(grass_7->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_8->SetTransform(grass_8->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_9->SetTransform(grass_9->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_10->SetTransform(grass_10->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_11->SetTransform(grass_11->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_12->SetTransform(grass_12->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_13->SetTransform(grass_13->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_14->SetTransform(grass_14->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_15->SetTransform(grass_15->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_16->SetTransform(grass_16->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_17->SetTransform(grass_17->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_18->SetTransform(grass_18->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_19->SetTransform(grass_19->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		grass_20->SetTransform(grass_20->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
	}


	SceneNode::Update(dt);
}
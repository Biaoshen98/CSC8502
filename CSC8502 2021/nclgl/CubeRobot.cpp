#include "CubeRobot.h"

CubeRobot::CubeRobot(Mesh* cube)
{
	SetMesh(cube);

	SceneNode* body = new SceneNode(cube);		
	body->SetModelScale(Vector3(30, 30, 30));
	body->SetTransform(Matrix4::Translation(Vector3(2050, 500, 2100)));
	AddChild(body);

	tree_1 = new SceneNode(cube);				
	tree_1->SetModelScale(Vector3(30, 30, 30));
	tree_1->SetTransform(Matrix4::Translation(Vector3(1400, -200, 10)));
	tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_1);

	tree_2 = new SceneNode(cube);				
	tree_2->SetModelScale(Vector3(30, 30, 30));
	tree_2->SetTransform(Matrix4::Translation(Vector3(1400, -200, 150)));
	//tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(-10.0f*2.5, Vector3(1, 0, 0)));
	tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_2);

	tree_3 = new SceneNode(cube);			
	tree_3->SetModelScale(Vector3(30, 30, 30));
	tree_3->SetTransform(Matrix4::Translation(Vector3(1400, -200, 250)));
	tree_3->SetTransform(tree_3->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_3);

	tree_4 = new SceneNode(cube);				
	tree_4->SetModelScale(Vector3(30, 30, 30));
	tree_4->SetTransform(Matrix4::Translation(Vector3(1400, -200, 400)));
	tree_4->SetTransform(tree_4->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_4);

	tree_5 = new SceneNode(cube);			
	tree_5->SetModelScale(Vector3(30, 30, 30));
	tree_5->SetTransform(Matrix4::Translation(Vector3(1400, -200, 300)));
	tree_5->SetTransform(tree_5->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_5);

	tree_6 = new SceneNode(cube);			
	tree_6->SetModelScale(Vector3(30, 30, 30));
	tree_6->SetTransform(Matrix4::Translation(Vector3(1400, -200, 350)));
	tree_6->SetTransform(tree_6->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_6);

	tree_7 = new SceneNode(cube);			
	tree_7->SetModelScale(Vector3(30, 30, 30));
	tree_7->SetTransform(Matrix4::Translation(Vector3(1400, -200, 150)));
	tree_7->SetTransform(tree_7->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_7);

	tree_8 = new SceneNode(cube);			
	tree_8->SetModelScale(Vector3(30, 30, 30));
	tree_8->SetTransform(Matrix4::Translation(Vector3(1400, -200, 500)));
	tree_8->SetTransform(tree_8->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_8);

	tree_9 = new SceneNode(cube);			
	tree_9->SetModelScale(Vector3(30, 30, 30));
	tree_9->SetTransform(Matrix4::Translation(Vector3(1400, -200, 300)));
	tree_9->SetTransform(tree_9->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_9);

	tree_10 = new SceneNode(cube);
	tree_10->SetModelScale(Vector3(30, 30, 30));
	tree_10->SetTransform(Matrix4::Translation(Vector3(1400, -200, 150)));
	tree_10->SetTransform(tree_10->GetTransform() * Matrix4::Rotation(5.0f * 0.5, Vector3(1, 0, 0)));
	body->AddChild(tree_10);
}
float numdt = 0;
int a = 0;
void CubeRobot::Update(float dt)
{
	//transform = transform * Matrix4::Rotation(30.0f * dt, Vector3(0, 1, 0));
	numdt = dt + numdt;
		a = numdt/3;
	if (a%2==1) {
		//tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(-10.0f * dt, Vector3(0, 1, 0)));
		//tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(-10.0f * dt, Vector3(1, 0, 0)));
		tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_3->SetTransform(tree_3->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_4->SetTransform(tree_4->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_5->SetTransform(tree_5->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_6->SetTransform(tree_6->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_7->SetTransform(tree_7->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_8->SetTransform(tree_8->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_9->SetTransform(tree_9->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
		tree_10->SetTransform(tree_10->GetTransform() * Matrix4::Rotation(2.5f * dt, Vector3(1, 0, 0)));
	}
	else {
		//tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(10.0f * dt, Vector3(0, 1, 0)));
		//tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(10.0f * dt, Vector3(1, 0, 0)));
		tree_1->SetTransform(tree_1->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_2->SetTransform(tree_2->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_3->SetTransform(tree_3->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_4->SetTransform(tree_4->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_5->SetTransform(tree_5->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_6->SetTransform(tree_6->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_7->SetTransform(tree_7->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_8->SetTransform(tree_8->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_9->SetTransform(tree_9->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
		tree_10->SetTransform(tree_10->GetTransform() * Matrix4::Rotation(-2.5f * dt, Vector3(1, 0, 0)));
	}


	SceneNode::Update(dt);
}
#pragma once
#include "../nclgl/OGLRenderer.h"

class Camera;
class Mesh;

class Renderer :public OGLRenderer
{
public:
	Renderer(Window& parent);
	~Renderer(void);

	void UpdateScene(float dt)	override;
	void RenderScene()			override;

protected:
	void DrawShadowScene();

	GLuint	shadowTex;
	GLuint	shadowFBO;

	GLuint	sceneDiffuse;

	Shader* sceneShader;
	Shader* shadowShader;

	vector<Mesh*>	sceneMeshes;
	vector<Matrix4> sceneTransforms;

	Camera* camera;
	Light*	light;
};
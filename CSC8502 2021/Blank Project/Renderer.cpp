#include "Renderer.h"
#include "../nclgl/Light.h"
#include "../nclgl/HeightMap.h"
#include "../nclgl/Shader.h"
#include "../nclgl/Camera.h"
#include "../nclgl/MeshAnimation.h"
#include "../nclgl/MeshMaterial.h"
#include "../nclgl/Window.h"

const int LIGHT_NUM = 32;
Renderer::Renderer(Window& parent) : OGLRenderer(parent)
{
	//import picture and model material files
	sphere = Mesh::LoadFromMeshFile("Sphere.msh");
	quad = Mesh::GenerateQuad();
	cube = Mesh::LoadFromMeshFile("tree_e.msh");
	heightMap = new HeightMap(TEXTUREDIR"newmap9.png");
	waterTex = SOIL_load_OGL_texture(TEXTUREDIR"water.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	waterBump = SOIL_load_OGL_texture(TEXTUREDIR"waterbump.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	earthTex = SOIL_load_OGL_texture(TEXTUREDIR"newmap9colour.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	earthBump = SOIL_load_OGL_texture(TEXTUREDIR"MylandDOT3.JPG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	cubeMap = SOIL_load_OGL_cubemap(TEXTUREDIR"skyed_east.jpg", TEXTUREDIR"skyed_west.jpg",
		TEXTUREDIR"skyed_up.jpg", TEXTUREDIR"skyed_down.jpg",
		TEXTUREDIR"skyed_south.jpg", TEXTUREDIR"skyed_north.jpg",
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	if (!earthTex || !earthBump || !cubeMap || !waterTex)
		return;

	SetTextureRepeating(earthTex, true);
	SetTextureRepeating(earthBump, true);
	SetTextureRepeating(waterTex, true);
	SetTextureRepeating(waterBump, true);

	reflectShader = new Shader("reflectVertex.glsl", "reflectFragment.glsl");
	skyboxShader = new Shader("skyboxVertex.glsl", "skyboxFragment.glsl");
	lightShader = new Shader("bumpVertex.glsl", "bumpFragment.glsl");
	robotshader = new Shader("sceneVertex.glsl", "sceneFragment.glsl");
	anishader = new Shader("skinningVertex.glsl", "texturedFragment.glsl");

	if (!reflectShader->LoadSuccess() || !skyboxShader->LoadSuccess()
		|| !lightShader->LoadSuccess() || !robotshader->LoadSuccess()
		|| !anishader->LoadSuccess())
		return;

	aniMesh = Mesh::LoadFromMeshFile("Role_T.msh");
	anim = new  MeshAnimation("Role_T.anm");
	material = new  MeshMaterial("Role_T.mat");

	for (int i = 0; i < aniMesh->GetSubMeshCount(); ++i) {
		const  MeshMaterialEntry* matEntry = material->GetMaterialForLayer(i);

		const  string* filename = nullptr;
		matEntry->GetEntry("Diffuse", &filename);
		string  path = TEXTUREDIR + *filename;
		GLuint  texID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
		matTexture.emplace_back(texID);
	}
	currentFrame = 0;
	frameTime = 0.0f;

	Vector3 heightmapSize = heightMap->GetHeightMapSize();

	camera = new Camera(-45.0f, -135.0f, heightmapSize * Vector3(0.0f, 15.0f, 0.0f));
	camera_1 = new Camera(-45.0f, -135.0f, heightmapSize * Vector3(0.5f, 5.0f, 0.0f));
	camera_2 = new Camera(-45.0f, -135.0f, heightmapSize * Vector3(0.0f, 5.0f, 0.5f));
	camera_3 = new Camera(-45.0f, -135.0f, heightmapSize * Vector3(0.0f, 25.0f, 0.0f));

	light = new Light(heightmapSize * Vector3(0.5f, 15.0f, 0.5f), Vector4(1, 1, 1, 1), heightmapSize.x*2);

	//from tutorial 15
	pointLights = new Light[LIGHT_NUM];

	for (int i = 0; i < LIGHT_NUM; ++i)
	{
		Light& l = pointLights[i];
		l.SetPosition(Vector3(rand() % (int)heightmapSize.x, 150.0f, rand() % (int)heightmapSize.z));
		l.SetColour(Vector4(0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			0.5f + (float)(rand() / (float)RAND_MAX),
			1));
		l.SetRadius(500.0f + (rand() % 250));
	}


	projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);

	root = new SceneNode();
	root->AddChild(new CubeRobot(cube));
	DrawTree();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	waterRotate = 0.0f;
	waterCycle = 0.0f;

	//from tutorial 15
	sceneShader = new Shader("bumpVertex.glsl", "bufferFragment.glsl");
	pointlightShader = new Shader("pointlightVert.glsl", "pointlightFrag.glsl");
	combineShader = new Shader("combineVert.glsl", "combineFrag.glsl");

	if (!sceneShader->LoadSuccess() || !pointlightShader->LoadSuccess() || !combineShader->LoadSuccess())
		return;

	glGenFramebuffers(1, &bufferFBO);
	glGenFramebuffers(1, &pointLightFBO);

	GLenum buffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

	//Generate scene depth texture
	GenerateScreenTexture(bufferDepthTex, true);
	GenerateScreenTexture(bufferColourTex);
	GenerateScreenTexture(bufferNormalTex);
	GenerateScreenTexture(lightDiffuseTex);
	GenerateScreenTexture(lightSpecularTex);

	//Attach them to FBOs
	glBindFramebuffer(GL_FRAMEBUFFER, bufferFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferColourTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bufferNormalTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, bufferDepthTex, 0);
	glDrawBuffers(2, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, pointLightFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, lightDiffuseTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, lightSpecularTex, 0);
	glDrawBuffers(2, buffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	init = true;
}

Renderer ::~Renderer(void)
{
	delete sceneShader;
	delete combineShader;
	delete pointlightShader;
	delete camera;
	delete camera_1;
	delete camera_2;
	delete camera_3;
	delete heightMap;
	delete quad;
	delete sphere;
	delete reflectShader;
	delete skyboxShader;
	delete lightShader;
	delete light;
	delete root;
	delete robotshader;
	delete cube;
	delete aniMesh;
	delete anim;
	delete material;
	delete anishader;
	delete[] pointLights;
	//from tutorial 15
	glDeleteTextures(1, &bufferColourTex);
	glDeleteTextures(1, &bufferNormalTex);
	glDeleteTextures(1, &bufferDepthTex);
	glDeleteTextures(1, &lightDiffuseTex);
	glDeleteTextures(1, &lightSpecularTex);
	glDeleteFramebuffers(1, &bufferFBO);
	glDeleteFramebuffers(1, &pointLightFBO);
}

//from tutorial 15.
void Renderer::GenerateScreenTexture(GLuint& into, bool depth)
{
	glGenTextures(1, &into);
	glBindTexture(GL_TEXTURE_2D, into);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLuint format = depth ? GL_DEPTH_COMPONENT24 : GL_RGBA8;
	GLuint type = depth ? GL_DEPTH_COMPONENT : GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, type, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::UpdateScene(float dt)
{
	camera->UpdateCamera(dt);
	camera_1->UpdateCamera(dt);
	camera_2->UpdateCamera(dt);
	camera_3->UpdateCamera(dt);

	light->Updatelight(dt);

	waterRotate += dt * 2.0f;	//2 degrees a second
	waterCycle += dt * 0.25f;	//10 units a second

	root->Update(dt);

	frameTime -= dt;
	while (frameTime < 0.0f) {
		currentFrame = (currentFrame + 1) % anim->GetFrameCount();
		frameTime += 1.0f / anim->GetFrameRate();
	}

}

bool cameramode = 0;

void Renderer::RenderScene()
{
	//here, change camera location show 4 different scene.
	if (!changecamera)
	{
		//use Tutorial 15 code to show deferred shading by if loop.
		if (!deferred) {
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, width, height);
			projMatrix = Matrix4::Perspective(1.0f, 15000.0f, (float)width / (float)height, 45.0f);
			viewMatrix = camera->BuildViewMatrix();
			DrawSkybox();
			DrawHeightmap();
			DrawWater();
			DrawAnimation();
			BindShader(robotshader);
			UpdateShaderMatrices();
			glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 1);
			DrawNode(root);
		}
		if (deferred) {
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, width, height);
			viewMatrix = camera->BuildViewMatrix();
			//DrawSkybox();
			//DrawHeightmap();
			//DrawWater();
			//DrawAnimation();
			//BindShader(robotshader);
			//UpdateShaderMatrices();
			FillBuffers();
			DrawPointLights();
			CombineBuffers();
			//glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 1);
			//DrawNode(root);
		}
	}
	if (changecamera) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, width / 2, height / 2);
		viewMatrix = camera->BuildViewMatrix();
		DrawSkybox();
		DrawHeightmap();
		DrawWater();
		DrawAnimation();
		BindShader(robotshader);
		UpdateShaderMatrices();
		glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 1);
		DrawNode(root);

		glViewport(width / 2, 0, width / 2, height / 2);
		viewMatrix = camera_1->BuildViewMatrix();
		DrawSkybox();
		DrawHeightmap();
		DrawWater();
		DrawAnimation();
		BindShader(robotshader);
		UpdateShaderMatrices();
		glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 1);
		DrawNode(root);

		glViewport(0, height / 2, width / 2, height / 2);
		viewMatrix = camera_2->BuildViewMatrix();
		DrawSkybox();
		DrawHeightmap();
		DrawWater();
		DrawAnimation();
		BindShader(robotshader);
		UpdateShaderMatrices();
		glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 1);
		DrawNode(root);

		glViewport(width / 2, height / 2, width / 2, height / 2);
		viewMatrix = camera_3->BuildViewMatrix();
		DrawSkybox();
		DrawHeightmap();
		DrawWater();
		DrawAnimation();
		BindShader(robotshader);
		UpdateShaderMatrices();
		glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 1);
		DrawNode(root);
	}
	
}

void Renderer::DrawSkybox()
{
	glDepthMask(GL_FALSE);

	BindShader(skyboxShader);
	UpdateShaderMatrices();

	quad->Draw();
	glDepthMask(GL_TRUE);
}

void Renderer::DrawHeightmap()
{
	BindShader(lightShader);
	SetShaderLight(*light);
	glUniform3fv(glGetUniformLocation(lightShader->GetProgram(), "cameraPos"), 1, (float*)& camera->GetPosition());

	glUniform1i(glGetUniformLocation(lightShader->GetProgram(), "diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earthTex);

	glUniform1i(glGetUniformLocation(lightShader->GetProgram(), "bumpTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, earthBump);


	modelMatrix.ToIdentity();		//New
	textureMatrix.ToIdentity();		//New

	UpdateShaderMatrices();

	heightMap->Draw();
}

void Renderer::DrawWater()
{
	BindShader(reflectShader);
	glUniform3fv(glGetUniformLocation(reflectShader->GetProgram(), "cameraPos"), 1, (float*)& camera->GetPosition());

	glUniform1i(glGetUniformLocation(reflectShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(reflectShader->GetProgram(), "cubeTex"), 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, waterTex);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	Vector3 hSize = heightMap->GetHeightMapSize();
	hSize = hSize * Vector3(1, 0.82, 1);

	modelMatrix = Matrix4::Translation(hSize * 0.5f) *
		Matrix4::Scale(hSize * 6.0f) *
		Matrix4::Rotation(90, Vector3(1, 0, 0));

	textureMatrix = Matrix4::Translation(Vector3(waterCycle, 0.0f, waterCycle)) *
		Matrix4::Scale(Vector3(10, 10, 10)) *
		Matrix4::Rotation(waterRotate, Vector3(0, 0, 1));

	UpdateShaderMatrices();/*SetShaderLight(*light);
						   No lighting in this shader*/
	quad->Draw();
}
void Renderer::DrawNode(SceneNode* n)
{
	if (n->GetMesh())
	{
		BindShader(robotshader);
		glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "diffuseTex"), 0);

		Matrix4 model = n->GetWorldTransform() * Matrix4::Scale(n->GetModelScale());
		glUniformMatrix4fv(glGetUniformLocation(robotshader->GetProgram(), "modelMatrix"), 1, false, model.values);

		glUniform4fv(glGetUniformLocation(robotshader->GetProgram(), "nodeColour"), 1, (float*)& n->GetColour());

		glUniform1i(glGetUniformLocation(robotshader->GetProgram(), "useTexture"), 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, treeTex);

		n->Draw(*this);
	}

	for (vector<SceneNode*>::const_iterator i = n->GetChildIteratorStart(); i != n->GetChildIteratorEnd(); i++)
		DrawNode(*i);
}
//import skeletal animation
void Renderer::DrawAnimation() {
	BindShader(anishader);
	glUniform1i(glGetUniformLocation(anishader->GetProgram(), "diffuseTex"), 0);

	//glUniform3fv(glGetUniformLocation(model1shader->GetProgram(), "position"), Vector3(100, 100, 100));
	Vector3 hSize = heightMap->GetHeightMapSize();
	hSize = hSize * Vector3(1, 26, 1);
	modelMatrix = Matrix4::Translation((hSize * 0.5f) - Vector3(150, 3100, 150))
		* Matrix4::Scale(hSize * 0.03f) * Matrix4::Rotation(0, Vector3(1, 0, 0));

	UpdateShaderMatrices();

	vector<Matrix4> frameMatrices;

	const  Matrix4* invBindPose = aniMesh->GetInverseBindPose();
	const  Matrix4* frameData = anim->GetJointData(currentFrame);

	for (unsigned int i = 0; i < aniMesh->GetJointCount(); ++i) {
		frameMatrices.emplace_back(frameData[i] * invBindPose[i]);
	}

	int j = glGetUniformLocation(anishader->GetProgram(), "joints");
	glUniformMatrix4fv(j, frameMatrices.size(), false, (float*)frameMatrices.data());

	for (int i = 0; i < aniMesh->GetSubMeshCount(); ++i) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, matTexture[i]);
		aniMesh->DrawSubMesh(i);
	}
}
//import tree model.
void Renderer::DrawTree() {
	treeTex = SOIL_load_OGL_texture(TEXTUREDIR"tree_e.png", 
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	if (!treeTex)return;
	tree = new SceneNode();
	treeMesh = Mesh::LoadFromMeshFile("tree_e.msh");
	tree->SetMesh(treeMesh);
	tree->SetColour(Vector4(0, 0.6, 0, 1));
	tree->SetModelScale(Vector3(30, 30, 30));
	tree->SetTransform(Matrix4::Translation(Vector3(1500, 600, 1500)));
	tree->SetTexture(treeTex);
	root->AddChild(tree);
}

//tutorial 15
void Renderer::FillBuffers()
{
	glBindFramebuffer(GL_FRAMEBUFFER, bufferFBO);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	BindShader(sceneShader);
	glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(sceneShader->GetProgram(), "bumpTex"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earthTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, earthBump);
	modelMatrix.ToIdentity();
	viewMatrix = camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 10000.0f, (float)width / (float)height, 45.0f);
	UpdateShaderMatrices();
	heightMap->Draw();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawPointLights()
{
	glBindFramebuffer(GL_FRAMEBUFFER, pointLightFBO);
	BindShader(pointlightShader);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_ALWAYS);
	glDepthMask(GL_FALSE);
	glUniform1i(glGetUniformLocation(pointlightShader->GetProgram(), "depthTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bufferDepthTex);
	glUniform1i(glGetUniformLocation(pointlightShader->GetProgram(), "normTex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bufferNormalTex);
	glUniform3fv(glGetUniformLocation(pointlightShader->GetProgram(), "cameraPos"), 1, (float*)&camera->GetPosition());
	glUniform2f(glGetUniformLocation(pointlightShader->GetProgram(), "pixelSize"), 1.0f / width, 1.0f / height);
	Matrix4 invViewProj = (projMatrix * viewMatrix).Inverse();
	glUniformMatrix4fv(glGetUniformLocation(pointlightShader->GetProgram(), "inverseProjView"), 1, false, invViewProj.values);
	UpdateShaderMatrices();
	for (int i = 0; i < LIGHT_NUM; i++)
	{
		Light& l = pointLights[i];
		SetShaderLight(l);
		sphere->Draw();
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glClearColor(0.2f, 0.2f, 0.2f, 1);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::CombineBuffers()
{
	BindShader(combineShader);
	modelMatrix.ToIdentity();
	viewMatrix.ToIdentity();
	projMatrix.ToIdentity();
	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(combineShader->GetProgram(), "diffuseTex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bufferColourTex);
	glUniform1i(glGetUniformLocation(combineShader->GetProgram(), "diffuseLight"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightDiffuseTex);
	glUniform1i(glGetUniformLocation(combineShader->GetProgram(), "specularLight"), 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, lightSpecularTex);
	quad->Draw();
}
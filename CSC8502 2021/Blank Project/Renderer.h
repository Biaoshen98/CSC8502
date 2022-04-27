#pragma once
#include "../nclgl/OGLRenderer.h"
#include "../nclgl/CubeRobot.h"

class Camera;
class Shader;
class HeightMap;
class CubeRobot;
class Mesh;
class MeshAnimation;
class MeshMaterial;
class Grass;


class Renderer : public OGLRenderer
{
public:
	Renderer(Window& parent);
	~Renderer(void);

	void RenderScene()			override;
	void UpdateScene(float dt)	override;
	bool        changecamera = false;
	bool        deferred = false;
protected:
	void		DrawHeightmap();
	void		DrawWater();
	void		DrawSkybox();
	void        DrawAnimation();
	void		DrawTree();

	void DrawNode(SceneNode* n);

	void FillBuffers();			//G-Buffer Fill Render Pass
	void DrawPointLights();		//Lighting Render Pass
	void CombineBuffers();		//Combination Render Pass

	void GenerateScreenTexture(GLuint& into, bool depth = false);

	Shader* sceneShader;		//Shader to fill GBuffers
	Shader* pointlightShader;	//Shader to calculate lighting
	Shader* combineShader;		//Shader to stick it all together



	Shader* lightShader;
	Shader* reflectShader;
	Shader* skyboxShader;
	Shader* robotshader;
	Shader* grassshader;
	Shader* anishader;

	SceneNode* root;
	SceneNode* tree;

	HeightMap* heightMap;

	Mesh* quad;
	Mesh* cube;
	Mesh* aniMesh;
	Mesh* treeMesh;
	Mesh* sphere;				//Light volume

	MeshAnimation* anim;
	MeshMaterial* material;
	vector<GLuint>	matTexture;

	Light* light;
	Light* pointLights;			//Array of lighting data

	Camera* camera;
	Camera* camera_1;
	Camera* camera_2;
	Camera* camera_3;

	GLuint		cubeMap;
	GLuint		waterTex;
	GLuint		waterBump;
	GLuint		earthTex;
	GLuint		earthBump;
	GLuint		treeTex;
	GLuint bufferFBO;			//FBO for G-Buffer pass
	GLuint bufferColourTex;		//Albedo goes here
	GLuint bufferNormalTex;		//Normals go here
	GLuint bufferDepthTex;		//Depth goes here

	GLuint pointLightFBO;		//FBO for lighting pass
	GLuint lightDiffuseTex;		//Store diffuse lighting
	GLuint lightSpecularTex;	//Store specular lighting

	float		waterRotate;
	float		waterCycle;
	int		currentFrame;
	float	frameTime;
};
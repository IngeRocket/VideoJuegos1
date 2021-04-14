////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "terrainclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "fontshaderclass.h"
#include "textclass.h"
#include "terrainshaderclass.h"
#include "watershaderclass.h"
#include "lightclass.h"
#include "skydomeClass.h"
#include "skydomeshaderclass.h"
#include "billboardclass.h"
#include "billboardshaderclass.h"
#include "model.h"
#include "groupshaderclass.h"
#include "sphereclass.h"
#include "diffuseshaderclass.h"
#include "enemy.h"
#include "Random.h"
////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();
	void ResertGame();
	void ColisionTerreno(float X, float Y, float Z);
	int indices();
	int subindice;
private:
	bool HandleInput(float);
	bool RenderGraphics();
	int vidas;
	int m_projectileCount;
	vector <D3DXVECTOR3> m_projectilePos;
	vector <D3DXVECTOR3> m_projectileRot;


	vector <D3DXVECTOR3> m_projectilePos2;
	vector <D3DXVECTOR3> m_projectileRot2;
	int m_projectileCount2;
private:
	Random*Sorteo;
	InputClass* m_Input;
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TerrainClass* m_Terrain, *m_Water;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	FontShaderClass* m_FontShader;
	TextClass* m_Text;
	TerrainShaderClass* m_TerrainShader;
	SkydomeShaderClass* m_SkydomeShader;
	WaterShaderClass* m_WaterShader;
	BillboardShaderClass* m_BillboardShader;
	LightClass* m_Light;
	ModelClass* m_Skydome, *m_Billboard[4]; // , *m_Projectile;
	DiffuseShaderClass *m_DiffuseShader;
	Model* m_Principal, *m_Cup, *m_canion, *m_wheels, *m_Projectile, *m_Projectile2, *m_palm;
	Model*m_enemyRP, *m_enemyRB;
	Model*m_barril, *m_botella, *m_cofre, *m_key;
	GroupShaderClass* m_GroupShader;
	BoundingSphere* globalSphere;
	BoundingSphere* EnemyRedSphere;
	BoundingSphere* EnemyBlueSphere;
	BoundingSphere* EnemyPurpleSphere;
	BoundingSphere* EnemyRedRange, *keyRange[3];
	BoundingSphere*CambioColor[3];
	BoundingSphere*ColBarril[3];
	BoundingSphere*SurtirGolpe[3];
	//BoundingSphere*PowerSphere;
	bool bolColBarril[3], keyPosition[3];
	enemy*Morado;
	enemy*Rojo;
	enemy*Azul;
	//bool golpear;
	bool bolBotella, bolkey;
	float rotacion;
	bool powerUp;
	bool RojoDefeat;
	bool AzulDefeat;
	bool MoradoDefeat;
	bool Cofre = 0;
};

#endif
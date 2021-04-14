#ifndef _ENEMY_
#define _ENEMY_
#include "model.h"
#include "d3dclass.h"
#include "lightclass.h"
#include "cameraclass.h"
#include "groupshaderclass.h"
enum Colores {
	rojo, azul, morado

};

class enemy
{
private:
	int vidas = 3;
	Model*m_enemyRP, *m_enemyRB;
	//D3DMATRIX TranslateM, RotateM, Mmatrix;
	bool B_B_max[8];
	float B_B_angle[6];
	void Movimiento();
	bool golpear;
	float posX, posY, posZ;
	float ang = 0;
	D3DXMATRIX en_r_body0_trans, en_r_body0_rotate, en_M_b0;
	bool impacto;
	bool caida;
	bool levantarse;
	bool existo;
	
public:
	enemy(D3DClass*m_Direct3D, Colores Color, float X, float Y, float Z, float angulo);
	void SetAttack(bool golpe);
	bool Dibuja(D3DClass*m_Direct3D, CameraClass* camara,LightClass*luz,D3DXMATRIX viewMatrix, D3DXMATRIX ProjectionMatrix, GroupShaderClass* m_GroupShader);
	bool Colision(Model*objeto, int opcion, BoundingSphere*esfera);
	void ResetEnemy();
	int GetVidas();
	float CalculaAngulo(float X, float Y, float Z);
	~enemy();
	bool vivo();
	void EnemyCaida();
	void AutoAtack();
	bool evalua();
};



#endif
#include "enemy.h"

struct Puntos {
	float X = 0;
	float Y = 0;
	float Z = 0;
};

enemy::enemy(D3DClass*m_Direct3D, Colores Color, float X , float Y , float Z, float angulo)
{
	posX = X;
	posY = Y;
	posZ = Z;
	caida = false;
	existo = true;
	//ang = angulo;
	D3DXMatrixTranslation(&en_r_body0_trans, posX, posY, posZ);
	//D3DXMatrixRotationY(&en_r_body0_rotate, ang);
	B_B_max[0] = B_B_max[1] = B_B_max[2] = B_B_max[3] = B_B_max[4] = B_B_max[5] = B_B_max[6] = B_B_max[7] = false;
	B_B_angle[0] = B_B_angle[1] = B_B_angle[2] = B_B_angle[3] = B_B_angle[4] = B_B_angle[5] = 0.0f;
	golpear = false;

	m_enemyRP=0; 
	m_enemyRB=0;
	if (Color == rojo) {
		m_enemyRB = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/red", "p_body.obj");
		m_enemyRP = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/red", "p_punta.obj");
	}
	else {
		if (Color == azul) {
			m_enemyRB = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/blue", "p_body.obj");
			m_enemyRP = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/blue", "p_punta.obj");
		}
		else {
			m_enemyRB = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/purple", "p_body.obj");
			m_enemyRP = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/purple", "p_punta.obj");
		}
	}


}


enemy::~enemy()
{
}

bool enemy::Dibuja(D3DClass*m_Direct3D, CameraClass* camara, LightClass*luz, D3DXMATRIX viewMatrix, D3DXMATRIX ProjectionMatrix, GroupShaderClass* m_GroupShader){
	Movimiento();
	
	if (existo) {
		//D3DXMatrixRotationY(&en_r_body0_rotate, ang);
		D3DXMatrixRotationYawPitchRoll(&en_r_body0_rotate,ang,0,0);
		en_M_b0 = en_r_body0_rotate * en_r_body0_trans;
		m_enemyRB->UpdateColliders(en_M_b0);
		bool result = false;
		for (auto &group : *m_enemyRB->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b0, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}

		//enemy body[1]
		D3DXMATRIX en_r_body1_trans, en_r_body1_rotate, en_M_b1;
		D3DXMatrixTranslation(&en_r_body1_trans, 0.0f, 3.4f, 0.0f);
		D3DXMatrixRotationY(&en_r_body1_rotate, 0);
		D3DXMatrixRotationX(&en_r_body1_rotate, -B_B_angle[0]);
		en_M_b1 = (en_r_body1_rotate * en_r_body1_trans)*(en_M_b0);
		for (auto &group : *m_enemyRB->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b1, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}

		//enemy body[2]
		D3DXMATRIX en_r_body_2_trans, en_r_body_2_rotate, en_M_b2;
		D3DXMatrixTranslation(&en_r_body_2_trans, 0.0f, 3.4f, 0.0f);
		D3DXMatrixRotationY(&en_r_body_2_rotate, 0);
		D3DXMatrixRotationX(&en_r_body_2_rotate, -B_B_angle[1]);
		en_M_b2 = (en_r_body_2_rotate * en_r_body_2_trans)*(en_M_b1);
		for (auto &group : *m_enemyRB->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b2, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}

		//enemy body[3]
		D3DXMATRIX en_r_body_3_trans, en_r_body_3_rotate, en_M_b3;
		D3DXMatrixTranslation(&en_r_body_3_trans, 0.0f, 3.4f, 0.0f);
		D3DXMatrixRotationY(&en_r_body_3_rotate, 0);
		D3DXMatrixRotationX(&en_r_body_3_rotate, -B_B_angle[2]);
		en_M_b3 = (en_r_body_3_rotate * en_r_body_3_trans)*(en_M_b2);
		for (auto &group : *m_enemyRB->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b3, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}

		//enemy body[4]
		D3DXMATRIX en_r_body_4_trans, en_r_body_4_rotate, en_M_b4;
		D3DXMatrixTranslation(&en_r_body_4_trans, 0.0f, 3.4f, 0.0f);
		D3DXMatrixRotationY(&en_r_body_4_rotate, 0);
		D3DXMatrixRotationX(&en_r_body_4_rotate, -B_B_angle[3]);
		en_M_b4 = (en_r_body_4_rotate * en_r_body_4_trans)*(en_M_b3);
		for (auto &group : *m_enemyRB->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b4, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
		//enemy body[5]
		D3DXMATRIX en_r_body_5_trans, en_r_body_5_rotate, en_M_b5;
		D3DXMatrixTranslation(&en_r_body_5_trans, 0.0f, 3.4f, 0.0f);
		D3DXMatrixRotationY(&en_r_body_5_rotate, 0);
		D3DXMatrixRotationX(&en_r_body_5_rotate, -B_B_angle[4]);
		en_M_b5 = (en_r_body_5_rotate * en_r_body_5_trans)*(en_M_b4);
		for (auto &group : *m_enemyRB->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b5, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
		//enemy 1 punta
		D3DXMATRIX en_r_punta_trans, en_r_punta_rotate, en_M_b6;
		D3DXMatrixTranslation(&en_r_punta_trans, 0.0f, 3.8f, 0.0f);
		D3DXMatrixRotationX(&en_r_punta_rotate, -B_B_angle[5]);
		en_M_b6 = (en_r_punta_rotate * en_r_punta_trans) * en_M_b5;
		for (auto &group : *m_enemyRP->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), en_M_b6, viewMatrix, ProjectionMatrix, luz->GetAmbientColor(), luz->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), luz->GetDirection(), camara->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
	}
	
}

void enemy::Movimiento() {
	if (!caida) {
		if (B_B_max[7]) {
			//golpear = true;
		//movimiento rigido
			if (B_B_angle[1] > 0.0)
				B_B_angle[1] -= 0.5f;
			else
				B_B_angle[1] = 0.0f;


			if (B_B_angle[2] > 0.0)
				B_B_angle[2] -= 0.5f;
			else
				B_B_angle[2] = 0.0f;

			if (B_B_angle[3] > 0.0)
				B_B_angle[3] -= 0.5f;
			else
				B_B_angle[3] = 0.0f;

			if (B_B_angle[4] > 0.0)
				B_B_angle[4] -= 0.5f;
			else
				B_B_angle[4] = 0.0f;

			if (B_B_angle[5] > 0.0)
				B_B_angle[5] -= 0.5f;
			else
				B_B_angle[5] = 0.0f;

			//golpe con B_B_max[0]
			B_B_max[6] = true; //se va a levantar al acabar la animacion ataque (volver a iddle)
			if (B_B_angle[0] < 2.0f && B_B_max[6]) {
				B_B_angle[0] += 0.05;
			}
			else {
				B_B_max[7] = false;
				B_B_max[0] = true;
				B_B_max[1] = true;
				B_B_max[2] = true;
				B_B_max[3] = true;
				B_B_max[4] = true;
				B_B_max[5] = true;
				B_B_max[6] = true;
				golpear = false;
			}



		}
		else {
			if (!B_B_max[6]) { //indica iddle
			//si es falso no han llegado a 0.3
				if (!B_B_max[0]) {
					//pieza 0
					if (B_B_angle[0] < 0.3)
						B_B_angle[0] += 0.01;
					else
						B_B_max[0] = true;
//no recibir daño al levantarse
					if (B_B_max[0]) {
						levantarse = false;
					}
				}
				else {
					//pieza 1
					if (!B_B_max[1]) {
						if (B_B_angle[1] < 0.3)
							B_B_angle[1] += 0.01;
						else
							B_B_max[1] = true;
					}
					else {
						//pieza 2
						if (!B_B_max[2]) {
							if (B_B_angle[2] < 0.3)
								B_B_angle[2] += 0.01;
							else
								B_B_max[2] = true;
						}
						else {
							//pieza 3
							if (!B_B_max[3]) {
								if (B_B_angle[3] < 0.3)
									B_B_angle[3] += 0.01;
								else
									B_B_max[3] = true;
							}
							else {
								//pieza 4
								if (!B_B_max[4]) {
									if (B_B_angle[4] < 0.3)
										B_B_angle[4] += 0.01;
									else
										B_B_max[4] = true;
								}
								else {
									//pieza 5
									if (!B_B_max[5]) {
										if (B_B_angle[5] < 0.3)
											B_B_angle[5] += 0.01;
										else
											B_B_max[5] = true;
									}
									else {
										B_B_max[6] = true; //fin de iddle
									}
								}
							}
						}

					}
				}

			}
			else {
				if (B_B_max[5]) {
					//pieza 0
					if (B_B_angle[5] > 0.0f)
						B_B_angle[5] -= 0.20f;
					else
						B_B_max[5] = false;
				}
				else {
					//pieza 1
					if (B_B_max[4]) {
						if (B_B_angle[4] > 0.0f)
							B_B_angle[4] -= 0.20f;
						else
							B_B_max[4] = false;
					}
					else {
						//pieza 2
						if (B_B_max[3]) {
							if (B_B_angle[3] > -0.20f)
								B_B_angle[3] -= 0.01;
							else
								B_B_max[3] = false;
						}
						else {
							//pieza 3
							if (B_B_max[2]) {
								if (B_B_angle[2] > -0.20f)
									B_B_angle[2] -= 0.01;
								else
									B_B_max[2] = false;
							}
							else {
								//pieza 4
								if (B_B_max[1]) {
									if (B_B_angle[1] > -0.20f)
										B_B_angle[1] -= 0.01;
									else
										B_B_max[1] = false;
								}
								else {
									//pieza 5
									if (B_B_max[0]) {
										if (B_B_angle[0] > -0.20f)
											B_B_angle[0] -= 0.01;
										else
											B_B_max[0] = false;
									}
									else {
										B_B_max[6] = false; //comienza iddle de nuevo
									}
								}
							}
						}

					}
				}

			}//fin if iddle bajar
			// fin movimiento iddle de enemigo
		}
	}
	else {
	EnemyCaida();
}
		
}

void enemy::SetAttack(bool golpe) {
	if (golpe) {
		if (!golpear && !B_B_max[7] && !B_B_max[6])
			B_B_max[7] = true;
	}
	else {
		if (!caida && !levantarse) {
			caida = true;
		}
	}
	
}

bool enemy::Colision(Model*objeto, int opcion, BoundingSphere*esfera) {
	bool respuesta = false;
	if (opcion == 0) {
		respuesta = m_enemyRB->Collides(objeto);
		//animacion de golpear objeto
		if (respuesta) {
			if (!golpear && !B_B_max[7] && !B_B_max[6])
				B_B_max[7] = true;
		}	
	}

	return respuesta;
}

void enemy::ResetEnemy() {
	vidas = 3;
	existo = true;
}

int enemy::GetVidas() {
	return vidas;
}

float enemy::CalculaAngulo(float X, float Y, float Z) {
	Puntos U; //modelo
	Puntos V; //camara
	//Puntos P3; //nuevo punto
/*
	//P1.X = posZ;
	//P1.Y = posX;
	//
	//P2.X = X;
	//P2.Y = Y;

	//P3.X = posZ;
	//P3.Y = Y;
	*/
/*
	float DistanciaCO = ((P2.X-P3.X)*(P2.X - P3.X))+((P2.Y - P3.Y)*(P2.Y - P3.Y));
	DistanciaCO = sqrt(DistanciaCO);

	float DistanciaHipotenusa = ((P2.X - P1.X)*(P2.X - P1.X)) +((P2.Y - P1.Y)*(P2.Y - P1.Y));

	float angulo = asinf(DistanciaCO/DistanciaHipotenusa) * 180 / 3.14159265;
	*/
	U.X = posX;
	U.Y = posY;
	U.Z = posZ;

	V.X = X;
	V.Y = Y;
	V.Z = Z;

	//float numerador = (U.X * V.X) + (U.Y * V.Y) + (U.Z * V.Z);
	//float LongitudU= (U.X*U.X) + (U.Y*U.Y) + (U.Z*U.Z); //SIN RAIZ
	//float LongitudV= (V.X*V.X) + (V.Y*V.Y) + (V.Z*V.Z); //SIN RAIZ



	//float angulo = (numerador)/(sqrtf(LongitudU) * sqrtf(LongitudV)); //numero pequeño
	//angulo = (acosf(angulo) * 180) / 3.14159265;
	//ang = angulo;

	float angulo = atan2(U.X - V.X, U.Z - V.Z) * (180.0 / D3DX_PI);
	
		angulo = angulo * 0.0174532925f;
	ang = angulo;
	return angulo;

}

bool enemy::vivo() {
	if (vidas != 0) {
		return true;
	}

	return false;
}

void enemy::EnemyCaida() {
	//movimiento rigido
	if (B_B_angle[1] > 0.0)
		B_B_angle[1] -= 0.5f;
	else
		B_B_angle[1] = 0.0f;


	if (B_B_angle[2] > 0.0)
		B_B_angle[2] -= 0.5f;
	else
		B_B_angle[2] = 0.0f;

	if (B_B_angle[3] > 0.0)
		B_B_angle[3] -= 0.5f;
	else
		B_B_angle[3] = 0.0f;

	if (B_B_angle[4] > 0.0)
		B_B_angle[4] -= 0.5f;
	else
		B_B_angle[4] = 0.0f;

	if (B_B_angle[5] > 0.0)
		B_B_angle[5] -= 0.5f;
	else
		B_B_angle[5] = 0.0f;
	B_B_max[0] = B_B_max[1] = B_B_max[2] = B_B_max[3] = B_B_max[4] = B_B_max[5] = false;


	if (B_B_angle[0] > -2.0f) {
		B_B_angle[0] -= 0.05f;
		caida = true;
	}
	else {
		vidas--;
		if (vidas > 0)
			existo = true;
		else
			existo = false;

		caida = false;
		levantarse = true;
		B_B_max[0] = B_B_max[1] = B_B_max[2] = B_B_max[3] = B_B_max[4] = B_B_max[5] =true;
	}

	//caida completa
	//B_B_angle[0] = -2.0f;
	//impacto = true;
}

void enemy::AutoAtack() {
	if (!golpear && !B_B_max[7] && !B_B_max[6])
		B_B_max[7] = true;
}
bool enemy::evalua() {
	if (B_B_angle[0] > 1.80f && B_B_max[7]) //si ya esta en el rango de ataque y ataque esta activo
		return true;

	return false;
}

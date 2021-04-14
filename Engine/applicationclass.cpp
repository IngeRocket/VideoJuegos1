////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"

enum ultimaTecla{
	adelante,atras,derecha,izquierda
};
bool inmunity = false;
float tiempo = 0.0f;
ultimaTecla K;
float giro = 0.0f;
ApplicationClass::ApplicationClass()
{
	subindice = 0;
	m_Input = 0;
	m_Direct3D = 0;
	m_Camera = 0;
	m_Terrain = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Fps = 0;
	m_Cpu = 0;
	m_FontShader = 0;
	m_Text = 0;
	m_TerrainShader = 0;
	m_Light = 0;
	m_projectileCount = 0;
	m_canion = 0;
	m_wheels = 0;
	m_botella = 0;
	m_barril = 0;
	rotacion=0;
	globalSphere = 0;
	bolBotella = bolkey = false;
	EnemyRedRange = 0;
	Morado=0;
	Rojo = 0;
	Azul = 0;

	EnemyBlueSphere=0;
	EnemyPurpleSphere=0;
	EnemyRedSphere = 0;

	ColBarril[0]=0;
	ColBarril[1] = 0;
	ColBarril[2] = 0;
	bolColBarril[0] = bolColBarril[1]= bolColBarril[2] = false;
	CambioColor[0]=0;
	CambioColor[1]=0;
	CambioColor[2]=0;
	m_cofre = 0;
	m_key = 0;
	keyPosition[0] = keyPosition[1] = keyPosition[2] = false;

}

ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}

ApplicationClass::~ApplicationClass()
{
}

bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	float cameraX, cameraY, cameraZ;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;
	vidas = 3;
	powerUp = false;
	 RojoDefeat	  = false;
	 AzulDefeat	  = false;
	 MoradoDefeat = false;
	 m_projectileCount2 = 0;
	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	cameraX = 41.0f;
	cameraY = 4.0f;
	cameraZ = 88.0f;

	m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	int textureCount = 5;
	WCHAR** filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/terrain/lavatexture1.jpg"; //sustituye blanco de alpha map
	filenames[1] = L"../Engine/data/mapas/terrain/test2.jpg"; //negro
	filenames[2] = L"../Engine/data/mapas/terrain/soil.jpg"; //madera
	filenames[3] = L"../Engine/data/mapas/terrain/test1.jpg"; // cesped
	filenames[4] = L"../Engine/data/mapas/terrain/AlphaMapTerrain.jpg";

	result = m_Terrain->Initialize(m_Direct3D->GetDevice(), "../Engine/data/mapas/terrain/mapa128x128.bmp", filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Water = new TerrainClass;
	if (!m_Water)
	{
		return false;
	}

	// Initialize the terrain object.
	textureCount = 3;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/terrain/WATER1.jpg"; //difusse
	filenames[1] = L"../Engine/data/mapas/terrain/WATER1NM.png";  //normal
	filenames[2] = L"../Engine/data/mapas/terrain/WATER1SM.png"; //specular

	result = m_Water->Initialize(m_Direct3D->GetDevice(), "../Engine/data/mapas/terrain/waterHeightmap.bmp", filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_Skydome = new SkydomeClass;
	if (!m_Skydome)
	{
		return false;
	}

	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/billboards/blackSky.jpg";
	filenames[1] = L"../Engine/data/mapas/billboards/night.jpg";

	// Initialize the model object.
	result = m_Skydome->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Billboard[0] = new BillboardClass;
	if (!m_Billboard[0])
	{
		return false;
	}

	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/billboards/Grass2.png";
	filenames[1] = L"../Engine/data/mapas/billboards/Grass2NormalMap.png";

	// Initialize the model object.
	result = m_Billboard[0]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Billboard[1] = new BillboardClass;
	if (!m_Billboard[1])
	{
		return false;
	}

	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/billboards/grass4.png";
	filenames[1] = L"../Engine/data/mapas/billboards/grass4NormalMap.png";

	// Initialize the model object.
	result = m_Billboard[1]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Billboard[2] = new BillboardClass;
	if (!m_Billboard[2])
	{
		return false;
	}

	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/billboards/PALMERA.png";
	filenames[1] = L"../Engine/data/mapas/billboards/PalmeraNormalMap.png";

	// Initialize the model object.
	result = m_Billboard[2]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	//mis billboards
	//PALMERA
	m_Billboard[3] = new BillboardClass;
	if (!m_Billboard[3])
	{
		return false;
	}
	textureCount = 2;
	filenames = new WCHAR*[textureCount];
	filenames[0] = L"../Engine/data/mapas/terrain/coco.png";
	filenames[1] = L"../Engine/data/mapas/terrain/cocoNormalMap.png";

	result = m_Billboard[3]->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	//fin de mis billboards

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(cameraX, cameraY, cameraZ);

	// Create the fps object.
	m_Fps = new FpsClass;
	if(!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if(!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_Direct3D->GetVideoCardInfo(videoCard, videoMemory);

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_SkydomeShader = new SkydomeShaderClass;
	if (!m_SkydomeShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_SkydomeShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_WaterShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_BillboardShader = new BillboardShaderClass;
	if (!m_BillboardShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_BillboardShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_GroupShader = new GroupShaderClass;
	if (!m_GroupShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_GroupShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_DiffuseShader = new DiffuseShaderClass;
	if (!m_DiffuseShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_DiffuseShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}


	// Create the model object.
	m_Projectile = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/bullet/", "bullet.obj");
	if (!m_Projectile)
	{
		return false;
	}

	m_Projectile2 = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/bomba3ds/", "bomba.obj");
	if (!m_Projectile)
	{
		return false;
	}
	//textureCount = 1;
	//filenames = new WCHAR*[textureCount];
	//filenames[0] = L"../Engine/data/waterDiffuse.jpg";

	// Initialize the model object.
	/*result = m_Projectile->Initialize(m_Direct3D->GetDevice(), filenames, textureCount);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}*/

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, -1.0f, 1.0f);
	
	//m_Cup = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/cup", "cup.obj");
	m_Principal = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/boat", "bote.obj");
	m_canion = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/model_parts/canion", "canion.obj");
	m_wheels = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/model_parts/wheels", "wheels.obj");
	m_enemyRB = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/blue", "p_body.obj");
	m_enemyRP = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/enemy/blue", "p_punta.obj");
	m_botella = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/botella", "botallaOBJ.obj");
	m_barril = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/barril", "barrilOBJ.obj");
	m_cofre = Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/cofre", "cofre.obj");
	m_key	= Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/key", "key.obj");
	m_palm= Model::ObjToModel(m_Direct3D->GetDevice(), "../Engine/data/mapas/palmera", "palm.obj");
	// x 19 z 107
	Morado = new enemy(m_Direct3D, morado,107,5,24,-90);
	Azul = new enemy(m_Direct3D, azul, 27, 5, 24, 90);
	Rojo = new enemy(m_Direct3D, rojo, 101, 5, 97, -90);
	// Turn on the alpha blending before rendering the text.
	m_Direct3D->TurnOnAlphaBlending();
	globalSphere = new BoundingSphere(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f);
	//colisones con proyectiles
	EnemyRedSphere = new BoundingSphere(D3DXVECTOR3(101.0f, 4.0f, 97.0f), 6.0f);
	EnemyBlueSphere = new BoundingSphere(D3DXVECTOR3(27.0f, 4.0f, 24.0f), 6.0f);
	EnemyPurpleSphere = new BoundingSphere(D3DXVECTOR3(107.0f, 4.0f, 24.0f), 6.0f);
	
	//proximidad con enemigos
	CambioColor[0] = new BoundingSphere(D3DXVECTOR3(101.0f, 4.0f, 97.0f), 30.0f);
	CambioColor[1] = new BoundingSphere(D3DXVECTOR3(27.0f, 4.0f, 24.0f), 30.0f);
	CambioColor[2] =  new BoundingSphere(D3DXVECTOR3(107.0f, 4.0f, 24.0f), 30.0f);

	SurtirGolpe[0] = new BoundingSphere(D3DXVECTOR3(101.0f, 4.0f, 97.0f), 17.50f);
	SurtirGolpe[1] = new BoundingSphere(D3DXVECTOR3(27.0f, 4.0f, 24.0f), 17.50f);
	SurtirGolpe[2] = new BoundingSphere(D3DXVECTOR3(107.0f, 4.0f, 24.0f), 17.50f);

	//colisiones con proyectiles
	ColBarril[0] = new BoundingSphere(D3DXVECTOR3(70.0f, 4.0f, 81.0f), 7.0f);
	ColBarril[1] = new BoundingSphere(D3DXVECTOR3(101.0f, 4.0f, 55.0f), 7.0f);
	ColBarril[2] = new BoundingSphere(D3DXVECTOR3(74.0f, 4.0f, 42.0f), 7.0f);

	//referencia de posiciones en base a enemigos
		keyRange[0] = EnemyRedSphere; 
		keyRange[1] = EnemyBlueSphere;
		keyRange[2] = EnemyPurpleSphere;

		//sortear la llave
		Sorteo = new Random();
		int valor = indices();
		keyPosition[valor] = true;
	

	return true;
}

void ApplicationClass::Shutdown()
{
	if (Sorteo) {
		delete Sorteo;
		Sorteo = 0;
	}

	if (Morado) {
		delete Morado;
		Morado = 0;
	}

	if (Azul) {
		delete Azul;
		Azul = 0;
	}

	if (Rojo) {
		delete Rojo;
		Rojo = 0;
	}

	if (EnemyRedRange) {
		delete EnemyRedRange;
		EnemyRedRange = 0;
	}
	// Release the light object.
	if (globalSphere) {
		delete globalSphere;
		globalSphere = 0;
	}

	if (EnemyRedSphere) {
		delete EnemyRedSphere;
		EnemyRedSphere = 0;
	}

	if (EnemyBlueSphere) {
		delete EnemyBlueSphere;
		EnemyBlueSphere = 0;
	}

	if (EnemyPurpleSphere) {
		delete EnemyPurpleSphere;
		EnemyPurpleSphere = 0;
	}

	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the cpu object.
	if(m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if(m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}


	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	

	return;
}

bool ApplicationClass::Frame()
{
	if (giro < 360)
		giro += 0.01f;
	else
		giro = 0.0f;
	
	bool result;

	if (inmunity) {
		tiempo += 0.01;
		if (tiempo >= 1.20f) { //aproximadamente 3 segundos
			tiempo = 0;
			inmunity = false;
			//MessageBox(0, L"Fin de inmunidad", L"Aviso", 0);
		}
	}

	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	// Update the FPS value in the text object.
	result = m_Text->SetFps(m_Fps->GetFps(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}
	
	// Update the CPU usage value in the text object.
	result = m_Text->SetCpu(m_Cpu->GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}

	// Render the graphics.
	result = RenderGraphics();
	if(!result)
	{
		return false;
	}

	return result;
}

bool ApplicationClass::HandleInput(float frameTime)
{
	bool keyDown, result, type;
	float posX, posY, posZ, rotX, rotY, rotZ;
	int mouseX, mouseY;
	

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);


	// Handle the input.
	keyDown = m_Input->IsF2Pressed();
	if (keyDown) {
		ResertGame();
	}

	keyDown = m_Input->IsAPressed();
	m_Position->TurnLeft(keyDown);
	if (keyDown) {
		K = izquierda;
	}
		


	keyDown = m_Input->IsDPressed();
	m_Position->TurnRight(keyDown);
	if (keyDown) {
		K = derecha;
	}



	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);
	if (keyDown) {
		K = adelante;

		if (rotacion <= 0) 
			rotacion = 360;
		else 
			rotacion -= 0.05f;
		
	}

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);
	if (keyDown) {
		K = atras;

		if (rotacion >= 360) 
			rotacion = 0;
		else
			rotacion += 0.05f;
	}

	keyDown = m_Input->IsXPressed();
	m_Position->MoveUpward(keyDown);
	//if (keyDown) {
	//	string s = to_string(vidas);
	//	int len;
	//	int slength = (int)s.length() + 1;
	//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	//	wchar_t* buf = new wchar_t[len];
	//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	//	MessageBox(0, buf, L"VIDAS", 0);
	//	delete buf;
	//}


	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	
	keyDown = m_Input->IsCPressed();
	m_Position->ChangeCameraType(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Position->GetCameraType(type);

	m_Input->GetMouseLocation(mouseX, mouseY);

	// Set the position of the camera.
	m_Terrain->GetHeightAtPosition(posX, posZ, posY);

	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(mouseY, mouseX, 0);
	m_Camera->SetCameraType(type);

	// Update the position values in the text object.
	result = m_Text->SetCameraPosition(posX, posY, posZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Update the rotation values in the text object.
	result = m_Text->SetCameraRotation(rotX, rotY, rotZ, m_Direct3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	keyDown = m_Input->IsLeftClickPressed();

	if (keyDown)
	{//clic normal debe cambiar proyectil modelo
		

		
		if (m_projectileCount <= 0 ) {
			m_projectileCount++;
			m_projectilePos.push_back(D3DXVECTOR3(posX, posY, posZ));
			m_projectileRot.push_back(D3DXVECTOR3(rotX, rotY, rotZ));
		

		}
		
		
	}

	keyDown = m_Input->IsRightClickPressed();

	if (keyDown)
	{
			m_projectileCount2++;
			m_projectilePos2.push_back(D3DXVECTOR3(posX, posY, posZ));
			m_projectileRot2.push_back(D3DXVECTOR3(rotX, rotY, rotZ));	
	}


	return true;
}

bool ApplicationClass::RenderGraphics()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	//m_Direct3D->TurnZBufferOff();

	m_Skydome->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_SkydomeShader->Render(m_Direct3D->GetDeviceContext(), m_Skydome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Skydome->GetTexture(), m_Skydome->GetTextureCount());
	if (!result)
	{
		return false;
	}

	//m_Direct3D->TurnZBufferOn();

	//aqui comienza billboard
	m_Direct3D->TurnZBufferOff();
	// Render the terrain buffers.
	m_Billboard[0]->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	for (int i = 0; i < 5; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[0]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(6 + (4*i), 15.8, 56)), viewMatrix, projectionMatrix,
			m_Billboard[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}
	// Render the terrain buffers.
	m_Billboard[1]->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	for (int i = 0; i < 12; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[1]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(122, 15.5, 82-(4*i))), viewMatrix, projectionMatrix,
			m_Billboard[1]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}
	for (int i = 0; i < 8; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[1]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(116, 15.5, 46 + (4 * i))), viewMatrix, projectionMatrix,
			m_Billboard[1]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}
	// Render the terrain buffers.
	m_Billboard[2]->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	for (int i = 0; i < 31; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[2]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(4+(4*i), 16.5, 2)), viewMatrix, projectionMatrix,
			m_Billboard[2]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}

	for (int i = 0; i < 30; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[2]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(126, 16.5, 9 +(4*i))), viewMatrix, projectionMatrix,
			m_Billboard[2]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}

	for (int i = 0; i < 31; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[2]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(124 - (4 * i), 16.5, 123)), viewMatrix, projectionMatrix,
			m_Billboard[2]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}

	for (int i = 0; i < 31; i++) {
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[2]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(1, 16.5, 122-(4*i))), viewMatrix, projectionMatrix,
			m_Billboard[2]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}


	//RENDER BILLBOARD coral
	for (int i = 0; i < 5;  i++) {
		m_Billboard[3]->Render(m_Direct3D->GetDeviceContext());
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[3]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(58+(4*i), 15, 115)), viewMatrix, projectionMatrix,
			m_Billboard[3]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}

		m_Billboard[3]->Render(m_Direct3D->GetDeviceContext());
		result = m_BillboardShader->Render(m_Direct3D->GetDeviceContext(), m_Billboard[3]->GetIndexCount(), BillboardClass::GenerateWorldMatrix(m_Camera->GetPosition(), D3DXVECTOR3(77 - (4 * i), 14.5, 111)), viewMatrix, projectionMatrix,
			m_Billboard[3]->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(1, 1, 1, 1), 10);
		if (!result)
		{
			return false;
		}
	}



	m_Direct3D->TurnZBufferOn();
	//aqui acaba billboard





	// Render the terrain buffers.
	m_Terrain->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_TerrainShader->Render(m_Direct3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									 m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTextures(), m_Terrain->GetTextureCount());
	if(!result)
	{
		return false;
	}


	//D3DXMATRIX trans, scale, cupWorldMatrix;
	//D3DXMatrixTranslation(&trans, 80, 5, 20);
	//D3DXMatrixScaling(&scale, 5, 5, 5);
	//cupWorldMatrix = scale * trans;
	//m_Cup->UpdateColliders(cupWorldMatrix);
	//for (auto &group : *m_Cup->GetGroupList())
	//{
	//	group.Render(m_Direct3D->GetDeviceContext());
	//	result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), cupWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
	//	if (!result)
	//	{
	//		return false;
	//	}
	//}

	D3DXMATRIX transla, rotat;
		
	static D3DXMATRIX tempprincipalWorldMatrix, principalWorldMatrix;
	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0);
	float yaw, pitch, roll;

	m_Position->GetPosition(position.x, position.y, position.z);
	m_Position->GetRotation(rotation.x, rotation.y, rotation.z);

	pitch = rotation.x * 0.0174532925f;
	yaw = (rotation.y + 180.0) * 0.0174532925f;
	roll = rotation.z * 0.0174532925f;

	m_Terrain->GetHeightAtPosition(position.x, position.z, position.y);

	D3DXMatrixTranslation(&transla, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&rotat, yaw, 0, 0);

	tempprincipalWorldMatrix = rotat * transla;

	m_Principal->UpdateColliders(tempprincipalWorldMatrix);

	//if (!m_Principal->Collides(m_Cup)) {
		principalWorldMatrix = tempprincipalWorldMatrix;
	//}
	//else
	//{
		//tempprincipalWorldMatrix = tempprincipalWorldMatrix;
	//}
	//modelo
	D3DXMATRIX tempMatrixGlobalNave = principalWorldMatrix;

	if (m_Camera->GetCameraType()) {
		D3DXMATRIX temptrasladar;
		D3DXMatrixTranslation(&temptrasladar, 0, -1.4, 0);
		tempMatrixGlobalNave = temptrasladar * principalWorldMatrix;
	}

	for (auto &group : *m_Principal->GetGroupList())
	{
		group.Render(m_Direct3D->GetDeviceContext());
		result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), tempMatrixGlobalNave, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
		if (!result)
		{
			return false;
		}
	}
	//wheels

	D3DXMATRIX Wtransla, Wrotat, W_MATRIX;
	D3DXMatrixTranslation(&Wtransla, 0, 0, 2);
	D3DXMatrixRotationX(&Wrotat, rotacion);
	W_MATRIX = (Wrotat*Wtransla)*tempMatrixGlobalNave;
	for (auto &group : *m_wheels->GetGroupList())
	{
		group.Render(m_Direct3D->GetDeviceContext());
		result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), W_MATRIX, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
		if (!result)
		{
			return false;
		}
	}

	//canion
	D3DXMATRIX Ctransla, Crotat, C_MATRIX;
	D3DXMatrixTranslation(&Ctransla, 0.042f, 1.45f, -2.20f);
	C_MATRIX =Ctransla * tempMatrixGlobalNave;
	for (auto &group : *m_canion->GetGroupList())
	{
		group.Render(m_Direct3D->GetDeviceContext());
		result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), C_MATRIX, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
		if (!result)
		{
			return false;
		}
	}

	//logica juego
	if (bolBotella) {
		bool verdad[3] = { false };
		//cambio de color de skydome
		if (Rojo->vivo()) {
			
			if (CambioColor[0]->Collides(m_Principal->GetBS())) {
				m_SkydomeShader->setChange(0.01f, true);
				verdad[0] = true;
			}
			
		}
		
			if (Azul->vivo()) {
				if (CambioColor[1]->Collides(m_Principal->GetBS())) {
					m_SkydomeShader->setChange(0.01f, true);
					verdad[1] = true;
				}
			}
			
			if (Morado->vivo()) {
				if (CambioColor[2]->Collides(m_Principal->GetBS())) {
					m_SkydomeShader->setChange(0.01f, true);
					verdad[2] = true;
				}
			}
				
			if(!verdad[0] && !verdad[1] && !verdad[2])
				m_SkydomeShader->setChange(0.01f, false);
		

		//barril 1
		if (!bolColBarril[0]) {
			D3DXMATRIX BTrans1;
			D3DXMatrixTranslation(&BTrans1, 70.0f, 4.0f, 81.0f);

			for (auto &group : *m_barril->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), BTrans1, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
				{
					return false;
				}
			}
		}
		//barril 2
		if (!bolColBarril[1]) {
			D3DXMATRIX BTrans2;
			D3DXMatrixTranslation(&BTrans2, 101.0f, 4.0f, 55.0f);

			for (auto &group : *m_barril->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), BTrans2, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
				{
					return false;
				}
			}
		}
		//barril 3
		if (!bolColBarril[2]) {
			D3DXMATRIX BTrans3;
			D3DXMatrixTranslation(&BTrans3, 74.0f, 4.0f, 42.0f);

			for (auto &group : *m_barril->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), BTrans3, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
				{
					return false;
				}
			}
		}

		Morado->CalculaAngulo(position.x, position.y,position.z);
		result = Morado->Dibuja(m_Direct3D,m_Camera,m_Light, viewMatrix, projectionMatrix, m_GroupShader);
		if (!result) {
			return false;
		}

		Azul->CalculaAngulo(position.x, position.y, position.z);
		result = Azul->Dibuja(m_Direct3D, m_Camera, m_Light, viewMatrix, projectionMatrix, m_GroupShader);
		if (!result) {
			return false;
		}

		Rojo->CalculaAngulo(position.x, position.y, position.z);
		result = Rojo->Dibuja(m_Direct3D, m_Camera, m_Light, viewMatrix, projectionMatrix, m_GroupShader);
		if (!result) {
			return false;
		}
		
		//aprovechando que el juego ya inicio
		//ver colosion de nave con barril
		
		//barril 1
		if (!bolColBarril[0]) {
			D3DXMATRIX BTrans1;
			D3DXMatrixTranslation(&BTrans1, 70.0f, 4.0f, 81.0f);
			m_barril->UpdateColliders(BTrans1);
			
			if (m_Principal->Collides(m_barril)) {
				vidas -= 1;
				bolColBarril[0] = true; //ignorar esta posicion
				if (vidas == 0) {
					ResertGame();
				}
			}
		}
		//barril 2
		if (!bolColBarril[1]) {
			D3DXMATRIX BTrans2;
			D3DXMatrixTranslation(&BTrans2, 101.0f, 4.0f, 55.0f);
			m_barril->UpdateColliders(BTrans2);

			if (m_Principal->Collides(m_barril)) {
				vidas -= 1;
				bolColBarril[1] = true; //ignorar esta posicion
				if (vidas == 0) {
					ResertGame();
				}
			}
		}
		//barril 3
		if (!bolColBarril[2]) {
			D3DXMATRIX BTrans3;
			D3DXMatrixTranslation(&BTrans3, 74.0f, 4.0f, 42.0f);
			m_barril->UpdateColliders(BTrans3);
			if (m_Principal->Collides(m_barril)) {
				vidas -= 1;
				bolColBarril[2] = true; //ignorar esta posicion
				if (vidas == 0) {
					ResertGame();
				}
			}
		
		}

		//aumentar salud

		if (!Rojo->vivo() && !RojoDefeat) {
			RojoDefeat = true;
			vidas = 3;
		}

		if (!Morado->vivo() && !MoradoDefeat) {
			MoradoDefeat = true;
			vidas = 3;
		}

		if (!Azul->vivo() && !AzulDefeat) {
			AzulDefeat = true;
			vidas = 3;
		}
		
	}
	ColisionTerreno(position.x, position.y, position.z);

	//OBJETOS
	D3DXMATRIX Botella_MATRIX, BotellaRot, BotellaTrans;
	D3DXMatrixTranslation(&BotellaTrans,62,4,59);
	Botella_MATRIX = BotellaTrans;
	m_botella->UpdateColliders(Botella_MATRIX);
	//m_botella->Render(m_Direct3D->GetDeviceContext());
	if (!bolBotella) {
		m_SkydomeShader->setChange(0.01, false);
		if (m_Principal->Collides(m_botella)) {
			bolBotella = true;
		}

		for (auto &group : *m_botella->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), Botella_MATRIX, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
	}

	//aqui codigo de golpe para no crecer el de logica juego 
	if (bolBotella) {
	//si juego esta activo entonces
		//preguntar proximidad
		if (SurtirGolpe[0]->Collides(m_Principal->GetBS()) && Rojo->vivo()) {
			Rojo->AutoAtack();
			bool valor = Rojo->evalua();
			if (valor) {
				if (SurtirGolpe[0]->Collides(m_Principal->GetBS()) && !inmunity) {
					vidas -= 1;

					if (vidas == 0)
						ResertGame();
					else
					inmunity = true;

					
				}
			}
		}

		if (SurtirGolpe[1]->Collides(m_Principal->GetBS()) && Azul->vivo()) {
			Azul->AutoAtack();
			bool valor = Azul->evalua();
			if (valor) {
				if (SurtirGolpe[1]->Collides(m_Principal->GetBS()) && !inmunity) {
					vidas -= 1;
					if (vidas == 0)
						ResertGame();
					else
					inmunity = true;

				
				}
			}
		}

		if (SurtirGolpe[2]->Collides(m_Principal->GetBS()) && Morado->vivo()) {
			Morado->AutoAtack();
			bool valor = Morado->evalua();
			if (valor) {
				if (SurtirGolpe[2]->Collides(m_Principal->GetBS()) && !inmunity) {
					vidas -= 1;
					if (vidas == 0)
						ResertGame();
					else
					inmunity = true;

					
				}
			}
		}

	}


	

	//PROYECTIL CODIGO
	//m_Projectile->Render(m_Direct3D->GetDeviceContext());
	for (int i = 0; i < m_projectileCount; i++)
	{

		D3DXMATRIX rotatPro, proWorldMatrix;

		D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 2.25);

		pitch = m_projectileRot[i].x * 0.0174532925f;
		yaw = (m_projectileRot[i].y) * 0.0174532925f;
		roll = m_projectileRot[i].z * 0.0174532925f;


		//float suma1 = sinf(m_projectileRot[i].y * 10);
		//float suma2 =  cosf(m_projectileRot[i].y * 10);
		//m_projectilePos[i].x + suma1;
		//m_projectilePos[i].z + suma2; // posicionar mas delante mi disparo

		D3DXMatrixRotationYawPitchRoll(&rotatPro, yaw, 0, 0);



		D3DXVECTOR4 transformed;
		D3DXVec3Transform(&transformed, &move, &rotatPro);
		m_projectilePos[i].x += transformed.x;
		m_projectilePos[i].y += transformed.y;
		m_projectilePos[i].z += transformed.z;

		D3DXMatrixTranslation(&proWorldMatrix, m_projectilePos[i].x, m_projectilePos[i].y + 1.5, m_projectilePos[i].z);

		if (!globalSphere->Collides(new BoundingSphere(m_projectilePos[i], 2.5)))
		{
			//se salio del terreno
			m_projectileCount--;
			m_projectilePos.erase(m_projectilePos.begin() + i);
			m_projectileRot.erase(m_projectileRot.begin() + i);
			//m_projectileVel.erase(m_projectileVel.begin() + i);
		}
		else {
			//por altura
					//eliminar colisiones de terreno
			float height = 0;
			m_Terrain->GetHeightAtPosition(m_projectilePos[i].x, m_projectilePos[i].z, height);

			if (height > m_projectilePos[i].y)
			{
				m_projectileCount--;
				m_projectilePos.erase(m_projectilePos.begin() + i);
				m_projectileRot.erase(m_projectileRot.begin() + i);
				//m_projectileVel.erase(m_projectileVel2.begin() + i);
			}
			else {
				//por enemigo
				bool m_Crashed = false;
				//m_Crashed |= m_enemyRB->GetBS()->Collides(new BoundingSphere(m_projectilePos[i], 5));
				m_Crashed |= EnemyPurpleSphere->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
				if (m_Crashed && Morado->vivo()) {
					//poner validacion de enemigo si esta vivo
					Morado->SetAttack(false);
					m_projectileCount--;
					m_projectilePos.erase(m_projectilePos.begin() + i);
					m_projectileRot.erase(m_projectileRot.begin() + i);
					//B_B_max[7] = true; //enemigo ataca por golpe colision
				}
				else {
					m_Crashed |= EnemyBlueSphere->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
					if (m_Crashed && Azul->vivo()) {
						Azul->SetAttack(false);
						m_projectileCount--;
						m_projectilePos.erase(m_projectilePos.begin() + i);
						m_projectileRot.erase(m_projectileRot.begin() + i);
						//B_B_max[7] = true; //enemigo ataca por golpe colision
					}
					else {
						m_Crashed |= EnemyRedSphere->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
						if (m_Crashed && Rojo->vivo()) {
							Rojo->SetAttack(false);
							m_projectileCount--;
							m_projectilePos.erase(m_projectilePos.begin() + i);
							m_projectileRot.erase(m_projectileRot.begin() + i);
							//B_B_max[7] = true; //enemigo ataca por golpe colision
						}
						else {
							//colision a explosivo

							if (!bolColBarril[0] && bolBotella) {
								m_Crashed |= ColBarril[0]->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
								if (m_Crashed) {
									bolColBarril[0] = true;
									m_projectileCount--;
									m_projectilePos.erase(m_projectilePos.begin() + i);
									m_projectileRot.erase(m_projectileRot.begin() + i);
								}
								else {
									if (!bolColBarril[1] && bolBotella) {
										m_Crashed |= ColBarril[1]->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
										if (m_Crashed) {
											bolColBarril[1] = true;
											m_projectileCount--;
											m_projectilePos.erase(m_projectilePos.begin() + i);
											m_projectileRot.erase(m_projectileRot.begin() + i);
										}
										else {
											if (!bolColBarril[2] && bolBotella) {
												m_Crashed |= ColBarril[2]->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
												if (m_Crashed) {
													bolColBarril[2] = true;
													m_projectileCount--;
													m_projectilePos.erase(m_projectilePos.begin() + i);
													m_projectileRot.erase(m_projectileRot.begin() + i);
												}
											}
										}
									}
								}
							}
							else {
								if (!bolColBarril[1] && bolBotella) {
									m_Crashed |= ColBarril[1]->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
									if (m_Crashed) {
										bolColBarril[1] = true;
										m_projectileCount--;
										m_projectilePos.erase(m_projectilePos.begin() + i);
										m_projectileRot.erase(m_projectileRot.begin() + i);
									}
									else {
										if (!bolColBarril[2] && bolBotella) {
											m_Crashed |= ColBarril[2]->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
											if (m_Crashed) {
												bolColBarril[2] = true;
												m_projectileCount--;
												m_projectilePos.erase(m_projectilePos.begin() + i);
												m_projectileRot.erase(m_projectileRot.begin() + i);
											}
										}
									}
								}
								else {
									if (!bolColBarril[2] && bolBotella) {
										m_Crashed |= ColBarril[2]->Collides(new BoundingSphere(m_projectilePos[i], 2.5));
										if (m_Crashed) {
											bolColBarril[2] = true;
											m_projectileCount--;
											m_projectilePos.erase(m_projectilePos.begin() + i);
											m_projectileRot.erase(m_projectileRot.begin() + i);
										}
									}
								}
							}

							//fin locuras






						}
					}

				}
			}


			for (auto &group : *m_Projectile->GetGroupList())
			{
				group.Render(m_Direct3D->GetDeviceContext());
				result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
				if (!result)
				{
					return false;
				}
			}


			if (!result)
			{
				return false;
			}
		}
	}
	
	//PROYECTIL 2
	if (powerUp && bolBotella) {
	//si recogi la botella y el powerup
		for (int i = 0; i < m_projectileCount2; i++)
		{

			D3DXMATRIX rotatPro, proWorldMatrix;

			D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 2.25);

			pitch = m_projectileRot2[i].x * 0.0174532925f;
			yaw = (m_projectileRot2[i].y) * 0.0174532925f;
			roll = m_projectileRot2[i].z * 0.0174532925f;


			//float suma1 = sinf(m_projectileRot[i].y * 10);
			//float suma2 =  cosf(m_projectileRot[i].y * 10);
			//m_projectilePos[i].x + suma1;
			//m_projectilePos[i].z + suma2; // posicionar mas delante mi disparo

			D3DXMatrixRotationYawPitchRoll(&rotatPro, yaw, 0, 0);



			D3DXVECTOR4 transformed;
			D3DXVec3Transform(&transformed, &move, &rotatPro);
			m_projectilePos2[i].x += transformed.x;
			m_projectilePos2[i].y += transformed.y;
			m_projectilePos2[i].z += transformed.z;

			D3DXMatrixTranslation(&proWorldMatrix, m_projectilePos2[i].x, m_projectilePos2[i].y + 1.5, m_projectilePos2[i].z);

			if (!globalSphere->Collides(new BoundingSphere(m_projectilePos2[i], 2.5)))
			{
				//se salio del terreno
				m_projectileCount2--;
				m_projectilePos2.erase(m_projectilePos2.begin() + i);
				m_projectileRot2.erase(m_projectileRot2.begin() + i);
				//m_projectileVel.erase(m_projectileVel.begin() + i);
			}
			else {
				//por altura
						//eliminar colisiones de terreno
				float height = 0;
				m_Terrain->GetHeightAtPosition(m_projectilePos2[i].x, m_projectilePos2[i].z, height);

				if (height > m_projectilePos2[i].y)
				{
					m_projectileCount2--;
					m_projectilePos2.erase(m_projectilePos2.begin() + i);
					m_projectileRot2.erase(m_projectileRot2.begin() + i);
					//m_projectileVel.erase(m_projectileVel2.begin() + i);
				}
				else {
					//por enemigo
					bool m_Crashed = false;
					//m_Crashed |= m_enemyRB->GetBS()->Collides(new BoundingSphere(m_projectilePos[i], 5));
					m_Crashed |= EnemyPurpleSphere->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
					if (m_Crashed && Morado->vivo()) {
						//poner validacion de enemigo si esta vivo
						Morado->SetAttack(false);
						m_projectileCount2--;
						m_projectilePos2.erase(m_projectilePos2.begin() + i);
						m_projectileRot2.erase(m_projectileRot2.begin() + i);
						//B_B_max[7] = true; //enemigo ataca por golpe colision
					}
					else {
						m_Crashed |= EnemyBlueSphere->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
						if (m_Crashed && Azul->vivo()) {
							Azul->SetAttack(false);
							m_projectileCount2--;
							m_projectilePos2.erase(m_projectilePos2.begin() + i);
							m_projectileRot2.erase(m_projectileRot2.begin() + i);
							//B_B_max[7] = true; //enemigo ataca por golpe colision
						}
						else {
							m_Crashed |= EnemyRedSphere->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
							if (m_Crashed && Rojo->vivo()) {
								Rojo->SetAttack(false);
								m_projectileCount2--;
								m_projectilePos2.erase(m_projectilePos2.begin() + i);
								m_projectileRot2.erase(m_projectileRot2.begin() + i);
								//B_B_max[7] = true; //enemigo ataca por golpe colision
							}
							else {
								//colision a explosivo

								if (!bolColBarril[0] && bolBotella) {
									m_Crashed |= ColBarril[0]->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
									if (m_Crashed) {
										bolColBarril[0] = true;
										m_projectileCount2--;
										m_projectilePos2.erase(m_projectilePos2.begin() + i);
										m_projectileRot2.erase(m_projectileRot2.begin() + i);
									}
									else {
										if (!bolColBarril[1] && bolBotella) {
											m_Crashed |= ColBarril[1]->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
											if (m_Crashed) {
												bolColBarril[1] = true;
												m_projectileCount2--;
												m_projectilePos2.erase(m_projectilePos2.begin() + i);
												m_projectileRot2.erase(m_projectileRot2.begin() + i);
											}
											else {
												if (!bolColBarril[2] && bolBotella) {
													m_Crashed |= ColBarril[2]->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
													if (m_Crashed) {
														bolColBarril[2] = true;
														m_projectileCount2--;
														m_projectilePos2.erase(m_projectilePos2.begin() + i);
														m_projectileRot2.erase(m_projectileRot2.begin() + i);
													}
												}
											}
										}
									}
								}
								else {
									if (!bolColBarril[1] && bolBotella) {
										m_Crashed |= ColBarril[1]->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
										if (m_Crashed) {
											bolColBarril[1] = true;
											m_projectileCount2--;
											m_projectilePos2.erase(m_projectilePos2.begin() + i);
											m_projectileRot2.erase(m_projectileRot2.begin() + i);
										}
										else {
											if (!bolColBarril[2] && bolBotella) {
												m_Crashed |= ColBarril[2]->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
												if (m_Crashed) {
													bolColBarril[2] = true;
													m_projectileCount2--;
													m_projectilePos2.erase(m_projectilePos2.begin() + i);
													m_projectileRot2.erase(m_projectileRot2.begin() + i);
												}
											}
										}
									}
									else {
										if (!bolColBarril[2] && bolBotella) {
											m_Crashed |= ColBarril[2]->Collides(new BoundingSphere(m_projectilePos2[i], 2.5));
											if (m_Crashed) {
												bolColBarril[2] = true;
												m_projectileCount2--;
												m_projectilePos2.erase(m_projectilePos2.begin() + i);
												m_projectileRot2.erase(m_projectileRot2.begin() + i);
											}
										}
									}
								}

								//fin locuras






							}
						}

					}
				}


				for (auto &group : *m_Projectile2->GetGroupList())
				{
					group.Render(m_Direct3D->GetDeviceContext());
					result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), proWorldMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
					if (!result)
					{
						return false;
					}
				}


				if (!result)
				{
					return false;
				}
			}
		}

		
	}


	//FIN PROYECTIL 2
	//quitar vida vehiculo, con lo de abajo queda animacion de golpe y levantamiento
	if (Morado->vivo() && bolBotella){
	Morado->Colision(m_Principal, 0,NULL);
	//cambiar color skydome
	
	}

	if(Azul->vivo() && bolBotella){
	Azul->Colision(m_Principal, 0, NULL);

	}

	if(Rojo->vivo() && bolBotella){
	Rojo->Colision(m_Principal, 0, NULL);
	
	}

	//29,4,99
	//powerup
	D3DXMATRIX Power_MATRIX, Power_Trans, Power_Scale;
	D3DXMatrixTranslation(&Power_Trans, 29, 4, 99);
	D3DXMatrixScaling(&Power_Scale,4,4,4);
	Power_MATRIX = Power_Scale * Power_Trans;
	m_Projectile2->UpdateColliders(Power_Trans);
	//29,4,99
	if (!powerUp && bolBotella) {

		if (m_Principal->Collides(m_Projectile2)) {
			powerUp = true;
		}

		for (auto &group : *m_Projectile2->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), Power_MATRIX, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
	}
	//ultimos modelos

	

	if (bolkey && bolBotella) {
		D3DXMATRIX CofreMatrix, TranslateCofre, RotateCofre;
		D3DXMatrixTranslation(&TranslateCofre, 23, 8, 107);
		D3DXMatrixRotationY(&RotateCofre, 90);
		CofreMatrix = RotateCofre * TranslateCofre;

		for (auto &group : *m_cofre->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), CofreMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
	}


	D3DXMATRIX KeyMatrix, TranslatKey, RotateKey;
	if (keyPosition[0]) {	//rojo
		D3DXMatrixTranslation(&TranslatKey, 101.0f, 4.0f, 97.0f);
		
	}
	if (keyPosition[1]) {	//azul
		D3DXMatrixTranslation(&TranslatKey, 27.0f, 4.0f, 24.0f);
	}
	if (keyPosition[2]) {	//morado
		D3DXMatrixTranslation(&TranslatKey, 107.0f, 4.0f, 24.0f);
	}

	D3DXMatrixRotationY(&RotateKey, giro);
	
	KeyMatrix = RotateKey * TranslatKey;
	m_key->UpdateColliders(KeyMatrix);

	if (keyPosition[0] && !Rojo->vivo() && !bolkey) {
	//la llave la tiene rojo, y debe estar muerto para que de dibuje
		for (auto &group : *m_key->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), KeyMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
		if (m_key->Collides(m_Principal)) {
			bolkey = true;
		}
	}

	if (keyPosition[1] && !Azul->vivo() && !bolkey) {
		//la llave la tiene rojo, y debe estar muerto para que de dibuje
		for (auto &group : *m_key->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), KeyMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
		if (m_key->Collides(m_Principal)) {
			bolkey = true;
		}
	}

	if (keyPosition[2] && !Morado->vivo() && !bolkey) {
		//la llave la tiene rojo, y debe estar muerto para que de dibuje
		for (auto &group : *m_key->GetGroupList())
		{
			group.Render(m_Direct3D->GetDeviceContext());
			result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), KeyMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
			if (!result)
			{
				return false;
			}
		}
		if (m_key->Collides(m_Principal)) {
			bolkey = true;
		}
	}



	//fin de codigo modelos
	// Render the terrain buffers.
	D3DXMATRIX PalmTrans, PalmRot, PalmMatrix;
	D3DXMatrixTranslation(&PalmTrans,23,6,103);
	PalmMatrix = PalmTrans;
	for (auto &group : *m_palm->GetGroupList())
	{
		group.Render(m_Direct3D->GetDeviceContext());
		result = m_GroupShader->Render(m_Direct3D->GetDeviceContext(), PalmMatrix, viewMatrix, projectionMatrix, m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR4(1, 1, 1, 1), m_Light->GetDirection(), m_Camera->GetPosition(), group);
		if (!result)
		{
			return false;
		}
	}


	m_Water->Render(m_Direct3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_WaterShader->Render(m_Direct3D->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Water->GetTextures(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(), D3DXVECTOR4(0.9, 0.3, 0.3, 1), 10);

	if (!result)
	{
		return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	// Render the text user interface elements.
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), m_FontShader, worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	//m_Direct3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

void ApplicationClass::ResertGame() {
	vidas = 3;
	Rojo->ResetEnemy();
	Azul->ResetEnemy();
	Morado->ResetEnemy();
	bolBotella = false;
	bolColBarril[0] = bolColBarril[1] = bolColBarril[2] = bolkey = false;
	m_SkydomeShader->setChange(1, true);

	inmunity = false;
	tiempo = 0.0f;

	powerUp = false;
	RojoDefeat = AzulDefeat = MoradoDefeat = false;
	
	int valor = indices();
	keyPosition[valor] = true;
}

void ApplicationClass::ColisionTerreno(float X, float Y, float Z) {
	if (Y > 4) {
		if (K == adelante) {
			//m_Position->MoveBackward(true);
			m_Position->Rollback(Y, true);
			
		}
		else {
		//	if (K == atras) {
				//m_Position->MoveForward(true);
				m_Position->Rollback(Y, false);
			//}
		}
	}

	//ahora contra las posiciones delos enemigos
	if (bolBotella) {
	if (EnemyRedSphere->Collides(m_Principal->GetBS()) && Rojo->vivo()) {
		if (K == adelante) {
			//m_Position->MoveBackward(true);
			m_Position->MoveBackward(true);
		}
		else {
			if (K == atras) {
	//			m_Position->MoveForward(true);
				m_Position->MoveForward(true);
			}
			else {
				if (K == izquierda) {
				//	m_Position->TurnRight(true);
					m_Position->TurnRight(true);
				}
				else {
					if (K == derecha) {
						//m_Position->TurnLeft(true);
						m_Position->TurnLeft(true);
					}
				}
			}
		}
	}

	if (EnemyBlueSphere->Collides(m_Principal->GetBS()) && Azul->vivo()) {
		if (K == adelante) {
			//m_Position->MoveBackward(true);
			m_Position->MoveBackward(true);
		}
		else {
			if (K == atras) {
				//m_Position->MoveForward(true);
				m_Position->MoveForward(true);
			}
			else {
				if (K == izquierda) {
					//m_Position->TurnRight(true);
					m_Position->TurnRight(true);
				}
				else {
					if (K == derecha) {
						//m_Position->TurnLeft(true);
						m_Position->TurnLeft(true);
					}
				}
			}
		}
	}

	if (EnemyPurpleSphere->Collides(m_Principal->GetBS()) && Morado->vivo()) {
		if (K == adelante) {
			//m_Position->MoveBackward(true);
			m_Position->MoveBackward(true);
		}
		else {
			if (K == atras) {
			//	m_Position->MoveForward(true);
				m_Position->MoveForward(true);
			}
			else {
				if (K == izquierda) {
				//	m_Position->TurnRight(true);
					m_Position->TurnRight(true);
				}
				else {
					if (K == derecha) {
					//	m_Position->TurnLeft(true);
						m_Position->TurnLeft(true);
					}
				}
			}
		}
	}
	}

	//ahora van las colisiones con los mounstuos
}

int ApplicationClass::indices() {
	keyPosition[0] = false;
	keyPosition[1] = false;
	keyPosition[2] = false;
	int numero = Sorteo->GetValor();
	return numero;
}
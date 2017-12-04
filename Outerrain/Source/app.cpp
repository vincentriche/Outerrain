#include "app.h"
#include "GL/glew.h"
#include "fields.h"

App::App(const int& width, const int& height, const int& major, const int& minor) 
		: m_window(nullptr), m_context(nullptr)
{
	m_window = create_window(width, height);
	m_context = create_context(m_window, major, minor);
}

App::~App()
{
	if (m_context)
		release_context(m_context);
	if (m_window)
		release_window(m_window);
}

int App::Init()
{
	// Default gl state
	glClearDepthf(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LESS);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	/*Heightfield hf(64, 64, Vector2(-64, -64), Vector2(64, 64));
	hf.InitFromNoise();
	mesh = hf.GetMesh();*/
	mesh.read_mesh("Data/bigguy.obj");

	Shader shader;
	shader.InitFromFile("Shaders/Diffuse.glsl");
	mesh.SetShader(shader);
	
	//orbiter = CameraOrbiter(Vector3(0.0, 0.0, 0.0), 300.0);
	orbiter.LookAt(mesh.GetBounds());

	return 1;
}

void App::Quit()
{
}

int App::Render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	mesh.Draw(orbiter);
	return 1;
}

int App::Update(const float time, const float deltaTime)
{
	// Deplace la camera
	int mx, my;
	unsigned int mb = SDL_GetRelativeMouseState(&mx, &my);
	if (mb & SDL_BUTTON(1))
		orbiter.rotation(mx, my);
	if (mb & SDL_BUTTON(3))
		orbiter.move(my);
	if (mb & SDL_BUTTON(2))
		orbiter.translation((float)mx / (float)window_width(), (float)my / (float)window_height());

	// Keyboard
	if (key_state(SDLK_PAGEUP))
		orbiter.move(1.0f);
	if (key_state(SDLK_PAGEDOWN))
		orbiter.move(-1.0f);
	if (key_state(SDLK_UP))
		orbiter.translation(0.0f, 10.0f / (float)window_height());
	if (key_state(SDLK_DOWN))
		orbiter.translation(0.0f, -10.0f / (float)window_height());
	if (key_state(SDLK_LEFT))
		orbiter.translation(10.0f / (float)window_width(), 0.0f);
	if (key_state(SDLK_RIGHT))
		orbiter.translation(-10.0f / (float)window_width(), 0.0f);

	return 1;
}

void App::Run()
{
	if (Init() < 0)
		return;

	glViewport(0, 0, window_width(), window_height());
	while (events(m_window))
	{
		if (Update(global_time(), delta_time()) < 0)
			break;
		if (Render() < 1)
			break;
		SDL_GL_SwapWindow(m_window);
	}

	Quit();
}

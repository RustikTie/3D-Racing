#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// Paths
	rampDef.SetPos(0, 0.5, 50);
	rampDef.size = { 25, 1, 100 };
	rampDef.SetRotation(-20, { 1, 0, 0 });
	App->physics->AddBody(rampDef, 0);

	pathDef1.SetPos(0, 0.5, 50);
	pathDef1.size = { 25, 1, 100 };
	pathDef1.color = Black;
	App->physics->AddBody(pathDef1, 0);
	
	pathDef2.SetPos(0, 17.6, 116.8);
	pathDef2.size = { 25, 1, 40 };
	App->physics->AddBody(pathDef2, 0);

	pathDef3.SetPos(15.8, 17.55, 147.5);
	pathDef3.size = { 25, 1, 55 };
	pathDef3.SetRotation(45, { 0, 1, 0 });
	App->physics->AddBody(pathDef3, 0);

	pathDef4.SetPos(71.6, 17.6, 163.4);
	pathDef4.size = { 25, 1, 90 };
	pathDef4.SetRotation(90, { 0, 1, 0 });
	App->physics->AddBody(pathDef4, 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.color = Pink;
	p.Render();
	
	rampDef.Render();
	pathDef1.Render();
	pathDef2.Render();	
	pathDef3.Render();
	pathDef4.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}


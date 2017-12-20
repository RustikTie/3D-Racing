#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

#define SIZE_ARRAY(_A_) (sizeof(_A_)/sizeof(_A_[0]))

// Road
static const float RW = 15.0f;
static const float RH = 5.0f;

// Circuit
static const float CX = 150.0f;
static const float CY = 80.0f;

// Circuit Def
struct CubeDef {
	float size_x, size_y, size_z;
	float pos_x, pos_y, pos_z;
	bool add_collision_listener;
};

CubeDef cube_defs[] = {
	{ RW, RH,  CX, 0,   RH/2,  CX/2,        true },
	{ CY + RW, RH, RW,  -CY/2, CX + RW/2,   false },
	{ RW, RH,  CX, -CY, RH/2,  CX/2,        false },
	{ CY + RW, RH, RW,  -CY/2, RH/2, -RW/2, false }
};

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

	for (int i = 0; i < SIZE_ARRAY(cube_defs); i++)
	{
		Cube c;
		c.size.Set(cube_defs[i].size_x, cube_defs[i].size_y, cube_defs[i].size_z);
		c.SetPos(cube_defs[i].pos_x, cube_defs[i].pos_y, cube_defs[i].pos_z);
		PhysBody3D *p = App->physics->AddBody(c);
		if (cube_defs[i].add_collision_listener)
			p->collision_listeners.add(this);
	}

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

	p2List_item<Cube>* s_item = cubes.getFirst();
	while (s_item)
	{
		s_item->data.Render();
		s_item = s_item->next;
	}
	
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

void ModuleSceneIntro::CreatePath(vec3 _pos, vec3 _size, Color _color)
{

}
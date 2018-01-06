#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "ModulePhysics3D.h"

#define SIZE_ARRAY(_A_) (sizeof(_A_)/sizeof(_A_[0]))

// Road
static const float RW = 15.0f;
static const float RH = 5.0f;

// Circuit
static const float C_X = 150.0f;
static const float C_Y = 80.0f;

// Circuit Def
struct CubeDef {
	float size_x, size_y, size_z;
	float pos_x, pos_y, pos_z;
	Color _color;
	float _mass = 0;
	bool _rotate = false;
	float _angle = 0;
	const vec3 _axis = { 0, 0, 0 };
	bool add_collision_listener = false;
};

CubeDef cube_defs[] = {
	
	{ 25, 1, 100, 0, 0.5, 50, White, 0, true, -20, { 1, 0, 0 } },
	{ 25, 3, 100, 0, 1, 50, White },
	{ 25, 1, 40, 0, 17.6, 116.18, White },
	{ 25, 1, 55, 15.8, 17.55, 147.5, White, 0, true, 45, { 0, 1, 0 } },
	{ 25, 1, 90, 71.6, 17.6, 163.4, White, 0, true, 90,{ 0, 1, 0 } },
	{ 25,1,90, 108, 17.6, 131, White },
	{ 25, 1, 90, 108, 5.5, 0, White }
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



	for (int i = 0; i < SIZE_ARRAY(cube_defs); i++)
	{
		Cube c;
		c.size.Set(cube_defs[i].size_x, cube_defs[i].size_y, cube_defs[i].size_z);
		c.SetPos(cube_defs[i].pos_x, cube_defs[i].pos_y, cube_defs[i].pos_z);
		c.color = cube_defs[i]._color;
		if (cube_defs[i]._rotate)
			c.SetRotation(cube_defs[i]._angle, cube_defs[i]._axis);
		PhysBody3D *p = App->physics->AddBody(c, cube_defs[i]._mass);
		if (cube_defs[i].add_collision_listener)
			p->collision_listeners.add(this);
		cubes.add(c);
	}

	// Paths
	/*rampDef.SetPos(0, 0.5, 50);
	rampDef.size = { 25, 1, 100 };
	rampDef.SetRotation(-20, { 1, 0, 0 });
	App->physics->AddBody(rampDef, 0);

	pathDef1.SetPos(0, 1, 50);
	pathDef1.size = { 25, 3, 100 };
	pathDef1.color = White;
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

	pathDef5.SetPos(108, 17.6, 131);
	pathDef5.size = {25,1,90};
	App->physics->AddBody(pathDef5, 0);	
	
	pathDef6.SetPos(108, 5.5, 0);
	pathDef6.size = { 25, 1, 90 };
	App->physics->AddBody(pathDef6, 0);*/

	pillar1.SetPos(117.5, 7.5, 70);
	pillar1.size = { 12,15,12 };
	body1 = App->physics->AddBody(pillar1,1000);

	pillar2.SetPos(100, 10, 55);
	pillar2.size = { 25, 10, 1 };
	body2 = App->physics->AddBody(pillar2, 1);

	btHingeConstraint* hinge = App->physics->AddConstraintHinge(*body1, *body2, vec3{ 0,0,0 }, vec3{ 10, 0,0 }, vec3{ 0,1,0}, vec3{0,1,0}, true);

	hinge->setLimit(1, 0);

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
	
	body1->GetTransform(&pillar1.transform);
	pillar1.Render();
	body2->GetTransform(&pillar2.transform);
	pillar2.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreatePath(vec3 _pos, vec3 _size, Color _color)
{

}
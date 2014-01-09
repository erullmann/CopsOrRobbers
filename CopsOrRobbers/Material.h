//Material.h
//implements a material structure and some basic marterials for use.
#pragma once

struct Material {
	float density;
	float restitution; //absorbation of force from collision
	float friction;
};
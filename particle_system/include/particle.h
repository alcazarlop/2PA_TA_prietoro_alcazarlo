//Author: Manuel Alcazar Lopez
#ifndef __PARTICLE_H__
#define __PARTICLE_H__ 1

#include "entity.h"
#include "path.h"
#include "sprite.h"
#include "game_manager.h"
#include <stdlib.h>

class Vec3;

class Particle {
public: 
	Particle();
	Particle(const Particle& copy);
	~Particle();

	void init(Uint8 type);
	void draw(SDL_Renderer* renderer);
	void update();

	Entity* entity() const;

	struct ParticleParams {
		Vec3 velocity;
		float speed;
		float lifeTime;
		float spawnTime;
		float maxTimeAlive;
	} params_;

private:
	Entity* entity_;

};

#endif
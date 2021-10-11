//
// Created by Leo on 2021/10/11.
//

#ifndef MASS_SPRING_GAME_MASS_SPRING_SYSTEM_H
#define MASS_SPRING_GAME_MASS_SPRING_SYSTEM_H
#include "vector2f.h"
#include "vector"

const int max_num_particles = 100;
const float particle_mass = 1.0;
const float dt = 1e-3;
const int subSteps = 10;
const float connection_radius = 0.15;
class MassSpringSystem{
public:
    MassSpringSystem();
    void update();
    void addNewParticle(const Vector2f& pos, bool fixed);
    void attract(const Vector2f& pos);
    void clear();

public:
    void draw();

    void drawParticles();
    void drawSprings();

public:
    float m_springY;
    bool m_paused;
    float m_dragDamping;
    float m_dashPotDamping;
private:
    int m_numParticles{};
    Vector2f m_x[max_num_particles];
    Vector2f m_v[max_num_particles];
    Vector2f m_f[max_num_particles];
    bool m_fixed[max_num_particles];
    float m_restLength[max_num_particles][max_num_particles]{};
};


#endif //MASS_SPRING_GAME_MASS_SPRING_SYSTEM_H

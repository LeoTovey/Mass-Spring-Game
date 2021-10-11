//
// Created by Leo on 2021/10/11.
//

#include "mass_spring_system.h"
#include <iostream>
#include "imgui/imgui_internal.h"

void MassSpringSystem::update()
{
    for(int i = 0; i < m_numParticles; i++)
    {
        m_f[i] = Vector2f(0, -9.8f) * particle_mass;
        for(int j = 0; j < m_numParticles; j++)
        {
            if (m_restLength[i][j] != 0.0f)
            {
                Vector2f x_ij = m_x[i] - m_x[j];
                Vector2f d = x_ij.Normalized();

                // spring force
                m_f[i] += -m_springY * (x_ij.Length() / m_restLength[i][j] - 1.0f) * d;

                // dashpot damping
                //todo: add dashpot damping
                float v_rel = Dot((m_v[i] - m_v[j]), d);
                m_f[i] += - m_dashPotDamping * v_rel * d;
            }
        }
    }


    //We use a semi-implicit Euler (aka symplectic Euler) time integrator

    for (int i = 0; i < m_numParticles; ++i)
    {
        if (!m_fixed[i])
        {
            m_v[i] += dt * m_f[i];

            //todo: add drag dampping

            m_x[i] += m_v[i] * dt;
        }
        else
        {
            m_v[i] = Vector2f(0.0f, 0.0f);
        }

        // collide with four walls
        if (m_x[i].x < 0.0f)
        {
            m_x[i].x = 0.0f;
            m_v[i].x = 0.0f;
        }

        if (m_x[i].y < 0.0f)
        {
            m_x[i].y = 0.0f;
            m_v[i].y = 0.0f;
        }

        if (m_x[i].x > 1.0f)
        {
            m_x[i].x = 1.0f;
            m_v[i].x = 0.0f;
        }

        if (m_x[i].y > 1.0f)
        {
            m_x[i].y = 1.0f;
            m_v[i].y = 0.0f;
        }

    }

}

MassSpringSystem::MassSpringSystem()
{
    m_springY = 1000;
    m_dragDamping = 1;
    m_dashPotDamping = 100;
    m_paused = false;
}

void MassSpringSystem::addNewParticle(const Vector2f &pos, bool fixed)
{
    if (m_numParticles == max_num_particles)
    {
        return;
    }
    int id = m_numParticles;
    m_x[id] = pos;
    m_v[id] = Vector2f(0.0f, 0.0f);
    m_fixed[id] = fixed;
    m_numParticles++;

    for (int i = 0; i < id; i++)
    {
        float dist = (m_x[id] - m_x[i]).Length();

        if (dist < connection_radius)
        {
            std::cout<<"add springs"<<std::endl;
            m_restLength[i][id] = 0.1f;
            m_restLength[id][i] = 0.1f;
        }
    }
}

void MassSpringSystem::attract(const Vector2f &pos)
{
    for (int i = 0; i < m_numParticles; i++)
    {
        m_v[i] += -dt * subSteps * (m_x[i] - pos) * 100.0f;
    }

}

void MassSpringSystem::draw()
{
    drawSprings();
    drawParticles();
}

void MassSpringSystem::drawParticles()
{
    ImDrawList* draw_list = ImGui::GetCurrentWindow()->DrawList;
    ImVec2 size = ImGui::GetCurrentWindow()->Size;
    float radius = 10.0f;
    for (int i = 0; i < m_numParticles; i++)
    {
        draw_list->AddCircleFilled(ImVec2(m_x[i].x * size.x, size.y - m_x[i].y * size.y),
                                   radius,
                                   ImGui::GetColorU32(ImVec4(247.0f/256.0f, 246.0f/256.0f, 238.0f/256.0f, 1.0f)));
    }
}

void MassSpringSystem::drawSprings()
{
    ImDrawList* draw_list = ImGui::GetCurrentWindow()->DrawList;
    ImVec2 size = ImGui::GetCurrentWindow()->Size;

    for (int i = 0; i < m_numParticles; i++)
    {
        for (int j = i + 1; j < m_numParticles; j++)
        {
            if (m_restLength[i][j] != 0)
            {
                draw_list->AddLine(ImVec2(m_x[i].x * size.x, size.y - m_x[i].y * size.y),
                                   ImVec2(m_x[j].x * size.x, size.y - m_x[j].y * size.y),
                                   ImGui::GetColorU32(ImVec4(112.0f/256.0f, 223.0f/256.0f, 223.0f/256.0f, 1.0f) ), 5.0f);
            }
        }
    }
}

void MassSpringSystem::clear()
{
    m_numParticles = 0;
}

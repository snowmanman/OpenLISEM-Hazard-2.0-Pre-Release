#ifndef GL3DCAMERACONTROLLER_H
#define GL3DCAMERACONTROLLER_H


#include "sph_vector2.h"
#include "gl3dcamera.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "gl3delevationprovider.h"

class GL3DCameraController
{

private:

    GL3DCamera * m_Camera;
    GL3DElevationProvider * m_ElevationProvider;

public:
    inline GL3DCameraController(GL3DCamera * c, GL3DElevationProvider * p )
    {

        m_Camera = c;
        m_ElevationProvider = p;
    }

    inline void OnFrame(float dt, GLFWwindow*w)
    {

         double elevation = m_ElevationProvider->GetElevation(m_Camera->GetPosition().x,m_Camera->GetPosition().z);
         if(elevation < -1e25 || !std::isfinite(elevation))
         {
             elevation  = 0.0;
         }


         if(m_Camera->GetPosition().Y() < elevation + 0.0001f)
         {
            m_Camera->SetPosition(m_Camera->GetPosition().x,elevation + 0.01f,m_Camera->GetPosition().z);
         }

         float c_above = std::max(0.001f,(float)(m_Camera->GetPosition().Y() -elevation));

         float m_ZNear = std::max(0.00000001f,std::min(1e2f,c_above * 0.1f));
         float m_ZFar = std::max(100.0f,std::min(1e9f,c_above * 1000.0f));


         m_Camera->SetZNear(m_ZNear);
         m_Camera->SetZFar(m_ZFar);

         double speed = std::max(0.01f,(float)(0.3f * (m_Camera->GetPosition().Y()-elevation)));

        if(glfwGetKey(w,GLFW_KEY_LEFT_CONTROL) ==GLFW_PRESS)
        {
            speed = speed * 10.0;
        }
        if(glfwGetKey(w,GLFW_KEY_W) ==GLFW_PRESS)
        {
            m_Camera->MoveForward(-dt*speed);
        }
        if(glfwGetKey(w,GLFW_KEY_A) ==GLFW_PRESS)
        {
            m_Camera->StrafeRight(dt*speed);
        }
        if(glfwGetKey(w,GLFW_KEY_S) ==GLFW_PRESS)
        {
             m_Camera->MoveForward(dt*speed);
        }
        if(glfwGetKey(w,GLFW_KEY_D) ==GLFW_PRESS)
        {
             m_Camera->StrafeRight(-dt*speed);
        }
        if(glfwGetKey(w,GLFW_KEY_Q) ==GLFW_PRESS)
        {
            m_Camera->MoveUpward(dt*speed);
        }
        if(glfwGetKey(w,GLFW_KEY_E) ==GLFW_PRESS)
        {
            m_Camera->MoveUpward(-dt*speed);
        }
    }

    inline void OnMouseDrag(SPHVector2 pos, SPHVector2 mov)
    {

        if(std::fabs(mov.X()) > 0.0f)
        {
            m_Camera->RotateY(-0.1f* float(mov.X()));
        }
        if(std::fabs(mov.Y()) > 0.0f)
        {
            m_Camera->RotateX(-0.1f* float(mov.Y()));
        }


    }

    inline void OnMouseMove(SPHVector2 pos, SPHVector2 mov)
    {

    }

    inline void OnMouseScroll(SPHVector2 pos, SPHVector2 mov)
    {

    }

    inline void OnMousePressed(int button, int pressed)
    {

    }

    inline void OnMouseLeave(bool leave)
    {

    }

    inline void OnKeyPressed(int key, bool pressed)
    {

    }
};

#endif // GL3DCAMERACONTROLLER_H

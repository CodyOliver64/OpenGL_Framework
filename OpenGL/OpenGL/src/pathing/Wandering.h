#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iostream>

#include <GLFW/glfw3.h>

void Wander(glm::vec3* currentPos, glm::vec3* m_Target, glm::vec3* randArray, int* counterPoint)
{
    
    if (abs(currentPos->x - m_Target->x) < 3 && abs(currentPos->y - m_Target->y) < 3) // need to fix, it cant move back down
    {

        m_Target->x = randArray[*counterPoint].x;
        m_Target->y = randArray[*counterPoint].y;

        if (*counterPoint == 10)
            *counterPoint = 0;

        *counterPoint = *counterPoint + 1;

        std::cout << *counterPoint << std::endl;
    }
    
    glm::vec3 desired = *m_Target - *currentPos;

    float magnitude = sqrt(pow(desired.x, 2) + pow(desired.y, 2));

    desired = desired / magnitude;

    desired = desired * 4.0f; // 2 pixels per frame 

    currentPos->x += desired.x;
    currentPos->y += desired.y;
    

}

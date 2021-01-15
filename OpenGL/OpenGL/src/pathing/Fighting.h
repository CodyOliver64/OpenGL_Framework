#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <stdlib.h>
#include <cmath>

#include <GLFW/glfw3.h>

void Fight(glm::vec3* currentPos, glm::vec3* enemyPos, glm::vec3* point1, glm::vec3* point2, glm::vec3* target)
{
    
    if (abs(currentPos->x - point1->x) < 3 && abs(currentPos->y - point1->y) < 3)
    {
        target->x = point2->x;
        target->y = point2->y;
    }

    if (abs(currentPos->x - point2->x) < 3 && abs(currentPos->y - point2->y) < 3)
    {
        target->x = point1->x;
        target->y = point1->y;
    }
    
    
    glm::vec3 desired = *target - *currentPos;

    float magnitude = sqrt(pow(desired.x, 2) + pow(desired.y, 2));

    desired = desired / magnitude;

    desired = desired * 4.0f; // 2 pixels per frame 

    currentPos->x += desired.x;
    currentPos->y += desired.y;
    
    // Reset to the other side if it goes of Horitzontally
    if (currentPos->x > 956)
        currentPos->x = 4;
    if (currentPos->x < 4)
        currentPos->x = 956;

    // Reset to the other side if it goes of Vertically
    if (currentPos->y > 536)
        currentPos->y = 4;
    if (currentPos->y < 4)
        currentPos->y = 536;

}

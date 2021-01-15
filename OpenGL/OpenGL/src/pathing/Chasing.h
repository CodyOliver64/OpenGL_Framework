#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <stdlib.h>
#include <cmath>

#include <GLFW/glfw3.h>

void Chase(glm::vec3* currentPos, double x_Mouse, double y_Mouse)
{
    
    
    glm::vec3 target(x_Mouse, 540 - y_Mouse, 0);
    
    glm::vec3 desired = target - *currentPos;

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

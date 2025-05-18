#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <glm/glm.hpp>
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include <cmath>

class RenderGUISystem: public System {
    public:
        RenderGUISystem() = default;

        void Update(SDL_Renderer* renderer, const std::unique_ptr<Registry>& registry){
            ImGui_ImplSDLRenderer2_NewFrame();                                                                              // iniitalize ImGui
            ImGui_ImplSDL2_NewFrame();                                                                                      // ...
            ImGui::NewFrame();                                                                                              // ...

            if(ImGui::Begin("Spawn enemies")){                                                                              // createe "Spawn enemies" ImGui window
                const char* textures[] = {"tank-image", "truck-image"};                                                     // create static variables for input widgets
                static int texturesIndex = 0;                                                                               // ...
                static float xPos = 200;                                                                                    // ...
                static float yPos = 200;                                                                                    // ...
                static float xScale = 1.0;                                                                                  // ...
                static float yScale = 1.0;                                                                                  // ...
                static float rotation = 0.0;                                                                                // ...
                static float xVel = 10;                                                                                     // ...
                static float yVel = -10;                                                                                    // ...
                static float projectileAngleRad = 0.0;                                                                      // ...
                static float projectileSpeed = 100;                                                                         // ...
                static float projectileRepeatHz = 1.0;                                                                      // ...
                static float projectileDurationSec = 1.0;                                                                   // ...
                static int healthPercentage = 100;                                                                          // ...

                if(ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)){                                      // create collapsible section for sprite
                    ImGui::Combo("texture id", &texturesIndex, textures, IM_ARRAYSIZE(textures));                           // create combobox for texture id
                }
                ImGui::Spacing();                                                                                           // add spacing

                if(ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)){                                   // create collapsible section for transform
                    ImGui::InputFloat("x position", &xPos, 1.0f, 0.0f, "%.0f");                                             // create input for x position
                    ImGui::InputFloat("y position", &yPos, 1.0f, 0.0f, "%.0f");                                             // create input for y position
                    ImGui::SliderFloat("x scale", &xScale, 0.0, 5.0, "%.1f");                                               // create input for x scale
                    ImGui::SliderFloat("y scale", &yScale, 0.0, 5.0, "%.1f");                                               // create input for y scale
                    ImGui::SliderAngle("angle (deg)", &rotation, 0.0f, 360.0f);                                             // create slider for rotation
                }
                ImGui::Spacing();                                                                                           // add spacing

                if(ImGui::CollapsingHeader("Rigid body", ImGuiTreeNodeFlags_DefaultOpen)){                                  // create collapsible section for rigid body
                    ImGui::InputFloat("x velocity", &xVel, 1.0f, 0.0f, "%.0f");                                             // create input for x velocity
                    ImGui::InputFloat("y velocity", &yVel, 1.0f, 0.0f, "%.0f");                                             // create input for y velocity
                }
                ImGui::Spacing();                                                                                           // add spacing

                if(ImGui::CollapsingHeader("Projectile emitter", ImGuiTreeNodeFlags_DefaultOpen)){                          // create collapsible section for projectile emitter
                    ImGui::SliderAngle("angle", &projectileAngleRad, 0);                                                    // create slider for projectile angle
                    ImGui::InputFloat("speed (px/sec)", &projectileSpeed, 1.0f, 0.0f, "%.0f");                                                    // create input for projectile speed
                    ImGui::SliderFloat("repeat (hz)", &projectileRepeatHz, 0, 10, "%.1f");                                  // create slider for repeat hz
                    ImGui::SliderFloat("duration (sec)", &projectileDurationSec, 0, 10, "%.1f");                            // create slider for projectile duration
                }
                ImGui::Spacing();                                                                                           // add spacing

                if(ImGui::CollapsingHeader("Health", ImGuiTreeNodeFlags_DefaultOpen)){                                      // create collapsible section for heatlh
                    ImGui::SliderInt("health %", &healthPercentage, 0, 100);                                                // create slider for health percentage
                }
                ImGui::Spacing();                                                                                           // add spacing

                if(ImGui::Button("Create new enemy")){
                    float projectileXPos = static_cast<float>(cos(projectileAngleRad) * projectileSpeed);                   // get x component of projectile speed vector
                    float projectileYPos = static_cast<float>(-sin(projectileAngleRad) * projectileSpeed);                  // get y component of projectile speed vector
                    int repeatFrequencyMil = static_cast<int>((1/projectileRepeatHz) * 1000);                               // convert projectile repeat hz to milliseconds
                    int projectileDurationMil = static_cast<int>(projectileDurationSec * 1000);                             // convert projectile duration to milliseconds

                    Entity enemy = registry->CreateEntity();                                                                // creat enemy entity
                    enemy.Group("enemies");                                                                                 // add 'enemies' tag to enemy
                    enemy.AddComponent<TransformComponent>(glm::vec2(xPos, yPos), glm::vec2(xScale, yScale), glm::degrees(rotation));   // add transform component to enemy
                    enemy.AddComponent<RigidBodyComponent>(glm::vec2(xVel, yVel));                                          // add rigid body component to enemy
                    enemy.AddComponent<SpriteComponent>(textures[texturesIndex], 32, 32, 1);                                // add sprite component to enemy
                    enemy.AddComponent<BoxColliderComponent>(32, 32, glm::vec2(xScale, yScale));                            // add box collider component
                    enemy.AddComponent<ProjectileEmitterComponent>(glm::vec2(projectileXPos, projectileYPos), repeatFrequencyMil, projectileDurationMil, 25, false);    // add projectile emitter component to enemy
                    enemy.AddComponent<HealthComponent>(healthPercentage);                                                  // add health component to enemy
                }
            }
            ImGui::End();                                                                                                   // end "Spawn enemies" ImGui window

            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;  // set window flags for "Map coordinates" ImGui window
            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always, ImVec2(0, 0));                                        // set widnow position for "Map coordinates" ImGui window
            ImGui::SetNextWindowBgAlpha(0.9f);

            if(ImGui::Begin("Map coordinates", NULL, windowFlags)){                                                         // create "Map coordinates" ImGui window
                ImGui::Text(                                                                                                // add mouse pointer position to window
                    "Map coordinates (x=%.1f, y=%.1f)",                                                                     // ...
                    ImGui::GetIO().MousePos.x,                                                                              // ...
                    ImGui::GetIO().MousePos.y                                                                               // ...
                );
            }
            ImGui::End();                                                                                                   // end "Map coordinates" ImGui window

            ImGui::Render();                                                                                                // render ImGui
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);                                          // ...
        }
};

#endif

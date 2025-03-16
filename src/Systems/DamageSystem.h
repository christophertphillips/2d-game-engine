#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"

class DamageSystem: public System{
    public:
        DamageSystem(){
            RequireComponent<BoxColliderComponent>();                                                                       // require box collider component
        }

        void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus){
            eventBus->SubscribeEventCallback<DamageSystem, CollisionEvent>(this, &DamageSystem::onCollision);               // subscribe onCollision callback function pointer to event bus
        }

        void onCollision(CollisionEvent& event){
            Logger::Log("The damage system received a collision event between entities " + std::to_string(event.a.GetId()) + " and " + std::to_string(event.b.GetId()));
            event.a.KillEntity();                                                                                           // kill entity a
            event.b.KillEntity();                                                                                           // kill entity b
        }

        void onProjectileHitsPlayer(Entity projectile, Entity player){
            auto projectileComponent = projectile.GetComponent<ProjectileComponent>();                                      // get projectile's projectile component

            if(!projectileComponent.isFriendly){                                                                            // is the projectile non-friendly (e.g., fired by an enemy)?
                auto& healthComponent = player.GetComponent<HealthComponent>();                                             // if yes, get player's health component

                healthComponent.healthPercentage -= projectileComponent.hitPercentDamange;                                  // subtract projectile's hitPercentDamage from enemy's healthPercentage
                if(healthComponent.healthPercentage <= 0){                                                                  // is the enemy's healthPercentage less than or equal to 0?
                    player.KillEntity();                                                                                    // if yes, kill the enemy
                }

                projectile.KillEntity();                                                                                    // kill the projectile
            }
        }

        void onProjectileHitsEnemy(Entity projectile, Entity enemy){
            auto projectileComponent = projectile.GetComponent<ProjectileComponent>();                                      // get projectile's projectile component

            if(projectileComponent.isFriendly){                                                                             // is the projectile friendly (e.g., fired by the player)?
                auto& healthComponent = enemy.GetComponent<HealthComponent>();                                              // if yes, get enemy's health component

                healthComponent.healthPercentage -= projectileComponent.hitPercentDamange;                                  // subtract projectile's hitPercentDamage from enemy's healthPercentage
                if(healthComponent.healthPercentage <= 0){                                                                  // is the enemy's healthPercentage less than or equal to 0?
                    enemy.KillEntity();                                                                                     // if yes, kill the enemy
                }

                projectile.KillEntity();                                                                                    // kill the projectile
            }
        }

        void Update(){

        }
};

#endif

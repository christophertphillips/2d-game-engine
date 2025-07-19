--set day/night tilemap asset id depending on current system hour
local current_system_hour = os.date("*t").hour                                                                              -- get current system hour

local tilemap_asset_id_day_night                                                                                            -- declare variable to hold tilemap asset id
if current_system_hour >= 9 and current_system_hour < 18 then                                                               -- if the current system hour is between 9 AM and 5 PM...
    tilemap_asset_id_day_night = "tilemap-image"                                                                            -- ... set the tilemap asset id to the daytime tile set
else
    tilemap_asset_id_day_night = "tilemap-image-night"                                                                      -- ... else, set it to the nighttime tile set
end

level = {
    assets = {
        [0] =
        { type = "texture", id = "tilemap-image",             file_path = "./assets/tilemaps/jungle.png" },
        { type = "texture", id = "tilemap-image-night",       file_path = "./assets/tilemaps/jungle-night.png" },
        { type = "texture", id = "chopper-image",             file_path = "./assets/images/chopper-green-spritesheet.png" },
        { type = "texture", id = "su27-image",                file_path = "./assets/images/su27-spritesheet.png" },
        { type = "texture", id = "f22-image",                 file_path = "./assets/images/f22-spritesheet.png" },
        { type = "texture", id = "fw190-image",               file_path = "./assets/images/fw190-spritesheet.png" },
        { type = "texture", id = "upf7-image",                file_path = "./assets/images/upf7-spritesheet.png" },
        { type = "texture", id = "bf109-image",               file_path = "./assets/images/bf109-spritesheet.png" },
        { type = "texture", id = "bomber-image",              file_path = "./assets/images/bomber-spritesheet.png" },
        { type = "texture", id = "carrier-image",             file_path = "./assets/images/carrier.png" },
        { type = "texture", id = "boat-image",                file_path = "./assets/images/boat.png" },
        { type = "texture", id = "tank-tiger-up-image",       file_path = "./assets/images/tank-tiger-up.png" },
        { type = "texture", id = "tank-tiger-right-image",    file_path = "./assets/images/tank-tiger-right.png" },
        { type = "texture", id = "tank-tiger-down-image",     file_path = "./assets/images/tank-tiger-down.png" },
        { type = "texture", id = "tank-tiger-left-image",     file_path = "./assets/images/tank-tiger-left.png" },
        { type = "texture", id = "tank-tiger-killed-image",   file_path = "./assets/images/tank-tiger-killed.png" },
        { type = "texture", id = "tank-panther-up-image",     file_path = "./assets/images/tank-panther-up.png" },
        { type = "texture", id = "tank-panther-right-image",  file_path = "./assets/images/tank-panther-right.png" },
        { type = "texture", id = "tank-panther-down-image",   file_path = "./assets/images/tank-panther-down.png" },
        { type = "texture", id = "tank-panther-left-image",   file_path = "./assets/images/tank-panther-left.png" },
        { type = "texture", id = "tank-panther-killed-image", file_path = "./assets/images/tank-panther-killed.png" },
        { type = "texture", id = "truck-ford-up-image",       file_path = "./assets/images/truck-ford-up.png" },
        { type = "texture", id = "truck-ford-right-image",    file_path = "./assets/images/truck-ford-right.png" },
        { type = "texture", id = "truck-ford-down-image",     file_path = "./assets/images/truck-ford-down.png" },
        { type = "texture", id = "truck-ford-left-image",     file_path = "./assets/images/truck-ford-left.png" },
        { type = "texture", id = "truck-ford-killed-image",   file_path = "./assets/images/truck-ford-killed.png" },
        { type = "texture", id = "army-walk-up-image",        file_path = "./assets/images/army-walk-up.png" },
        { type = "texture", id = "army-walk-right-image",     file_path = "./assets/images/army-walk-right.png" },
        { type = "texture", id = "army-walk-down-image",      file_path = "./assets/images/army-walk-down.png" },
        { type = "texture", id = "army-walk-left-image",      file_path = "./assets/images/army-walk-left.png" },
        { type = "texture", id = "army-walk-killed-image",    file_path = "./assets/images/army-walk-killed.png" },
        { type = "texture", id = "army-gun-up-image",         file_path = "./assets/images/army-gun-up.png" },
        { type = "texture", id = "army-gun-right-image",      file_path = "./assets/images/army-gun-right.png" },
        { type = "texture", id = "army-gun-down-image",       file_path = "./assets/images/army-gun-down.png" },
        { type = "texture", id = "army-gun-left-image",       file_path = "./assets/images/army-gun-left.png" },
        { type = "texture", id = "sam-truck-right-image",     file_path = "./assets/images/sam-truck-right.png" },
        { type = "texture", id = "sam-tank-left-image",       file_path = "./assets/images/sam-tank-left-spritesheet.png" },
        { type = "texture", id = "sam-tank-right-image",      file_path = "./assets/images/sam-tank-right-spritesheet.png" },
        { type = "texture", id = "takeoff-base-image",        file_path = "./assets/images/takeoff-base.png" },
        { type = "texture", id = "landing-base-image",        file_path = "./assets/images/landing-base.png" },
        { type = "texture", id = "runway-image",              file_path = "./assets/images/runway.png" },
        { type = "texture", id = "obstacles1-image",          file_path = "./assets/images/obstacles-1.png" },
        { type = "texture", id = "obstacles2-image",          file_path = "./assets/images/obstacles-2.png" },
        { type = "texture", id = "obstacles3-image",          file_path = "./assets/images/obstacles-3.png" },
        { type = "texture", id = "obstacles4-image",          file_path = "./assets/images/obstacles-4.png" },
        { type = "texture", id = "obstacles5-image",          file_path = "./assets/images/obstacles-5.png" },
        { type = "texture", id = "obstacles6-image",          file_path = "./assets/images/obstacles-6.png" },
        { type = "texture", id = "obstacles7-image",          file_path = "./assets/images/obstacles-7.png" },
        { type = "texture", id = "tree1-image",               file_path = "./assets/images/tree-1.png" },
        { type = "texture", id = "tree2-image",               file_path = "./assets/images/tree-2.png" },
        { type = "texture", id = "tree3-image",               file_path = "./assets/images/tree-3.png" },
        { type = "texture", id = "tree4-image",               file_path = "./assets/images/tree-4.png" },
        { type = "texture", id = "tree5-image",               file_path = "./assets/images/tree-5.png" },
        { type = "texture", id = "tree6-image",               file_path = "./assets/images/tree-6.png" },
        { type = "texture", id = "tree7-image",               file_path = "./assets/images/tree-7.png" },
        { type = "texture", id = "tree8-image",               file_path = "./assets/images/tree-8.png" },
        { type = "texture", id = "tree9-image",               file_path = "./assets/images/tree-9.png" },
        { type = "texture", id = "tree10-image",              file_path = "./assets/images/tree-10.png" },
        { type = "texture", id = "tree11-image",              file_path = "./assets/images/tree-11.png" },
        { type = "texture", id = "tree12-image",              file_path = "./assets/images/tree-12.png" },
        { type = "texture", id = "tree13-image",              file_path = "./assets/images/tree-13.png" },
        { type = "texture", id = "tree14-image",              file_path = "./assets/images/tree-14.png" },
        { type = "texture", id = "tree15-image",              file_path = "./assets/images/tree-15.png" },
        { type = "texture", id = "tree16-image",              file_path = "./assets/images/tree-16.png" },
        { type = "texture", id = "tree17-image",              file_path = "./assets/images/tree-17.png" },
        { type = "texture", id = "tree18-image",              file_path = "./assets/images/tree-18.png" },
        { type = "texture", id = "tree19-image",              file_path = "./assets/images/tree-19.png" },
        { type = "texture", id = "tree20-image",              file_path = "./assets/images/tree-20.png" },
        { type = "texture", id = "bullet-image",              file_path = "./assets/images/bullet.png" },
        { type = "texture", id = "radar-image",               file_path = "./assets/images/radar-spritesheet.png" },
        { type = "font"   , id = "pico8-font-5",                file_path = "./assets/fonts/pico8.ttf", font_size = 5 },
        { type = "font"   , id = "pico8-font-10",               file_path = "./assets/fonts/pico8.ttf", font_size = 10 },
        { type = "font",    id = "charriot-font-12", file_path = "./assets/fonts/charriot.ttf",             font_size = 12 },
        { type = "texture", id = "tank-image",       file_path = "./assets/images/tank-panther-right.png"                  },
        { type = "texture", id = "truck-image",      file_path = "./assets/images/truck-ford-right.png"                    },
    },
    tilemap = {
        map_file_path = "./assets/tilemaps/jungle.map",
        tilemap_asset_id = tilemap_asset_id_day_night,
        tile_rows = 20,
        tile_cols = 25,
        tile_size = 32,
        tile_scale = 2.0
    },
    entities = {
        [0] =
        {
            -- Player
            tag = "player",
            components = {
                transform_component = {
                    position = { x = 242, y = 110 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigid_body_component = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite_component = {
                    asset_id = "chopper-image",
                    width = 32,
                    height = 32,
                    z_index = 4,
                    is_fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                },
                box_collider_component = {
                    width = 32,
                    height = 25,
                    offset = { x = 0, y = 5 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 200, y = 200 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 0, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = true
                },
                keyboard_controlled_component = {
                    up_velocity = { x = 0, y = -100 },
                    right_velocity = { x = 100, y = 0 },
                    down_velocity = { x = 0, y = 100 },
                    left_velocity = { x = -100, y = 0 }
                },
                camera_follow_component = {
                    follow = true
                }
            }
        },
        {
            -- Takeoff base
            components = {
                transform_component = {
                    position = { x = 240, y = 113 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "takeoff-base-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Landing base
            components = {
                transform_component = {
                    position = { x = 1396, y = 493 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "landing-base-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Radar UI animation
            group = "ui",
            components = {
                transform_component = {
                    position = { x = 10, y = 10 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "radar-image",
                    width = 64,
                    height = 64,
                    z_index = 10,
                    is_fixed = true
                },
                animation_component = {
                    num_frames = 8,
                    frame_speed_rate = 7 -- fps
                }
            }
        },
        {
            -- Runway
            components = {
                transform_component = {
                    position = { x = 940, y = 65 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 270.0, -- degrees
                },
                sprite_component = {
                    asset_id = "runway-image",
                    width = 21,
                    height = 191,
                    z_index = 1
                }
            }
        },
        {
            -- Runway
            components = {
                transform_component = {
                    position = { x = 470, y = 385 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "runway-image",
                    width = 21,
                    height = 191,
                    z_index = 1
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 200, y = 497 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 0, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 100, y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 20,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 785, y = 170 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 18,
                    offset = { x = 7, y = 10 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -50 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 785, y = 250 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 20,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 20 },
                    projectile_duration = 3, -- seconds
                    repeat_frequency = 3, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 785, y = 350 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -50, y = 0 },
                    projectile_duration = 3, -- seconds
                    repeat_frequency = 3, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 570, y = 520 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 60, y = 0 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 570, y = 600 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -60, y = 0 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1050, y = 170 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 60, y = 0 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1170, y = 116 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 18,
                    offset = { x = 8, y = 6 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 40 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1380, y = 116 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 18,
                    offset = { x = 8, y = 6 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 40 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1265, y = 240 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-killed-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1265, y = 290 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 20,
                    height = 17,
                    offset = { x = 7, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -40, y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 640, y = 800 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 18,
                    height = 20,
                    offset = { x = 7, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 100 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 5, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 790, y = 745 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 7, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -60, y = 0 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 980, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 0, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 60, y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1070, y = 870 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 8, y = 4 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 100 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1190, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1210, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1230, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1250, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1000, y = 445 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 7, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1426, y = 760 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 22,
                    height = 18,
                    offset = { x = 5, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 200, y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1423, y = 835 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 18,
                    offset = { x = 7, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -200, y = 0 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1450, y = 300 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 19,
                    height = 20,
                    offset = { x = 6, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 300 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 195, y = 980 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-tiger-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 18,
                    height = 25,
                    offset = { x = 7, y = 7 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -100 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 110, y = 1125 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 17,
                    height = 20,
                    offset = { x = 8, y = 4 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = 300 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1395, y = 540 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tank-panther-killed-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 113, y = 580 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 180, y = 1045 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 195, y = 1055 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 210, y = 1065 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 545, y = 660 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 560, y = 670 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1360, y = 880 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 20,
                    offset = { x = 10, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1380, y = 880 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 20,
                    offset = { x = 10, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1400, y = 880 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 12,
                    height = 20,
                    offset = { x = 10, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1505, y = 780 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                box_collider_component = {
                    width = 25,
                    height = 16,
                    offset = { x = 3, y = 10 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1515, y = 790 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "truck-ford-left-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 25,
                    height = 16,
                    offset = { x = 3, y = 10 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- SAM Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 495, y = 380 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-tank-left-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 2 -- fps
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -50, y = -50 },
                    projectile_duration = 3, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 495, y = 410 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-tank-left-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 2 -- fps
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -50, y = -50 },
                    projectile_duration = 3, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1290, y = 115 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-tank-left-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 2 -- fps
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -100, y = -75 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Tank
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 935, y = 557 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-tank-left-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 2 -- fps
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = -100, y = -60 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 114, y = 700 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-truck-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 50, y = -50 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 114, y = 720 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-truck-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 50, y = -50 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 116, y = 499 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-truck-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 50, y = -70 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1454, y = 215 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-truck-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 50, y = -70 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1454, y = 231 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-truck-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 50, y = -70 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- SAM Truck
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1454, y = 247 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "sam-truck-right-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                box_collider_component = {
                    width = 17,
                    height = 15,
                    offset = { x = 8, y = 8 }
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 50, y = -70 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    is_friendly = false
                }
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 115, y = 633 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree5-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 117, y = 650 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree5-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 318, y = 490 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree6-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 668, y = 526 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree14-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 1018, y = 738 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree17-image",
                    width = 17,
                    height = 20,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 1034, y = 738 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree17-image",
                    width = 17,
                    height = 20,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 1028, y = 745 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree18-image",
                    width = 17,
                    height = 20,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 1390, y = 440 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree10-image",
                    width = 31,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 1400, y = 445 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree10-image",
                    width = 31,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform_component = {
                    position = { x = 1365, y = 290 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "tree14-image",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 669, y = 549 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 685, y = 549 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 315, y = 505 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 3
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 330, y = 507 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 438, y = 390 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 1
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 449, y = 408 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 431, y = 416 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 940, y = 695 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 955, y = 705 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1085, y = 507 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1075, y = 527 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1075, y = 547 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1085, y = 567 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1355, y = 449 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles2-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1430, y = 446 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles2-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1435, y = 195 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1425, y = 215 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1425, y = 235 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1425, y = 255 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1435, y = 275 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1360, y = 310 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 1
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1380, y = 312 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles7-image",
                    width = 16,
                    height = 16,
                    z_index = 1
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1330, y = 212 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles1-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform_component = {
                    position = { x = 1360, y = 232 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "obstacles1-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 630, y = 405 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 497, y = 450 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 572, y = 560 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-gun-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 114, y = 980 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 114, y = 1030 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 883, y = 490 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 113, y = 851 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-gun-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 750, y = 630 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-left-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 800, y = 630 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 856, y = 115 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-gun-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 900, y = 115 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-gun-up-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 1117, y = 530 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-right-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 755, y = 440 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-gun-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 810, y = 440 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-gun-down-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 1390, y = 690 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-killed-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 1425, y = 690 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-killed-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform_component = {
                    position = { x = 1465, y = 690 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "army-walk-killed-image",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Boat
            components = {
                transform_component = {
                    position = { x = 80, y = 520 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "boat-image",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat
            components = {
                transform_component = {
                    position = { x = 80, y = 790 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "boat-image",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat
            components = {
                transform_component = {
                    position = { x = 345, y = 423 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 270.0, -- degrees
                },
                sprite_component = {
                    asset_id = "boat-image",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat
            components = {
                transform_component = {
                    position = { x = 1510, y = 460 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "boat-image",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Carrier
            components = {
                transform_component = {
                    position = { x = 670, y = 150 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "carrier-image",
                    width = 59,
                    height = 191,
                    z_index = 1
                },
            }
        },
        {
            -- Carrier
            components = {
                transform_component = {
                    position = { x = 300, y = 975 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "carrier-image",
                    width = 59,
                    height = 191,
                    z_index = 1
                },
            }
        },
        {
            -- F-22 fighter jet
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 688, y = 165 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "f22-image",
                    width = 32,
                    height = 32,
                    z_index = 4
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                },
                box_collider_component = {
                    width = 20,
                    height = 25,
                    offset = { x = 5, y = 5}
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- SU-27 fighter jet
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 685, y = 300 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = -10.0, -- degrees
                },
                rigid_body_component = {
                    velocity = { x = -5.5 , y = -35.0 }
                },
                sprite_component = {
                    asset_id = "su27-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                },
                box_collider_component = {
                    width = 25,
                    height = 30,
                    offset = { x = 5, y = 0 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Bomber plane
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 464, y = 520 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "bomber-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                },
                box_collider_component = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- FW190 plane
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 1000, y = 143 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = -90.0, -- degrees
                },
                rigid_body_component = {
                    velocity = { x = -50.0, y = 0.0 }
                },
                sprite_component = {
                    asset_id = "fw190-image",
                    width = 32,
                    height = 32,
                    z_index = 6
                },
                animation_component = {
                    num_frames = 3,
                    frame_speed_rate = 15 -- fps
                },
                box_collider_component = {
                    width = 32,
                    height = 30,
                    offset = { x = 0, y = 0 }
                },
                health_component = {
                    health_percentage = 100
                }
            }
        },
        {
            -- UPF7 plane
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 920, y = 179 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "upf7-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                }
            }
        },
        {
            -- UPF7 plane
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 950, y = 179 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "upf7-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                }
            }
        },
        {
            -- UPF7 plane
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 980, y = 179 },
                    scale = { x = 0.8, y = 0.8 },
                    rotation = 0.0, -- degrees
                },
                sprite_component = {
                    asset_id = "upf7-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    frame_speed_rate = 10 -- fps
                }
            }
        },
        {
            -- SU-27 fighter jet
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 317, y = 985 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigid_body_component = {
                    velocity = { x = 0.0, y = -50.0 }
                },
                sprite_component = {
                    asset_id = "su27-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                box_collider_component = {
                    width = 32,
                    height = 32
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 0, y = -100 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                },
                script_component = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        -- this function makes the fighter jet move up and down the map shooting projectiles
                        local current_position_x, current_position_y = get_entity_position(entity)
                        local current_velocity_x, current_velocity_y = get_entity_velocity(entity)

                        -- if it reaches the top or the bottom of the map
                        if current_position_y < 10  or current_position_y > map_height - (32 + 10 + 1) then
                            set_entity_velocity(entity, 0, current_velocity_y * -1); -- flip the entity y-velocity
                        else
                            set_entity_velocity(entity, 0, current_velocity_y); -- do not flip y-velocity
                        end

                        -- set the transform rotation to match going up or down
                        if (current_velocity_y < 0) then
                            set_entity_rotation(entity, 0) -- point up
                            set_entity_projectile_emitter_velocity(entity, 0, -200) -- shoot projectiles up
                        else
                            set_entity_rotation(entity, 180) -- point down
                            set_entity_projectile_emitter_velocity(entity, 0, 200) -- shoot projectiles down
                        end
                    end
                }
            }
        },
        {
            -- F-22 fighter jet
            group = "enemies",
            components = {
                transform_component = {
                    position = { x = 10, y = 10 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 90.0, -- degrees
                },
                rigid_body_component = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite_component = {
                    asset_id = "f22-image",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation_component = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                box_collider_component = {
                    width = 32,
                    height = 32
                },
                health_component = {
                    health_percentage = 100
                },
                projectile_emitter_component = {
                    projectile_velocity = { x = 200, y = 0 },
                    projectile_duration = 1, -- secondsm
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    is_friendly = false
                },
                script_component = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        -- change the position of the the airplane to follow a sine wave movement
                        local new_x = ellapsed_time * 0.09
                        local new_y = 200 + (math.sin(ellapsed_time * 0.001) * 50)
                        set_entity_position(entity, new_x, new_y) -- set the new position
                    end
                }
            }
        }
    }
}

map_width = level.tilemap.tile_cols * level.tilemap.tile_size * level.tilemap.tile_scale
map_height = level.tilemap.tile_rows * level.tilemap.tile_size * level.tilemap.tile_scale

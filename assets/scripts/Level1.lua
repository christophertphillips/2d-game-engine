level = {
    assets = {
        [0] =
        { type = "texture", id = "jungle-map",    file_path = "./assets/tilemaps/jungle.png"                               },
        { type = "texture", id = "chopper-image",    file_path = "./assets/images/chopper-spritesheet.png"                 },
        { type = "texture", id = "tank-image",       file_path = "./assets/images/tank-panther-right.png"                  },
        { type = "texture", id = "bullet-image",     file_path = "./assets/images/bullet.png"                              },
        { type = "texture", id = "truck-image",      file_path = "./assets/images/truck-ford-right.png"                    },
        { type = "texture", id = "radar-image",      file_path = "./assets/images/radar.png"                               },
        { type = "texture", id = "tree-image",       file_path = "./assets/images/tree.png"                                },
        { type = "font",    id = "charriot-font",    file_path = "./assets/fonts/charriot.ttf",             font_size = 24 },
        { type = "font",    id = "charriot-font-12", file_path = "./assets/fonts/charriot.ttf",             font_size = 12 },
    },
    tilemap = {
        map_file_path = "./assets/tilemaps/jungle.map",
        texture_id = "tilemap-texture",
        tile_size = 32,
        tile_scale = 2.0
    },
    entities = {
        [0] =
        {
            tag = "player",
            components = {
                transform_component = {
                    position = {
                        x = 100.0,
                        y = 100.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
                rigid_body_component = {
                    velocity = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
                sprite_component = {
                    asset_id = "chopper-image",
                    width = 32,
                    height = 32,
                    z_index = 20,
                    is_fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0,
                },
                box_collider_component = {
                    width = 32,
                    height = 32,
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    offset = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
                health_component = {
                    health_percentage = 100,
                },
                projectile_emitter_component = {
                    projectile_velocity = {
                        x = 200.0,
                        y = 200.0
                    },
                    repeat_frequency = 0,
                    projectile_duration = 4,
                    hit_percentage_damage = 25,
                    is_friendly = true,
                },
                camera_follow_component = {
                    follow = true,
                },
            },
        },
        {
            components = {
                transform_component = {
                    position = {
                        x = 726.0,
                        y = 10.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
                sprite_component = {
                    asset_id = "radar-image",
                    width = 64,
                    height = 64,
                    z_index = 30,
                    is_fixed = true,
                    src_rect_x = 0,
                    src_rect_y = 0,
                },
            },
        },
        {
            group = "enemies",
            components = {
                transform_component = {
                    position = {
                        x = 500.0,
                        y = 500.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
                rigid_body_component = {
                    velocity = {
                        x = 25.0,
                        y = 0.0,
                    },
                },
                sprite_component = {
                    asset_id = "tank-image",
                    width = 32,
                    height = 32,
                    z_index = 1,
                    is_fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0,
                },
                box_collider_component = {
                    width = 32,
                    height = 32,
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    offset = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
                health_component = {
                    health_percentage = 100,
                },
                projectile_emitter_component = {
                    projectile_velocity = {
                        x = 0.0,
                        y = -100.0
                    },
                    repeat_frequency = 1,
                    projectile_duration = 4,
                    hit_percentage_damage = 25,
                    is_friendly = false,
                },
            },
        },
        {
            group = "enemies",
            components = {
                transform_component = {
                    position = {
                        x = 115.0,
                        y = 500.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
                rigid_body_component = {
                    velocity = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
                sprite_component = {
                    asset_id = "truck-image",
                    width = 32,
                    height = 32,
                    z_index = 1,
                    is_fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0,
                },
                box_collider_component = {
                    width = 32,
                    height = 32,
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    offset = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
                health_component = {
                    health_percentage = 100,
                },
                projectile_emitter_component = {
                    projectile_velocity = {
                        x = 0.0,
                        y = -100.0
                    },
                    repeat_frequency = 1,
                    projectile_duration = 2,
                    hit_percentage_damage = 25,
                    is_friendly = false,
                },
            },
        },
        {
            group = "obstacles",
            components = {
                transform_component = {
                    position = {
                        x = 400.0,
                        y = 490.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
                sprite_component = {
                    asset_id = "tree-image",
                    width = 16,
                    height = 32,
                    z_index = 10,
                    is_fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0,
                },
                box_collider_component = {
                    width = 16,
                    height = 32,
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    offset = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
            },
        },
        {
            group = "obstacles",
            components = {
                transform_component = {
                    position = {
                        x = 600.0,
                        y = 495.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
                sprite_component = {
                    asset_id = "tree-image",
                    width = 16,
                    height = 32,
                    z_index = 10,
                    is_fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0,
                },
                box_collider_component = {
                    width = 16,
                    height = 32,
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    offset = {
                        x = 0.0,
                        y = 0.0,
                    },
                },
            },
        },
        {
            components = {
                transform_component = {
                    position = {
                        x = 360.0,
                        y = 10.0,
                    },
                    scale = {
                        x = 1.0,
                        y = 1.0,
                    },
                    rotation = 0.0,
                },
            },
        },
    }
}

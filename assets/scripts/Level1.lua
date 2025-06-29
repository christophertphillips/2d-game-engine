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

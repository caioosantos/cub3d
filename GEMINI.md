# GEMINI.md

This guide outlines the best practices for developing "Counter-Strike 3," a 3D first-person shooter game written in C, inspired by the classic Wolfenstein 3D. The game will use the MLX library for rendering and will implement a raycasting algorithm to draw the world. The project structure will follow the command pattern using the provided `t_game` struct.

---

### Project Overview

**Game Title:** Counter-Strike 3
**Language:** C
**Core Technology:** Raycasting for 3D rendering
**Graphics Library:** MLX42
**Design Pattern:** Command pattern using the `t_game` struct
**Key Features:**
* **Raycasting Engine:** Render a 3D view from a 2D map.
* **Player Control:** Implement movement and camera rotation.
* **Map Parsing:** Load and interpret a map file to define the game world.
* **Texture Mapping:** Apply textures to the walls to enhance visual detail.
* **Rendering Pipeline:** Use the MLX library's functions to display the rendered frame.

---

### Code Structure and Best Practices

#### 1. The `t_game` Struct and Command Pattern

The `t_game` struct, defined in `cub3D.h`, serves as the central hub for the game's state. It encapsulates all necessary data, including the map, player, and rendering information.

**Best Practice:** The command pattern principle dictates that functions should operate on this struct pointer (`t_game *game`), minimizing the need for global variables and making the code more modular and easier to debug. For example, the `init` and `parse` functions take a `t_game` pointer as an argument, allowing them to initialize and populate the game's state.

```c
typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	mlx_t		*mlx;
	t_ray		*ray;
}	t_game;
````

#### 2\. Raycasting Implementation

The raycasting logic will be contained within the `render.c` file, following the provided function stubs.

**Best Practice:** Break down the complex raycasting process into smaller, manageable functions as already outlined in `render.c`. This approach improves code readability and simplifies debugging.

  * `ray_setup(t_game *game, int i)`: This function will initialize the ray's properties for a given camera column `i`.
	* **Variables to set:** `camera_pixel`, `dir`, `delta_x`, and `delta_y` from the `t_ray` struct.
  * `dda_setup(t_game *game)`: This function will prepare the Digital Differential Analyzer (DDA) algorithm by setting the initial `dist_x`, `dist_y`, `step_x`, and `step_y` values.
  * `dda_exec(t_game *game)`: This function will execute the DDA algorithm, stepping through the grid until a wall is hit. It should update the `map_pos` and determine the `hit_side` of the wall.
  * `calculate_height(t_game *game)`: After a wall is hit, this function will calculate the vertical height of the wall slice to be drawn on the screen based on the perpendicular distance to the wall.
  * `draw_line(t_game *game, int i)`: This function will draw a vertical line on the screen for the current camera column `i`, based on the calculated wall height.

The `raycasting(t_game *game)` function will loop through all vertical screen pixels and call the above functions for each ray.

#### 3\. MLX Integration

The MLX library is essential for rendering the game world.

**Best Practice:** Use the MLX functions to handle the display loop, image creation, and pixel drawing.

  * `generate_frame(t_game *game)`: This function will serve as the main drawing loop. It will first clear the screen by drawing the ceiling and floor, then call `raycasting` to render the walls.
  * The `render(t_game *game)` function will handle the final presentation of the frame to the window. You will likely need to use MLX functions like `mlx_new_image` and `mlx_put_pixel` to build the frame.

-----

### Development Plan

1.  **Initial Setup:**

      * Implement the `init` function to allocate memory for all game structs and initialize the MLX window.
      * Implement the `parse` function to read and validate the map file.

2.  **Player Movement:**

      * Set up a loop hook using `mlx_loop_hook` to capture player input.
      * Implement functions to handle player movement (forward/backward) and rotation (left/right) by modifying the `t_player`'s `pos`, `dir`, and `plane` vectors.

3.  **Raycasting Engine (following `render.c`):**

      * Fill in the `ray_setup` function with the correct mathematical calculations to determine the ray's direction and initial position.
      * Implement the DDA algorithm within `dda_setup` and `dda_exec` to efficiently find wall intersections.
      * Calculate the wall height and draw the vertical lines using `calculate_height` and `draw_line`.

4.  **Final Touches:**

      * Implement the `destroy_game` function to free all allocated memory upon exit to prevent memory leaks.
      * Ensure proper error handling throughout the program, especially during file parsing and memory allocation.

<!-- end list -->

```
```
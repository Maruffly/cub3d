<p align="center">
    <img src="https://img.shields.io/badge/Score-125%2F100-success?style=for-the-badge&logo=42" alt="Score 125/100">
    <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="Language C">
</p>

# 📺 cub3D - SAV des Émissions (Omar & Fred Edition)

**cub3D** is a 3D raycasting engine developed in C. This specific version is a tribute to the famous French comedy duo **Omar & Fred**. Your mission is to survive the service center by avoiding "Omar" or strategically walling him in to prevent him from catching you.



## 🎮 The Game

* **Objective**: Survive the map by navigating through the 3D environment. 
* **The Threat**: Omar is roaming the corridors. If he gets too close, it's game over!
* **Strategy**: Use the environment to your advantage. You must trap Omar by walling him in or using doors to block his path while you search for the exit.
* **Health**: Watch out for the red screen effect! It indicates you are taking damage or are in immediate danger.

---

## 🌟 Bonus Features (125/100)

This version includes the following advanced features beyond the mandatory requirements:
* **Interactive Doors**: Open and close doors using the `E` key to block or allow passage.
* **Animated Sprites**: 2D enemies (Omar) that follow you through the maze.
* **Minimap**: A real-time 2D top-down view to help you navigate and track Omar.
* **Mouse Controls**: Smooth 360° rotation using the mouse (toggled with `M`).
* **Weapon Animation**: An interactive overlay that reacts when you click.
* **Distance-based Collision**: Advanced collision detection between the player, walls, and moving enemies.

---

## 🛠️ Technical Overview

### Raycasting Engine
The core of the game uses the **DDA (Digital Differential Analysis)** algorithm to project a 2D map into a 3D perspective.
* **Vertical Walls**: Rendered based on the distance to the camera plane to avoid the "fisheye" effect.
* **Textures**: Different textures for North, South, East, and West walls.



### AI & Visibility
* **Line of Sight**: Enemies only track you if there is a clear path (no walls or closed doors between you).
* **Pathfinding**: Simple enemy navigation that calculates the best direction to close the distance to the player.
* **Enemy Repulsion**: Logic to prevent multiple enemies from stacking on the same spot.

---

## ⌨️ Controls

| Key | Action |
| :--- | :--- |
| `W`, `A`, `S`, `D` | Move Forward, Left, Backward, Right |
| `Left` / `Right` | Rotate Camera |
| `E` | Interact with Doors |
| `M` | Toggle Mouse View |
| `ESC` | Exit Game |
| `Mouse Click` | Trigger Weapon Animation |

---

## Installation & Usage

### 1. Build mlx library
Inside the mlx folder:
```bash
make
```
### 2. Build game
```bash
make bonus
```
### 3. Launch game
```bash
./cub3d maps/<selected_map>
```


# 🐍 Retro Snake

A classic Snake game built in C++ using [raylib](https://www.raylib.com/), featuring smooth gameplay, sound effects, score tracking, and a retro aesthetic.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus) ![raylib](https://img.shields.io/badge/raylib-5.x-orange) ![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

---

## 🎮 Gameplay

Guide the snake to eat food, grow longer, and rack up the highest score — without hitting the walls or yourself!

![Snake Game Screenshot](media/screenshot.png)

---

## ✨ Features

- Smooth, grid-based snake movement
- Food with custom texture
- Collision detection — walls, edges, and self
- Sound effects for eating and game over
- Mute / unmute toggle
- Persistent best score tracked per session
- Start screen and game over overlay
- Retro green color palette

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| `Enter` | Start game / Restart after game over |
| `↑ ↓ ← →` | Move snake |
| `L` | Mute sound |
| `S` | Unmute sound |

---

## 🏗️ Project Structure

```
retro-snake/
├── main.cpp          # All game logic
├── media/
│   ├── food.png      # Food sprite
│   ├── eat.mp3       # Eat sound effect
│   └── wall.mp3      # Game over sound effect
└── README.md
```

---

## 🔧 Dependencies

- [raylib](https://github.com/raysan5/raylib) — graphics, input, audio, and math

Install raylib via your package manager or follow the [official instructions](https://github.com/raysan5/raylib#build-and-installation).

---

## 🚀 Building & Running

### Linux / macOS

```bash
g++ main.cpp -o snake -lraylib -lm -lpthread -ldl -lrt -lX11
./snake
```

### Windows (MinGW)

```bash
g++ main.cpp -o snake.exe -lraylib -lopengl32 -lgdi32 -lwinmm
snake.exe
```

### Using CMake

```cmake
cmake_minimum_required(VERSION 3.15)
project(RetroSnake)

set(CMAKE_CXX_STANDARD 17)
find_package(raylib REQUIRED)

add_executable(RetroSnake main.cpp)
target_link_libraries(RetroSnake raylib)
```

```bash
cmake -B build && cmake --build build
./build/RetroSnake
```

> Make sure the `media/` folder is in the same directory as the executable when running.

---

## 🎨 Customization

You can tweak these constants at the top of `main.cpp`:

| Variable | Default | Description |
|----------|---------|-------------|
| `cellsize` | `30` | Size of each grid cell in pixels |
| `cellCount` | `25` | Number of cells per row/column |
| `offset` | `75` | Border width in pixels |

The game window size is calculated automatically as `2 * offset + cellsize * cellCount`.

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

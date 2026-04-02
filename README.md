# 🐍 Retro Snake

A classic Snake game built in C++ using [raylib](https://www.raylib.com/), featuring smooth gameplay, sound effects, score tracking, and a retro aesthetic.

Retro Snake is a modern take on the timeless arcade classic. The snake lives on a 25×25 grid, growing one segment longer every time it devours a piece of food. The challenge ramps up naturally — the longer your snake, the harder it becomes to avoid your own tail. One wrong turn and it's game over.

The game is built entirely from scratch in a single C++ file using raylib for rendering, input handling, and audio. It is lightweight, dependency-minimal, and cross-platform, making it a great reference project for anyone learning game development in C++.

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

## 🧠 How It Works

The game is structured around three core classes:

- **`Snake`** — Stores the snake's body as a `deque<Vector2>`, where the front is the head and the back is the tail. Movement is handled by pushing a new head cell and popping the tail each tick. Eating food skips the pop, effectively growing the snake by one.

- **`Food`** — Loads a custom texture and picks a random grid cell that does not overlap the snake's body. A new position is generated every time the snake eats.

- **`Game`** — Orchestrates everything: it owns the snake and food, runs collision detection on every update tick, tracks the score and best score, and manages the running/stopped state.

The main loop runs at 60 FPS, but snake movement is decoupled from the frame rate — the snake updates every 200 ms using a time-based trigger, giving it that characteristic step-by-step arcade feel.

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

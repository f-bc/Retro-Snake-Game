# 🐍 Retro Snake

A classic Snake game built in C++ using [raylib](https://www.raylib.com/), featuring smooth gameplay, sound effects, score tracking, and a retro aesthetic.

![C++](https://img.shields.io/badge/C++-17-blue?logo=cplusplus) ![raylib](https://img.shields.io/badge/raylib-5.x-orange) ![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

---

## 🎮 Gameplay

Guide the snake to eat food, grow longer, and rack up the highest score — without hitting the walls or yourself!

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

## 🔧 Dependencies

- [raylib](https://github.com/raysan5/raylib) — graphics, input, audio, and math

Install raylib via your package manager or follow the [official instructions](https://github.com/raysan5/raylib#build-and-installation).

---

## 🎨 Customization

You can tweak these constants at the top of `main.cpp`:

| Variable | Default | Description |
|----------|---------|-------------|
| `cellsize` | `30` | Size of each grid cell in pixels |
| `cellCount` | `25` | Number of cells per row/column |
| `offset` | `75` | Border width in pixels |

The game window size is calculated automatically as `2 * offset + cellsize * cellCount`.


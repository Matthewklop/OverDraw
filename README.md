# 🔴 OVERDRAW

## DRAW ON YOUR SCREEN. LIKE A GOD.

**No windows. No borders. No bullshit. Just a red marker that answers to you.**

Your desktop is a canvas. Click. Drag. **Create.**

---

### 🎮 CONTROLS

| What | How |
|------|-----|
| **DRAW** | Left-click + drag |
| **ERASE** | Right-click + drag |
| **🟥 RED** | Press `R` |
| **🟦 BLUE** | Press `B` |
| **🟩 GREEN** | Press `G` |
| **🟨 YELLOW** | Press `Y` |
| **🧹 CLEAR** | Press `C` |
| **🚪 QUIT** | Press `Esc` |

---

### ⚡ ONE COMMAND

```bash
gcc overdraw.c -lX11 -o overdraw && ./overdraw
```

That's it. You're drawing.

---

### 🧠 HOW IT WORKS

1. Takes a screenshot of your desktop
2. Creates a fullscreen overlay window with that screenshot as its background
3. You draw on top
4. Right-click erases by restoring the original pixels underneath
5. Override-redirect keeps it above **everything** — yes, above your GNOME panel, above your windows, above your dignity

No toolkit. No framework. No Electron garbage. **Pure X11. Pure C. Pure will.**

---

### 🔧 DEPENDENCIES

- A C compiler (`gcc`)
- X11 development headers (`libx11-dev`)
- A soul

---

### 📦 BUILD

```bash
gcc overdraw.c -lX11 -o overdraw
```

Or don't. The binary is included. Just `./overdraw`.

---

### 🏆 WHY OVERDRAW

Because sometimes you need to draw a red circle around something and the universe isn't fast enough. Because screen annotation tools are bloated. Because you wanted to draw on your desktop and every solution sucked so you built your own.

**OverDraw. Draw over everything.**

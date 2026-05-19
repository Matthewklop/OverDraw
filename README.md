# 🔴 OverDraw

**Draw on your screen. Like a god. No compilation. No terminal. Just draw.**

---

## 🪟 Windows

1. Download **`OverDraw.exe`** from [Releases](https://github.com/Matthewklop/OverDraw/releases)
2. Double-click it
3. **Draw**

## 🐧 Linux

1. Download **`overdraw`** from [Releases](https://github.com/Matthewklop/OverDraw/releases)
2. Right-click → Properties → Permissions → **Allow executing as program**
3. Double-click → **Run**
4. **Draw**

Or terminal one-liner:
```bash
curl -L https://github.com/Matthewklop/OverDraw/releases/download/v1.0/overdraw -o overdraw && chmod +x overdraw && ./overdraw
```

## 🍎 macOS

```bash
gcc overdraw_mac.c -o overdraw -framework Cocoa -framework CoreGraphics && ./overdraw
```
(Working on a prebuilt binary — Apple makes this painful)

---

## 🎮 Controls

| Button | Action |
|--------|--------|
| 🖱 Left-drag | Draw |
| 🖱 Right-drag | Erase |
| ⌨ R / B / G / Y | Color |
| ⌨ C | Clear |
| ⌨ Esc | Quit |

---

## 📦 Downloads

👉 **[github.com/Matthewklop/OverDraw/releases](https://github.com/Matthewklop/OverDraw/releases)**

Prebuilt binaries for Linux and Windows. macOS coming soon.

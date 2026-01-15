# Penrose Tiling: Infinite Geometric Patterns 🧩
A C++ implementation of Penrose Tiling patterns using custom rasterization algorithms (DDA &amp; Scanline). Features Robinson Triangles, Rhombus modes, and Golden Ratio-based subdivision

**What is this project?**
This is a C++ application that generates the famous **Penrose Tiling**—a geometric pattern that extends infinitely without ever repeating itself (aperiodic).
It uses the **Golden Ratio** ($\phi \approx 1.618$) to subdivide shapes recursively.

**Why is it special?**
Unlike standard graphics projects that rely on pre-made tools, this project builds the rendering logic **from scratch**.
* It implements the **DDA Algorithm** to calculate and draw lines pixel-by-pixel.
* It uses the **Scanline Algorithm** to mathematically determine how to fill shapes with color.

**What can it do?**
* **Robinson Triangles:** Renders the classic pattern in pink shades.
* **Rhombus Mode:** Converts triangles into diamond shapes (Rhombuses).
* **Wallpaper Mode:** Generates unique, random-colored patterns sized perfectly for mobile phone wallpapers.

## 📂 Project Structure: Two Versions

To demonstrate both algorithmic understanding and modern development skills, this repository includes two distinct implementations:

### 1. `SimpleLibrary_version` (The Educational Core) 🎓
* **Goal:** To understand the fundamentals of computer graphics by implementing everything **from scratch**.
* **Tech:** Pure C++ with a custom `Image.h` helper.
* **Key Details:**
    * No external graphics libraries were used.
    * **Line Drawing:** Manually calculated using the **DDA Algorithm**.
    * **Filling:** Polygons are filled using a custom **Scanline Algorithm** with Active Edge Tables.
    * *This version is the result of the core learning outcomes of the Computer Graphics course.*

### 2. `SFML_version` (The Modern Engine) 🚀
* **Goal:** To create a smoother, high-performance version of the same logic using industry-standard tools.
* **Tech:** Built with **SFML** (Simple and Fast Multimedia Library).
* **Key Details:**
    * Utilizes hardware acceleration for faster rendering.
    * Provides better window management and real-time visualization.
    * Demonstrates the ability to adapt raw algorithms into modern frameworks.

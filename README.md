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

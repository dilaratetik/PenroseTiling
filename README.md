# Penrose Tiling: Infinite Geometric Patterns 🧩
A C++ implementation of Penrose Tiling patterns using custom rasterization algorithms (DDA &amp; Scanline). Features Robinson Triangles, Rhombus modes, and Golden Ratio-based subdivision

**What is this project?**
This is a C++ application that generates the famous **Penrose Tiling**—a geometric pattern that extends infinitely without ever repeating itself (aperiodic). [cite_start]It uses the **Golden Ratio** ($\phi \approx 1.618$) to subdivide shapes recursively[cite: 14, 15].

**Why is it special?**
Unlike standard graphics projects that rely on pre-made tools, this project builds the rendering logic **from scratch**.
* [cite_start]It implements the **DDA Algorithm** to calculate and draw lines pixel-by-pixel[cite: 27].
* [cite_start]It uses the **Scanline Algorithm** to mathematically determine how to fill shapes with color[cite: 28].

**What can it do?**
* [cite_start]**Robinson Triangles:** Renders the classic pattern in pink shades[cite: 18].
* [cite_start]**Rhombus Mode:** Converts triangles into diamond shapes (Rhombuses)[cite: 19].
* [cite_start]**Wallpaper Mode:** Generates unique, random-colored patterns sized perfectly for mobile phone wallpapers (1080x2160)[cite: 21, 23].

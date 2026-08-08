*This project has been created as part of the 42 curriculum by c3c4d4.*

# Description

`cub3D` is a small first-person maze renderer written in C with MiniLibX. It parses a `.cub` scene, validates that the map is closed, casts one ray per screen column, and applies a different XPM wall texture according to the wall side. The floor and ceiling are flat configurable RGB colors.

# Instructions

On Linux with the X11 development packages installed:

```sh
make
./cub3D scenes/demo.cub
```

Use `W`, `A`, `S`, and `D` to move, the left and right arrow keys to rotate, and `Esc` or the window close button to exit. The bundled `minilibx-linux` source is built automatically by the Makefile.

The scene format follows the subject: `NO`, `SO`, `WE`, `EA`, `F`, and `C` declarations come before the map. The map uses `0`, `1`, and exactly one orientation marker (`N`, `S`, `E`, or `W`). Empty spaces are preserved and validated as outside the playable area.

# Resources

- 42 cub3D subject PDF (included as `en.subject.pdf`).
- Lode's Computer Graphics Tutorial, “Raycasting”: https://lodev.org/cgtutor/raycasting.html
- MiniLibX documentation and examples in `minilibx-linux/`.

AI was used to help outline the parser, ray-casting calculations, and validation cases. The implementation was reviewed against the subject, compiled with strict warnings, and tested with valid and invalid scene files.

# Limitations

This is the mandatory Linux implementation. Bonus features such as a minimap, doors, sprites, and mouse rotation are intentionally not included. The bundled XPMs are deliberately simple sample textures; scenes can reference their own valid MiniLibX-compatible XPM files.

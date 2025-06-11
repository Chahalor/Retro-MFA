import struct

def extract_image(filepath, output_ppm):
    with open(filepath, "rb") as f:
        data = f.read()

    width = struct.unpack("<I", data[0:4])[0]
    height = struct.unpack("<I", data[4:8])[0]
    print(f"Image size: {width}x{height}")

    pixel_data_offset = 0x1A  # 26 bytes
    pixels = data[pixel_data_offset:pixel_data_offset + (width * height * 2)]

    with open(output_ppm, "w") as out:
        out.write(f"P3\n{width} {height}\n255\n")
        for i in range(0, len(pixels), 2):
            pixel = struct.unpack("<H", pixels[i:i+2])[0]
            # Format: 0RRRRRGG GGGBBBBB
            r = (pixel >> 10) & 0x1F
            g = (pixel >> 5) & 0x1F
            b = (pixel) & 0x1F
            # Convert 5-bit to 8-bit color
            r = (r << 3) | (r >> 2)
            g = (g << 3) | (g >> 2)
            b = (b << 3) | (b >> 2)
            out.write(f"{r} {g} {b} ")
            if ((i // 2 + 1) % width == 0):
                out.write("\n")

    print(f"Image written to: {output_ppm}")

# Exemple d'utilisation :
extract_image("../MFA/green.mfa", "output.ppm")

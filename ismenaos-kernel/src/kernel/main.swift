import Foundation

@_silgen_name("kmain") public func kmain() {
	let vram = UnsafeMutablePointer<UInt16>.allocate(capacity: 0xB8000)
	let vramSize = 80 * 25

	var i = 0
	repeat {
		vram[i] = 0x0F00 | 00
		i += 1
	} while i < vramSize

	var x = 0
    vram[x] = 0x0F48; x += 1
	vram[x] = 0x0F65; x += 1
	vram[x] = 0x0F6C; x += 1
	vram[x] = 0x0F6C; x += 1
	vram[x] = 0x0F6F; x += 1
	vram[x] = 0x0F00; x += 1
	vram[x] = 0x0F53; x += 1
	vram[x] = 0x0F77; x += 1
	vram[x] = 0x0F69; x += 1
	vram[x] = 0x0F74; x += 1
	vram[x] = 0x0F21; x += 1

	let _: StaticString = "Hello World!"
}
